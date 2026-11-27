// Steam profile pictures for the custom game screens. The game's own avatar system asked Xbox Live for gamerpics,
// which no longer answers (and players without Xbox profiles never had one), so lobby slots and loading screens
// showed blank squares. Here each player's Steam avatar is read through the Steam API, written to a small image
// file and loaded with the engine's own importer (KismetRenderingLibrary::ImportFileAsTexture2D).
#include <windows.h>
#include <map>
#include <vector>
#include <cstdio>
#include <algorithm>
#include "uobj.h"
#include "steam.h"
#include "mod.h"

namespace avatars {
namespace {
struct Entry { uo::UObject* tex = nullptr; DWORD nextTry = 0; std::wstring file; };
std::map<uint64_t, Entry> gCache;

std::wstring Dir() {
    wchar_t t[MAX_PATH]; GetTempPathW(MAX_PATH, t);
    std::wstring d = std::wstring(t) + L"be1v1-avatars\\";
    CreateDirectoryW(d.c_str(), nullptr);
    return d;
}
// RGBA PNG (8 bits per channel: the format the engine's importer turns into a texture; zlib "stored" blocks, no
// compression needed for 184x184 pictures).
uint32_t Crc(const uint8_t* p, size_t n, uint32_t c = 0xffffffffu) {
    static uint32_t t[256];
    if (!t[1]) for (uint32_t i = 0; i < 256; i++) { uint32_t v = i; for (int k = 0; k < 8; k++) v = v & 1 ? 0xedb88320u ^ (v >> 1) : v >> 1; t[i] = v; }
    for (size_t i = 0; i < n; i++) c = t[(c ^ p[i]) & 0xff] ^ (c >> 8);
    return c;
}
void Be32(std::vector<uint8_t>& o, uint32_t v) { for (int i = 3; i >= 0; i--) o.push_back((uint8_t)(v >> (i * 8))); }
void Chunk(std::vector<uint8_t>& o, const char* type, const std::vector<uint8_t>& d) {
    Be32(o, (uint32_t)d.size());
    size_t at = o.size();
    o.insert(o.end(), type, type + 4);
    o.insert(o.end(), d.begin(), d.end());
    Be32(o, Crc(&o[at], o.size() - at) ^ 0xffffffffu);
}
bool WritePng(const std::wstring& path, const std::vector<uint8_t>& rgba, int w, int h) {
    std::vector<uint8_t> raw;   // filter byte 0 + row
    raw.reserve((size_t)(w * 4 + 1) * h);
    for (int y = 0; y < h; y++) { raw.push_back(0); raw.insert(raw.end(), &rgba[(size_t)y * w * 4], &rgba[(size_t)(y + 1) * w * 4]); }
    std::vector<uint8_t> z = { 0x78, 0x01 };
    uint32_t a = 1, b = 0;
    for (uint8_t c : raw) { a = (a + c) % 65521; b = (b + a) % 65521; }
    for (size_t at = 0; at < raw.size() || at == 0;) {
        size_t n = std::min<size_t>(65535, raw.size() - at);
        bool last = at + n >= raw.size();
        z.push_back(last ? 1 : 0);
        z.push_back((uint8_t)n); z.push_back((uint8_t)(n >> 8)); z.push_back((uint8_t)~n); z.push_back((uint8_t)(~n >> 8));
        z.insert(z.end(), raw.begin() + at, raw.begin() + at + n);
        at += n;
        if (last) break;
    }
    Be32(z, (b << 16) | a);
    std::vector<uint8_t> png = { 0x89, 'P', 'N', 'G', 0x0d, 0x0a, 0x1a, 0x0a };
    std::vector<uint8_t> ihdr;
    Be32(ihdr, (uint32_t)w); Be32(ihdr, (uint32_t)h);
    ihdr.insert(ihdr.end(), { 8, 6, 0, 0, 0 });   // 8-bit RGBA, no interlace
    Chunk(png, "IHDR", ihdr);
    Chunk(png, "IDAT", z);
    Chunk(png, "IEND", {});
    std::wstring tmp = path + L".tmp";
    FILE* f = _wfopen(tmp.c_str(), L"wb");
    if (!f) return false;
    fwrite(png.data(), 1, png.size(), f);
    fclose(f);
    return MoveFileExW(tmp.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING) != 0;
}
uo::UObject* Import(const std::wstring& file) {
    static uo::UObject* lib;
    if (!lib || !uo::IsLive(lib)) lib = uo::FindFirst(uo::FindClass(L"KismetRenderingLibrary"), true);
    if (!lib) return nullptr;
    uo::Call c(lib, L"ImportFileAsTexture2D");
    if (!c.ok()) return nullptr;
    c.set<uo::UObject*>(L"WorldContextObject", (uo::UObject*)net::World()).str(L"Filename", file.c_str()).run();
    return c.get<uo::UObject*>(L"ReturnValue");
}
}  // namespace

// Local test lobbies (-be1v1devlobby) use made-up member ids: they show this account's own picture.
uint64_t SteamIdFor(uint64_t memberId) {
    if (memberId >= 90000000000ull && memberId < 100000000000ull) return steam::MyId();
    return memberId;
}

uo::UObject* Texture(uint64_t memberId) {
    uint64_t id = SteamIdFor(memberId);
    if (!id || !steam::Ready()) return nullptr;
    Entry& e = gCache[id];
    if (e.tex && uo::IsLive(e.tex)) return e.tex;   // textures nobody shows any more are collected: made again
    e.tex = nullptr;
    DWORD now = GetTickCount();
    if (now < e.nextTry) return nullptr;
    e.nextTry = now + 1000;
    if (e.file.empty() || GetFileAttributesW(e.file.c_str()) == INVALID_FILE_ATTRIBUTES) {
        std::vector<uint8_t> rgba; int w = 0, h = 0;
        if (!steam::AvatarRGBA(id, rgba, w, h)) return nullptr;   // Steam is still fetching it
        std::wstring file = Dir() + std::to_wstring(id) + L".png";
        if (!WritePng(file, rgba, w, h)) return nullptr;
        e.file = file;
    }
    e.tex = Import(e.file);
    if (e.tex) Log("avatars: %llu loaded (%ls)", (unsigned long long)id, uo::Name(e.tex).c_str());
    else { e.nextTry = now + 5000; Log("avatars: couldn't load %ls", e.file.c_str()); }
    return e.tex;
}

// Puts a texture on an Image widget (no change when it already shows it).
void Show(uo::UObject* image, uo::UObject* tex) {
    if (!image || !tex) return;
    static int brushOff = -2;
    if (brushOff == -2) brushOff = uo::PropOffset(uo::FindClass(L"Image"), L"Brush");
    // FSlateBrush: ResourceObject at +0x48 in 4.20 (ImageSize, Margin, TintColor come first)
    if (brushOff >= 0 && F<uo::UObject*>(image, brushOff + 0x48) == tex) return;
    uo::Call(image, L"SetBrushFromTexture").set<uo::UObject*>(L"Texture", tex).set<bool>(L"bMatchSize", false).run();
}
}  // namespace avatars
