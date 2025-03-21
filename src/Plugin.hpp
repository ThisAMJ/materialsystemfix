#pragma once
#include "Utils.hpp"

#define MSF_SIGNATURE "Material System Fix v1.1 by AMJ"

// CServerPlugin
#define CServerPlugin_m_Size 16
#define CServerPlugin_m_Plugins 4

class Plugin {
public:
    CPlugin* ptr;
    int index;

public:
    Plugin();
};
