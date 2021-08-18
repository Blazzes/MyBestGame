#pragma once
#include "ILogElement.h"
class LogEXor :
	public ILogElement
{
public:
	LogEXor(Position pos);
	void Update() override;
	void Render() override;

};

