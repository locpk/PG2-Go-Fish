#include "Game.h"

std::string getFileContents(std::ifstream&);
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
		//test different state 
		SetState(GAME_MENU);
		ifstream Reader("asc.txt");
		switch(m_state)
		{
		case GAME_INIT:
			// Insert initialization code here.
			break;
		case GAME_MENU:
			// Insert menu code here.
			Console::Clear();
			
			cout << getFileContents(Reader);
			/*_¦¦¦¦¦¦_   _¦¦¦¦¦¦_          _¦¦¦¦¦¦¦¦  _¦     _¦¦¦¦¦¦¦¦    _¦    ¦_
				¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦        ¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦    ¦¦¦   ¦¦¦    ¦¦¦
				¦¦¦    ¦¯  ¦¦¦    ¦¦¦        ¦¦¦    ¦¯  ¦¦¦¦   ¦¦¦    ¦¯    ¦¦¦    ¦¦¦
				_¦¦¦        ¦¦¦    ¦¦¦       _¦¦¦___     ¦¦¦¦   ¦¦¦         _¦¦¦____¦¦¦__
				¯¯¦¦¦ ¦¦¦¦_  ¦¦¦    ¦¦¦      ¯¯¦¦¦¯¯¯     ¦¦¦¦ ¯¦¦¦¦¦¦¦¦¦¦¦ ¯¯¦¦¦¯¯¯¯¦¦¦¯
				¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦        ¦¦¦        ¦¦¦           ¦¦¦   ¦¦¦    ¦¦¦
				¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦        ¦¦¦        ¦¦¦     _¦    ¦¦¦   ¦¦¦    ¦¦¦
				¦¦¦¦¦¦¦¦¯   ¯¦¦¦¦¦¦¯         ¦¦¦        ¦¯    _¦¦¦¦¦¦¦¦¯    ¦¦¦    ¦¯*/
			Console::SetCursorPosition(Console::WindowWidth() /2 -5,13);
			cout << ">>  "<< "Start\b\b\b\b\b\b\b\b\b"<<endl;

			                                                   
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

std::string getFileContents(std::ifstream& File)
{
	std::string Lines = "";        //All lines

	if (File)                      //Check if everything is good
	{
		while (File.good())
		{
			std::string TempLine;                  //Temp line
			std::getline(File, TempLine);        //Get temp line
			TempLine += "\n";                      //Add newline character

			Lines += TempLine;                     //Add newline
		}
		return Lines;
	}
	else                           //Return error
	{
		return "ERROR File does not exist.";
	}
}