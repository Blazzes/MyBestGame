#pragma once
#include "ILogElement.h"
class LogENor :
    public ILogElement
{
public:
    LogENor(Position pos);
    void Update() override;
    void Render() override;
};

