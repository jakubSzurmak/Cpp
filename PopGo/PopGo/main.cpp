#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"conio2.h"

//keyCodes
#define keyArrowUp 0x48
#define keyArrowDown 0x50
#define keyArrowLeft 0x4b
#define keyArrowRight 0x4d
#define keyENTER 0x0d
#define keyN 0x6e
#define keyI 0x69
#define keyESC 0x1b
#define keyK 0x6b
#define keyL 0x6c
#define keyS 0x73
#define keyQ 0x71

//errorCodes
#define BADMEM -420
#define BADPEER -690
#define BADBOARD -137
#define BADFILE -213

// MY STRUCTS
#define maxFieldsOnWidth 39
#define maxFieldsOnHeight 24
#define primalBoardYLR 3 //always first Y for Left and Right
#define primalBoardXL 3  //always first X for Left
#define primalBoardXR 41 //always first X for Right
#define frameBeginXR 40
#define frameBeginXL 2
#define frameBeginYLR 2
#define underTheLegendY 17

typedef struct playingField { //B-Black, W-White, N-Nobody x == displayX  y == displayY <=> Visible x,y
    int x = 0;
    int y = 0;
    char belongsTo = 'N';

}fieldT;


typedef struct gameInfo {                   //Information about current app Session 
    char curPlayer = 'B';                   // B - Black, W - White, N - None
    unsigned short int firstMove = 1;       //for handicap Handling
    int displayX = 1;		                // X coordinate according to board
    int x = 0;			                    // X coordinate according to window
    int displayY = 1;		                // Y coordinate according to window
    int y = 0;			                    // Y coordinate according to board
    unsigned short int handicapFlag = 0;    // 1 if handicap arrangement is happening
    unsigned short int handicapApproved = 0;// 1 after placing all handicaps
    unsigned short int moveApproved = 0;    // previous variable ==1 until move Approved == 1        
    int* placedStones = NULL;               //Array of stone indexes
    int zn = 0;						        //Currently pressed_key
    int zero = 0;                           //flag For detecting arrows
    short int begin = 1;                    //flag for showing starting menu accordingly
    int endBoardMenu = 0;                   //if size selected/loaded game starts no board menu = 0, else 1
    int lastlyPlacedStoneIndexWhite = -1;   //index in allFields
    int lastlyPlacedStoneIndexBlack = -1;   //index in allFields shown later
    fieldT* carryPtrAfterLoading = NULL;    //temporary memory for loading from file. Used to carry fields to be loaded
    char intCharBuff1[32] = {};             //Used to display XY on board and keycodes                  
    char boardWid[8] = {};                
    char boardHei[8] = {};                  //Used to read board h and w from user later sprintf
    char boardSide = 'R';
    char* startBoard = NULL;                //Used for holding static board visual -|-|-
    int totalBoardHeight = 0;
    int totalBoardWidth = 0;                //Including not Fields -|-|- = 5
    int totalFieldsOnWidth = 0;             // -|-|- = 2
    int totalBoardField = 0;                // Height*fieldsOnW How many fields on board
    int insideBoardCords[4] = {};           // [0]=first inside col, [1]=last inside col, [2]=first inside row, [3]=last inside row
    int insideScrollingWindowCords[4] = {}; // [0]=first/current inside col, [1]=last/current inside col, [2]=first/current inside row, [3]=last/current inside row
    int offsetsScrollingWindow[4] = {};     // from border displayed to end of field board
    int* fieldsToRemove = NULL;             // Array of allFields Indexes to be removed after a kill

}gameInfoT;


//Function Prototypes
void displayMainMenu(gameInfoT* curGame);
bool detectBoardMenuInput(gameInfoT* curGame);
void displayBlockBoardMenu();
bool startBoardMenu(gameInfoT* curGame);
bool allocateMemoryStaticBoard(gameInfoT* curGame);
void initStaticBoard(gameInfoT* curGame);
void preparePrintingBySide(gameInfoT* curGame);
void printFrame(gameInfoT* curGame);
bool checkFieldOccup(fieldT* allFields, int index);
bool checkFieldSuicide(gameInfoT* curGame, fieldT* allFields);
int getFieldIndex(int curX, int curY, int totalWidth);
bool insertStone(gameInfoT* curGame, fieldT* allFields);
int printFieldsOnStaticBoard(int x, int y, char boardSide, int FieldsInWidth, fieldT* allFields);
void printBoard(gameInfoT* curGame, fieldT* allFields);
bool approveYourMoveQuestion(gameInfoT* curGame);
int checkSurroundingStone(gameInfoT* curGame, fieldT* allFields, const short xOffset, const short yOffset);
int checkForKill(gameInfoT* curGame, fieldT* allFields);
void freeFieldSlot(gameInfoT* curGame, fieldT* allFields);
fieldT* allocateAllFieldsMemory(gameInfoT* curGame);
void initiateToRemoveMemory(int* ptrMem, gameInfoT* curGame);
bool checkKORule(gameInfoT* curGame, char p);
void writeToFile(gameInfoT* curGame, char* fileName, fieldT* allFields, int nStones);
void saveGameState(gameInfoT* curGame, fieldT* allFields);
void loadGameState(char* fileName, gameInfoT* curGame);


void displayMainMenu(gameInfoT* curGame) {
    
    unsigned int xLegend = 2;

    if (curGame->boardSide == 'L') {
        xLegend = curGame->totalBoardWidth + 10;
    }
    else if (curGame->boardSide == 'R') {
        xLegend = 2;
    }
    gotoxy(xLegend, 2);
    cputs("Jakub Szurmak 193095");
    gotoxy(xLegend, wherey() + 1);
    cputs("Functions: 2.2:a,b,c,d,e");
    gotoxy(xLegend, wherey() + 1);
    cputs("Functions: 2.3:f,g,h,k");
    gotoxy(xLegend, wherey()+1);
    cputs("q      = exit");
    gotoxy(xLegend, wherey() + 1);
    cputs("n      = new game");
    gotoxy(xLegend, wherey() + 1);
    cputs("enter  = complete your turn");
    gotoxy(xLegend, wherey() + 1);
    cputs("esc    = cancel current action");
    gotoxy(xLegend, wherey() + 1);
    cputs("i      = put stone on board");
    gotoxy(xLegend, wherey() + 1);
    cputs("s      = save game");
    gotoxy(xLegend, wherey() + 1);
    cputs("k      = handicap for black");
    gotoxy(xLegend, wherey() + 1);
    cputs("arrows = moving");
    gotoxy(xLegend, wherey() + 1);
    sprintf(curGame->intCharBuff1, "Your curr X axis position:  %.02d\0", curGame->displayX);
    cputs(curGame->intCharBuff1);
    gotoxy(xLegend, wherey() + 1);
    sprintf(curGame->intCharBuff1, "Your curr Y axis position:  %.02d\0", curGame->displayY);
    cputs(curGame->intCharBuff1);
    gotoxy(xLegend, wherey() + 1);

    if (curGame->zero) {
        sprintf(curGame->intCharBuff1, "key code: 0x00 0x%02x", curGame->zn);
    }else {
        sprintf(curGame->intCharBuff1, "key code: 0x%02x", curGame->zn);
    } 
    cputs(curGame->intCharBuff1);

    

}

//bool detectBoardMenuInput(gameInfoT* curGame, int zn) { //false if drawn from begin, true if loaded from file
bool detectBoardMenuInput(gameInfoT* curGame){
    char x;
    switch (curGame->zn)
    {
    case('a'): {
        curGame->begin = 0;
        curGame->totalBoardHeight = 19; //19 intersec 20 lines 2 borders
        curGame->totalBoardWidth = 39;  // Later By user, width passed*2 +1
        curGame->totalFieldsOnWidth = 19;
        curGame->totalBoardField = 741;
        initStaticBoard(curGame);
        clrscr();
        return false;
        break;
    }
    case('b'): {
        curGame->begin = 0;
        curGame->totalBoardHeight = 13;
        curGame->totalBoardWidth = 27;
        curGame->totalFieldsOnWidth = 13;
        curGame->totalBoardField = 351;
        initStaticBoard(curGame);
        clrscr();
        return false;
        break;
    }
    case('c'): {
        curGame->begin = 0;
        curGame->totalBoardHeight = 9;
        curGame->totalBoardWidth = 19;
        curGame->totalFieldsOnWidth = 9;
        curGame->totalBoardField = 171;
        initStaticBoard(curGame);
        clrscr();
        return false;
        break;
    }
    case('d'): {

        do {
            displayBlockBoardMenu();
            gotoxy(5, 10);
            unsigned int i = 0;
            gotoxy(1, wherey() + 2);
            cputs("Enter desired Width: MAX=38 !Hit enter when you are done with this dimension! ");
            do {
                x = (char)(getche());
                curGame->boardWid[i] = x;
                if (i > 5) {
                    i = 0;
                }
                i++;
            } while (x != keyENTER);
            gotoxy(1, wherey() + 2);
            cputs("Enter desired Height: MAX=23 !Hit enter when you are done with this dimension! "); //11801
            i = 0;
            do {
                x = (char)(getche());
                curGame->boardHei[i] = x;
                if (i > 5) {
                    i = 0;
                }
                i++;
            } while (x != keyENTER);

            if ((atoi(curGame->boardWid) > 1) && (atoi(curGame->boardHei) > 1) && ((atoi(curGame->boardWid) < maxFieldsOnWidth) && (atoi(curGame->boardHei) < maxFieldsOnHeight))) { //If good size if given initialize and continue
                curGame->endBoardMenu = 1;
                curGame->begin = 0;
                curGame->totalBoardHeight = atoi(curGame->boardHei);
                curGame->totalFieldsOnWidth = atoi(curGame->boardWid);
                curGame->totalBoardWidth = 2 * (atoi(curGame->boardWid)) + 1;
                curGame->totalBoardField = curGame->totalBoardWidth * curGame->totalBoardHeight;

                clrscr();
                return false;
            }
            else { //terminate previously given size
                clrscr();
                for (int j = 0; j < 6; j++) {
                    curGame->boardWid[j] = ' ';
                    curGame->boardHei[j] = ' ';
                }
                curGame->boardWid[6] = '\0';
                curGame->boardHei[6] = '\0';
                continue;
            }
        } while (curGame->endBoardMenu == 0);
        return false;
        break;
    }
    case('l'): {
        gotoxy(2, 12);
        cputs("Enter file name: ");

        char* fileName = (char*)malloc(sizeof(char) * 256);
        unsigned short int i = 0;

        do {
            x = (char)getche();
            fileName[i] = x;
            i++;
        } while (x != keyENTER);

        fileName[i - 1] = 0;
        curGame->begin = 0;
        loadGameState(fileName, curGame);
        free(fileName);
        return true;
        break;
    }

    default:
        return false;
        break;
    }
}

void displayBlockBoardMenu() {
    gotoxy(3, 2);
    cputs("------------------------------------");
    gotoxy(2, 2);
    cputs("|\n |\n |\n |\n |\n |\n |\n |\n |\n |\n");
    gotoxy(3, 11);
    cputs("------------------------------------");
    gotoxy(39, 2);
    cputs("|\n");
    gotoxy(39, 3);
    cputs("|\n");
    gotoxy(39, 4);
    cputs("|\n");
    gotoxy(39, 5);
    cputs("|\n");
    gotoxy(39, 6);
    cputs("|\n");
    gotoxy(39, 7);
    cputs("|\n");
    gotoxy(39, 8);
    cputs("|\n");
    gotoxy(39, 9);
    cputs("|\n");
    gotoxy(39, 10);
    cputs("|\n");
    gotoxy(39, 11);
    cputs("|\n");
    gotoxy(5, 4);
    cputs("Choose the size for your board: ");
    gotoxy(5, 5);
    cputs("a = 19x19 ");
    gotoxy(5, 6);
    cputs("b = 13x13 ");
    gotoxy(5, 7);
    cputs("c = 9x9 ");
    gotoxy(5, 8);
    cputs("d = Get your own! ");
    gotoxy(5, 9);
    cputs("l = Load Game State! ");

}

bool startBoardMenu(gameInfoT* curGame) { //Display start menu, true if loaded from file, false otherwise
    bool allocatedFields = false;
    do {
        displayBlockBoardMenu();
        gotoxy(5, 9);
        curGame->zn = getch();
        allocatedFields = detectBoardMenuInput(curGame);
    } while (curGame->begin == 1);
    return allocatedFields;
}


bool allocateMemoryStaticBoard(gameInfoT* curGame) {    //Give mem for static board elems -|-|-
    curGame->startBoard = (char*)malloc((curGame->totalBoardField * sizeof(char)+1));
    if (curGame->startBoard == NULL) {
        return false;
    }
    return true;
}

void initStaticBoard(gameInfoT* curGame) { //Initialize array in the mem block from f. above
    if (allocateMemoryStaticBoard(curGame) == true) {
        curGame->startBoard[curGame->totalBoardField] = '\0';
        int tempCnt = 1;

        for (int y = 0; y < (curGame->totalBoardField); y++) {
            if (tempCnt == curGame->totalBoardWidth) {
                curGame->startBoard[y] = '-';
                tempCnt = 1;
                continue;
            }
            if (tempCnt % 2 == 0) {
                curGame->startBoard[y] = '|';
                tempCnt += 1;
                continue;
            }
            else {
                curGame->startBoard[y] = '-';
                tempCnt += 1;
            }
        }
    }
    else {
        exit(BADMEM);
    }
    
}

void preparePrintingBySide(gameInfoT* curGame) { //set good const borders for board according to its side for printing
    if (curGame->boardSide == 'L') {
        curGame->insideBoardCords[0] = { primalBoardXL};					// [0]=first inside col, [1]=last inside col, [2]=first inside row, [3]=last inside row
        curGame->insideBoardCords[1] = { (primalBoardXL + curGame->totalBoardWidth - 1) };
        curGame->insideBoardCords[2] = { primalBoardYLR };
        curGame->insideBoardCords[3] = { (primalBoardYLR + curGame->totalBoardHeight - 1) };
    }
    else if (curGame->boardSide == 'R') {
        curGame->insideBoardCords[0] = { primalBoardXR };					// [0]=first inside col, [1]=last inside col, [2]=first inside row, [3]=last inside row
        curGame->insideBoardCords[1] = { (primalBoardXR + curGame->totalBoardWidth -1 ) };
        curGame->insideBoardCords[2] = { primalBoardYLR };
        curGame->insideBoardCords[3] = { (primalBoardYLR + curGame->totalBoardHeight - 1) };
    }

    if (curGame->totalBoardHeight % 2 != 0) { //set cursor on the middle
        curGame->x = (curGame->insideBoardCords[0] + (curGame->totalBoardHeight));
    }
    else {
        curGame->x = (curGame->insideBoardCords[0] + curGame->totalBoardHeight - 1);
    }
    curGame->y = (curGame->insideBoardCords[2] + (curGame->totalBoardHeight / 2));


    if (curGame->boardSide == 'R') {// synchronize displayedXY to screenXY
        curGame->displayX = (curGame->x - 40) / 2;
        curGame->displayY = (curGame->y) - 2;
    }
    else if (curGame->boardSide == 'L') {
        curGame->displayX = (curGame->x - 2) / 2;
        curGame->displayY = (curGame->y) - 2;
    }

}


void printFrame(gameInfoT* curGame) { // Printing the borders of board
    int tempX = frameBeginXR, tempY = frameBeginYLR, leftX = frameBeginXL;
 
    if (curGame->boardSide == 'R') {
        tempX = frameBeginXR, tempY = frameBeginYLR; leftX = frameBeginXR;
    }
    else if (curGame->boardSide == 'L') {
        tempX = frameBeginXL, tempY = frameBeginYLR;
    }

    gotoxy(tempX, tempY);
    for (int i = 0; i < (curGame->totalBoardHeight + 2); i++) { //going arround constants set in preparePrinting
        for (int j = 0; j < curGame->totalBoardWidth + 2; j++) {
            if ((i == 0) || (i == curGame->totalBoardHeight + 1)) {
                cputs("=");
                tempX += 1;
                gotoxy(tempX, tempY);
                continue;
            }if ((j == 0) || (j == curGame->totalBoardWidth)) {
                if (j == curGame->totalBoardWidth) {
                    gotoxy(tempX + curGame->totalBoardWidth, tempY);
                    cputs("I");
                    break;
                }
                cputs("I");
                tempX += 1;
                gotoxy(tempX, tempY);
            }
        }
        tempX = leftX;
        tempY += 1;
        gotoxy(tempX, tempY);
    }
}

bool checkFieldOccup(fieldT* allFields, int index) { //true if taken, false if free
    if (allFields[index].belongsTo != 'N') {
        return true;
    }
    else {
        return false;
    }
}

bool checkFieldSuicide(gameInfoT* curGame, fieldT* allFields) { //true if suicidal, false if good [0]=first inside col, [1]=last inside col, [2]=first inside row, [3]=last inside row
    if (curGame->y == curGame->insideBoardCords[2]) {  // y on top  displayY == 1 for correct calc top row displayY = 0;  on the same lvl y-1  above y-2  below y
        if (curGame->x == curGame->insideBoardCords[0] + 1) { // x on left border for correct calc left col displayX = 0;  on the same line x-1 left x-2 right x
            unsigned short req = 2;
            if (allFields[getFieldIndex(curGame->displayX , curGame->displayY-1, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { //to the right
                if (allFields[getFieldIndex(curGame->displayX , curGame->displayY-1, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { //below
                if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (req == 0) {
                return true;
            }
            return false;
        }
        else if (curGame->x == curGame->insideBoardCords[1] - 1) { // x on right border
            unsigned short req = 2;
            if (allFields[getFieldIndex(curGame->displayX - 2, curGame->displayY-1, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { //to the left
                if (allFields[getFieldIndex(curGame->displayX - 2, curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { //below
                if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (req == 0) {
                return true;
            }
            return false;
        }
        else { //left border < x < right border
            unsigned short req = 3;
            if (allFields[getFieldIndex(curGame->displayX - 2, curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { // to the left
                if (allFields[getFieldIndex(curGame->displayX - 2, curGame->displayY -1, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { // below
                if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX , curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { // to the right
                if (allFields[getFieldIndex(curGame->displayX , curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (req == 0) {
                return true;
            }
            return false;
        }

    }
    else if (curGame->y == curGame->insideBoardCords[3]) { // y == boardheight-1
        if (curGame->x == curGame->insideBoardCords[0] + 1) { // x == leftBorder
            unsigned short req = 2;
            if (allFields[getFieldIndex(curGame->displayX , curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { //to the right
                if (allFields[getFieldIndex(curGame->displayX , curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY - 2, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { //above
                if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY - 2, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (req == 0) {
                return true;
            }
            return false;
        }
        else if (curGame->x == curGame->insideBoardCords[1] - 1) { // x == rightBorder
            unsigned short req = 2;
            if (allFields[getFieldIndex(curGame->displayX - 2, curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { //to the left
                if (allFields[getFieldIndex(curGame->displayX - 2, curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY - 2, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { //above
                if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY - 2, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (req == 0) {
                return true;
            }
            return false;
        }
        else { //leftBorder < x < rightBorder
            unsigned short req = 3;
            if (allFields[getFieldIndex(curGame->displayX - 2, curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { // to the left
                if (allFields[getFieldIndex(curGame->displayX - 2, curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY - 2, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { // above
                if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY - 2, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX , curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) { //to the right
                if (allFields[getFieldIndex(curGame->displayX , curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (req == 0) {
                return true;
            }
            return false;
        }
    }
    else { // 3<y<boardheight-1
        if (curGame->x == curGame->insideBoardCords[0] + 1) { // x==leftBorder [0] = first inside col, [1] = last inside col, [2] = first inside row, [3] = last inside row
            unsigned short req = 3;
            if (allFields[getFieldIndex(curGame->displayX , curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) {//to the Right
                if (allFields[getFieldIndex(curGame->displayX , curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) {//below
                if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY - 2, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) {//above
                if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY - 2, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (req == 0) {
                return true;
            }
            return false;

        }
        else if (curGame->x == curGame->insideBoardCords[1] - 1) { //x == rightBorder
            unsigned short req = 3;
            if (allFields[getFieldIndex(curGame->displayX - 2, curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) {//to the left
                if (allFields[getFieldIndex(curGame->displayX - 2, curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) {//below
                if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY - 2, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) {//above
                if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY - 2, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (req == 0) {
                return true;
            }
            return false;
        }
        else { //leftBorder < x < rightBorder
            unsigned short req = 4;
            if (allFields[getFieldIndex((curGame->displayX - 2), (curGame->displayY - 1), curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) {//to the left
                if (allFields[getFieldIndex(curGame->displayX - 2, curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) {//below
                if (allFields[getFieldIndex(curGame->displayX-1, curGame->displayY, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX-1, (curGame->displayY) - 2, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) {//above
                if (allFields[getFieldIndex(curGame->displayX-1, (curGame->displayY) - 2, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (allFields[getFieldIndex(curGame->displayX, curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != curGame->curPlayer) {//to the right
                if (allFields[getFieldIndex(curGame->displayX, curGame->displayY - 1, curGame->totalFieldsOnWidth)].belongsTo != 'N') {
                    req -= 1;
                }
            }
            if (req == 0) {
                return true;
            }
            return false;
        }
    }
}

int getFieldIndex(int curX, int curY, int totalWidth) { //Get the field's index in allFields from board's XY
    return (totalWidth * (curY) + (curX));
}

bool insertStone(gameInfoT* curGame, fieldT* allFields) {                                                                                                     //true if inserted False if not

    if (checkFieldOccup(allFields, getFieldIndex((curGame->displayX)-1, (curGame->displayY)-1, curGame->totalFieldsOnWidth)) == false) {                      // check if free
        if (checkKORule(curGame, curGame->curPlayer) != true) {                                                                                               //check if ko
            allFields[getFieldIndex((curGame->displayX) - 1, (curGame->displayY) - 1, curGame->totalFieldsOnWidth)].belongsTo = curGame->curPlayer;           //temporary placement to check if kill happens
            if (checkForKill(curGame, allFields) > 0) {                                                                                                          // if killed end
                return true; 
            }
            else {
                if (checkFieldSuicide(curGame, allFields) == false) {                                                                                              // there if no kill and no suicide so place
                    allFields[getFieldIndex((curGame->displayX) - 1, (curGame->displayY) - 1, curGame->totalFieldsOnWidth)].belongsTo = curGame->curPlayer;
                    return true;
                }
                else {                                                                                                                                        // no kill and suicide set free
                    allFields[getFieldIndex((curGame->displayX) - 1, (curGame->displayY) - 1, curGame->totalFieldsOnWidth)].belongsTo = 'N';
                    return false;
                }
            }
        }
        else {                                                                                                                                                // KO is not happening so no repetition
            if (checkFieldSuicide(curGame, allFields) == false) {                                                                                                  //Not suicidal so place
                allFields[getFieldIndex((curGame->displayX) - 1, (curGame->displayY) - 1, curGame->totalFieldsOnWidth)].belongsTo = curGame->curPlayer;
                return true;
            }
            else {                                                                                                                                            //Suicidal End
                allFields[getFieldIndex((curGame->displayX) - 1, (curGame->displayY) - 1, curGame->totalFieldsOnWidth)].belongsTo = 'N';
                return false;
            }
        }
    }
    else {                                                                                                                                                    //Occupied end
        return false;
    }
}

int printFieldsOnStaticBoard(int x, int y, char boardSide, int FieldsInWidth, fieldT* allFields) {                                                                  //OverPrint static elements with Fields
    int index = 0;
    if (boardSide == 'R') {
        y -= 3;
        index = getFieldIndex(x, y, FieldsInWidth);
    }
    else if (boardSide == 'L') {
        y -= 3;
        index = getFieldIndex(x, y, FieldsInWidth);
    }
    else {
        return -1;
    }

    if (allFields[index].belongsTo == 'W') {
        return WHITE;
    }
    else if (allFields[index].belongsTo == 'B') {
        return BLACK;
    }
    else {
        return -1;
    }
}                                                       //Return color

void printBoard(gameInfoT* curGame, fieldT* allFields) {//printing Based on Colors based on returning value of other funcs

    int tempX = primalBoardXL, tempY = primalBoardYLR, cnt = 0, leftX = primalBoardXR, arrIndice = 0;                                                                                        //setting temp variables for printing static board

    if (curGame->boardSide == 'R') {
        tempX = primalBoardXR, leftX = primalBoardXR, arrIndice = 0;
    }
    else if (curGame->boardSide == 'L') {
        tempX = primalBoardXL, leftX = primalBoardXL, arrIndice = 0;
    }

    for (int i = 0; i < (curGame->totalBoardField); i++) {                                                                                                      //when we printed the last element go to next row
        if (cnt == curGame->totalBoardWidth)
        {
            tempY += 1; tempX = leftX; cnt = 0; arrIndice = 0;
        }

        gotoxy(tempX, tempY);
        if (tempX % 2 == 0) {                                                                                                                                   //Fields are located on even X's
            if (printFieldsOnStaticBoard(arrIndice, tempY, curGame->boardSide, curGame->totalFieldsOnWidth, allFields) == (-1)) {
                textbackground(BROWN);
                textcolor(BLACK);
                arrIndice += 1;
            }
            else if (printFieldsOnStaticBoard(arrIndice, tempY, curGame->boardSide, curGame->totalFieldsOnWidth, allFields) == WHITE) {
                textbackground(printFieldsOnStaticBoard(arrIndice, tempY, curGame->boardSide, curGame->totalFieldsOnWidth, allFields));
                textcolor(printFieldsOnStaticBoard(arrIndice, tempY, curGame->boardSide, curGame->totalFieldsOnWidth, allFields));
                arrIndice += 1;
            }
            else if (printFieldsOnStaticBoard(arrIndice, tempY, curGame->boardSide, curGame->totalFieldsOnWidth, allFields) == BLACK) {
                textbackground(printFieldsOnStaticBoard(arrIndice, tempY, curGame->boardSide, curGame->totalFieldsOnWidth, allFields));
                textcolor(printFieldsOnStaticBoard(arrIndice, tempY, curGame->boardSide, curGame->totalFieldsOnWidth, allFields));
                arrIndice += 1;
            }
            putch(curGame->startBoard[i]);
            tempX += 1;
            cnt += 1;
            textbackground(BROWN);
            textcolor(BLACK);
        }
        else {
            putch(curGame->startBoard[i]);
            tempX += 1;
            cnt += 1;
            textbackground(BROWN);
            textcolor(BLACK);
        }       
    }
}

bool approveYourMoveQuestion(gameInfoT* curGame) {                                                                                                                 //Confirm placing Stone
    gotoxy((curGame->insideBoardCords[0]) -1, curGame->insideBoardCords[3] +3);
    cputs("Are you sure about that? ");
    gotoxy((curGame->insideBoardCords[0]) - 1, curGame->insideBoardCords[3] + 4);
    cputs("ESC<=>Cancel, ENTER<=>Approve");
    curGame->zn = getch();
    clrscr();

    if (curGame->zn == keyESC) {
        return false;
    }
    else if(curGame->zn == keyENTER) {                                                                                                                                //True if confirmed, False otherwise
        return true;
    }
    else {
        return false;
    }

}

int checkSurroundingStone(gameInfoT* curGame, fieldT* allFields, const short xOffset, const short yOffset) {             //after placing stone check it's surrounding if they got killed.
    int saveState[2] = { curGame->displayX, curGame->displayY };
    
    curGame->displayX += (-1 + xOffset);    //change placed stone to stone to be checked
    curGame->displayY += (-1 + yOffset);

    curGame->curPlayer = allFields[getFieldIndex(curGame->displayX-1, curGame->displayY-1, curGame->totalFieldsOnWidth)].belongsTo;
    if (checkFieldSuicide(curGame, allFields) == true) {
        curGame->fieldsToRemove[getFieldIndex(curGame->displayX-1, curGame->displayY-1, curGame->totalFieldsOnWidth)] = getFieldIndex(curGame->displayX-1, curGame->displayY-1, curGame->totalFieldsOnWidth);
        curGame->displayX = saveState[0];   //return to placed stone
        curGame->displayY = saveState[1];
        return 1;
    }
    curGame->displayX = saveState[0];
    curGame->displayY = saveState[1];
    return 0;

}

int checkForKill(gameInfoT* curGame, fieldT* allFields) { //return No of kills [0]=first inside col, [1]=last inside col, [2]=first inside row, [3]=last inside row Check if surrounding stones got killed
    char killingPlayer = curGame->curPlayer;
    int killed = 0;
    if (curGame->y == curGame->insideBoardCords[2]) { //y = firstRow
        if (curGame->x == curGame->insideBoardCords[0] + 1) { //x = firstColumn

            curGame->y += 1;
            killed += checkSurroundingStone(curGame, allFields, 1, 2); //below
            curGame->y -= 1;
            curGame->curPlayer = killingPlayer;

            curGame->x += 2;
            killed += checkSurroundingStone(curGame, allFields, 2, 1); //right
            curGame->x -= 2;
            curGame->curPlayer = killingPlayer;

            return killed;

        }
        else if (curGame->x == curGame->insideBoardCords[1] - 1) { //x = lastColumn

            curGame->x -= 2;
            killed += checkSurroundingStone(curGame, allFields, 0, 1);//left
            curGame->x += 2;
            curGame->curPlayer = killingPlayer;

            curGame->y += 1;
            killed += checkSurroundingStone(curGame, allFields, 1, 2); //below
            curGame->y -= 1;
            curGame->curPlayer = killingPlayer;

            return killed;

        }
        else { //firstColumn < x < lastColumn

            curGame->y += 1;
            killed += checkSurroundingStone(curGame, allFields, 1, 2); //below
            curGame->y -= 1;
            curGame->curPlayer = killingPlayer;

            curGame->x -= 2;
            killed += checkSurroundingStone(curGame, allFields, 0, 1);//left
            curGame->x += 2;
            curGame->curPlayer = killingPlayer;

            curGame->x += 2;
            killed += checkSurroundingStone(curGame, allFields, 2, 1); //right
            curGame->x -= 2;
            curGame->curPlayer = killingPlayer;

            return killed;

        }
    }
    else if (curGame->y == curGame->insideBoardCords[3]) { //y = lastRow
        if (curGame->x == curGame->insideBoardCords[0] + 1) {//x = firstColumn

            curGame->y -= 1;
            killed += checkSurroundingStone(curGame, allFields, 1, 0);//above
            curGame->y += 1;
            curGame->curPlayer = killingPlayer;

            curGame->x += 2;
            killed += checkSurroundingStone(curGame, allFields, 2, 1); //right
            curGame->x -= 2;
            curGame->curPlayer = killingPlayer;

            return killed;
        }
        else if (curGame->x == curGame->insideBoardCords[1] - 1) {//x = last column

            curGame->y -= 1;
            killed += checkSurroundingStone(curGame, allFields, 1, 0);//above
            curGame->y += 1;
            curGame->curPlayer = killingPlayer;

            curGame->x -= 2;
            killed += checkSurroundingStone(curGame, allFields, 0, 1);//left
            curGame->x += 2;
            curGame->curPlayer = killingPlayer;

            return killed;
        }
        else {                                                  // firstColumn<x<lastColumn

            curGame->y -= 1;
            killed += checkSurroundingStone(curGame, allFields, 1, 0);//above
            curGame->y += 1;
            curGame->curPlayer = killingPlayer;

            curGame->x -= 2;
            killed += checkSurroundingStone(curGame, allFields, 0, 1);//left
            curGame->x += 2;
            curGame->curPlayer = killingPlayer;

            curGame->x += 2;
            killed += checkSurroundingStone(curGame, allFields, 2, 1); //right
            curGame->x -= 2;
            curGame->curPlayer = killingPlayer;

            return killed;
        }
    }
    else { //firstRow < y < lastRow
        if (curGame->x == curGame->insideBoardCords[0] + 1) {         // x = first column

            curGame->y -= 1;
            killed += checkSurroundingStone(curGame, allFields, 1, 0);//above
            curGame->y += 1;
            curGame->curPlayer = killingPlayer;

            curGame->y += 1;
            killed += checkSurroundingStone(curGame, allFields, 1, 2); //below
            curGame->y -= 1;
            curGame->curPlayer = killingPlayer;

            curGame->x += 2;
            killed += checkSurroundingStone(curGame, allFields, 2, 1); //right
            curGame->x -= 2;
            curGame->curPlayer = killingPlayer;

            return killed;

        }
        else if (curGame->x == curGame->insideBoardCords[1] - 1) {    //x = last column

            curGame->y -= 1;
            killed += checkSurroundingStone(curGame, allFields, 1, 0);//above
            curGame->y += 1;
            curGame->curPlayer = killingPlayer;

            curGame->y += 1;
            killed += checkSurroundingStone(curGame, allFields, 1, 2); //below
            curGame->y -= 1;
            curGame->curPlayer = killingPlayer;

            curGame->x += 2;
            killed += checkSurroundingStone(curGame, allFields, 2, 1); //right
            curGame->x -= 2;
            curGame->curPlayer = killingPlayer;

            return killed;
        }
        else {                                                        // firstColumn<x<lastColumn

            curGame->y -= 1;
            killed += checkSurroundingStone(curGame, allFields, 1, 0);//above
            curGame->y += 1;
            curGame->curPlayer = killingPlayer;

            curGame->y += 1;
            killed += checkSurroundingStone(curGame, allFields, 1, 2); //below
            curGame->y -= 1;
            curGame->curPlayer = killingPlayer;

            curGame->x += 2;
            killed += checkSurroundingStone(curGame, allFields, 2, 1); //right
            curGame->x -= 2;
            curGame->curPlayer = killingPlayer;

            curGame->x -= 2;
            killed += checkSurroundingStone(curGame, allFields, 0, 1);//left
            curGame->x += 2;
            curGame->curPlayer = killingPlayer;

            return killed;
        }
    }
}

void freeFieldSlot(gameInfoT* curGame, fieldT* allFields){                              // remove stones after move/kill
    for (int i = 0; i < (curGame->totalFieldsOnWidth * curGame->totalBoardHeight); i++) {
        if (curGame->fieldsToRemove[i] < curGame->totalBoardField) {
            allFields[i].belongsTo = 'N';
        }
    }
}

fieldT* allocateAllFieldsMemory(gameInfoT* curGame) {                                   //Create an array of structures, where every structure is a Field. x=displayX, y=displayY, belongsTo=Player/None
    fieldT* allFields = (fieldT*)malloc((curGame->totalBoardHeight * curGame->totalFieldsOnWidth) * sizeof(fieldT));

    int tempY = 1, tempX = 1, counter = 0;
    for (int i = 0; i < (curGame->totalBoardHeight * curGame->totalFieldsOnWidth); i++) {
        if (counter == 9) {
            counter = 0;
            tempY += 1;
            tempX = 1;
        }
        allFields[i].x = tempX;
        allFields[i].y = tempY;
        allFields[i].belongsTo = 'N';
        tempX += 1;
        counter += 1;
    }

    return allFields;                                                                     //returns a pointer to array
}

void initiateToRemoveMemory(int* ptrMem, gameInfoT* curGame) {                                    //initMemory for field removal
    for (int i = 0; i < (curGame->totalFieldsOnWidth * curGame->totalBoardHeight); i++) {
        ptrMem[i] = curGame->totalBoardField;
    }
}

bool checkKORule(gameInfoT* curGame, char p) { //true <=> repetition false<=>good
    if (p == 'W') {
        if (getFieldIndex(curGame->displayX - 1, curGame->displayY - 1, curGame->totalFieldsOnWidth) == curGame->lastlyPlacedStoneIndexWhite) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (p == 'B') {
        if (getFieldIndex(curGame->displayX - 1, curGame->displayY - 1, curGame->totalFieldsOnWidth) == curGame->lastlyPlacedStoneIndexBlack) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        exit(BADPEER);
    }
}

void writeToFile(gameInfoT* curGame, char* fileName, fieldT* allFields, int nStones) { //FILE STRUCTURE: 1)alwaysFirstFour: boardWidth, boardHeight, lastWhiteStone, lastBlackStone  2)[StoneIndex][Player] ....
    FILE* f;
    f = fopen(fileName, "wb");
    if (f == NULL) {
        clrscr();
        exit(BADFILE);
    }
    else {
        int alwaysFirstFour[4] = { curGame->totalFieldsOnWidth, curGame->totalBoardHeight,curGame->lastlyPlacedStoneIndexWhite, curGame->lastlyPlacedStoneIndexBlack };
        fwrite(alwaysFirstFour, 4*sizeof(int), 1, f);

        if (curGame->placedStones == NULL) {
            fwrite( "K", sizeof(char), 1, f);
        }
        else {
            for (int i = 0; i < nStones; i++) {
                fwrite(&(curGame->placedStones[i]), sizeof(int), 1, f);                                 //write field index of allfields 
                fwrite(&(allFields[curGame->placedStones[i]].belongsTo), sizeof(char), 1, f);           //write it's player
            }
        }         
    }
    fclose(f);   
}

void saveGameState(gameInfoT* curGame, fieldT* allFields) {
    int stonesOnBoard = 0, xLegend, k = 0;
    for (int i = 0; i < (curGame->totalBoardHeight * curGame->totalFieldsOnWidth); i++) {               //count stones on Board
        if (allFields[i].belongsTo != 'N') {
            stonesOnBoard += 1;
        }
    }
    if (stonesOnBoard == 0) {   
        curGame->placedStones=NULL;
    }
    else{
        curGame->placedStones = (int*)malloc(sizeof(int) * stonesOnBoard);
        for (int j = 0; j < (curGame->totalBoardHeight * curGame->totalFieldsOnWidth); j ++) {          //save stone indexes from allFields
            if (allFields[j].belongsTo != 'N') {
                curGame->placedStones[k] = j;
                k += 1;
            }
        }
    }
    if (curGame->boardSide == 'R') {
        xLegend = 2;
    }
    else if (curGame->boardSide == 'L') {
        xLegend = curGame->totalBoardWidth + 10;
    }
    else {
        exit(BADBOARD);
    }

    gotoxy(xLegend, underTheLegendY);
    cputs("Type desired File Name: ");
    short i = 0;
    char* fileName = (char*)malloc(sizeof(char)*256); //max on Windows
    char x; 
    do {
        x = (char)getche();
        fileName[i] = x;
        i++;
    } while (x != keyENTER);                           //Get fileName
    fileName[i - 1] = 0;
    writeToFile(curGame, fileName, allFields, k);
    free(fileName);
    clrscr();
  
}

void loadGameState(char* fileName, gameInfoT* curGame) { //file structure: one liner: FieldsOnWidth FieldsOnHeight LastPlacedBlack LastPlacedWhite [index of Field in allFields]'<=>'Player.....
    FILE* f = fopen(fileName, "rb");
    if (f == NULL) {
        clrscr();
        gotoxy(1, 1);
        cputs("Sorry Bad File Name try again Later. \n");
        exit(BADFILE);
    }
    else {
        int alwaysFirstFour[4] = {};
        fread(alwaysFirstFour, 4 * sizeof(int), 1, f);
        curGame->totalFieldsOnWidth = alwaysFirstFour[0];
        curGame->totalBoardHeight = alwaysFirstFour[1];
        curGame->lastlyPlacedStoneIndexWhite = alwaysFirstFour[2];
        curGame->lastlyPlacedStoneIndexBlack = alwaysFirstFour[3];
        curGame->totalBoardWidth = 2 * (curGame->totalFieldsOnWidth) + 1;
        curGame->totalBoardField = (curGame->totalBoardHeight * curGame->totalBoardWidth);
        fieldT* allFieldsPtr = allocateAllFieldsMemory(curGame);
        if (curGame->lastlyPlacedStoneIndexBlack == (-1) && curGame->lastlyPlacedStoneIndexWhite == (-1)) { // If no moves were made board empty
            curGame->carryPtrAfterLoading = allFieldsPtr;                                           //assign Values to allFIelds
            allocateMemoryStaticBoard(curGame);
            initStaticBoard(curGame);
            
            fclose(f);
        }
        else {
            for (int j = 0; j < curGame->totalBoardHeight * curGame->totalFieldsOnWidth; j++) {
                int tempIndBuf;
                char tempPlrBuf;
                fread(&tempIndBuf, sizeof(int), 1, f);
                fread(&tempPlrBuf, sizeof(char), 1, f);
                allFieldsPtr[tempIndBuf].belongsTo = tempPlrBuf;                                    //assign stones from file to allFIelds dynamic stone board
            }
            curGame->carryPtrAfterLoading = allFieldsPtr;                                           //assign Values to allFIelds
            allocateMemoryStaticBoard(curGame);
            initStaticBoard(curGame);
            curGame->firstMove = 0;
            fclose(f);

        }       
    }
}


int main() {
	gameInfoT curGame;
	gameInfoT *giPtr = &curGame;

    fieldT* allFields = NULL;
    
#ifndef __cplusplus
	gameInfo_t curGame;
	Conio2_Init();
#endif

	settitle("Jakub, Szurmak, 193095");
	
	_setcursortype(_NOCURSOR);

	do {
		
		if (curGame.begin == 1) {
			curGame = {};
            if (startBoardMenu(giPtr)) {
                allFields = giPtr->carryPtrAfterLoading;
                curGame.fieldsToRemove = (int*)malloc(sizeof(int) * (curGame.totalFieldsOnWidth * curGame.totalBoardHeight));
                preparePrintingBySide(giPtr);
                clrscr();
            }
            else {
                allFields = allocateAllFieldsMemory(giPtr);
                preparePrintingBySide(giPtr);
                curGame.fieldsToRemove = (int*)malloc(sizeof(int) * (curGame.totalFieldsOnWidth * curGame.totalBoardHeight));
                clrscr();
            }       
		}
		else if (curGame.begin == 0) {
			displayMainMenu(giPtr);	
            
            initStaticBoard(giPtr);
            textcolor(WHITE);
            textbackground(MAGENTA);
            printFrame(giPtr);

            textcolor(BLACK);
            textbackground(BROWN);
            printBoard(giPtr, allFields);

            gotoxy(giPtr->x, giPtr->y);
            putch('X');
		
			textcolor(WHITE);
			textbackground(BLACK);

            giPtr->zero = 0;
            giPtr->zn = getch();
			

            if (giPtr->zn == 0) {
                giPtr->zero = 1;		// if this is the case then we read
                giPtr->zn = getch();		// the next code knowing that this
				if (giPtr->zn == keyArrowUp) {
					if (giPtr->insideBoardCords[2] < giPtr->y) {
                        giPtr->y--;
                        giPtr->displayY--;
					}
					else {
						continue;
					}
				}
					// will be a special key
				else if (giPtr->zn == keyArrowDown) {
					if (giPtr->insideBoardCords[3] > giPtr->y) {
						giPtr->y++;
                        giPtr->displayY++;
					}
					else {
						continue;
					}
				} 
				else if (giPtr->zn == keyArrowLeft) {
					if (giPtr->insideBoardCords[0]+1 < giPtr->x) {
                        giPtr->x -= 2;
                        giPtr->displayX--;
					}
					else {
						continue;
					}
				} 
				else if (giPtr->zn == keyArrowRight) {
					if (giPtr->insideBoardCords[1] - 2 > giPtr->x) {
                        giPtr->x += 2;
                        giPtr->displayX++;
					}
					else {
						continue;
					}
				}
			}
            else if (giPtr->zn == keyK) {
                if ((giPtr->firstMove == 1) && (giPtr->handicapFlag == 0)) {
                    giPtr->handicapFlag = 1;
                    giPtr->handicapApproved = 0;
                }
                else if (giPtr->handicapFlag == 1) {
                    giPtr->handicapFlag = 0;
                    giPtr->handicapApproved = 1;
                    giPtr->firstMove = 0;
                    giPtr->curPlayer = 'W';
                }
                else {
                    continue;
                }

            }
			else if (giPtr->zn == keyN) {
				clrscr();
				free(giPtr->startBoard);
                free(giPtr->fieldsToRemove);
                free(allFields);
                giPtr->begin = 1;
				continue;
            }

            else if (giPtr->zn == keyS) {
                saveGameState(giPtr, allFields);
            }
            else if (giPtr->zn == keyI) {
                if (giPtr->handicapFlag != 1) {
                    giPtr->firstMove = 0;
                }    
                if (approveYourMoveQuestion(giPtr) == true) {
                    if (giPtr->handicapFlag == 1) {
                        if (insertStone(giPtr, allFields) != true) {
                            continue;
                        }
                    }
                    else {
                        initiateToRemoveMemory(giPtr->fieldsToRemove, giPtr);
                        if (insertStone(giPtr, allFields) == true) {

                            const int killed = checkForKill(giPtr, allFields);
                            if (killed > 0) {           
                                if (giPtr->curPlayer == 'B') {
                                    giPtr->lastlyPlacedStoneIndexBlack = getFieldIndex(giPtr->displayX - 1, giPtr->displayY - 1, giPtr->totalFieldsOnWidth);
                                    giPtr->curPlayer = 'W';
                                    freeFieldSlot(giPtr, allFields);
                                }
                                else {
                                    giPtr->lastlyPlacedStoneIndexWhite = getFieldIndex(giPtr->displayX - 1, giPtr->displayY - 1, giPtr->totalFieldsOnWidth);
                                    giPtr->curPlayer = 'B';
                                    freeFieldSlot(giPtr, allFields);
                                }
                            }
                            else {
                                if (giPtr->curPlayer == 'B') {
                                    giPtr->lastlyPlacedStoneIndexBlack = getFieldIndex(giPtr->displayX - 1, giPtr->displayY - 1, giPtr->totalFieldsOnWidth);
                                    giPtr->curPlayer = 'W';
                                    continue;
                                 
                                }
                                else {                           
                                    giPtr->lastlyPlacedStoneIndexWhite = getFieldIndex(giPtr->displayX - 1, giPtr->displayY - 1, giPtr->totalFieldsOnWidth);
                                    giPtr->curPlayer = 'B';
                                    continue;                         
                                }
                            }
                        }
                    }
                }			
			}
		}
	} while (giPtr->zn != keyQ);
	clrscr();
    free(giPtr->startBoard);
    free(giPtr->fieldsToRemove);
    free(allFields);
	_setcursortype(_NORMALCURSOR);	
	
	return 0;
}
