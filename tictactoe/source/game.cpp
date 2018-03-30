#include <nds.h>
#include <stdio.h>

typedef struct Bounds 
{
	int x;
	int y;
	int width;
	int height;
} Bound;


Bound boardBounds[] = 
{
	{51,19,48,48},
	{104,19,48,48},
	{157,19,48,48},
	{51,72,48,48},
	{104,72,48,48},
	{157,72,48,48},
	{51,125,48,48},
	{104,125,48,48},
	{157,125,48,48}
};


void gameLoop()
{
	int area = 0;
	touchPosition touch;

	scanKeys();
	int held = keysHeld();

	if(held & KEY_TOUCH) {

		touchRead(&touch);

	/*	if (touch.z1 != 0 ) {
			area = touch.px * touch.z2 / touch.z1 - touch.px;
		}

		iprintf("\x1b[10;0HTouch x = %04i, %04i\n", touch.rawx, touch.px);

		iprintf("Touch y = %04i, %04i\n", touch.rawy, touch.py);

		iprintf("Touch Area (pressure) %04i\n", area);*/

		int selectGrid = checkBoard(touch.px,touch.py);

		iprintf("Selected %i",selectGrid);
	}
}

int checkBoard(int posX, int posY)
{
	int index = 0;

	for (index=0; index < 9; index++)
	{
		if (posX >= boardBounds[index].x && posX <= boardBounds[index].x + boardBounds[index].width &&
			posY >= boardBounds[index].y && posX <= boardBounds[index].y + boardBounds[index].height)
			return index;
	}

	return -1;
}