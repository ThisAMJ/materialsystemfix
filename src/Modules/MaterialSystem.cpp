#include "MaterialSystem.hpp"

#include "Console.hpp"
#include "Interface.hpp"
#include "MSF.hpp"
#include "Utils.hpp"

#define OLD_ALLOC 0x226000 // 2.15 MB
#define NEW_ALLOC 0x672000 // 6.45 MB

bool MaterialSystem::Init() {
#ifdef _WIN32
    auto sigSize = "BE 00 60 22 00";
    auto sigTerm = "FF 0D ? ? ? ? 75 ? B9";
    auto sigInit = "83 3D ? ? ? ? 00 0F 85 ? ? ? ? 56";
    auto offSize = 1;
#else
    auto sigSize = "81 C3 00 60 22 00";
    auto sigTerm = "83 2D ? ? ? ? 01 74 ? C3";
    auto sigInit = "A1 ? ? ? ? 85 C0 74 ? 83 C0 01";
    auto offSize = 2;
#endif
    // TODO: Use OLD_ALLOC to determine sigSize (00 60 22 00 = 0x226000)
    defaultContextSize = (uint32_t *)Memory::Scan(this->Name(), sigSize, offSize);
    RenderContextTerm = (_RenderContextTerm)Memory::Scan(this->Name(), sigTerm);
    RenderContextInit = (_RenderContextInit)Memory::Scan(this->Name(), sigInit);
    if (defaultContextSize && RenderContextTerm && RenderContextInit) {
        Memory::UnProtect((void *)defaultContextSize, 4);
        origContextSize = *defaultContextSize;
        *defaultContextSize = NEW_ALLOC;

        // OHGODPLEASEHELP: This is very jank. I'm sorry.
        RenderContextTerm();
        RenderContextInit();
        return this->hasLoaded = true;
    } else {
        console->Print("MSF: Failed to find material system signatures! %p %p %p\n", defaultContextSize, RenderContextTerm, RenderContextInit);
        return this->hasLoaded = false;
    }
}

void MaterialSystem::Shutdown() {
    if (defaultContextSize) {
        *defaultContextSize = origContextSize;
        if (RenderContextTerm && RenderContextInit) {
            RenderContextTerm();
            RenderContextInit();
        }
    }
}

MaterialSystem *materialSystem;
