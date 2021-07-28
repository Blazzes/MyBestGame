#include "Connection.h"
#include "ILogElement.h"

Connection::Connection(ILogElement* inElem, ILogElement* outElem) : pInElem(inElem), pOutElem(outElem)
{}

Connection::~Connection()
{
	//pInElem->delOut(this);
}
