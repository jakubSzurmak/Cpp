#pragma once
#include "String.h"

class ListSll
{
private:
	String name;
	String value; //For Attributes
	short index;

public:
	ListSll* next;
	ListSll();
	ListSll(String* givenString);//Selectors
	ListSll(String* givenName, String* givenValue);//Attrs
	void removeNode(ListSll** rootNode, short keyIndex);
	void appendSelector(ListSll** rootNode, String data);
	bool appendAttribute(ListSll** rootNode, String givenName, String givenValue);
	char* getSelectorName();
	char* getAttributeValue();

};
