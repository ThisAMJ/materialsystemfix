#include "Console.hpp"

#include "Utils.hpp"

Console::Console() : Module() {}
bool Console::Init() {
    auto tier0 = Memory::GetModuleHandleByName(this->Name());
    if (tier0) {
        this->Msg = Memory::GetSymbolAddress<_Msg>(tier0, MSG_SYMBOL);
        this->ColorMsg = Memory::GetSymbolAddress<_ColorMsg>(tier0, CONCOLORMSG_SYMBOL);
        this->Warning = Memory::GetSymbolAddress<_Warning>(tier0, WARNING_SYMBOL);
        this->DevMsg = Memory::GetSymbolAddress<_DevMsg>(tier0, DEVMSG_SYMBOL);
        this->DevWarning = Memory::GetSymbolAddress<_DevWarning>(tier0, DEVWARNINGMSG_SYMBOL);
        this->CommandLine = Memory::GetSymbolAddress<_CommandLine>(tier0, COMMANDLINE_SYMBOL);

        Memory::CloseModuleHandle(tier0);
    }

    return this->hasLoaded = tier0 && this->Msg && this->ColorMsg &&
                             this->Warning && this->DevMsg &&
                             this->DevWarning && this->CommandLine;
}
void Console::Shutdown() {}

Console* console;
