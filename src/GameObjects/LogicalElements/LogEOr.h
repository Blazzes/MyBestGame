#pragma once
#include "ILogElement.h"
class LogEOr :
    public ILogElement
{
public:
    LogEOr(Position pos);
    void Update() override;
    void Render() override;
};

