#pragma once
#include "ILogElement.h"
class LogEAnd :
    public ILogElement
{
public:
    LogEAnd(Position pos);
    void Update() override;
    void Render() override;
};

