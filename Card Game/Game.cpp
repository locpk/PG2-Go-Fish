#include "Game.h"

// Default ctor
Game::Game()
{
	m_state = GAME_INIT;
}

// Dtor
Game::~Game()
{

}

void Game::Run()
{
	// Bool to control whether the game should continue to run.
	bool bRun = true;

	// Loop while our bool remains true.
	while(bRun)
	{
		switch(m_state)
		{
		case GAME_INIT:
			// Insert initialization code here.
			break;
		case GAME_MENU:
			// Insert menu code here.
			break;
		case GAME_PLAY:
			// Insert game play code here.
			break;
		case GAME_END:
			// The game is over, change the bool to stop the loop.
			bRun = false;
			break;
		}
	}
}