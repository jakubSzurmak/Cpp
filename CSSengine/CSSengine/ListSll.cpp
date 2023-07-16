#include "ListSll.h"

ListSll::ListSll() {
	name = NULL;
	value = NULL;
	index = 0;
	next = nullptr;
}

ListSll::ListSll(String* givenName, String* givenValue) {
	name = *givenName;
	value = *givenValue;
	index = 0;
	next = nullptr;
}


ListSll::ListSll(String* givenString) {
	name = *givenString;
	value = NULL;
	index = 0;
	next = nullptr;
}


void ListSll::removeNode(ListSll** rootNode, short keyIndex) {
	ListSll* root = *rootNode;

	if (keyIndex == 0) {
		if (root->next == nullptr) {
			*rootNode = nullptr;
			return;
		}
		else {
			*rootNode = root->next;
			return;
		}
	}

}

void ListSll::appendSelector(ListSll** rootNode, String data) {
	ListSll* newNode = new ListSll();
	ListSll* lastNode = *rootNode;
	//data = NULL;

	newNode->name = data;
	newNode->value = NULL;


	if (lastNode == nullptr) {
		*rootNode = newNode;
		//lastNode = newNode;//this = newNode
		return;
	}
	else {
		while (lastNode->next != nullptr) {
			lastNode = lastNode->next;
		}
		lastNode->next = newNode;
		newNode->index = lastNode->index + 1;
		return;
	}
}

bool ListSll::appendAttribute(ListSll** rootNode, String givenName, String givenValue) {

	if (*rootNode == nullptr) {
		*rootNode = new ListSll();
		(*rootNode)->name = givenName;
		(*rootNode)->value = givenValue;
		return true;
	}
	else {
		ListSll* lastNode = *rootNode;
		ListSll* temp = nullptr;
		while (lastNode) {
			if (strcmp(lastNode->getSelectorName(), givenName.getStrArr()) == 0) {
				lastNode->name = givenName;
				lastNode->value = givenValue;
				return false;
			}
			else {
				temp = lastNode;
				lastNode = lastNode->next;
			}
		}

		ListSll* newNode = new ListSll();
		newNode->name = givenName;
		newNode->value = givenValue;
		temp->next = newNode;

		return true;

	}
}

char* ListSll::getSelectorName() {
	if (name.getStrArr() != NULL) {
		return name.getStrArr();
	}
	else {
		return nullptr;
	}
	
}

char* ListSll::getAttributeValue() {
	if (value.getStrArr() != NULL) {
		return value.getStrArr();
	}
	else {
		return nullptr;
	}
	
}