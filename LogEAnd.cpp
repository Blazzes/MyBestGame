#include "LogEAnd.h"

LogEAnd::LogEAnd(Position pos) : ILogElement(pos)
{
	SGame->AddUpdateFuction(this);
}

void LogEAnd::Update()
{
	bool out = inX->signal && inY->signal;
	for (auto i : outCon) i->signal = out;
}

void LogEAnd::Render()
{
}
