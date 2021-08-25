#pragma once
#include "ILogElement.h"
class LogEBuf :
    public ILogElement
{
public:
    LogEBuf(Position pos) : ILogElement(pos) {}
    void Update() override;
    void Render() override;
};

