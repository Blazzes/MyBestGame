#pragma once

#include "ILogElement.h"

class LogEInv :
    public ILogElement
{
public:
    LogEInv(Position pos);
    void Update() override;
    void Render() override;
};

