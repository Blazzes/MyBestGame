#pragma once
#include "ILogElement.h"
class Switch :
    public ILogElement
{
public:
    Switch(Position pos);
    void Update() override;
    void Render() override;
    void Toggle();
private:
    bool state = false;
};

