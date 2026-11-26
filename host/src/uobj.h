// Minimal native UObject reflection for this build (UE 4.20.3 with a UStruct that is 0x20 larger than stock).
// Everything here must run on the game thread unless noted.
#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <list>
#include "ue.h"

namespace uo {
using UObject = uint8_t;

// Layout (measured live, see docs/v2-implementation.md)
constexpr size_t Obj_Flags = 0x08, Obj_Index = 0x0c, Obj_Class = 0x10, Obj_Name = 0x18, Obj_Outer = 0x20;
constexpr size_t Field_Next = 0x28;
constexpr size_t Struct_Super = 0x30, Struct_Children = 0x38, Struct_Size = 0x40;
constexpr size_t Func_Flags = 0xa8, Func_NumParms = 0xac, Func_ParmsSize = 0xae, Func_RetOffset = 0xb0, Func_Native = 0xd0;
constexpr size_t Prop_ArrayDim = 0x30, Prop_ElementSize = 0x34, Prop_Flags = 0x38, Prop_Offset = 0x44, Prop_Inner = 0x70;
constexpr size_t Class_CDO = 0x118;   // verified at runtime in Init()

bool Init();
FName MakeName(const wchar_t* s);
std::wstring NameStr(FName n);
inline FName NameOf(UObject* o) { return F<FName>(o, Obj_Name); }
inline UObject* ClassOf(UObject* o) { return F<UObject*>(o, Obj_Class); }
inline UObject* OuterOf(UObject* o) { return F<UObject*>(o, Obj_Outer); }
std::wstring Name(UObject* o);
inline bool NameIs(UObject* o, FName n) { FName a = F<FName>(o, 0x18); return a.Index == n.Index && a.Number == n.Number; }
std::wstring FullPath(UObject* o);     // Outer.Outer.Name (no class prefix)
bool IsA(UObject* o, UObject* cls);
bool IsDefault(UObject* o);            // class default object or archetype
bool IsLive(UObject* o);               // in GUObjectArray, not pending kill
int32_t NumObjects();
UObject* ObjectAt(int32_t i);

UObject* FindClass(const wchar_t* name);                       // native or BP class by short name ("MBFrontEnd", "FE_MainMenuScreen_C")
UObject* FindObjectPath(const wchar_t* path);                  // "/Game/UI/.../X.X_C"
UObject* FindFirst(UObject* cls, bool includeDefaults = false); // first live instance of class
std::vector<UObject*> FindAll(UObject* cls);
std::vector<UObject*> FindAllNow(UObject* cls);                // full scan (~20 ms): objects created this frame included
UObject* FindTransient(UObject* cls);                          // first runtime-created instance (outermost = /Engine/Transient)
std::vector<UObject*> FindAllTransient(UObject* cls);
UObject* Outermost(UObject* o);
void IndexStep(int32_t budget);
void Prewarm(const std::vector<const wchar_t*>& classNames);   // index these classes now (one pass over all objects)                                // scans a slice of the object array (call every frame)
UObject* FindFunction(UObject* objOrClass, const wchar_t* name, bool isClass = false);
UObject* FindProp(UObject* structObj, const wchar_t* name);    // walks supers
int32_t PropOffset(UObject* structObj, const wchar_t* name);   // -1 if missing
void ProcessEvent(UObject* obj, UObject* fn, void* parms);
bool SetBool(UObject* obj, const wchar_t* prop, bool v);       // bitfield-aware bool property write
bool GetBool(UObject* obj, const wchar_t* prop);

// Calls a UFunction by name with a zeroed parameter block; set/get parameters by name.
struct Call {
    UObject* obj = nullptr; UObject* fn = nullptr;
    std::vector<uint8_t> buf;
    Call(UObject* o, const wchar_t* func);
    bool ok() const { return fn != nullptr; }
    template <class T> Call& set(const wchar_t* p, const T& v) { int o = off(p); if (o >= 0) *(T*)(buf.data() + o) = v; return *this; }
    template <class T> T get(const wchar_t* p) { int o = off(p); return o >= 0 ? *(T*)(buf.data() + o) : T{}; }
    Call& str(const wchar_t* p, const wchar_t* s);   // FString parameter (memory owned by Call)
    Call& run();
    int off(const wchar_t* p);
    std::list<std::wstring> keep;
};

// FText from a string (FText::FText(FString&&) / FText::FromString)
struct FText { void* Data; void* Ref; int32_t Flags; int32_t Pad; };
void MakeText(FText* out, const wchar_t* s);
void* Malloc(size_t n);
void SetFString(FString& s, const std::wstring& v);   // (re)allocates with the game's allocator
}  // namespace uo
