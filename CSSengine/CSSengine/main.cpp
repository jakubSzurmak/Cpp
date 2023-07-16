#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include "ListDll.h"
#include "ListSll.h"
#include <stdio.h>
#include <iostream>


#define STANDARD_CHUNK_SIZE 8
#define commandFlag "????"
#define cssCountSectionsFlag "?"
#define cssFlag "****"
#define cssShortFlag "*"

#define error -1
#define Q 0
#define iSQ 1 //Q - Question Mark
#define iAQ 2
#define iSj 3
#define iAn 4
#define nAQ 5
#define zSQ 6
#define zEn 7
#define iDa 8 //a - asterisk
#define iDn 9 

struct streamInfo {
    bool readingCss = true;
    bool readingCommands = false;
    bool endProgram = false;
    bool endBlockFlag = false;
    short totalBlocksAppended = 0;
    short currDllNode = 0;
    int currSectionNumber = 1;
};

struct commandElements {
    short i = NULL;
    short j = NULL;
    char* n1 = NULL;
    char* n2 = NULL;
    char type = NULL;
    char singleQ = NULL;
};

char* readInputT(streamInfo* flowInfo, char key) {
    char* buff = NULL;
    char ch = ' ';
    short len = 0;
    short size = STANDARD_CHUNK_SIZE;
    char beginning = 'y';

    buff = (char*)realloc(NULL, sizeof(*buff) * size);
    if (!buff) {
        free(buff);
        return NULL;
    }

    switch (key)
    {
    case '{':
        while (!std::cin.eof() && ch != key) {

            ch = (char)getchar();
            //if ((ch == '\n' || ch == '\r' || ch == '\0' || ch == '\t') || ch == key) {
            if ((ch == '\n' || ch == '\r' || ch == '\t' || ch == 11 || ch == 12) || ch == key) {
                continue;
            }
            else if (ch == '?') {
                buff = (char*)malloc(5);
                if (buff == nullptr) {
                    free(buff);
                    return NULL;
                }
                buff[0] = '?';
                std::cin.get(buff[1]).get(buff[2]).get(buff[3]).get(ch);
                buff[4] = '\0';
                flowInfo->readingCommands = true;
                flowInfo->readingCss = false;
                return buff;
            }
            else if (ch == ' ') {
                if (std::cin.peek() == '{' || std::cin.peek() == '\n') {
                    continue;
                }
            }
            buff[len] = ch;
            len++;

            if (len == size) {
                buff = (char*)realloc(buff, sizeof(*buff) * (int)(1.5 * len));
                size = (short)(1.5 * size);
                if (buff == nullptr) {
                    free(buff);
                    return NULL;
                }
            }
        }
        ch = std::cin.peek();
        //if (ch == '\n' || ch == '\r' || ch == '\0' || ch == '\t') {
        if ((ch == '\n' || ch == '\r' || ch == '\t' || ch == 11 || ch == 12)) {
            ch = (char)getchar();
        }
        break;


    case ';':
        while (!std::cin.eof() && ch != key) {
            ch = (char)getchar();
            //if ((ch == '\n' || ch == '\r' || ch == '\0' || ch == '\t') || ch == key) {
            if ((ch == '\n' || ch == '\r' ||  ch == '\t' || ch == 11 || ch==12) || ch == key) {
                continue;
            }
            else if (ch == ' ' && beginning == 'y') {
                ch = (char)getchar();
                beginning = 'n';
            }
            buff[len] = ch;
            len++;

            if (len == size) {
                buff = (char*)realloc(buff, sizeof(*buff) * (int)(1.5 * len));
                size = (short)(1.5 * size);
                if (buff == nullptr) {
                    free(buff);
                    return NULL;
                }
            }
        }
        break;
    default:
        while (!std::cin.eof() && ch != key) {
            if (flowInfo->readingCommands) {   
                /*
                if (key == ',') {
                    ch = (char)getchar();
                    while (ch == '\n' && ch == '\r') {
                        ch = (char)getchar();
                    }
                    free(buff);
                    return NULL;
                }
                */
                if (key == '\n') {
                    ch = (char)getchar();
                    //if ((ch == '\r' || ch == '\0' || ch == '\t') || ch == key) {
                    if ((ch == '\n' || ch == '\r' || ch == '\t' || ch == 11 || ch == 12) || ch == key) {
                        continue;
                    }
                    else if (ch == ',') {
                        free(buff);
                        return NULL;
                    }
                    
                    buff[len] = ch;
                    len++;

                    if (len == size) {
                        buff = (char*)realloc(buff, sizeof(*buff) * (int)(1.5 * len));
                        size = (short)(1.5 * size);
                        if (buff == nullptr) {
                            free(buff);
                            return NULL;
                        }
                    }
                }
                else {
                    ch = (char)getchar();

                    //if ((ch == '\n' || ch == '\r' || ch == '\0' || ch == '\t') || ch == key) {
                    if ((ch == '\n' || ch == '\r' || ch == '\t' || ch == 11 || ch == 12) || ch == key) {
                        continue;
                    }
                    buff[len] = ch;
                    len++;

                    if (len == size) {
                        buff = (char*)realloc(buff, sizeof(*buff) * (int)(1.5 * len));
                        size = (short)(1.5 * size);
                        if (buff == nullptr) {
                            free(buff);
                            return NULL;
                        }
                    }
                }
            }
            else {
                ch = (char)getchar();

                //if ((ch == '\n' || ch == '\r' || ch == '\0' || ch == '\t') || ch == key) {
                if ((ch == '\n' || ch == '\r' || ch == '\t' || ch == 11 || ch == 12) || ch == key) {
                    continue;
                }
                if (ch == '}') {
                    ch = (char)getchar();
                    free(buff);
                    return NULL;
                }

                buff[len] = ch;
                len++;

                if (len == size) {
                    buff = (char*)realloc(buff, sizeof(*buff) * (int)(1.5 * len));
                    size = (short)(1.5 * size);
                    if (buff == nullptr) {
                        free(buff);
                        return NULL;
                    }
                }
            }
          
        }
    }           
    buff[len] = '\0';
    len++; //add 1 for terminator

    if (std::cin.peek() == '\n' || std::cin.peek() == '\r') {
        ch = (char)getchar();
    }

    return (char*)realloc(buff, sizeof(*buff) * len);
}


short decideCommType(commandElements* currCom) {
    if (currCom->singleQ != NULL) {
        return Q;
    }
    else if (currCom->i == NULL) {
        if (currCom->type == 'S') {
            return zSQ;
        }
        else if (currCom->type == 'E') {
            return zEn;
        }
        else if (currCom->type == 'A') {
            return nAQ;
        }
        else {
            return error;
        }
    }
    else if (currCom->n1 == NULL) {
        if (currCom->type == 'A') {
            if (String(currCom->n2).stringLength() == 2) {
                return iAQ;
            }
            else {
                return iAn;
            }
        }
        else if (currCom->type == 'S') {
            if (String(currCom->n2).stringLength() == 2) {
                return iSQ;
            }
            else if (currCom->n2 == NULL) {
                return iSj;
            }
            else {
                return error;
            }
        }
        else if (currCom->type == 'D') {
            if (String(currCom->n2).stringLength() == 2) {
                return iDa;
            }
            else {
                return iDn;
            }
        }
        else {
            return error;
        }
    }
    return error;
}

short getComm(streamInfo* flowInfo, commandElements* currCom) {
    char tmp = ' ';

    if (!std::cin.eof() && isdigit(std::cin.peek()) != 0) {
        while (tmp != '\n') {
            std::cin >> currCom->i >> tmp >> currCom->type >> tmp;
            if (isdigit(std::cin.peek())) {
                std::cin >> currCom->j;
                tmp = (char)getchar();
                break;
            }
            else {
                currCom->n2 = readInputT(flowInfo, '\n');
                if (currCom->n2 == NULL) {
                    return -1;
                }
                break;
            }
        }
    }
    else {
        currCom->n1 = readInputT(flowInfo, ',');
        if (String(currCom->n1).stringLength() == 2) {
            currCom->singleQ = '?';
            tmp = (char)getchar();
            return decideCommType(currCom);
        }
        std::cin >> currCom->type;
        std::cin >> tmp;
        if (isdigit(std::cin.peek())) {
            std::cin >> currCom->j;
            tmp = (char)getchar();
        }
        else {
            currCom->n2 = readInputT(flowInfo, '\n');
            if (currCom->n2 == NULL) {
                return -1;
            }           
        }
    }
    return decideCommType(currCom);
}

void Q_func(streamInfo* flowInfo) {
    std::cout << "? == " << flowInfo->totalBlocksAppended << std::endl;
}

void iSQ_func(ListDll* rootNode, int i) {
    while (1) {
        for (short j = 0; j < 8; j++) {
            if (rootNode->getTBlocksPtr()[j].sectionNumber == i) {
                std::cout << i << ",S,? == " << rootNode->getSelectorCount(j) << std::endl;
                return;
            }
        }
        if (rootNode->next != nullptr) {
            rootNode = rootNode->next;
        }
        else {
            return;
        }
    }

}

void iAQ_func(ListDll* rootNode, int i) {
    while (1) {
        for (short j = 0; j < 8; j++) {
            if (rootNode->getTBlocksPtr()[j].sectionNumber == i) {
                std::cout << i << ",A,? == " << rootNode->getAttributeCount(j) << std::endl;
                return;
            }
        }
        if (rootNode->next != nullptr) {
            rootNode = rootNode->next;
        }
        else {
            return;
        }
    }

}

void iSj_func(ListDll* rootNode, int given_i, short given_j) {
    while (1) {
        for (short i = 0; i < 8; i++) {
            if (rootNode->getTBlocksPtr()[i].sectionNumber == given_i) {
                if (rootNode->getTBlocksPtr()[i].selectorCounter < given_j) {
                    return;
                }
                short h = 1;
                ListSll* selecTmp = rootNode->getTBlocksPtr()[i].selectorRoot;
                while (h != given_j) {
                    if (selecTmp->next == nullptr) {
                        h = 1;
                        break;
                    }
                    else {
                        selecTmp = selecTmp->next;
                        h++;
                    }
                }
                std::cout << given_i << ",S," << given_j << " == " << selecTmp->getSelectorName() << std::endl;
                return;
            }
        }
        if (rootNode->next != nullptr) {
            rootNode = rootNode->next;
        }
        else {
            return;
        }
    }
}

void iAn_func(ListDll* rootNode, int i, char* n) {
    while (rootNode) {
        for (short j = 0; j < 8; j++) {
            if (rootNode->getTBlocksPtr()[j].sectionNumber == i) {
                ListSll* attrTmp = rootNode->getTBlocksPtr()[j].attributeRoot;
                while (attrTmp != nullptr) {
                    if (strcmp(attrTmp->getSelectorName(), n) == 0) {
                        std::cout << i << ",A," << n << " == " << attrTmp->getAttributeValue() << std::endl;
                        return;
                    }
                    else {
                        attrTmp = attrTmp->next;
                    }
                }
                return;
            }
        }
        if (rootNode->next != nullptr) {
            rootNode = rootNode->next;
        }
        else {
            return;
        }
    }
}

void nAQ_func(ListDll* rootNode, char* n1) {
    char go = 'y';
    unsigned short counter = 0;
    ListDll* tempHead = rootNode;

    while (go == 'y') {
        for (unsigned short i = 0; i < 8; i++) {

            ListSll* tmpAttrHead = tempHead->getTBlocksPtr()[i].attributeRoot;
            if (tempHead->getTBlocksPtr()[i].attributeRoot == nullptr) {
                continue;
            }
            else {
                while (tmpAttrHead != nullptr) {
                    if (strcmp(tmpAttrHead->getSelectorName(), n1) == 0) {
                        counter += 1;
                        break;
                    }
                    else {
                        tmpAttrHead = tmpAttrHead->next;
                        continue;
                    }
                }
            }
        }
        if (tempHead->next != nullptr) {
            tempHead = tempHead->next;
        }
        else {
            std::cout << n1 << ",A,? == " << counter << std::endl;
            go = 'n';
            return;
        }
    }
}

void zSQ_func(ListDll* rootNode, char* z) {
    ListDll* tmp = rootNode;
    block* tmpBlock;
    ListSll* tmpRoot;
    short counter = 0;
    short i = 0;
    while (tmp) {
        tmpBlock = tmp->getTBlocksPtr();
        for (short j = 0; j < T; j++) {
            tmpRoot = tmpBlock[j].selectorRoot;
            while (tmpRoot != nullptr) {
                if (strcmp(tmpRoot->getSelectorName(), z) == 0) {
                    counter++;
                    tmpRoot = tmpRoot->next;
                }
                else {
                    tmpRoot = tmpRoot->next;
                }
            }
        }
        tmp = tmp->next;
    }
    std::cout << z << ",S,? == " << counter << std::endl;
}

void zEn_func(ListDll* rootNode, char* z, char* n) {
    rootNode = rootNode->last;
    char selectorFound = 'n';
    char attributeFound = 'n';
    block tempIBlock;
    while (rootNode) {
        for (short i = 7; i >= 0; i--) {
            tempIBlock = rootNode->getTBlocksPtr()[i];
            if (tempIBlock.selectorCounter > 0) {
                while (tempIBlock.selectorRoot) {
                    if (strcmp(tempIBlock.selectorRoot->getSelectorName(), z) == 0) {
                        selectorFound = 'y';
                        break;
                    }
                    else {
                        tempIBlock.selectorRoot = tempIBlock.selectorRoot->next;
                    }
                }
                if (selectorFound == 'y') {
                    while (tempIBlock.attributeRoot) {
                        if (strcmp(tempIBlock.attributeRoot->getSelectorName(), n) == 0) {
                            attributeFound = 'y';
                            std::cout << z << ",E," << n << " == " << tempIBlock.attributeRoot->getAttributeValue() << std::endl;
                            return;
                        }
                        else {
                            tempIBlock.attributeRoot = tempIBlock.attributeRoot->next;
                        }
                    }
                    selectorFound = 'n';
                }
            }
        }
        rootNode = rootNode->prev;
    }
}

void iDa_func(ListDll* rootNode, streamInfo* flowInfo, int i) {
    while (1) {
        for (short j = 0; j < 8; j++) {
            if (rootNode->getTBlocksPtr()[j].sectionNumber == i) {
                ListSll* tempSel = rootNode->getTBlocksPtr()[j].selectorRoot;

                while (tempSel != nullptr) {
                    tempSel = tempSel->next;
                    delete rootNode->getTBlocksPtr()[j].selectorRoot;
                    rootNode->getTBlocksPtr()[j].selectorCounter -= 1;
                    rootNode->getTBlocksPtr()[j].selectorRoot = tempSel;
                }
                if (rootNode->getTBlocksPtr()[j].selectorRoot == nullptr) {
                    ListSll* tempAtr = rootNode->getTBlocksPtr()[j].attributeRoot;
                    while (tempAtr != nullptr) {
                        tempAtr = tempAtr->next;
                        delete rootNode->getTBlocksPtr()[j].attributeRoot;
                        rootNode->getTBlocksPtr()[j].attributeCounter -= 1;
                        rootNode->getTBlocksPtr()[j].attributeRoot = tempAtr;
                    }
                    if (tempAtr == nullptr) {
                        
                        rootNode->getTBlocksPtr()[j].written = false;
                        rootNode->increaseFreeBlocks(j);
                        flowInfo->totalBlocksAppended -= 1;
                        if (rootNode->getFreeBlocks() == 8) {
                            if (rootNode->next != nullptr) {
                                ListDll* root = rootNode;
                                rootNode = rootNode->next;
                                rootNode->prev = NULL;
                                rootNode->last = root->last;   
                                rootNode->updateSectionNumbers(rootNode, 0);
                                std::cout << i << ",D,* == deleted" << std::endl;
                           
                                return;
                            }
                            else {
                                if (rootNode->next == nullptr && rootNode->prev == nullptr) {
                                    rootNode = NULL;
                                    flowInfo->totalBlocksAppended = 0;
                                }
                            }
                        }
                        
                        rootNode->updateSectionNumbers(rootNode, j);
                        std::cout << i << ",D,* == deleted" << std::endl;
                        return;
                    }
                }
            }
        }
        if (rootNode->next != nullptr) {
            rootNode = rootNode->next;
        }
        else {
            return;
        }
    }
}

void iDn_func(ListDll* rootNode, streamInfo* flowInfo, int i, char* n2) {
    while (1) {
        for (short j = 0; j < 8; j++) {
            if (rootNode->getTBlocksPtr()[j].sectionNumber == i) {
                if (rootNode->getTBlocksPtr()[j].written == false) {
                    return;
                }
                else {
                    ListSll* temp = rootNode->getTBlocksPtr()[j].attributeRoot;
                    if (strcmp(temp->getSelectorName(), n2) == 0) {
                        if (rootNode->getTBlocksPtr()[j].attributeRoot->next != nullptr) {
                            ListSll* tempNext = rootNode->getTBlocksPtr()[j].attributeRoot->next;
                            delete rootNode->getTBlocksPtr()[j].attributeRoot;
                            rootNode->getTBlocksPtr()[j].attributeRoot = tempNext;
                            //rootNode->getTBlocksPtr()[j].attributeRoot = rootNode->getTBlocksPtr()[j].attributeRoot->next;
                            //delete rootNode->getTBlocksPtr()[j].attributeRoot->next;
                        }
                        else {
                            delete rootNode->getTBlocksPtr()[j].attributeRoot;
                            rootNode->getTBlocksPtr()[j].attributeRoot = NULL;
                        }
                        rootNode->getTBlocksPtr()[j].attributeCounter -= 1;
                    }
                    else {
                        if (temp->next == nullptr || temp == nullptr) {
                            return;
                        }                     
                        while (temp != nullptr && temp->next != nullptr) {
                            if (strcmp(temp->next->getSelectorName(), n2) == 0) {
                                ListSll* tempNextNext = temp->next->next;
                                delete temp->next;
                                rootNode->getTBlocksPtr()[j].attributeCounter -= 1;
                                temp->next = tempNextNext;
                                break;
                            }
                            else {
                                temp = temp->next;
                            }
                        }
                    }
                    if (rootNode->getTBlocksPtr()[j].attributeCounter == 0) {
                        ListSll* temp = rootNode->getTBlocksPtr()[j].selectorRoot;
                        while (temp != nullptr) {
                            temp = temp->next;
                            delete rootNode->getTBlocksPtr()[j].selectorRoot;
                            rootNode->getTBlocksPtr()[j].selectorCounter -= 1;
                            rootNode->getTBlocksPtr()[j].selectorRoot = temp;
                        }
                        if (temp == nullptr) {
                            rootNode->getTBlocksPtr()[j].written = false;
                            flowInfo->totalBlocksAppended -= 1;
                            rootNode->updateSectionNumbers(rootNode, j);
                        }
                    }
                    std::cout << i << ",D," << n2 << " == deleted" << std::endl;
                    return;
                }
            }
        }
        if (rootNode->next != nullptr) {
            rootNode = rootNode->next;
        }
        else {
            return;
        }
    }

}

void setWrittenFlag(streamInfo* flowInfo, ListDll* rootNode) {
    short i = flowInfo->totalBlocksAppended;
    while (i - 1 > 7) {
        if (rootNode->next != nullptr) {
            rootNode = rootNode->next;
            i -= 8;
            continue;
        }
        return;
    }
    rootNode->decreaseFreeBlocks();
    rootNode->getTBlocksPtr()[i - 1].written = true;

}

void getInput(streamInfo* flowInfo, ListDll* rootNode) {
    commandElements currCom;
    while (!(flowInfo->endProgram)) {
        if (flowInfo->readingCss == true) {
            char* selectorX = readInputT(flowInfo, '{');
            if (strcmp(selectorX, commandFlag) == 0) {
                continue;
            }// if selector name = '' not appending selector
            else if (strcmp(selectorX, "") == 0) {
                rootNode->appendSelector(rootNode, String(selectorX));
            }
            else {
                char* singleSelector = strtok(selectorX, ",");
                while (singleSelector) {
                    String x(singleSelector);
                    singleSelector = strtok(NULL, ",");
                    rootNode->appendSelector(rootNode, x);
                }
            }
            while (flowInfo->endBlockFlag == false) {
                String property(readInputT(flowInfo, ':'));
                if (property.stringLength() == 0) {
                    flowInfo->totalBlocksAppended += 1;
                    if (flowInfo->totalBlocksAppended == 8) {
                        flowInfo->currDllNode += 1;
                    }
                    setWrittenFlag(flowInfo, rootNode);//
                    break;
                }
                String value(readInputT(flowInfo, ';'));
                rootNode->appendAttribute(rootNode, property, value);

            }
            //rootNode->decreaseFreeBlocks();
            flowInfo->endBlockFlag = false;

        }
        else if (flowInfo->readingCommands == true) {
            char tmp = ' ';
            while (flowInfo->readingCommands) {
                if (std::cin.eof()) {
                    flowInfo->endProgram = true;
                    return;
                }
                if (std::cin.peek() == '\n' || std::cin.peek() == '\r') {
                    std::cin.get(tmp);
                }
                if (tmp == NULL) {
                    continue;
                }
                if (std::cin.peek() == '?') {
                    tmp = (char)getchar();
                    Q_func(flowInfo);
                    while (std::cin.peek() == '\n' || std::cin.peek() == '\r') {
                        std::cin.get(tmp);
                    }
                }
                else if (std::cin.peek() == '*') {
                    std::cin >> tmp;
                    if (std::cin.peek() == '*') {
                        std::cin >> tmp >> tmp >> tmp;
                        tmp = (char)getchar();
                        flowInfo->readingCommands = false;
                        flowInfo->readingCss = true;

                        break;
                    }
                }
                else {
                    switch (getComm(flowInfo, &currCom)) {
                    case iSQ:
                        iSQ_func(rootNode, currCom.i);
                        currCom = {};
                        break;
                    case iAQ:
                        iAQ_func(rootNode, currCom.i);
                        currCom = {};
                        break;
                    case iSj:
                        iSj_func(rootNode, currCom.i, currCom.j);
                        currCom = {};
                        break;
                    case iAn:
                        iAn_func(rootNode, currCom.i, currCom.n2);
                        currCom = {};
                        break;
                    case nAQ:
                        nAQ_func(rootNode, currCom.n1);
                        currCom = {};
                        break;
                    case zSQ:
                        zSQ_func(rootNode, currCom.n1);
                        currCom = {};
                        break;
                    case zEn:
                        zEn_func(rootNode, currCom.n1, currCom.n2);
                        currCom = {};
                        break;
                    case iDa:
                        iDa_func(rootNode, flowInfo, currCom.i);
                        currCom = {};
                        break;
                    case iDn:
                        iDn_func(rootNode, flowInfo, currCom.i, currCom.n2);
                        currCom = {};
                        break;
                    default:
                        break;
                    }                  
                }
                currCom = {};
            }
        }
        else {
            break;
        }
    }
}

int main()
{
    streamInfo flowInfo;
    ListDll* root = new ListDll();
    root->last = root;
    getInput(&flowInfo, root);
    delete root;
    return 0;
}

