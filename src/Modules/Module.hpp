#pragma once
#include <vector>

class Module {
public:
    bool hasLoaded;

public:
    virtual ~Module() = default;
    virtual bool Init() = 0;
    virtual void Shutdown() = 0;
    virtual const char* Name() = 0;
};
