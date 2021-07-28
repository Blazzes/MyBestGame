#pragma once
#include "IGameObject.h"
#include "BitMapTexture.h"
#include "Connection.h"
class ILogElement :
    public IGameObject
{
public:
    //virtual void setConnect(Uint32 connect) = 0;
    virtual void addOut(Connection* elem) = 0;
    virtual void updatePosition(int x, int y) = 0;
    virtual void delOut(Connection* elem) = 0;

protected:
    BitMapTexture* tex;
    Uint32 isConnected = BITMAP::NOTCON;
    std::vector<Connection*> outCon;
    Connection* xCon, yCon;
};
