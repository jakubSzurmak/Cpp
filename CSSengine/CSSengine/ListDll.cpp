#include "ListDll.h"

short ListDll::getFreeBlocks() {
	return this->currFreeBlocks;
}

unsigned short ListDll::getSelectorCount(short i) {
	return TBlocks[i].selectorCounter;
}

unsigned short ListDll::getAttributeCount(short i) {
	return TBlocks[i].attributeCounter;
}

block* ListDll::getTBlocksPtr() {
	return TBlocks;
}

void ListDll::decreaseFreeBlocks() {
	this->currFreeBlocks -= 1;
}


void ListDll::appendNode(ListDll* rootNode) {
	ListDll* newNode = new ListDll();
	ListDll* lastNode = rootNode;

	if (rootNode == nullptr) {
		rootNode = newNode;
		rootNode->last = rootNode;
		return;
	}
	else {
		while (lastNode->next != nullptr) {
			lastNode = lastNode->next;
		}
		lastNode->next = newNode;
		newNode->prev = lastNode;
		if (newNode->prev != nullptr) {
			newNode->nodeIndex = newNode->prev->nodeIndex + 1;
			return;
		}
		else {
			newNode->nodeIndex = 0;
			return;
		}

	}
}

short ListDll::findFreeBlock() {
	short lastFree = T - 1;
	for (short i = T - 2; i >= 0; i--) {
		if (this->getTBlocksPtr()[i].written) {
			break;
		}
		else {
			lastFree = i;
		}
	}
	return lastFree;
}

void ListDll::updateSectionNumbers(ListDll* rootNode, unsigned short ind) {
	short num = ind + 2;

	while (rootNode != nullptr) {
		if (ind == 8) {
			rootNode = rootNode->next;
			ind = 0;
			continue;
		}
		if (rootNode->getTBlocksPtr()[ind].selectorCounter == 0) {
			rootNode->getTBlocksPtr()[ind].sectionNumber = 0;
			ind += 1;
		}
		else {
			rootNode->getTBlocksPtr()[ind].sectionNumber -= 1;
			ind += 1;
		}
	}

}

bool ListDll::checkLastNodeForAdd() {
	return (this->next == nullptr && !this->getTBlocksPtr()[T - 1].written);
}

void ListDll::increaseFreeBlocks(short i) {
	short free = 0;
	for (short i = T - 1; i >= 0; i--) {
		if (this->getTBlocksPtr()[i].written) {
			break;
		}
		else {
			free = T - i;
		}
	}

	this->currFreeBlocks = free;
}

void ListDll::setSectionNumber(short ind) {
	short offset = 1;
	short safe = ind;
	if (this->prev == nullptr) {
		if (ind == 0) {
			this->getTBlocksPtr()[ind].sectionNumber = 1;
		}
		else {
			while(this->getTBlocksPtr()[ind - offset].selectorRoot == nullptr){
				if (offset == ind) {
					this->getTBlocksPtr()[ind].sectionNumber = 1;
					return;
				}
				offset += 1;			
			}
			this->getTBlocksPtr()[ind].sectionNumber = this->getTBlocksPtr()[ind - offset].sectionNumber + 1;
		}
	}
	else {
		ListDll* tempRoot = this;
		if (ind < offset) {
			offset = 1;
			ind = T;
			if (tempRoot->prev != nullptr) {
				tempRoot = tempRoot->prev;
			}
			else {
				this->getTBlocksPtr()[safe].sectionNumber = 1;
				return;
			}
		}
		while (tempRoot->getTBlocksPtr()[ind - offset].selectorRoot == nullptr) {
			if (offset == ind) {
				offset = 1;
				ind = T;
				if (tempRoot->prev) {
					tempRoot = tempRoot->prev;
					continue;
				}
				else {
					this->getTBlocksPtr()[safe].sectionNumber = 1;
					return;
				}
			}
			offset += 1;
		}
		this->getTBlocksPtr()[safe].sectionNumber = tempRoot->getTBlocksPtr()[ind - offset].sectionNumber + 1;
	}
}

void ListDll::appendSelector(ListDll* rootNode, String data) {
	short ind;
	if (rootNode == nullptr) {
		return;
	}
	else {
		while (1) {
			if (this->last->checkLastNodeForAdd()) {
				ind = this->last->findFreeBlock();
				this->last->getTBlocksPtr()[ind].selectorRoot->appendSelector(&this->last->getTBlocksPtr()[ind].selectorRoot, data);
				this->last->getTBlocksPtr()[ind].selectorCounter += 1;
				this->last->setSectionNumber(ind);
				return;
				/*
				if (ind == 0 && !this->last->prev) {
					this->last->getTBlocksPtr()[ind].sectionNumber = 1;
				}
				else {
					this->last->getTBlocksPtr()[ind].sectionNumber = this->last->getTBlocksPtr()[ind - 1].sectionNumber + 1;

				}
				*/
				
			}
			else {
				ListDll* newNode = new ListDll();
				newNode->prev = this->last;
				this->last->next = newNode;
				this->last = newNode;
				ind = this->last->findFreeBlock();
				this->last->getTBlocksPtr()[ind].selectorRoot->appendSelector(&this->last->getTBlocksPtr()[ind].selectorRoot, data);
				this->last->getTBlocksPtr()[ind].selectorCounter += 1;
				this->last->setSectionNumber(ind);
				return;

				/*
				if (this->last->currFreeBlocks == T) {
					this->last->getTBlocksPtr()[ind].sectionNumber = this->last->prev->getTBlocksPtr()[T - 1].sectionNumber + 1;
				}
				else {
					this->last->getTBlocksPtr()[ind].sectionNumber = this->last->getTBlocksPtr()[ind - 1].sectionNumber + 1;
				}
				*/
			}
		}
		return;
	}
}



void ListDll::appendAttribute(ListDll* rootNode, String name, String value) {
	ListDll* temp = rootNode;
	short ind;
	if (temp == nullptr) {
		return;
	}
	else {
		while (1) {
			if (this->last->checkLastNodeForAdd()) {
				ind = this->last->findFreeBlock();
				if (this->last->getTBlocksPtr()[ind].attributeRoot->appendAttribute(&this->last->getTBlocksPtr()[ind].attributeRoot, name, value)) {
					this->last->getTBlocksPtr()[ind].attributeCounter += 1;
				}
				return;
			}
			else {
				ListDll* newNode = new ListDll();
				newNode->prev = this->last;
				this->last->next = newNode;
				this->last = newNode;
				ind = newNode->findFreeBlock();
				if (this->last->getTBlocksPtr()[ind].attributeRoot->appendAttribute(&this->last->getTBlocksPtr()[ind].attributeRoot, name, value)) {
					this->last->getTBlocksPtr()[ind].attributeCounter += 1;
				}
				return;
			}
		}
		return;
	}
}

void ListDll::removeNode(ListDll* rootNode, short index) {
	ListDll* root = rootNode;

	if (index == 0) {
		if (root->next == nullptr) {
			rootNode = nullptr;
			return;
		}
		else {
			root->next->prev = nullptr;
			rootNode = root->next;
			return;
		}
	}
	else if (index > 0) {
		while (root->next->nodeIndex != index)
		{
			root = root->next;
		}
		root->prev->next = root->next;
		root->next->prev = root->prev;
		root = nullptr;
		return;
	}
	else {
		return;
	}

}
