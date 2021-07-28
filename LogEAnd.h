#pragma once
#include "ILogElement.h"
class LogEAnd :
    public ILogElement
{
public:
    LogEAnd(int x, int y);
    void Update() override;
    void Render() override;
    int getPosX() override;
    int getPosY() override;
    void updatePosition(int x, int y) override;
    void addOut(Connection* elem) override;
    void delOut(Connection* elem) override;
};

