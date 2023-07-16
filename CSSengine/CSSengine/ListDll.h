#pragma once
#include "ListSll.h"
#include <iostream>

#define T 8

struct block {
	ListSll* attributeRoot = nullptr;
	ListSll* selectorRoot = nullptr;
	unsigned short attributeCounter = 0;
	unsigned short selectorCounter = 0;
	int sectionNumber = 1;
	bool written = false;
};

class ListDll
{
private:
	struct block TBlocks[T];
	unsigned short currOperatingNode = 0;
	short nodeIndex = 0;
	short currFreeBlocks = T; //[1,1,0] free block is 2

public:
	ListDll* last = nullptr;
	ListDll* next = nullptr;
	ListDll* prev = nullptr;
	short getFreeBlocks();
	unsigned short getSelectorCount(short i);
	unsigned short getAttributeCount(short i);
	void setSectionNumber(short ind);
	void increaseFreeBlocks(short i);
	short findFreeBlock();
	block* getTBlocksPtr();
	void decreaseFreeBlocks();
	void appendNode(ListDll* rootNode);
	void updateSectionNumbers(ListDll* rootNode, unsigned short ind);
	bool checkLastNodeForAdd();
	void appendSelector(ListDll* rootNode, String data);
	void appendAttribute(ListDll* rootNode, String name, String value);
	void removeNode(ListDll* rootNode, short index);
	void removeAttributeNode(ListSll* attributeRoot);
	void removeSelectorNode(ListSll* selectorRoot);

};

