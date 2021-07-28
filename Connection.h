#pragma once

class ILogElement;

class Connection
{
public:
	Connection(ILogElement* inElem, ILogElement* outElem);
	~Connection();
	bool signal = false;
private:
	ILogElement* pInElem;
	ILogElement* pOutElem;
};

