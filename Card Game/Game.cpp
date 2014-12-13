#include "Game.h"
//define menu layout positions
#define CURSORLEFT Console::WindowWidth() /2 -5
#define STARTBUTTON 13
#define QUITBUTTON 14
std::string getFileContents(std::ifstream&);
// Default ctor
Game::Game()
{
	m_state = GAME_INIT;
	for (size_t i = 0; i < 4; i++)
	{
		m_players[i] = nullptr;
	}
	m_currPlayer = 0;
	m_numPlayers = 0;
	isComputer = 0;
	m_title_art = ifstream(m_filename);
	Console::Lock(true);
	engine = createIrrKlangDevice();
	Console::Clear();
	Console::Lock(false);
	
}

// Dtor
Game::~Game()
{
	for (int i = 0; i < m_numPlayers; i++)
	{
		delete m_players[i];
		m_players[i] = nullptr;
	}
}

void Game::Run()
{
	// Bool to control whether the game should continue to run.
	bool bRun = true;

	// Loop while our bool remains true.
	while(bRun)
	{
		//test different state 
		
		
		switch(m_state)
		{
		case GAME_INIT:
			
			// Insert initialization code here.
			while (m_numPlayers < 2 || m_numPlayers > 4)
			{
				cout << "How many players? (2 - 4)";
				while (!(cin >> m_numPlayers))
				{
					cout << "invalid input";
					cin.clear();
					cin.sync();
				}
			}

			for (int i = 0; i < m_numPlayers; i++)
			{
				cout << "Player " << i + 1 << " is computer? (0 for NO, 1 for YES)";
				while (!(cin >> isComputer) || (isComputer != 0 && isComputer != 1))
				{
					cout << "invalid input";
					cin.clear();
					cin.sync();
				}
				
				if (1 == isComputer)
				{
					m_players[i] = new Computer(Console::RandomName());
				}
				else
				{
					m_players[i] = new Human;
				}
				
			}
			
			
			for (int i = 0; i < m_numPlayers; i++)
			{
				//draw 7 card for the player 
				for (int j = 0; j < 7; j++)
				{
					m_Deck.Draw(m_temp_card1);
					m_players[i]->AddCard(m_temp_card1);
				}

			}

			
			cin.clear();
			cin.ignore(LLONG_MAX,'\n');
			SetState(GAME_MENU);
			break;
		case GAME_MENU:
			// Insert menu code here.
			Console::FlushKeys();
			cout << "Loading...I wish I am a Quantum computer.";
			Sleep(1500);
			engine->play2D("TheForestAwakes.ogg", true);
			
			Console::Clear();
			cout << getFileContents(m_title_art);
			/*_¦¦¦¦¦¦_   _¦¦¦¦¦¦_          _¦¦¦¦¦¦¦¦  _¦     _¦¦¦¦¦¦¦¦    _¦    ¦_
				¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦        ¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦    ¦¦¦   ¦¦¦    ¦¦¦
				¦¦¦    ¦¯  ¦¦¦    ¦¦¦        ¦¦¦    ¦¯  ¦¦¦¦   ¦¦¦    ¦¯    ¦¦¦    ¦¦¦
				_¦¦¦        ¦¦¦    ¦¦¦       _¦¦¦___     ¦¦¦¦   ¦¦¦         _¦¦¦____¦¦¦__
				¯¯¦¦¦ ¦¦¦¦_  ¦¦¦    ¦¦¦      ¯¯¦¦¦¯¯¯     ¦¦¦¦ ¯¦¦¦¦¦¦¦¦¦¦¦ ¯¯¦¦¦¯¯¯¯¦¦¦¯
				¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦        ¦¦¦        ¦¦¦           ¦¦¦   ¦¦¦    ¦¦¦
				¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦        ¦¦¦        ¦¦¦     _¦    ¦¦¦   ¦¦¦    ¦¦¦
				¦¦¦¦¦¦¦¦¯   ¯¦¦¦¦¦¦¯         ¦¦¦        ¦¯    _¦¦¦¦¦¦¦¦¯    ¦¦¦    ¦¯*/

			Console::SetCursorPosition(CURSORLEFT, STARTBUTTON);
			cout << ">>      " << "Start\n";
			Console::SetCursorPosition(CURSORLEFT, QUITBUTTON);
			cout << ">>      " << "Quit\n";
			Console::SetCursorPosition(CURSORLEFT, STARTBUTTON);
			MenuCursor();
			Console::CursorVisible(false);
			engine->drop(); // delete engine
			break;
		case GAME_PLAY:
			// Insert game play code here.
			for (int m_currPlayer = 0; m_currPlayer <= m_numPlayers; m_currPlayer++)
			{
				if (m_currPlayer == m_numPlayers) //reset players let them take turns
					m_currPlayer = 0;
				// dummy game over condition without allowing quiting game
				if (m_Deck.IsEmpty())
				{
					bool keep = false;
					for (size_t i = 0; i < m_numPlayers; i++)
					{
						if (m_players[i]->GetNumCards() != 0)
							keep = true;
					}

					if (keep == false)
					{
						SetState(GAME_END);
						break;
					}
				}
				if (m_players[m_currPlayer]->IsPlaying())
				{
					m_players[m_currPlayer]->SortCardsbySuit();
					cin.get();
					//Sleep(1500);
					Console::Clear();

					//show each player's hand
					for (int i = 0; i < m_numPlayers; i++)
					{
						m_players[i]->Show();
					}
					// test if a player is run out of cards
					if (0 == m_players[m_currPlayer]->GetNumCards())
					{
						for (size_t i = 0; i < 7; i++)
						{
							if (m_Deck.Draw(m_temp_card1))
								m_players[m_currPlayer]->AddCard(m_temp_card1);
							else
							{
								m_players[m_currPlayer]->SetIsPlaying(false);
								break;
							}
						}
					}

					while (AskCard(m_players[m_currPlayer], m_players)) // if ask card fails draw from deck
					{
						cout << "Ask successful! Keep asking." << endl;
					}
					if (m_Deck.Draw(m_temp_card1))
					{
						m_players[m_currPlayer]->AddCard(m_temp_card1);
						cout << endl << m_players[m_currPlayer]->GetName() << " draws from the deck. a " << m_temp_card1 << endl;
					}
					Score(m_players[m_currPlayer]); // check pairs 
				}	
			}
			SetState(GAME_END);
			break;
		case GAME_END:
			// The game is over, change the bool to stop the loop.
			Console::BackgroundColor(Blue);
			Console::Clear();
			Console::SetCursorPosition(Console::WindowWidth() / 3, Console::WindowHeight() / 3);
			
			cout << "Game ENDs!" << endl;
			Sleep(1500);
			int iWinner{ 0 }, iMaxScore{0};
			for (int i = 0; i < m_numPlayers; i++)
			{
				if (m_players[i]->GetScore() > iMaxScore)
				{
					iMaxScore = m_players[i]->GetScore();
					iWinner = i;
				}
				Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
				std::string str1 = m_players[i]->GetName();
				std::string str2 = "'s FINAL SCORE is: ";
				std::string str3 = std::to_string(m_players[i]->GetScore());
				std::string str = str1 + str2 + str3;
				for (char& c : str) {
					cout << c;
					Sleep(60);
				}
				Sleep(1500);
				Console::Clear();
				
			}
			Console::ForegroundColor(Red);
			Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
			cout << "The Winner is : " << m_players[iWinner]->GetName() << " , scored " << m_players[iWinner]->GetScore() << endl;
			Sleep(6000);
			bRun = false;
			Console::ResetColor();
			Console::Clear();
			Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
			std::string str = "Bye Bye!";
			for (char& c : str) {
				cout << c;
				Sleep(150);
			}
			Console::CursorVisible(true);
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
		return "Menu Art File does not exist.";
	}
}

int Game::Score(Player* _player)
{
	int iPairs{0};
	//pair checking
	for (int i = 0; i < _player->GetNumCards(); i++)
	{
		_player->GetCard(i, m_temp_card1);
		for (int j = i + 1; j < _player->GetNumCards(); j++)
		{
			_player->GetCard(j, m_temp_card2);
			if (m_temp_card1.GetFace() == m_temp_card2.GetFace())
			{
				_player->Discard(j, m_temp_card2);
				_player->Discard(i, m_temp_card1);
				iPairs++;
				i = 0;
				_player->AddToScore(1);
				break;
			}
		}
	}
	return iPairs;
}

bool Game::AskCard(Player* _current_player, Player** _next_player)
{
	//jump out when current player's hand is empty
	if (0 == _current_player->GetNumCards())
		return false;
	int p = 0;// Player to be asked
	int iFace = 0;

	if (NULL == dynamic_cast<Computer*>(_current_player))
	{
		//Human player behavior
		cout << "What do you want? _\b";
		//check if the card the player asking for is in its hand or not
		while (!(cin >> iFace) || iFace > 14 || iFace < 0)
		{
			bool inHand = false;
			for (int i = 0; i < _current_player->GetNumCards(); i++)
			{
				_current_player->GetCard(i, m_temp_card2);
				if (iFace == m_temp_card2.GetFace())
					inHand = true;
			}
			cout << "invalid input";
			cin.clear();
			cin.sync();
		}
		// validation for choice of player index
		do
		{
			cin.clear();
			cin.sync();
			cout << "Choose a player to ask for (0 - 3) _\b";
		} while (!(cin >> p) || (p < 0 || p >= m_numPlayers || _next_player[p] == _current_player));
		
		//jump out when player's is being asked hand is empty
		if (0 == _next_player[p]->GetNumCards())
			return false;
		
		cout << _current_player->GetName() << " is asking " << _next_player[p]->GetName() << " for: " << iFace << endl;

		for (int i = 0; i < _next_player[p]->GetNumCards(); i++)
		{
			_next_player[p]->GetCard(i, m_temp_card2);
			if (m_temp_card2.GetFace() == iFace)
			{
				_next_player[p]->Discard(i, m_temp_card2);
				_current_player->AddCard(m_temp_card2);
				return true;
			}
		}
		return false;
	}
	else
	{
		// Computer behavior
		do
		{
			p = rand() % m_numPlayers;
		} while (p < 0 || p >= m_numPlayers || _next_player[p] == _current_player);
		//jump out when player's is being asked hand is empty
		if (0 == _next_player[p]->GetNumCards())
			return false;

		int iCount{ 0 };		
		iCount = rand() % _current_player->GetNumCards();
		_current_player->GetCard(iCount, m_temp_card1);
		iFace = m_temp_card1.GetFace();
		cout << _current_player->GetName() << " is asking " << _next_player[p]->GetName() << " for: " << iFace << endl;

		for (int i = 0; i < _next_player[p]->GetNumCards(); i++)
		{
			_next_player[p]->GetCard(i, m_temp_card2);
			if (m_temp_card2.GetFace() == iFace)
			{
				_next_player[p]->Discard(i, m_temp_card2);
				_current_player->AddCard(m_temp_card2);
				return true;
			}
		}
		return false;
	}
}

void Game::MenuCursor()
{
	//get keyboard input 
	while (true)
	{
		//a pause in case loops too quick before user release the key
		Sleep(500);
		if (GetAsyncKeyState(VK_UP))
		{
			if (Console::CursorTop() == QUITBUTTON)
			{
				Console::SetCursorPosition(CURSORLEFT, STARTBUTTON);
			}
			else
			{
				Console::SetCursorPosition(CURSORLEFT, QUITBUTTON);
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (Console::CursorTop() == STARTBUTTON)
			{
				Console::SetCursorPosition(CURSORLEFT, QUITBUTTON);
			}
			else
			{
				Console::SetCursorPosition(CURSORLEFT, STARTBUTTON);
			}
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			if (QUITBUTTON == Console::CursorTop())
			{
				SetState(GAME_END);
				break;
			}
			else
			{
				Console::Clear();
				SetState(GAME_PLAY);
				break;
			}
		}
	}
}

