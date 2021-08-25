#pragma once
#include "ILogElement.h"
class LogENand :
    public ILogElement
{
public:
    LogENand(Position pos);
    void Update() override;
    void Render() override;
};

