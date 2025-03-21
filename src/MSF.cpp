#include <algorithm>
#include <chrono>
#include <cstring>
#include <stdarg.h>

#include "MSF.hpp"

#include "Modules/Console.hpp"
#include "Modules/MaterialSystem.hpp"
#include "Modules/Module.hpp"

#include "Utils.hpp"

MSF msf;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(MSF, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, msf);

MSF::MSF()
    : plugin(new Plugin())
{

}

// Used callbacks
bool MSF::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory) {
    console = new Console();
    if (!console->Init())
        return false;

    materialSystem = new MaterialSystem();
    if (!materialSystem->Init()) {
        console->Warning("MSF: Failed to patch materialsystem!\n");
        return false;
    }

    console->Print("Material System Fix enabled.\n");

    return true;
}
void MSF::Unload() {
    this->Cleanup();
}
const char* MSF::GetPluginDescription() {
    return MSF_SIGNATURE;
}



void MSF::Cleanup() {
    SAFE_UNLOAD(this->plugin);
    SAFE_UNLOAD(materialSystem);
    SAFE_UNLOAD(console);
}

// Might fix potential deadlock
#ifdef _WIN32
BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_DETACH) {
        msf.Cleanup();
    }
    return TRUE;
}
#endif

#pragma region Unused callbacks
void MSF::LevelInit(char const* pMapName) {}
void MSF::Pause()  {}
void MSF::UnPause()  {}
void MSF::ServerActivate(void* pEdictList, int edictCount, int clientMax) {}
void MSF::GameFrame(bool simulating) {}
void MSF::LevelShutdown() {}
void MSF::ClientFullyConnect(void* pEdict) {}
void MSF::ClientActive(void* pEntity) {}
void MSF::ClientDisconnect(void* pEntity) {}
void MSF::ClientPutInServer(void* pEntity, char const* playername) {}
void MSF::SetCommandClient(int index) {}
void MSF::ClientSettingsChanged(void* pEdict) {}
int MSF::ClientConnect(bool* bAllowConnect, void* pEntity, const char* pszName, const char* pszAddress, char* reject, int maxrejectlen) {
    return 0;
}
int MSF::ClientCommand(void* pEntity, const void*& args) {
    return 0;
}
int MSF::NetworkIDValidated(const char* pszUserName, const char* pszNetworkID) {
    return 0;
}
void MSF::OnQueryCvarValueFinished(int iCookie, void* pPlayerEntity, int eStatus, const char* pCvarName, const char* pCvarValue) {}
void MSF::OnEdictAllocated(void* edict) {}
void MSF::OnEdictFreed(const void* edict) {}
#pragma endregion
