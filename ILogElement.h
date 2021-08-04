#pragma once
#include "IGameObject.h"
#include "BitMapTexture.h"
#include "Connection.h"
class ILogElement :
    public IGameObject
{
public:
    ILogElement(Position pos);
    void addOut(Connection* con);
    void addInX(Connection* con);
    void addInY(Connection* con);
protected:
    std::vector<Connection*> outCon;
    Connection* inX,* inY;
};
