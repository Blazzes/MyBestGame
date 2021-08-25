#pragma once
#include "ILogElement.h"
class LogEXnor :
    public ILogElement
{
public:
    LogEXnor(Position pos);
    void Update() override;
    void Render() override;
};

