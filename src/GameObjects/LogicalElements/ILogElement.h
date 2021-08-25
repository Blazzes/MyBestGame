#pragma once
#include "../IGameObject.h"
#include "../../BitMapTexture.h"
#include "../Connection.h"

class ILogElement :
    public IGameObject
{
public:
    ILogElement(Position pos);
    ~ILogElement();
    void addOut(Connection* con);
    void addInX(Connection* con);
    void addInY(Connection* con);
    void delOut(Connection* con);
    void delInX();
    void delInY();
    void delConnection(int connectionType);
protected:
    std::vector<Connection*> outCon;
    Connection* inX = nullptr, * inY = nullptr;
    Uint32 conTex = BITMAP::NOTCON;
};