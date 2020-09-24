//---------------------------------------------------------------------------------------------------------
//
//Simple Game Project for GVSU CIS 693. Main game engine code is loosely based off of
// Ather Omar's tutorials found here: https://www.youtube.com/channel/UCCKlrE0p4IZxqBpq98KFBmw
//Game engine credits go to him and his tutorials
//---------------------------------------------------------------------------------------------------------

#include "gameManager.h"

int main(int argc, char* args[])
{
	GameManager* game = GameManager::Instance();

	game->Run();

	GameManager::Release();
	game = NULL;

	return 0;
}