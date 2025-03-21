#pragma once

#ifdef _WIN32
#define MODULE_EXTENSION ".dll"
#define DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define MODULE_EXTENSION ".so"
#define DLL_EXPORT extern "C" __attribute__((visibility("default")))
#endif
