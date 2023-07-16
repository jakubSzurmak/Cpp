#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <direct.h>

extern "C" {
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
}

#define CREATIONERROR -111
#define INITERROR -222
#define BADPARAMETER -333
#define BADFILE -444
#define OK 0

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define FULLSCREEN 1
#define NOFULLSCREEN 0

#define SEGMENTHEIGHT SCREEN_HEIGHT/3
#define SEGMENT1 1111
#define SEGMENT2 2222
#define SEGMENT3 3333
#define SEGMENT4 4444

#define PLAYERY SCREEN_HEIGHT-SEGMENTHEIGHT
#define PLAYERWIDTH 26
#define PLAYERHEIGHT 59

#define TOTALSEGMENTITEMS 12

#define MAXWIDTHLEFTGRASS SCREEN_WIDTH/6
#define MAXWIDTHRIGHTGRASS SCREEN_WIDTH/6
#define MAXWIDTHMIDDLEGRASS SCREEN_WIDTH/4

#define MINWIDTHLEFTGRASS SCREEN_WIDTH/14
#define MINWIDTHRIGHTGRASS SCREEN_WIDTH/12
#define MINWIDTHMIDDLEGRASS SCREEN_WIDTH/14

#ifdef __cplusplus
extern "C"
#endif

struct timeData {
	int t1 = 0;
	int t2 = 0;
	int t2Load = 0;
	int t3 = 0;
	int t4 = 0;
	double tLoad = 0;
	double worldTime = 0;
	double delta = 0;
};

struct frameDisposal {
	double frames = 0;
	double fpsTimer = 0;
	double fps = 0;
	char text[64] = {};
	char fileName[64] = {};
	short activePage = 1;
	double pagesTotal = 0;
	short activeFile = 0;
	short filesTotal = 0; 	
	short fileRangeInArrayStart = 0;
	short fileRangeInArrayEnd = 5;
	int BLACK = 0;
	int WHITE = 0;
	int RED = 0;
	int DARKRED = 0;
	int GREEN = 0;
	int BLUE = 0;
	SDL_Rect* ptr_topInfoBoxRect = NULL;
	SDL_Rect* ptr_bottomInfoBoxRect = NULL; 
};

struct gameFlow { // Y = Yes, N = No
	char quit = 'N';
	double score = 0;
	char over = 'N';
	char pause = 'N';
	char alive = 'Y';
	char loadScreen = 'N';
	char beginLoading = 'N';
	char gameLoaded = 'N';
	char beginSaving = 'N';
	char finished = 'N';
	char begining = 'Y';
	char beginingAfterLoading = 'N';
	char newGameFlag = 'N';
	char playerLeft = 'N';
	char playerRight = 'N';
	char playerUp = 'N';
	short distanceY = 0; 
	short ndDistanceY = 0;
	short distanceX = 0;
	const short speed = 1;
};

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt œrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface* p_ptr_screen, SDL_Surface* p_ptr_sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - p_ptr_sprite->w / 2;
	dest.y = y - p_ptr_sprite->h / 2;
	dest.w = p_ptr_sprite->w;
	dest.h = p_ptr_sprite->h;
	SDL_BlitSurface(p_ptr_sprite, NULL, p_ptr_screen, &dest);
};

//draw text on screen
void DrawString(SDL_Surface* p_ptr_screen, int x, int y, const char* text, SDL_Surface* p_ptr_charset, SDL_Rect* p_ptr_PasteTo, SDL_Renderer* p_ptr_renderer) {
	static SDL_Texture* charsetTxt = SDL_CreateTextureFromSurface(p_ptr_renderer, p_ptr_charset);
	int px, py, c;
	SDL_Rect source, destination;
	source.w = 8;
	source.h = 8;
	destination.w = 8;
	destination.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		source.x = px;
		source.y = py;
		destination.x = x;
		destination.y = y;
		SDL_RenderCopyEx(p_ptr_renderer, charsetTxt, &source, &destination, 0, 0, SDL_FLIP_NONE);
		x += 8;
		text++;
	};
};

//generate pseudo-random number from min including to max including
short generateRand(const short incMax, const short incMin) {
	return ((rand() % (incMax - incMin + 1)) + incMin);
}

//edit textures rectangle struct with given x,y,w,h
SDL_Rect* editTextureRects(SDL_Rect* p_ptr_textureRect, const short p_x, const short p_y, const short p_w, const short p_h) {
	if (p_h == 1) {
		(p_ptr_textureRect)->x = p_x;
		(p_ptr_textureRect)->y = p_y;
		(p_ptr_textureRect)->w = p_w;
		(p_ptr_textureRect)->h = SEGMENTHEIGHT;
	}
	else if(p_h > 1){
		(p_ptr_textureRect)->x = p_x;
		(p_ptr_textureRect)->y = p_y;
		(p_ptr_textureRect)->w = p_w;
		(p_ptr_textureRect)->h = p_h;
	}
	else {
		(p_ptr_textureRect)->x = 0;
		(p_ptr_textureRect)->y = 0;
		(p_ptr_textureRect)->w = 0;
		(p_ptr_textureRect)->h = 0;
	}
	return p_ptr_textureRect;
}

//after enough of a drive we generate next segment to view
SDL_Rect* generateSegment4(const short p_segNo, const short p_boundIndex, SDL_Rect* p_ptr_boundRect) {
	unsigned short x = generateRand(MAXWIDTHRIGHTGRASS, MINWIDTHRIGHTGRASS);
	unsigned short y = generateRand(MAXWIDTHMIDDLEGRASS, MINWIDTHMIDDLEGRASS);
	switch (p_boundIndex)
	{
	case 0:
		editTextureRects(p_ptr_boundRect, 0, 0-SEGMENTHEIGHT, generateRand(MAXWIDTHLEFTGRASS, MINWIDTHLEFTGRASS), SEGMENTHEIGHT);
		return p_ptr_boundRect;
		break;
	case 1:
		editTextureRects(p_ptr_boundRect, ((SCREEN_WIDTH / 2) - (y / 2)), 0-SEGMENTHEIGHT, y, generateRand(1, 0));
		return p_ptr_boundRect;
		break;
	case 2:		
		//editTextureRects(p_boundRect, SCREEN_WIDTH, 0-SEGMENTHEIGHT, -1 * generateRand(MAXWIDTHRIGHTGRASS, 5), SEGMENTHEIGHT); 
		editTextureRects(p_ptr_boundRect, SCREEN_WIDTH-x, 0-SEGMENTHEIGHT, x, SEGMENTHEIGHT);
		return p_ptr_boundRect;
		break;
	default:
		return p_ptr_boundRect;
		break;
	}
	return p_ptr_boundRect;
}

//generate starting graphical and logic state
int initAndCreateFoundation(SDL_Surface** p_ptr_screen, SDL_Window** p_ptr_window, SDL_Renderer** p_ptr_renderer, frameDisposal* p_ptr_frameDisposal) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != OK) {	
		printf("SDL_Init error: %s\n", SDL_GetError());
		return INITERROR;
	}

	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, NOFULLSCREEN, p_ptr_window, p_ptr_renderer) != OK) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return CREATIONERROR;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(*p_ptr_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(*p_ptr_renderer, 0, 0, 0, 255);
	SDL_SetWindowTitle(*p_ptr_window, "SpyHunter");

	*p_ptr_screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	p_ptr_frameDisposal->BLACK = SDL_MapRGB((*p_ptr_screen)->format, 0x00, 0x00, 0x00);
	p_ptr_frameDisposal->WHITE = SDL_MapRGB((*p_ptr_screen)->format, 0xFF, 0xFF, 0xFF);
	p_ptr_frameDisposal->GREEN = SDL_MapRGB((*p_ptr_screen)->format, 0x00, 0xFF, 0x00);
	p_ptr_frameDisposal->RED = SDL_MapRGB((*p_ptr_screen)->format, 0xFF, 0x00, 0x00);
	p_ptr_frameDisposal->DARKRED = SDL_MapRGB((*p_ptr_screen)->format, 0x6E, 0x02, 0x02);
	p_ptr_frameDisposal->BLUE = SDL_MapRGB((*p_ptr_screen)->format, 0x11, 0x11, 0xCC);
	p_ptr_frameDisposal->ptr_bottomInfoBoxRect = editTextureRects(p_ptr_frameDisposal->ptr_bottomInfoBoxRect, 0, PLAYERY + 100, SCREEN_WIDTH, SCREEN_HEIGHT - (PLAYERY + 100));
	p_ptr_frameDisposal->ptr_topInfoBoxRect = editTextureRects(p_ptr_frameDisposal->ptr_topInfoBoxRect, 0, 0, SCREEN_WIDTH, SEGMENTHEIGHT / 3);

	return OK;
}

//setup bmp's as surface for further transfromation to texture
SDL_Surface* loadAndSetupBMPs(SDL_Surface** p_ptr_icon, char type) {
	if (type == 'P') {
		*p_ptr_icon = SDL_LoadBMP("../Debug/Textures/alivePlayer.bmp");
		return *p_ptr_icon;
	}
	else if (type == 'C') {
		*p_ptr_icon = SDL_LoadBMP("../Debug/Textures/cs8x8.bmp");
		return *p_ptr_icon;
	}
	else if (type == 'S') {
		*p_ptr_icon = SDL_LoadBMP("../Debug/Textures/leftRightBound.bmp");
		return *p_ptr_icon;
	}
	else if (type == 'D') {
		*p_ptr_icon = SDL_LoadBMP("../Debug/Textures/deadPlayer.bmp");
		return *p_ptr_icon;
	}
	else {		
		exit(BADPARAMETER);
	}
	return NULL;
	
}

//check if number x is in range including min to inluding max
int inRange(const short min, const short max, const short x) {
	if ((x - min) * (x - max) <= 0) {
		return 1;
	}
	else {
		return 0;
	}
}

//check if front of user's car hit a wall
char checkFrontalCollision(SDL_Rect* p_ptr_texturePlayerRect, SDL_Rect* p_ptr_s2Side, const char sideDeterminant) {
	if (sideDeterminant == 'L') {
		if (p_ptr_texturePlayerRect->y == (p_ptr_s2Side->y + SEGMENTHEIGHT)) {
			if (inRange(p_ptr_s2Side->x, (p_ptr_s2Side->x + p_ptr_s2Side->w), p_ptr_texturePlayerRect->x)) {
				return 'Y';
			}
		}
		return 'N';
	}
	else if (sideDeterminant == 'R') {
		if (p_ptr_texturePlayerRect->y == (p_ptr_s2Side->y + SEGMENTHEIGHT)) {
			if (inRange(p_ptr_s2Side->x, (p_ptr_s2Side->x + p_ptr_s2Side->w), (p_ptr_texturePlayerRect->x + p_ptr_texturePlayerRect->w))) {
				return 'Y';
			}
		}
		return 'N';
	}
	else if (sideDeterminant == 'M') {
		if (p_ptr_texturePlayerRect->y == (p_ptr_s2Side->y + SEGMENTHEIGHT)) {
			if (inRange(p_ptr_s2Side->x, (p_ptr_s2Side->x + p_ptr_s2Side->w), p_ptr_texturePlayerRect->x)) {
				return 'Y';
			}
			else if (inRange(p_ptr_s2Side->x, (p_ptr_s2Side->x + p_ptr_s2Side->w), (p_ptr_texturePlayerRect->x + p_ptr_texturePlayerRect->w))) {
				return 'Y';
			}
		}
		return 'N';
	}
	else {
		exit(BADPARAMETER);		
	}
}

//check if right side of user's car hit a wall
char checkByRightCollision(SDL_Rect* p_ptr_texturePlayerRect, SDL_Rect* p_ptr_s1Side, SDL_Rect* p_ptr_s2Side) {
	if (p_ptr_s1Side->y > (p_ptr_texturePlayerRect->y + PLAYERHEIGHT)) {
		if ((p_ptr_texturePlayerRect->x + p_ptr_texturePlayerRect->w) == p_ptr_s2Side->x) {
			return 'Y';
		}
	}
	else {
		if ((p_ptr_texturePlayerRect->x + p_ptr_texturePlayerRect->w) == p_ptr_s1Side->x) {
			return 'Y';
		}
		else if ((p_ptr_texturePlayerRect->x + p_ptr_texturePlayerRect->w) == p_ptr_s2Side->x) {
			return 'Y';
		}
	}
	return 'N';
}

//check if left side of user's car hit a wall
char checkByLeftCollision(SDL_Rect* p_ptr_texturePlayerRect, SDL_Rect* p_ptr_s1Side, SDL_Rect* p_ptr_s2Side) {
	if (p_ptr_s1Side->y > (p_ptr_texturePlayerRect->y + PLAYERHEIGHT)) {
		if (p_ptr_texturePlayerRect->x == (p_ptr_s2Side->x + p_ptr_s2Side->w)) {
			return 'Y';
		}
	}
	else {
		if (p_ptr_texturePlayerRect->x == (p_ptr_s1Side->x + p_ptr_s1Side->w)) {
			return 'Y';
		}
		else if (p_ptr_texturePlayerRect->x == (p_ptr_s2Side->x + p_ptr_s2Side->w)) {
			return 'Y';
		}

	}
	return 'N';
}

//call above specialized functions
char detectCollision(SDL_Rect* p_ptr_texturePlayerRect, gameFlow* p_ptr_gameFlow, SDL_Rect** p_ptr_textureRects) {
	//leftbound lefthit
	
	if (checkFrontalCollision(p_ptr_texturePlayerRect, p_ptr_textureRects[5], 'R') == 'Y') { //from front on right
		p_ptr_gameFlow->alive = 'N';
		return 'Y';
	}
	if (checkFrontalCollision(p_ptr_texturePlayerRect, p_ptr_textureRects[3], 'L') == 'Y') {//from front on left
		p_ptr_gameFlow->alive = 'N';
		return 'Y';
	}
	if (checkFrontalCollision(p_ptr_texturePlayerRect, p_ptr_textureRects[4], 'M') == 'Y') {//from front on left
		p_ptr_gameFlow->alive = 'N';
		return 'Y';
	}
	if (checkByRightCollision(p_ptr_texturePlayerRect, p_ptr_textureRects[2], p_ptr_textureRects[5]) == 'Y') {//Right
		p_ptr_gameFlow->alive = 'N';
		return 'Y';
	}
	if (checkByRightCollision(p_ptr_texturePlayerRect, p_ptr_textureRects[1], p_ptr_textureRects[4]) == 'Y') {//Mid
		p_ptr_gameFlow->alive = 'N';
		return 'Y';
	}
	if (checkByLeftCollision(p_ptr_texturePlayerRect, p_ptr_textureRects[0], p_ptr_textureRects[3]) == 'Y') {//left
		p_ptr_gameFlow->alive = 'N';
		return 'Y';
	}
	if (checkByLeftCollision(p_ptr_texturePlayerRect, p_ptr_textureRects[1], p_ptr_textureRects[4]) == 'Y') {//left
		p_ptr_gameFlow->alive = 'N';
		return 'Y';
	}
	return 'N';
}
	
//background goes down while holding arrowUp key
void scrollBackgroundByDriving(gameFlow* p_ptr_gameFlow, SDL_Rect** p_ptr_textureRects) {
	
	for (int i = 0; i < 12; i++) {
		p_ptr_textureRects[i]->y += p_ptr_gameFlow->speed;
	}
	p_ptr_gameFlow->ndDistanceY += 1;

}

//move player's icon left and right depending on the arrowKey held
void leftRightMoveHandling(gameFlow* p_ptr_gameFlow, SDL_Rect* p_ptr_texturePlayerRect, SDL_Rect** p_ptr_textureRects) {

	if (p_ptr_gameFlow->playerLeft == 'Y') {
		p_ptr_texturePlayerRect->x -= p_ptr_gameFlow->speed;
	}
	if (p_ptr_gameFlow->playerRight == 'Y') {
		p_ptr_texturePlayerRect->x += p_ptr_gameFlow->speed;
	}
}

//!Must for understanding collisions!
//screen is divided into 3 visible and 1 logical segment numbered from the bottom up: 1,2,3,4 
//as background drops down to SEGMENT_HEIGHT-1 we interchange the segments with new ones without the need to create 9 new textures
//so when segment1 goes off screen we do:
//1.Segment1=Segment2 2.Segment2=Segment3 3.Segment3=Segment4 4.Generate new Segment4
//player is positioned in such way that he can colide on the sides wight segment1 and segment2
//on the middle as we start off without a middle lane the player can colide with segment2 and segment3
//because the middle starts to generate 1 segment later than the sides
void interchangeSegments(SDL_Rect** p_ptr_textureRects, gameFlow* p_ptr_gameFlow) { // &s1Rect0, & s1Rect1, & s1Rect2, & s2Rect0, & s2Rect1, & s2Rect2, & s3Rect0, & s3Rect1, & s3Rect2, & s4Rect0, & s4Rect1, & s4Rect2};
	for (short i = 0; i < 9; i++) {
		editTextureRects(p_ptr_textureRects[i], p_ptr_textureRects[i + 3]->x, p_ptr_textureRects[i + 3]->y, p_ptr_textureRects[i + 3]->w, p_ptr_textureRects[i + 3]->h);
	}
	generateSegment4(SEGMENT4, 0, p_ptr_textureRects[9]);
	generateSegment4(SEGMENT4, 1, p_ptr_textureRects[10]);
	generateSegment4(SEGMENT4, 2, p_ptr_textureRects[11]);

}

//call specialized functions and control the speed
void moveBasedOnEvents(gameFlow* p_ptr_gameFlow, SDL_Rect* p_ptr_texturePlayerRect, SDL_Rect** p_ptr_textureRects) {
	if (p_ptr_gameFlow->playerUp != 'N') {
		p_ptr_gameFlow->distanceY += 1;
		p_ptr_gameFlow->score += 0.03;
		
		if ((p_ptr_gameFlow->distanceY) % 8 == 0) {	
			p_ptr_gameFlow->distanceY = 1;
			if (p_ptr_gameFlow->ndDistanceY == SEGMENTHEIGHT-1) {
				interchangeSegments(p_ptr_textureRects, p_ptr_gameFlow);
				
				p_ptr_gameFlow->ndDistanceY = 0;
			}
			scrollBackgroundByDriving(p_ptr_gameFlow, p_ptr_textureRects);
			
			if (detectCollision(p_ptr_texturePlayerRect, p_ptr_gameFlow, p_ptr_textureRects) != 'N') {
				p_ptr_gameFlow->alive = 'N';
			}
		}		
	}
	if ((p_ptr_gameFlow->playerLeft != 'N') || (p_ptr_gameFlow->playerRight != 'N')) {
		p_ptr_gameFlow->distanceX += 1;
		if ((p_ptr_gameFlow->distanceX) % 6 == 0) {			
			leftRightMoveHandling(p_ptr_gameFlow, p_ptr_texturePlayerRect, p_ptr_textureRects);
			p_ptr_gameFlow->distanceX = 1;
			if (detectCollision(p_ptr_texturePlayerRect, p_ptr_gameFlow, p_ptr_textureRects) != 'N') {
				p_ptr_gameFlow->alive = 'N';
			}
			
		}		
	}
}

//handle pause event
int pauseAction(gameFlow* p_ptr_gameFlow, timeData* p_ptr_timeData) {
	if (p_ptr_gameFlow->finished != 'Y') {
		if (p_ptr_gameFlow->gameLoaded == 'Y') {
			if (p_ptr_gameFlow->alive == 'Y') {
				if (p_ptr_gameFlow->pause == 'N') {
					p_ptr_timeData->t3 = SDL_GetTicks() - p_ptr_timeData->t2Load;
					p_ptr_gameFlow->pause = 'Y';
					return 1;
				}
				else if ((p_ptr_gameFlow->pause == 'Y')) {
					p_ptr_timeData->t4 = SDL_GetTicks() - p_ptr_timeData->t2Load;
					p_ptr_timeData->worldTime -= (p_ptr_timeData->t4 - p_ptr_timeData->t3) * 0.001;
					p_ptr_gameFlow->pause = 'N';
					return 1;
				}
				else {
					return 1;
				}			
			}
		}
		else {
			if ((p_ptr_gameFlow->alive == 'Y') && (p_ptr_gameFlow->begining == 'N') && (p_ptr_gameFlow->finished != 'Y')) {
				if (p_ptr_gameFlow->pause == 'N') {
					p_ptr_timeData->t3 = SDL_GetTicks();
					p_ptr_gameFlow->pause = 'Y';
					return 1;
				}
				else if ((p_ptr_gameFlow->pause == 'Y')) {
					p_ptr_timeData->t4 = SDL_GetTicks();
					p_ptr_timeData->worldTime -= ((p_ptr_timeData->t4 - p_ptr_timeData->t3) * 0.001);
					p_ptr_gameFlow->pause = 'N';
					return 1;
				}
				else {
					return 1;
				}		
			}
			else {
				return 1;
			}		
		}
		return 1;
	}
	else {
		return 1;
	}
	
}

//handle esc event
int escAction(gameFlow* p_ptr_gameFlow, timeData* p_ptr_timeData, frameDisposal* p_ptr_frameDisposal) {
	if (p_ptr_gameFlow->loadScreen == 'Y') {
		if ((p_ptr_gameFlow->begining != 'Y') && (p_ptr_gameFlow->alive == 'Y')) {
			p_ptr_timeData->t4 = SDL_GetTicks();
			p_ptr_timeData->worldTime -= ((p_ptr_timeData->t4 - p_ptr_timeData->t3) * 0.001);
			p_ptr_timeData->t4 = 0;
			p_ptr_timeData->t3 = 0;
			p_ptr_gameFlow->loadScreen = 'N';
			p_ptr_frameDisposal->activeFile = 0;
			p_ptr_frameDisposal->activePage = 1;
			p_ptr_frameDisposal->fileRangeInArrayStart = 0;
			p_ptr_frameDisposal->fileRangeInArrayEnd = 5;
			return 1;
		}
		else {
			p_ptr_gameFlow->loadScreen = 'N';
			p_ptr_frameDisposal->activeFile = 0;
			p_ptr_frameDisposal->activePage = 1;
			p_ptr_frameDisposal->fileRangeInArrayStart = 0;
			p_ptr_frameDisposal->fileRangeInArrayEnd = 5;
			return 1;
		}
	}
	else {
		p_ptr_gameFlow->quit = 'Y';
		return 1;
	}	
}

//handle arrowDown event
int arrowDownAction(gameFlow* p_ptr_gameFlow, frameDisposal* p_ptr_frameDisposal) {
	if (p_ptr_gameFlow->loadScreen == 'Y') {
		if (p_ptr_frameDisposal->activeFile != 0) {
			if ((p_ptr_frameDisposal->activeFile % 5 != 0) && (p_ptr_frameDisposal->filesTotal - 1 != p_ptr_frameDisposal->activeFile)) {
				p_ptr_frameDisposal->activeFile += 1;
				return 1;
			}
			return 1;
		}
		else {
			p_ptr_frameDisposal->activeFile += 1;
			return 1;
		}
	}
	else {
		return 1;
	}
}

//handle arrowUp event
int arrowUpAction(gameFlow* p_ptr_gameFlow, timeData* p_ptr_timeData, frameDisposal* p_ptr_frameDisposal) {
	if (p_ptr_gameFlow->loadScreen == 'Y') {
		if (p_ptr_frameDisposal->activeFile != (p_ptr_frameDisposal->activePage - 1) * 6) {
			p_ptr_frameDisposal->activeFile -= 1;
			return 1;
		}
		else {
			return 1;
		}
	}
	else {
		if (p_ptr_gameFlow->playerUp == 'N') {
			if (p_ptr_gameFlow->begining == 'Y') {
				p_ptr_gameFlow->begining = 'N';
				p_ptr_timeData->t1 = SDL_GetTicks();
			}
			p_ptr_gameFlow->playerUp = 'Y';
			return 1;
		}
		else {
			return 1;
		}
	}
	
}

//handle arrowRight event
int arrowRightAction(gameFlow* p_ptr_gameFlow, frameDisposal* p_ptr_frameDisposal) {
	if (p_ptr_gameFlow->loadScreen == 'Y') {
		if (p_ptr_frameDisposal->activePage != p_ptr_frameDisposal->pagesTotal) {
			p_ptr_frameDisposal->activePage += 1;
			p_ptr_frameDisposal->fileRangeInArrayStart += 6;
			p_ptr_frameDisposal->fileRangeInArrayEnd += 6;
			p_ptr_frameDisposal->activeFile = (p_ptr_frameDisposal->activePage - 1) * 6;
			return 1;
		}
		else {
			return 1;
		}
	}
	else {
		if (p_ptr_gameFlow->playerRight == 'N') {
			p_ptr_gameFlow->playerRight = 'Y';
			return 1;
		}
		else {
			return 1;
		}
	}

}

//handle arrowLeft
int arrowLeftAction(gameFlow* p_ptr_gameFlow, frameDisposal* p_ptr_frameDisposal) {

	if (p_ptr_gameFlow->loadScreen == 'Y') {
		if (p_ptr_frameDisposal->activePage != 1) {
			p_ptr_frameDisposal->activePage -= 1;
			p_ptr_frameDisposal->fileRangeInArrayStart -= 6;
			p_ptr_frameDisposal->fileRangeInArrayEnd -= 6;
			p_ptr_frameDisposal->activeFile = (p_ptr_frameDisposal->activePage - 1) * 6;
			return 1;
		}
		else {
			return 1;
		}
	}
	else {
		if (p_ptr_gameFlow->playerLeft == 'N') {
			p_ptr_gameFlow->playerLeft = 'Y';
			return 1;
		}
		else {
			return 1;
		}
	}
}

//main event controller, calls above functions
void eventHandling(SDL_Event* p_ptr_event, gameFlow* p_ptr_gameFlow, SDL_Rect* p_ptr_texturePlayerRect, SDL_Rect** p_ptr_textureRects, timeData* p_ptr_timeData, frameDisposal* p_ptr_frameDisposal) {

	while (SDL_PollEvent(p_ptr_event)) {
		switch (p_ptr_event->type) {
			case SDL_KEYDOWN:
				switch (p_ptr_event->key.keysym.sym) {
					case SDLK_LEFT:
						if (arrowLeftAction(p_ptr_gameFlow, p_ptr_frameDisposal) == 1) {
							break;
						}
						else {
							break;
						}

					case SDLK_RIGHT:
						if (arrowRightAction(p_ptr_gameFlow, p_ptr_frameDisposal) == 1) {
							break;
						}
						else {
							break;
						}

					case SDLK_UP:
						if (arrowUpAction(p_ptr_gameFlow, p_ptr_timeData, p_ptr_frameDisposal) == 1) {
							break;
						}
						else {
							break;
						}

					case SDLK_DOWN:
						if (arrowDownAction(p_ptr_gameFlow, p_ptr_frameDisposal) == 1) {
							break;
						}
						else {
							break;
						}

					case SDLK_ESCAPE:	
						if (escAction(p_ptr_gameFlow, p_ptr_timeData, p_ptr_frameDisposal) == 1) {
							break;
						}
						else {
							break;
						}
						
					case SDLK_RETURN:
						if (p_ptr_gameFlow->loadScreen == 'Y') {
							p_ptr_gameFlow->gameLoaded = 'N';
							p_ptr_gameFlow->beginLoading = 'Y';
							p_ptr_gameFlow->loadScreen = 'N';
							break;
						}
						else {
							break;
						}
					case SDLK_n:
						if (p_ptr_gameFlow->newGameFlag == 'N') {
							p_ptr_gameFlow->newGameFlag = 'Y';
							break;
						}
						else {
							break;
						}
								
					case SDLK_p:
						if (pauseAction(p_ptr_gameFlow, p_ptr_timeData) == 1) {
							break;
						}
						else {
							break;
						}

					case SDLK_f:
						p_ptr_gameFlow->finished = 'Y';
						break;

					case SDLK_s:
						if (p_ptr_gameFlow->beginSaving != 'Y') {
							p_ptr_gameFlow->beginSaving = 'Y';
						}
						break;
													
					case SDLK_l:					
						if (p_ptr_gameFlow->loadScreen != 'Y') {				
							p_ptr_timeData->t3 = SDL_GetTicks();
							p_ptr_gameFlow->loadScreen = 'Y';
						}
						else {
							break;
						}
						
					default:
						break;
				}
				break;

			case SDL_KEYUP:
				switch (p_ptr_event->key.keysym.sym) {
					case SDLK_LEFT:
						p_ptr_gameFlow->playerLeft = 'N';
						break;

					case SDLK_RIGHT:
						p_ptr_gameFlow->playerRight = 'N';
						break;

					case SDLK_UP:
						p_ptr_gameFlow->playerUp = 'N';
						break;

					default:
						break;
				}
				break;

			case SDL_QUIT:
				p_ptr_gameFlow->quit = 'Y';
				break;

			default:
				break;
		}	
		break;
	};
}

//increment time by each game tick
void timeHandling(timeData* p_ptr_timeData, gameFlow* p_ptr_gameFlow, frameDisposal* p_ptr_frameDisposal) {	
	int temp;
	
	if (p_ptr_gameFlow->gameLoaded == 'Y') {
		temp = p_ptr_timeData->t2;
		p_ptr_timeData->t2 = SDL_GetTicks() - p_ptr_timeData->t2Load;
		p_ptr_timeData->delta = (p_ptr_timeData->t2 - p_ptr_timeData->t1) * 0.001;
		p_ptr_timeData->t1 = p_ptr_timeData->t2;
		p_ptr_timeData->worldTime += p_ptr_timeData->delta;
	}
	else {
		p_ptr_timeData->t2 = SDL_GetTicks();
		p_ptr_timeData->delta = (p_ptr_timeData->t2 - p_ptr_timeData->t1) * 0.001;
		p_ptr_timeData->t1 = p_ptr_timeData->t2;
		p_ptr_timeData->worldTime += p_ptr_timeData->delta;
	}

	p_ptr_frameDisposal->fpsTimer += p_ptr_timeData->delta;
	if (p_ptr_frameDisposal->fpsTimer > 0.5) {
		p_ptr_frameDisposal->fps = p_ptr_frameDisposal->frames * 2;
		p_ptr_frameDisposal->frames = 0;
		p_ptr_frameDisposal->fpsTimer -= 0.5;
	};
	
}

//render background textures on screen, Background is the sides that we can colide with and the middle lane, the 'road' that we 
//drive on is a solid color and it doesn't move
void renderBackground(SDL_Renderer* p_ptr_renderer, SDL_Rect** p_ptr_textureRects, SDL_Texture* p_ptr_txtLeftRightBound) {
	for (int i = 0; i < TOTALSEGMENTITEMS; i++) {
		SDL_RenderCopy(p_ptr_renderer, p_ptr_txtLeftRightBound, NULL , p_ptr_textureRects[i]);
	}
}

//put text into the upper box of the window
void fillTopInfoBox(SDL_Renderer* p_ptr_renderer, gameFlow* p_ptr_gameFlow, SDL_Surface* p_ptr_charset, SDL_Surface* p_ptr_screen, frameDisposal* p_ptr_frameDisposal, timeData* p_ptr_timeData) {
	SDL_SetRenderDrawColor(p_ptr_renderer, 80, 0, 0, 255);
	SDL_RenderDrawRect(p_ptr_renderer, p_ptr_frameDisposal->ptr_topInfoBoxRect);
	SDL_RenderFillRect(p_ptr_renderer, p_ptr_frameDisposal->ptr_topInfoBoxRect);


	sprintf(p_ptr_frameDisposal->text, "PLAYING TIME: %.1lfs", p_ptr_timeData->worldTime);
	DrawString(p_ptr_screen, 15, p_ptr_frameDisposal->ptr_topInfoBoxRect->h / 2, p_ptr_frameDisposal->text, p_ptr_charset, p_ptr_frameDisposal->ptr_topInfoBoxRect, p_ptr_renderer);

	sprintf(p_ptr_frameDisposal->text, "SCORE: %.0lf", p_ptr_gameFlow->score);
	//sprintf(p_ptr_frameDisposal->text, "SDL: %lf", p_ptr_frameDisposal->fps);
	DrawString(p_ptr_screen, ((SCREEN_WIDTH / 2) - 4 * (int)strlen(p_ptr_frameDisposal->text)), p_ptr_frameDisposal->ptr_topInfoBoxRect->h / 2, p_ptr_frameDisposal->text, p_ptr_charset, p_ptr_frameDisposal->ptr_topInfoBoxRect, p_ptr_renderer);

	sprintf(p_ptr_frameDisposal->text, "Jakub Szurmak 193095");
	DrawString(p_ptr_screen, (SCREEN_WIDTH - (8 * (int)strlen(p_ptr_frameDisposal->text) + 15)), p_ptr_frameDisposal->ptr_topInfoBoxRect->h / 2, p_ptr_frameDisposal->text, p_ptr_charset, p_ptr_frameDisposal->ptr_topInfoBoxRect, p_ptr_renderer);
}

//put text into the bottom box of the window
void fillBottomInfoBox(SDL_Renderer* p_ptr_renderer, gameFlow* p_ptr_gameFlow, SDL_Surface* p_ptr_charset, SDL_Surface* p_ptr_screen, frameDisposal* p_ptr_frameDisposal, timeData* p_ptr_timeData) {
	
	SDL_SetRenderDrawColor(p_ptr_renderer, 80, 0, 0, 255);
	SDL_RenderDrawRect(p_ptr_renderer, p_ptr_frameDisposal->ptr_bottomInfoBoxRect);
	SDL_RenderFillRect(p_ptr_renderer, p_ptr_frameDisposal->ptr_bottomInfoBoxRect);

	sprintf(p_ptr_frameDisposal->text, "a) b) c) d) e)");
	DrawString(p_ptr_screen, (SCREEN_WIDTH - (8 * (int)strlen(p_ptr_frameDisposal->text) + 15)), (SCREEN_HEIGHT-( p_ptr_frameDisposal->ptr_bottomInfoBoxRect->h / 2)-8), p_ptr_frameDisposal->text, p_ptr_charset, p_ptr_frameDisposal->ptr_topInfoBoxRect, p_ptr_renderer);
	sprintf(p_ptr_frameDisposal->text, "f) g) h) i)");
	DrawString(p_ptr_screen, (SCREEN_WIDTH - (8 * (int)strlen(p_ptr_frameDisposal->text) + 15)), (SCREEN_HEIGHT - (p_ptr_frameDisposal->ptr_bottomInfoBoxRect->h / 2)+4), p_ptr_frameDisposal->text, p_ptr_charset, p_ptr_frameDisposal->ptr_topInfoBoxRect, p_ptr_renderer);

	if (p_ptr_gameFlow->loadScreen == 'Y') {
		sprintf(p_ptr_frameDisposal->text, "..LOADING..");
		DrawString(p_ptr_screen, (SCREEN_WIDTH / 2) - (4 * (int)strlen(p_ptr_frameDisposal->text)), (SCREEN_HEIGHT - (p_ptr_frameDisposal->ptr_bottomInfoBoxRect->h / 2)), p_ptr_frameDisposal->text, p_ptr_charset, p_ptr_frameDisposal->ptr_bottomInfoBoxRect, p_ptr_renderer);
		sprintf(p_ptr_frameDisposal->text, "Next Page(RIGHT)");
		DrawString(p_ptr_screen, (SCREEN_WIDTH / 2) + (4 * (int)strlen(p_ptr_frameDisposal->text)), (SCREEN_HEIGHT - (p_ptr_frameDisposal->ptr_bottomInfoBoxRect->h / 2)), p_ptr_frameDisposal->text, p_ptr_charset, p_ptr_frameDisposal->ptr_bottomInfoBoxRect, p_ptr_renderer);
		sprintf(p_ptr_frameDisposal->text, "Previous Page(LEFT)");
		DrawString(p_ptr_screen, (SCREEN_WIDTH / 2) - (11 * (int)strlen(p_ptr_frameDisposal->text)), (SCREEN_HEIGHT - (p_ptr_frameDisposal->ptr_bottomInfoBoxRect->h / 2)), p_ptr_frameDisposal->text, p_ptr_charset, p_ptr_frameDisposal->ptr_bottomInfoBoxRect, p_ptr_renderer);
	}
	else {
		if (p_ptr_gameFlow->begining == 'Y') {
			if (p_ptr_gameFlow->finished == 'Y') {
				sprintf(p_ptr_frameDisposal->text, "GAME OVER");
				DrawString(p_ptr_screen, (SCREEN_WIDTH / 2) - (4 * (int)strlen(p_ptr_frameDisposal->text)), (SCREEN_HEIGHT - (p_ptr_frameDisposal->ptr_bottomInfoBoxRect->h / 2)), p_ptr_frameDisposal->text, p_ptr_charset, p_ptr_frameDisposal->ptr_bottomInfoBoxRect, p_ptr_renderer);
			}
			sprintf(p_ptr_frameDisposal->text, "? READY ?");
			DrawString(p_ptr_screen, (SCREEN_WIDTH / 2) - (4 * (int)strlen(p_ptr_frameDisposal->text)), (SCREEN_HEIGHT - (p_ptr_frameDisposal->ptr_bottomInfoBoxRect->h / 2)), p_ptr_frameDisposal->text, p_ptr_charset, p_ptr_frameDisposal->ptr_bottomInfoBoxRect, p_ptr_renderer);
		}
		else {
			if ((p_ptr_gameFlow->alive != 'Y') || (p_ptr_gameFlow->finished == 'Y')) {
				sprintf(p_ptr_frameDisposal->text, "GAME OVER");
				DrawString(p_ptr_screen, (SCREEN_WIDTH / 2) - (4 * (int)strlen(p_ptr_frameDisposal->text)), (SCREEN_HEIGHT - (p_ptr_frameDisposal->ptr_bottomInfoBoxRect->h / 2)), p_ptr_frameDisposal->text, p_ptr_charset, p_ptr_frameDisposal->ptr_bottomInfoBoxRect, p_ptr_renderer);
			}
			else if (p_ptr_gameFlow->pause == 'Y') {
				sprintf(p_ptr_frameDisposal->text, "PAUSE");
				DrawString(p_ptr_screen, (SCREEN_WIDTH / 2) - (4 * (int)strlen(p_ptr_frameDisposal->text)), (SCREEN_HEIGHT - (p_ptr_frameDisposal->ptr_bottomInfoBoxRect->h / 2)), p_ptr_frameDisposal->text, p_ptr_charset, p_ptr_frameDisposal->ptr_bottomInfoBoxRect, p_ptr_renderer);
			}
			else if ((p_ptr_gameFlow->pause == 'N') && (p_ptr_gameFlow->begining == 'N')) {
				sprintf(p_ptr_frameDisposal->text, "! GO !");
				DrawString(p_ptr_screen, (SCREEN_WIDTH / 2) - (4 * (int)strlen(p_ptr_frameDisposal->text)), (SCREEN_HEIGHT - (p_ptr_frameDisposal->ptr_bottomInfoBoxRect->h / 2)), p_ptr_frameDisposal->text, p_ptr_charset, p_ptr_frameDisposal->ptr_bottomInfoBoxRect, p_ptr_renderer);
			}
		}
	}
}

//draw rectangles on top and bottom of screen
void renderInfoBoxes(SDL_Renderer* p_ptr_renderer, gameFlow* p_ptr_gameFlow, SDL_Surface* p_ptr_charset, SDL_Surface* p_ptr_screen, frameDisposal* p_ptr_frameDisposal, timeData* p_ptr_timeData) {
	fillTopInfoBox(p_ptr_renderer, p_ptr_gameFlow, p_ptr_charset, p_ptr_screen, p_ptr_frameDisposal, p_ptr_timeData);
	fillBottomInfoBox(p_ptr_renderer, p_ptr_gameFlow, p_ptr_charset, p_ptr_screen, p_ptr_frameDisposal, p_ptr_timeData);
}

//render player icon dead and alive
void renderPlayer(SDL_Renderer* p_ptr_renderer, gameFlow* p_ptr_gameFlow, SDL_Rect* p_ptr_deadPlayerRect, SDL_Rect* p_ptr_texturePlayerRect, SDL_Texture* p_ptr_txtPlayerIcon, SDL_Texture* p_ptr_txtDeadPlayerIcon) {
	if (p_ptr_gameFlow->alive != 'Y') {
		editTextureRects(p_ptr_deadPlayerRect, p_ptr_texturePlayerRect->x, p_ptr_texturePlayerRect->y, p_ptr_texturePlayerRect->w, p_ptr_texturePlayerRect->h);
		SDL_RenderCopy(p_ptr_renderer, p_ptr_txtDeadPlayerIcon, NULL, p_ptr_deadPlayerRect);
		SDL_RenderPresent(p_ptr_renderer);
	}
	else {
		SDL_RenderCopy(p_ptr_renderer, p_ptr_txtPlayerIcon, NULL, p_ptr_texturePlayerRect);
		SDL_RenderPresent(p_ptr_renderer);
	}
}

//all action regarding saving
void saveGameState(frameDisposal* p_ptr_frameDisposal, gameFlow* p_ptr_gameFlow, timeData* p_ptr_timeData, SDL_Rect** p_ptr_backgroundRects, SDL_Rect* p_ptr_texturePlayerRect) {
	FILE* fSave;
	time_t myTime = time(NULL);
	struct tm myTimeInfo = *localtime(&myTime);
	int C1, C2;
	
	p_ptr_frameDisposal->fileName[0] = '\0';
	sprintf(p_ptr_frameDisposal->fileName, "%d-%02d-%02d_%02d-%02d-%02d", myTimeInfo.tm_year+1900, myTimeInfo.tm_mon+1, myTimeInfo.tm_mday, myTimeInfo.tm_hour, myTimeInfo.tm_min, myTimeInfo.tm_sec);
	

	FILE* fList;
	fList = fopen("../Debug/SaveFiles/FilesList", "ab+");
	fwrite(p_ptr_frameDisposal->fileName, 20, 1, fList);
	fclose(fList);

	C1 = _chdir("..//Debug//SaveFiles//");
	fSave = fopen(p_ptr_frameDisposal->fileName, "wb");
	if (fSave == NULL) {
		exit(CREATIONERROR);
	}
	else {
		fwrite(&(p_ptr_gameFlow->begining), sizeof(p_ptr_gameFlow->begining), 1, fSave);
		fwrite(&(p_ptr_gameFlow->alive), sizeof(p_ptr_gameFlow->alive), 1, fSave);
		fwrite(&(p_ptr_gameFlow->finished), sizeof(p_ptr_gameFlow->finished), 1, fSave);
		fwrite(&(p_ptr_gameFlow->pause), sizeof(p_ptr_gameFlow->pause), 1, fSave);
		fwrite(&(p_ptr_gameFlow->score), sizeof(p_ptr_gameFlow->score), 1, fSave);
		fwrite(&(p_ptr_texturePlayerRect->x), sizeof(p_ptr_texturePlayerRect->x), 1, fSave);
		fwrite(&(p_ptr_gameFlow->distanceY), sizeof(p_ptr_gameFlow->distanceY), 1, fSave);
		fwrite(&(p_ptr_gameFlow->ndDistanceY), sizeof(p_ptr_gameFlow->ndDistanceY), 1, fSave);
		fwrite(&(p_ptr_timeData->t3), sizeof(p_ptr_timeData->t3), 1, fSave);
		fwrite(&(p_ptr_timeData->worldTime), sizeof(p_ptr_timeData->worldTime), 1, fSave);
		fwrite(&(p_ptr_timeData->delta), sizeof(p_ptr_timeData->delta), 1, fSave);
		for (short i = 0; i < 12; i++) {
			fwrite(&(p_ptr_backgroundRects[i]->x), sizeof(p_ptr_backgroundRects[i]->x), 1, fSave);
			fwrite(&(p_ptr_backgroundRects[i]->y), sizeof(p_ptr_backgroundRects[i]->y), 1, fSave);
			fwrite(&(p_ptr_backgroundRects[i]->w), sizeof(p_ptr_backgroundRects[i]->w), 1, fSave);
			fwrite(&(p_ptr_backgroundRects[i]->h), sizeof(p_ptr_backgroundRects[i]->h), 1, fSave);
		}
		fclose(fSave);
	}
	p_ptr_gameFlow->beginSaving = 'N';
	C2 = _chdir("..//..//SpyHunter");
	
}

//display filenames in loading menu
void displayFileNames(SDL_Renderer* p_ptr_renderer, SDL_Surface* p_ptr_screen, SDL_Surface* p_ptr_charset, char p_ptr_files[][20], frameDisposal* p_ptr_frameDisposal) {
	SDL_Rect fileItem = {0, (SEGMENTHEIGHT / 3), SCREEN_WIDTH,  (((SCREEN_HEIGHT - SEGMENTHEIGHT) + 100) - SEGMENTHEIGHT / 3 )/6 };
	for (short i = p_ptr_frameDisposal->fileRangeInArrayStart; i <= p_ptr_frameDisposal->fileRangeInArrayEnd; i++) {
		if (i == p_ptr_frameDisposal->activeFile) {
			SDL_SetRenderDrawColor(p_ptr_renderer, 0, 128, 0, 255);
		}
		else {
			SDL_SetRenderDrawColor(p_ptr_renderer, 128, 0, 0, 255);
		}
		if (p_ptr_files[i] != "") {
			SDL_RenderDrawRect(p_ptr_renderer, &fileItem);
			SDL_RenderFillRect(p_ptr_renderer, &fileItem);
			sprintf(p_ptr_frameDisposal->text, p_ptr_files[i]);
			DrawString(p_ptr_screen, SCREEN_WIDTH / 2 - (20 * 4), fileItem.y + (fileItem.h/2), p_ptr_files[i], p_ptr_charset, &fileItem, p_ptr_renderer);
		}
		fileItem.y += (((SCREEN_HEIGHT - SEGMENTHEIGHT) + 100) - SEGMENTHEIGHT / 3) / 6;
	 }
	SDL_SetRenderDrawColor(p_ptr_renderer, 0, 0, 0, 255);

}

//initialize the loading screen
void loadScreen(SDL_Rect** p_ptr_backgroundRects, SDL_Rect* p_ptr_texturePlayerRect, gameFlow* p_ptr_gameFlow, timeData* p_ptr_timeData, frameDisposal* p_ptr_frameDisposal, SDL_Renderer* p_ptr_renderer, SDL_Surface* p_ptr_screen, SDL_Surface* p_ptr_charset) {
	const SDL_Rect saveScreen = { 0, SEGMENTHEIGHT / 3, SCREEN_WIDTH, ((SCREEN_HEIGHT-SEGMENTHEIGHT)+100)-SEGMENTHEIGHT/3};
	char files[36][20] = {};
	SDL_SetRenderDrawColor(p_ptr_renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(p_ptr_renderer, &saveScreen);
	SDL_RenderFillRect(p_ptr_renderer, &saveScreen);

	FILE* fList;
	fList = fopen("../Debug/SaveFiles/FilesList", "ab+");
	short i = 0;

	char Cont = 'Y';
	do {
		if (fread(files[i], 20, 1, fList) != 1) {
			Cont = 'N';
		}
		i++;
	} while (Cont == 'Y');

	fclose(fList);
	i--;
	p_ptr_frameDisposal->filesTotal = i ;
	p_ptr_frameDisposal->pagesTotal = ceil((double)i / 6);
	if (files[0] != "") {
		displayFileNames(p_ptr_renderer, p_ptr_screen, p_ptr_charset, files, p_ptr_frameDisposal);
		sprintf(p_ptr_frameDisposal->fileName, files[p_ptr_frameDisposal->activeFile]);
	}
	
}

//main graphic handling calls above functions
void graphicHandling(SDL_Surface* p_ptr_screen, SDL_Renderer* p_ptr_renderer, SDL_Texture* p_ptr_txtPlayerIcon, SDL_Surface* p_ptr_charset, SDL_Texture* p_ptr_txtLeftRightBound , gameFlow* p_ptr_gameFlow, SDL_Rect* p_ptr_texturePlayerRect, SDL_Rect** p_ptr_backgroundRects, SDL_Texture* p_ptr_txtDeadPlayerIcon, SDL_Rect* p_ptr_deadPlayerRect, frameDisposal* p_ptr_frameDisposal, timeData* p_ptr_timeData) {
	
	if (p_ptr_gameFlow->loadScreen == 'Y') {
		SDL_RenderClear(p_ptr_renderer);
		loadScreen(p_ptr_backgroundRects, p_ptr_texturePlayerRect, p_ptr_gameFlow, p_ptr_timeData, p_ptr_frameDisposal, p_ptr_renderer, p_ptr_screen, p_ptr_charset);
		renderInfoBoxes(p_ptr_renderer, p_ptr_gameFlow, p_ptr_charset, p_ptr_screen, p_ptr_frameDisposal, p_ptr_timeData);
		SDL_RenderPresent(p_ptr_renderer);
	}
	else {
		SDL_SetRenderDrawColor(p_ptr_renderer, 54, 65, 53, 255);
		SDL_RenderClear(p_ptr_renderer);
		renderBackground(p_ptr_renderer, p_ptr_backgroundRects, p_ptr_txtLeftRightBound);
		renderInfoBoxes(p_ptr_renderer, p_ptr_gameFlow, p_ptr_charset, p_ptr_screen, p_ptr_frameDisposal, p_ptr_timeData);
		renderPlayer(p_ptr_renderer, p_ptr_gameFlow, p_ptr_deadPlayerRect, p_ptr_texturePlayerRect, p_ptr_txtPlayerIcon, p_ptr_txtDeadPlayerIcon);
	}

}

//init starting background
SDL_Rect* initStartingGraphicState(int segmentNo, int arrInd, SDL_Rect* p_ptr_rect) {

	switch (segmentNo)
	{
	case SEGMENT1:
		switch (arrInd)
		{
		case 0:
			editTextureRects(p_ptr_rect, 0, SCREEN_HEIGHT - SEGMENTHEIGHT, MAXWIDTHLEFTGRASS, SEGMENTHEIGHT);
			return p_ptr_rect;
			break;
		case 1:
			editTextureRects(p_ptr_rect, 0, 0, 0, 0);
			return p_ptr_rect;
			break;
		case 2:
			editTextureRects(p_ptr_rect, SCREEN_WIDTH - MAXWIDTHRIGHTGRASS, SCREEN_HEIGHT - SEGMENTHEIGHT, MAXWIDTHRIGHTGRASS, SEGMENTHEIGHT);
			return p_ptr_rect;
			break;
		default:
			break;
		}

	case SEGMENT2:
		switch (arrInd)
		{
		case 0:
			editTextureRects(p_ptr_rect, 0, SCREEN_HEIGHT - 2 * SEGMENTHEIGHT, MAXWIDTHLEFTGRASS, SEGMENTHEIGHT);
			return p_ptr_rect;
			break;
		case 1:
			editTextureRects(p_ptr_rect, 0, 0, 0, 0);
			return p_ptr_rect;
			break;
		case 2:
			editTextureRects(p_ptr_rect, SCREEN_WIDTH - MAXWIDTHRIGHTGRASS, SCREEN_HEIGHT - 2 * SEGMENTHEIGHT, MAXWIDTHRIGHTGRASS, SEGMENTHEIGHT);
			return p_ptr_rect;
			break;
		default:
			break;
		}

	case SEGMENT3:
		switch (arrInd)
		{
		case 0:
			editTextureRects(p_ptr_rect, 0, 0, MAXWIDTHLEFTGRASS, SEGMENTHEIGHT);
			return p_ptr_rect;
			break;
		case 1:
			editTextureRects(p_ptr_rect, 0, 0, 0, 0);
			return p_ptr_rect;
			break;
		case 2:
			editTextureRects(p_ptr_rect, SCREEN_WIDTH - MAXWIDTHRIGHTGRASS, 0, MAXWIDTHRIGHTGRASS, SEGMENTHEIGHT);
			return p_ptr_rect;
			break;
		default:
			break;
		}
	default:
		break;
	}
	return p_ptr_rect;
};

//free SDL memory in case of error/quit
void destroyEverything(SDL_Surface** p_ptr_charset, SDL_Surface** p_ptr_playerIcon, SDL_Surface** p_ptr_screen, SDL_Surface** p_ptr_leftRightBound, SDL_Texture** p_ptr_txtPlayerIcon, SDL_Texture** p_ptr_txtLeftRightBound, SDL_Window** p_ptr_window, SDL_Renderer** p_ptr_renderer) {
	SDL_FreeSurface(*p_ptr_charset);
	SDL_FreeSurface(*p_ptr_playerIcon);
	SDL_FreeSurface(*p_ptr_screen);
	SDL_FreeSurface(*p_ptr_leftRightBound);
	SDL_DestroyTexture(*p_ptr_txtPlayerIcon);
	SDL_DestroyTexture(*p_ptr_txtLeftRightBound);
	SDL_DestroyWindow(*p_ptr_window);
	SDL_DestroyRenderer(*p_ptr_renderer);
}

//create textures from surfaces loaded from BMP's
int setupTextures(SDL_Surface** p_ptr_charset, SDL_Surface** p_ptr_playerIcon, SDL_Surface** p_ptr_deadPlayerIcon, SDL_Texture** p_ptr_txtDeadPlayerIcon, SDL_Surface** p_ptr_screen, SDL_Surface** p_ptr_leftRightBound, SDL_Texture** p_ptr_txtPlayerIcon, SDL_Texture** p_ptr_txtLeftRightBound, SDL_Window** p_ptr_window, SDL_Renderer** p_ptr_renderer, SDL_Rect** p_ptr_texturePlayerRect) {
	*p_ptr_charset = loadAndSetupBMPs(p_ptr_charset, 'C');
	if (p_ptr_charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", 
		SDL_GetError());
		destroyEverything(p_ptr_charset, p_ptr_playerIcon, p_ptr_screen, p_ptr_leftRightBound, p_ptr_txtPlayerIcon, p_ptr_txtLeftRightBound, p_ptr_window, p_ptr_renderer);
		
		return(INITERROR);
	}
	SDL_SetColorKey(*p_ptr_charset, true, 0x000000);

	*p_ptr_playerIcon = loadAndSetupBMPs(p_ptr_playerIcon, 'P');
	if (p_ptr_playerIcon == NULL) {
		printf("SDL_LoadBMP(PlayerIcon.bmp) error: %s\n", SDL_GetError());
		destroyEverything(p_ptr_charset, p_ptr_playerIcon, p_ptr_screen, p_ptr_leftRightBound, p_ptr_txtPlayerIcon, p_ptr_txtLeftRightBound, p_ptr_window, p_ptr_renderer);
		
		return INITERROR;
	}
	editTextureRects(*p_ptr_texturePlayerRect, SCREEN_WIDTH / 2, PLAYERY, (*p_ptr_playerIcon)->w, (*p_ptr_playerIcon)->h);
	*p_ptr_txtPlayerIcon = SDL_CreateTextureFromSurface(*p_ptr_renderer, *p_ptr_playerIcon);


	*p_ptr_leftRightBound = loadAndSetupBMPs(p_ptr_leftRightBound, 'S');
	if (p_ptr_leftRightBound == NULL) {
		printf("SDL_LoadBMP(LeftRightBound.bmp) error: %s\n", SDL_GetError());
		destroyEverything(p_ptr_charset, p_ptr_playerIcon, p_ptr_screen, p_ptr_leftRightBound, p_ptr_txtPlayerIcon, p_ptr_txtLeftRightBound, p_ptr_window, p_ptr_renderer);
		return INITERROR;
	}
	*p_ptr_txtLeftRightBound = SDL_CreateTextureFromSurface(*p_ptr_renderer, *p_ptr_leftRightBound);

	*p_ptr_deadPlayerIcon = loadAndSetupBMPs(p_ptr_deadPlayerIcon, 'D');
	if (p_ptr_deadPlayerIcon == NULL) {
		printf("SDL_LoadBMP(deadPlayerIcon.bmp) error: %s\n", SDL_GetError());
		destroyEverything(p_ptr_charset, p_ptr_playerIcon, p_ptr_screen, p_ptr_leftRightBound, p_ptr_txtPlayerIcon, p_ptr_txtLeftRightBound, p_ptr_window, p_ptr_renderer);
		return INITERROR;
	}
	*p_ptr_txtDeadPlayerIcon = SDL_CreateTextureFromSurface(*p_ptr_renderer, *p_ptr_deadPlayerIcon);

	return OK;
}

//on n press go back to starting phase
void startNewGame(SDL_Rect** p_ptr_backgroundRects, SDL_Rect* p_ptr_texturePlayerRect, gameFlow* p_ptr_gameFlow, timeData* p_ptr_timeData) {
	initStartingGraphicState(SEGMENT1, 0, p_ptr_backgroundRects[0]);
	initStartingGraphicState(SEGMENT1, 1, p_ptr_backgroundRects[1]);
	initStartingGraphicState(SEGMENT1, 2, p_ptr_backgroundRects[2]);

	initStartingGraphicState(SEGMENT2, 0, p_ptr_backgroundRects[3]);
	initStartingGraphicState(SEGMENT2, 1, p_ptr_backgroundRects[4]);
	initStartingGraphicState(SEGMENT2, 2, p_ptr_backgroundRects[5]);

	initStartingGraphicState(SEGMENT3, 0, p_ptr_backgroundRects[6]);
	initStartingGraphicState(SEGMENT3, 1, p_ptr_backgroundRects[7]);
	initStartingGraphicState(SEGMENT3, 2, p_ptr_backgroundRects[8]);

	generateSegment4(SEGMENT4, 0, p_ptr_backgroundRects[9]);
	generateSegment4(SEGMENT4, 1, p_ptr_backgroundRects[10]);
	generateSegment4(SEGMENT4, 2, p_ptr_backgroundRects[11]);

	editTextureRects(p_ptr_texturePlayerRect, SCREEN_WIDTH/2, PLAYERY, PLAYERWIDTH, PLAYERHEIGHT);

	p_ptr_gameFlow->ndDistanceY = 0;
	p_ptr_gameFlow->distanceY = 0;
	p_ptr_gameFlow->score = 0;
	p_ptr_gameFlow->alive = 'Y';
	p_ptr_gameFlow->begining = 'Y';
	p_ptr_gameFlow->pause = 'N';
	p_ptr_gameFlow->finished = 'N';
	p_ptr_gameFlow->gameLoaded = 'N';

	p_ptr_timeData->delta = 0;
	p_ptr_timeData->t1 = 0;
	p_ptr_timeData->t2 = 0;
	p_ptr_timeData->worldTime = 0;

}

//load game info from saved file
void loadGame(gameFlow* p_ptr_gameFlow, frameDisposal* p_ptr_frameDisposal, timeData* p_ptr_timeData, SDL_Rect** p_ptr_backgroundRects, SDL_Rect* p_ptr_texturePlayerRect) {
	FILE* fLoadFrom;
	int C1, C2;
	C1 = _chdir("..//Debug//SaveFiles");
	fLoadFrom = fopen(p_ptr_frameDisposal->fileName, "rb");
	if (fLoadFrom != NULL) {
		fread(&(p_ptr_gameFlow->begining), sizeof(p_ptr_gameFlow->begining), 1, fLoadFrom);
		fread(&(p_ptr_gameFlow->alive), sizeof(p_ptr_gameFlow->alive), 1, fLoadFrom);
		fread(&(p_ptr_gameFlow->finished), sizeof(p_ptr_gameFlow->finished), 1, fLoadFrom);
		fread(&(p_ptr_gameFlow->pause), sizeof(p_ptr_gameFlow->pause), 1, fLoadFrom);
		fread(&(p_ptr_gameFlow->score), sizeof(p_ptr_gameFlow->score), 1, fLoadFrom);
		fread(&(p_ptr_texturePlayerRect->x), sizeof(p_ptr_texturePlayerRect->x), 1, fLoadFrom);
		fread(&(p_ptr_gameFlow->distanceY), sizeof(p_ptr_gameFlow->distanceY), 1, fLoadFrom);
		fread(&(p_ptr_gameFlow->ndDistanceY), sizeof(p_ptr_gameFlow->ndDistanceY), 1, fLoadFrom);
		fread(&(p_ptr_timeData->t3), sizeof(p_ptr_timeData->t3), 1, fLoadFrom);
		fread(&(p_ptr_timeData->worldTime), sizeof(p_ptr_timeData->worldTime), 1, fLoadFrom);
		fread(&(p_ptr_timeData->delta), sizeof(p_ptr_timeData->delta), 1, fLoadFrom);
		for (short i = 0; i < 12; i++) {
			fread(&(p_ptr_backgroundRects[i]->x), sizeof(p_ptr_backgroundRects[i]->x), 1, fLoadFrom);
			fread(&(p_ptr_backgroundRects[i]->y), sizeof(p_ptr_backgroundRects[i]->y), 1, fLoadFrom);
			fread(&(p_ptr_backgroundRects[i]->w), sizeof(p_ptr_backgroundRects[i]->w), 1, fLoadFrom);
			fread(&(p_ptr_backgroundRects[i]->h), sizeof(p_ptr_backgroundRects[i]->h), 1, fLoadFrom);
		}
		fclose(fLoadFrom);
		p_ptr_gameFlow->beginLoading = 'N';
		p_ptr_gameFlow->gameLoaded = 'Y';
		p_ptr_timeData->t2Load = SDL_GetTicks();
		p_ptr_timeData->t1 = 0;
		p_ptr_gameFlow->pause = 'Y';
		p_ptr_gameFlow->beginingAfterLoading = 'Y';
		C2 = _chdir("..//..//SpyHunter");
	}
	else {
		SDL_Quit();
		exit(BADFILE);
	}
}

//loading/saving handler must be independent of player state
void loadOrSave(gameFlow* p_ptr_gameFlow, timeData* p_ptr_timeData, frameDisposal* p_ptr_frameDisposal, SDL_Rect** p_ptr_backgroundRects, SDL_Rect* p_ptr_texturePlayerRect) {
	if (p_ptr_gameFlow->beginLoading == 'Y') {
		loadGame(p_ptr_gameFlow, p_ptr_frameDisposal , p_ptr_timeData, p_ptr_backgroundRects, p_ptr_texturePlayerRect);
	}
	if (p_ptr_gameFlow->beginSaving == 'Y') {
		saveGameState(p_ptr_frameDisposal, p_ptr_gameFlow, p_ptr_timeData, p_ptr_backgroundRects, p_ptr_texturePlayerRect);
	}
}


int main(int argc, char** argv) {
	
	timeData main_timeData;
	timeData* ptr_timeData = &main_timeData;

	frameDisposal main_frameDisposal;
	frameDisposal* ptr_frameDisposal = &main_frameDisposal;

	gameFlow main_gameFlow;
	gameFlow* ptr_gameFlow = &main_gameFlow;

	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Surface* charset ;
	SDL_Surface* playerIcon;
	SDL_Surface* deadPlayerIcon;
	SDL_Surface* screen;
	SDL_Surface* leftRightBound;	
	SDL_Texture* txtPlayerIcon;
	SDL_Texture* txtDeadPlayerIcon;
	SDL_Texture* txtLeftRightBound;
	SDL_Window* window;	
	SDL_Rect texturePlayerRect;
	SDL_Rect* ptr_texturePlayerRect = &texturePlayerRect;
	SDL_Rect textureDeadPlayerRect;
	SDL_Rect* ptr_textureDeadPlayerRect = &textureDeadPlayerRect;

	//SCREEN divided into 3 segments, s1=bottom, s2=middle, s3=top, s4=next for s3. Divided into 3 peaces LeftBound,Middle, RightBound
	SDL_Rect s1Rect0;SDL_Rect s1Rect1;SDL_Rect s1Rect2;
	SDL_Rect s2Rect0;SDL_Rect s2Rect1;SDL_Rect s2Rect2;
	SDL_Rect s3Rect0;SDL_Rect s3Rect1;SDL_Rect s3Rect2;
	SDL_Rect s4Rect0;SDL_Rect s4Rect1;SDL_Rect s4Rect2;

	SDL_Rect* backgroundRects[12] = { &s1Rect0, &s1Rect1, &s1Rect2, &s2Rect0, &s2Rect1, &s2Rect2, &s3Rect0, &s3Rect1, &s3Rect2, &s4Rect0, &s4Rect1, &s4Rect2};

	SDL_Rect topInfoBoxRect;
	SDL_Rect bottomInfoBoxRect;

	ptr_frameDisposal->ptr_topInfoBoxRect = &topInfoBoxRect;
	ptr_frameDisposal->ptr_bottomInfoBoxRect = &bottomInfoBoxRect;

	initStartingGraphicState(SEGMENT1, 0, backgroundRects[0]);
	initStartingGraphicState(SEGMENT1, 1, backgroundRects[1]);
	initStartingGraphicState(SEGMENT1, 2, backgroundRects[2]);

	initStartingGraphicState(SEGMENT2, 0, backgroundRects[3]);
	initStartingGraphicState(SEGMENT2, 1, backgroundRects[4]);
	initStartingGraphicState(SEGMENT2, 2, backgroundRects[5]);

	initStartingGraphicState(SEGMENT3, 0, backgroundRects[6]);
	initStartingGraphicState(SEGMENT3, 1, backgroundRects[7]);
	initStartingGraphicState(SEGMENT3, 2, backgroundRects[8]);

	generateSegment4(SEGMENT4, 0, backgroundRects[9]);
	generateSegment4(SEGMENT4, 1, backgroundRects[10]);
	generateSegment4(SEGMENT4, 2, backgroundRects[11]);

	if (initAndCreateFoundation(&screen, &window, &renderer, ptr_frameDisposal) != OK) {
		printf("%s %s", "There was an error: ", SDL_GetError());
		destroyEverything(&charset, &playerIcon, &screen, &leftRightBound, &txtPlayerIcon, &txtLeftRightBound, &window, &renderer);
	}
	setupTextures(&charset, &playerIcon, &deadPlayerIcon, &txtDeadPlayerIcon, &screen, &leftRightBound, &txtPlayerIcon, &txtLeftRightBound, &window, &renderer, &ptr_texturePlayerRect );
	srand(time(0));

	while (main_gameFlow.quit != 'Y') {
		if (ptr_gameFlow->newGameFlag == 'Y') {
			startNewGame(backgroundRects, ptr_texturePlayerRect, ptr_gameFlow, ptr_timeData);
			ptr_gameFlow->newGameFlag = 'N';
		}		
		if ((ptr_gameFlow->pause == 'N') && (ptr_gameFlow->finished == 'N')) {					//If not paused and game not over by user press. Begin normal gameFlow
			if ((ptr_gameFlow->alive == 'Y')) {													//If alive do all and move player
				if ((ptr_gameFlow->begining != 'Y') && (ptr_gameFlow->loadScreen != 'Y')) {		//If game began and we are not in the loadscreen handle Time
					timeHandling(ptr_timeData, ptr_gameFlow, ptr_frameDisposal);
				}
				else if ((ptr_gameFlow->begining == 'Y') && (ptr_gameFlow->score != 0)) {		//Exception: If user while holding arrowUp starts newGame we can't detect it by event unless player realeses arrowUp key
					ptr_timeData->t1 = SDL_GetTicks();											//In such case we reset the timer and set newGame Flag manually
					ptr_gameFlow->begining = 'N';
				}

				eventHandling(&event, ptr_gameFlow, ptr_texturePlayerRect, backgroundRects, ptr_timeData, ptr_frameDisposal);			
				graphicHandling(screen, renderer, txtPlayerIcon, charset, txtLeftRightBound, ptr_gameFlow, ptr_texturePlayerRect, backgroundRects, txtDeadPlayerIcon, ptr_textureDeadPlayerRect, ptr_frameDisposal, ptr_timeData);				
				moveBasedOnEvents(ptr_gameFlow, ptr_texturePlayerRect, backgroundRects);
									
			}
			else {																				//If user is dead we show and interpret events but dont act on the player's texture
				graphicHandling(screen, renderer, txtPlayerIcon, charset, txtLeftRightBound, ptr_gameFlow, ptr_texturePlayerRect, backgroundRects, txtDeadPlayerIcon, ptr_textureDeadPlayerRect, ptr_frameDisposal, ptr_timeData);
				eventHandling(&event, ptr_gameFlow, ptr_texturePlayerRect, backgroundRects, ptr_timeData, ptr_frameDisposal);
			}
		}
		else if ((ptr_gameFlow->pause == 'Y') || (ptr_gameFlow->finished == 'Y')) {				//If user enabled Pause or finished the game by himself we show and interpret events but dont act on the player's texture
			graphicHandling(screen, renderer, txtPlayerIcon, charset, txtLeftRightBound, ptr_gameFlow, ptr_texturePlayerRect, backgroundRects, txtDeadPlayerIcon, ptr_textureDeadPlayerRect, ptr_frameDisposal, ptr_timeData);
			eventHandling(&event, ptr_gameFlow, ptr_texturePlayerRect, backgroundRects, ptr_timeData, ptr_frameDisposal);
		}	

		if (ptr_gameFlow->beginLoading == 'Y' || ptr_gameFlow->beginSaving == 'Y') {
			loadOrSave(ptr_gameFlow, ptr_timeData, ptr_frameDisposal, backgroundRects, ptr_texturePlayerRect);
		}
		ptr_frameDisposal->frames++;
	};
	destroyEverything(&charset, &playerIcon, &screen, &leftRightBound, &txtPlayerIcon, &txtLeftRightBound, &window, &renderer);
	SDL_FreeSurface(deadPlayerIcon);
	SDL_DestroyTexture(txtDeadPlayerIcon);
	SDL_Quit();
	return 0;
}