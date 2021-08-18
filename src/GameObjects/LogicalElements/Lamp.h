#pragma once
#include "ILogElement.h"
class Lamp :
    public ILogElement
{
public:
    Lamp(Position pos);
    void Update() override;
    void Render() override;
private:
};

