// Native UObject reflection: object array walk, names, functions, properties, ProcessEvent.
#include <windows.h>
#include <unordered_map>
#include <cstring>
#include <algorithm>
#include "uobj.h"

namespace uo {
namespace {
constexpr uintptr_t A_GUObjectArray = 0x14507ff60;
constexpr uintptr_t A_FNameToString = 0x14150ac20;   // void FName::ToString(FString&) const
constexpr uintptr_t A_FNameCtor = 0x1414f3970;       // FName::FName(const WIDECHAR*, EFindName)
constexpr uintptr_t A_FTextFromString = 0x141454760; // FText::FText(FString&&)
constexpr uintptr_t A_Realloc = 0x141440950;         // FMemory::Realloc(void*, SIZE_T, uint32)
constexpr int Slot_ProcessEvent = 0x41;
constexpr int32_t RF_ClassDefaultObject = 0x10, RF_ArchetypeObject = 0x20;
constexpr int32_t EIF_PendingKill = 1 << 29, EIF_Unreachable = 1 << 28;

struct FUObjectItem { UObject* Object; int32_t Flags; int32_t ClusterRootIndex; int32_t SerialNumber; int32_t Pad; };
uint8_t* gArr;
std::unordered_map<std::wstring, UObject*> gClassCache;
FName gClassName, gBPClassName, gWBPClassName, gFunctionName;

FUObjectItem* Item(int32_t i) {
    uint8_t* objs = gArr + 0x10;
    FUObjectItem** chunks = *(FUObjectItem***)objs;
    if (!chunks || i < 0 || i >= *(int32_t*)(objs + 0x14)) return nullptr;
    FUObjectItem* ch = chunks[i / 65536];
    return ch ? &ch[i % 65536] : nullptr;
}
bool SameName(FName a, FName b) { return a.Index == b.Index && a.Number == b.Number; }
}  // namespace

void* Malloc(size_t n) { return Fn<void*(__fastcall*)(void*, size_t, uint32_t)>(A_Realloc)(nullptr, n, 0); }

void SetFString(FString& s, const std::wstring& v) {
    auto realloc_ = Fn<void*(__fastcall*)(void*, size_t, uint32_t)>(A_Realloc);
    int32_t n = (int32_t)v.size() + 1;
    if (v.empty()) { if (s.Data && s.Max) s.Data[0] = 0; s.Num = 0; return; }
    if (s.Max < n) { s.Data = (wchar_t*)realloc_(s.Data, n * sizeof(wchar_t), 0); s.Max = n; }
    memcpy(s.Data, v.c_str(), n * sizeof(wchar_t));
    s.Num = n;
}

bool Init() {
    gArr = (uint8_t*)VA(A_GUObjectArray);
    int32_t num = *(int32_t*)(gArr + 0x10 + 0x14);
    gClassName = MakeName(L"Class");
    gBPClassName = MakeName(L"BlueprintGeneratedClass");
    gWBPClassName = MakeName(L"WidgetBlueprintGeneratedClass");
    gFunctionName = MakeName(L"Function");
    Log("uobj: %d objects", num);
    return num > 0;
}

FName MakeName(const wchar_t* s) {
    FName n{};
    Fn<void(__fastcall*)(FName*, const wchar_t*, int)>(A_FNameCtor)(&n, s, 1);
    return n;
}
std::wstring NameStr(FName n) {
    FString out;
    Fn<void(__fastcall*)(FName*, FString*)>(A_FNameToString)(&n, &out);
    std::wstring r = out.c_str();
    if (out.Data) Fn<void*(__fastcall*)(void*, size_t, uint32_t)>(A_Realloc)(out.Data, 0, 0);
    return r;
}
std::wstring Name(UObject* o) { return o ? NameStr(NameOf(o)) : L"None"; }
std::wstring FullPath(UObject* o) {
    if (!o) return L"None";
    std::wstring s = Name(o);
    UObject* outer = OuterOf(o);
    if (!outer) return s;
    UObject* oo = OuterOf(outer);
    // Package.Object or Package.Object:Sub (sub-objects use ':' after the top-level object)
    if (oo && !OuterOf(oo)) return FullPath(outer) + L":" + s;
    return FullPath(outer) + L"." + s;
}
int32_t NumObjects() { return *(int32_t*)(gArr + 0x10 + 0x14); }
UObject* ObjectAt(int32_t i) { FUObjectItem* it = Item(i); return it ? it->Object : nullptr; }

bool IsA(UObject* o, UObject* cls) {
    if (!o || !cls) return false;
    for (UObject* c = ClassOf(o); c; c = F<UObject*>(c, Struct_Super))
        if (c == cls) return true;
    return false;
}
bool IsDefault(UObject* o) { return (F<int32_t>(o, Obj_Flags) & (RF_ClassDefaultObject | RF_ArchetypeObject)) != 0; }
bool IsLive(UObject* o) {
    if (!o) return false;
    // The object may already be freed: read its index without faulting.
    int32_t idx;
    if (!ReadProcessMemory(GetCurrentProcess(), o + Obj_Index, &idx, sizeof idx, nullptr)) return false;
    FUObjectItem* it = Item(idx);
    return it && it->Object == o && !(it->Flags & (EIF_PendingKill | EIF_Unreachable));
}

static bool IsClassObject(UObject* o) {
    UObject* c = ClassOf(o);
    if (!c) return false;
    FName n = NameOf(c);
    return SameName(n, gClassName) || SameName(n, gBPClassName) || SameName(n, gWBPClassName);
}

UObject* FindClass(const wchar_t* name) {
    FName want = MakeName(name);
    auto it = gClassCache.find(name);
    // Blueprint classes get unloaded and reloaded between maps: re-validate the cached object completely.
    if (it != gClassCache.end() && IsLive(it->second) && SameName(NameOf(it->second), want) && IsClassObject(it->second)) return it->second;
    gClassCache.erase(name);
    int32_t n = NumObjects();
    for (int32_t i = 0; i < n; i++) {
        UObject* o = ObjectAt(i);
        if (o && SameName(NameOf(o), want) && IsClassObject(o)) { gClassCache[name] = o; return o; }
    }
    return nullptr;
}

UObject* FindObjectPath(const wchar_t* path) {
    std::wstring p = path;
    size_t dot = p.find_last_of(L".:");
    FName want = MakeName(p.substr(dot == std::wstring::npos ? 0 : dot + 1).c_str());
    int32_t n = NumObjects();
    for (int32_t i = 0; i < n; i++) {
        UObject* o = ObjectAt(i);
        if (o && SameName(NameOf(o), want) && FullPath(o) == p) return o;
    }
    return nullptr;
}

// ---- class index ------------------------------------------------------------------------------------------
// A full walk of the object array touches ~460k objects and costs 20-60 ms, far too slow to do several times a
// second. Instead, classes we search for are "tracked": IndexStep() scans a slice of the array every frame and keeps,
// per tracked class, the objects found in the last complete sweep. Searches read that list (validated on access).
namespace {
struct Entry { UObject* obj; UObject* cls; int32_t idx; };
struct Tracked { UObject* cls; std::vector<Entry> cur, next; bool swept; };
std::vector<Tracked> gTracked;
std::unordered_map<UObject*, uint32_t> gClassMask;    // object class -> bitmask of tracked classes it derives from
int32_t gSweepPos;

uint32_t MaskOf(UObject* objClass) {
    auto it = gClassMask.find(objClass);
    if (it != gClassMask.end()) return it->second;
    uint32_t m = 0;
    for (size_t i = 0; i < gTracked.size(); i++)
        for (UObject* c = objClass; c; c = F<UObject*>(c, Struct_Super))
            if (c == gTracked[i].cls) { m |= 1u << i; break; }
    gClassMask[objClass] = m;
    return m;
}
std::vector<UObject*> FullScan(UObject* cls) {
    std::vector<UObject*> r;
    int32_t n = NumObjects();
    for (int32_t i = 0; i < n; i++) {
        FUObjectItem* it = Item(i);
        UObject* o = it ? it->Object : nullptr;
        if (!o || (it->Flags & (EIF_PendingKill | EIF_Unreachable)) || IsDefault(o)) continue;
        if (IsA(o, cls)) r.push_back(o);
    }
    return r;
}
Tracked* Track(UObject* cls) {
    for (auto& t : gTracked) if (t.cls == cls) return &t;
    if (gTracked.size() >= 32) return nullptr;
    gTracked.push_back(Tracked{ cls, {}, {}, false });
    gClassMask.clear();
    Tracked& t = gTracked.back();
    // First use: one full scan so the caller gets an answer now.
    int32_t n = NumObjects();
    for (int32_t i = 0; i < n; i++) {
        FUObjectItem* it = Item(i);
        UObject* o = it ? it->Object : nullptr;
        if (!o || (it->Flags & (EIF_PendingKill | EIF_Unreachable)) || IsDefault(o)) continue;
        if (IsA(o, cls)) t.cur.push_back({ o, ClassOf(o), i });
    }
    t.swept = true;
    return &t;
}
}  // namespace

void IndexStep(int32_t budget) {
    if (gTracked.empty()) return;
    int32_t n = NumObjects();
    int32_t end = std::min(n, gSweepPos + budget);
    for (int32_t i = gSweepPos; i < end; i++) {
        FUObjectItem* it = Item(i);
        UObject* o = it ? it->Object : nullptr;
        if (!o || (it->Flags & (EIF_PendingKill | EIF_Unreachable))) continue;
        UObject* c = ClassOf(o);
        uint32_t m = c ? MaskOf(c) : 0;
        if (!m || IsDefault(o)) continue;
        for (size_t k = 0; k < gTracked.size(); k++) if (m & (1u << k)) gTracked[k].next.push_back({ o, c, i });
    }
    gSweepPos = end;
    if (gSweepPos >= n) {
        gSweepPos = 0;
        for (auto& t : gTracked) { t.cur.swap(t.next); t.next.clear(); }
        if (gClassMask.size() > 200000) gClassMask.clear();
    }
}

std::vector<UObject*> FindAll(UObject* cls) {
    std::vector<UObject*> r;
    if (!cls) return r;
    Tracked* t = Track(cls);
    if (!t) return FullScan(cls);
    // Validate through the object array only (the object itself may be freed memory by now).
    auto valid = [](const Entry& e) {
        FUObjectItem* it = Item(e.idx);
        return it && it->Object == e.obj && !(it->Flags & (EIF_PendingKill | EIF_Unreachable)) && ClassOf(e.obj) == e.cls;
    };
    for (auto& e : t->cur) if (valid(e)) r.push_back(e.obj);
    // Objects found so far in the running sweep (newly created ones) as well.
    for (auto& e : t->next) if (valid(e) && std::find(r.begin(), r.end(), e.obj) == r.end()) r.push_back(e.obj);
    return r;
}
UObject* FindFirst(UObject* cls, bool includeDefaults) {
    if (!cls) return nullptr;
    if (!includeDefaults) { auto v = FindAll(cls); return v.empty() ? nullptr : v[0]; }
    // Class default objects never go away: cache them.
    static std::unordered_map<UObject*, UObject*> cdo;
    auto it = cdo.find(cls);
    if (it != cdo.end() && IsLive(it->second)) return it->second;
    int32_t n = NumObjects();
    for (int32_t i = 0; i < n; i++) {
        FUObjectItem* item = Item(i);
        UObject* o = item ? item->Object : nullptr;
        if (o && IsA(o, cls)) { if (IsDefault(o)) cdo[cls] = o; return o; }
    }
    return nullptr;
}

UObject* Outermost(UObject* o) { while (o && OuterOf(o)) o = OuterOf(o); return o; }
static bool IsTransientPkg(UObject* pkg) {
    static UObject* cached;
    if (pkg && pkg == cached) return true;
    if (pkg && Name(pkg) == L"/Engine/Transient") { cached = pkg; return true; }
    return false;
}
UObject* FindTransient(UObject* cls) {
    for (UObject* o : FindAll(cls)) if (IsTransientPkg(Outermost(o))) return o;
    return nullptr;
}
std::vector<UObject*> FindAllTransient(UObject* cls) {
    std::vector<UObject*> r;
    for (UObject* o : FindAll(cls)) if (IsTransientPkg(Outermost(o))) r.push_back(o);
    return r;
}

static UObject* FindChild(UObject* st, FName want, bool walkSupers) {
    for (UObject* s = st; s; s = walkSupers ? F<UObject*>(s, Struct_Super) : nullptr)
        for (UObject* f = F<UObject*>(s, Struct_Children); f; f = F<UObject*>(f, Field_Next))
            if (SameName(NameOf(f), want)) return f;
    return nullptr;
}
UObject* FindFunction(UObject* objOrClass, const wchar_t* name, bool isClass) {
    if (!objOrClass) return nullptr;
    return FindChild(isClass ? objOrClass : ClassOf(objOrClass), MakeName(name), true);
}
UObject* FindProp(UObject* st, const wchar_t* name) { return st ? FindChild(st, MakeName(name), true) : nullptr; }
int32_t PropOffset(UObject* st, const wchar_t* name) {
    UObject* p = FindProp(st, name);
    return p ? F<int32_t>(p, Prop_Offset) : -1;
}

// UBoolProperty: FieldSize 0x70, ByteOffset 0x71, ByteMask 0x72, FieldMask 0x73 (after the 0x70-byte UProperty).
bool SetBool(UObject* obj, const wchar_t* prop, bool v) {
    UObject* p = obj ? FindProp(ClassOf(obj), prop) : nullptr;
    if (!p) return false;
    uint8_t* b = obj + F<int32_t>(p, Prop_Offset) + F<uint8_t>(p, 0x71);
    uint8_t mask = F<uint8_t>(p, 0x72);
    *b = v ? (*b | mask) : (*b & ~mask);
    return true;
}
bool GetBool(UObject* obj, const wchar_t* prop) {
    UObject* p = obj ? FindProp(ClassOf(obj), prop) : nullptr;
    if (!p) return false;
    return (obj[F<int32_t>(p, Prop_Offset) + F<uint8_t>(p, 0x71)] & F<uint8_t>(p, 0x72)) != 0;
}

void ProcessEvent(UObject* obj, UObject* fn, void* parms) {
    void** vt = *(void***)obj;
    ((void(__fastcall*)(UObject*, UObject*, void*))vt[Slot_ProcessEvent])(obj, fn, parms);
}

Call::Call(UObject* o, const wchar_t* func) : obj(o) {
    fn = o ? FindFunction(o, func) : nullptr;
    if (!fn) { Log("uobj: function %ls not found on %ls", func, o ? Name(o).c_str() : L"null"); return; }
    buf.assign(F<uint16_t>(fn, Func_ParmsSize) + 16, 0);
}
int Call::off(const wchar_t* p) {
    if (!fn) return -1;
    UObject* prop = FindChild(fn, MakeName(p), false);
    return prop ? F<int32_t>(prop, Prop_Offset) : -1;
}
Call& Call::str(const wchar_t* p, const wchar_t* s) {
    keep.emplace_back(s);
    FString f; f.Data = (wchar_t*)keep.back().c_str(); f.Num = f.Max = (int32_t)keep.back().size() + 1;
    return set(p, f);
}
Call& Call::run() { if (fn && obj) ProcessEvent(obj, fn, buf.data()); return *this; }

void MakeText(FText* out, const wchar_t* s) {
    FString src{};
    SetFString(src, s);
    memset(out, 0, sizeof *out);
    Fn<void(__fastcall*)(FText*, FString*)>(A_FTextFromString)(out, &src);
    if (src.Data) Fn<void*(__fastcall*)(void*, size_t, uint32_t)>(A_Realloc)(src.Data, 0, 0);
}
}  // namespace uo
