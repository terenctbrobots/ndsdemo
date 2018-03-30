/*---------------------------------------------------------------------------------

	$Id: main.cpp,v 1.13 2008-12-02 20:21:20 dovoto Exp $

	Simple console print demo
	-- dovoto


---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>

#include "backgroundBoard.h"
//#include <stdio.h>

/*
volatile int frame = 0;

void Vblank() {
	frame++;
}*/

extern void gameLoop();

enum GameState 
{
	GameState_Intro,
	GameState_Game
};

/* Select a low priority DMA channel to perform our background copying. */
static const int DMA_CHANNEL = 3;

void initVideo()
{
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_B_MAIN_BG_0x06020000);
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);
	vramSetBankD(VRAM_D_LCD);
	
	videoSetMode(MODE_5_2D |
				 DISPLAY_BG2_ACTIVE |
				 DISPLAY_BG3_ACTIVE);
	videoSetModeSub(MODE_5_2D |
					DISPLAY_BG3_ACTIVE);
}

void initBackgrounds()
{
    /*  Set up affine background 3 on main as a 16-bit color background. */
    REG_BG3CNT = BG_BMP16_256x256 |
                 BG_BMP_BASE(0) | // The starting place in memory
                 BG_PRIORITY(3); // A low priority

    /*  Set the affine transformation matrix for the main screen background 3
     *  to be the identity matrix.
     */
    REG_BG3PA = 1 << 8;
    REG_BG3PB = 0;
    REG_BG3PC = 0;
    REG_BG3PD = 1 << 8;

    /*  Place main screen background 3 at the origin (upper left of the
     *  screen).
     */
    REG_BG3X = 0;
    REG_BG3Y = 0;
}

void displayBoard()
{
    dmaCopyHalfWords(DMA_CHANNEL,
                     backgroundBoardBitmap, /* This variable is generated for us by
                                       * grit. */
                     (uint16 *)BG_BMP_RAM(0), /* Our address for main
                                               * background 3 */
                     backgroundBoardBitmapLen); /* This length (in bytes) is
                                           * generated from grit. */
}

void introLoop()
{

}

	
//---------------------------------------------------------------------------------
int main(void) 
{	

//---------------------------------------------------------------------------------
	/*touchPosition touchXY;

	irqSet(IRQ_VBLANK, Vblank);

	consoleDemoInit();

	iprintf("      Hello DS dev'rs\n");
	iprintf("     \x1b[32mwww.devkitpro.org\n");
	iprintf("   \x1b[32;1mwww.drunkencoders.com\x1b[39m");
 
	while(1) {
	
		swiWaitForVBlank();
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;

		touchRead(&touchXY);

		// print at using ansi escape sequence \x1b[line;columnH 
		iprintf("\x1b[10;0HFrame = %d",frame);
		iprintf("\x1b[16;0HTouch x = %04X, %04X\n", touchXY.rawx, touchXY.px);
		iprintf("Touch y = %04X, %04X\n", touchXY.rawy, touchXY.py);		
	
	}*/
	powerOn(POWER_ALL_2D);
	lcdMainOnBottom();

	initVideo();
	initBackgrounds();

	displayBoard();

	consoleDemoInit();

	enum GameState gameState = GameState_Game;

	// Loop forever so we don't get dumped out by the DS
	while (1)
	{
		switch(gameState)
		{
			case GameState_Intro:
				introLoop();
				break;
			case GameState_Game:
				gameLoop();
				break;
		}
		swiWaitForVBlank();
	}

	return 0;
}
