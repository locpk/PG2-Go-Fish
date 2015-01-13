#include "Game.h"
//define menu layout positions
#define CURSORLEFT Console::WindowWidth() /2 -5
#define STARTBUTTON 25
#define INTROBUTTON 26
#define QUITBUTTON 27
//turn on music here
#define MUSIC TRUE
//set QUICK_TEST to TRUE and  hold return key to quick run through a AI vs AI game
#define QUICK_TEST FALSE
// Default ctor
Game::Game() : m_filename("asc2.txt")
{
	
	m_state = GAME_INIT;
	for (size_t i = 0; i < 4; i++)
	{
		m_players[i] = nullptr;
	}
	m_currPlayer = 0;
	m_numPlayers = 0;
	isComputer = 0;
	m_MaxScore = 0;
	Console::Lock(true);
#if MUSIC
	engine = createIrrKlangDevice();
#endif
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
#if MUSIC
	//play BGM and it will loop
	engine->play2D("TheForestAwakes.ogg", true);
#endif

	// Loop while our bool remains true.
	while (bRun)
	{
		//test different state 
		

		switch (m_state)
		{
		case GAME_INIT:

			// Insert initialization code here.
			while (m_numPlayers < 2 || m_numPlayers > 4)
			{
				for (;;)
				{
					Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 4);
					std::cout << "How many players? (2 - 4)";
					if (std::cin >> m_numPlayers)
					{
						std::cin.sync();
						break;
					}
					std::cin.clear();
					std::cin.sync();
				}

			}

			for (int i = 0; i < m_numPlayers; i++)
			{
				for (;;)
				{
					Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 4);
					Console::ForegroundColor(rand() % (15 - 9) + 10);
					std::cout << "Player " << i + 1 << " is computer? (0 for NO, 1 for YES)";
					if (std::cin >> isComputer && (isComputer == 0 || isComputer == 1))
					{
						std::cin.sync();
						Console::Clear();
						Console::ResetColor();
						break;
					}
					std::cin.clear();
					std::cin.sync();
				}
				if (1 == isComputer)
				{
					m_players[i] = new Computer(Console::RandomName());
				}
				else
				{
					char PlayerName[21];
					PlayerName[20] = '\0';
					Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 4);
					std::cout << " What's your name?";
					std::cin.get(PlayerName, 20, '\n');
					m_players[i] = new Human(PlayerName);
				}

			}

			//initialize player's hands
			for (int i = 0; i < m_numPlayers; i++)
			{
				//draw 7 card for the player 
				for (int j = 0; j < 7; j++)
				{
					m_Deck.Draw(m_temp_card1);
					m_players[i]->AddCard(m_temp_card1);
				}

			}
			
			Console::Clear();
			Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 2);
			m_line = ">_<...I'm Loading...I wish I am a Quantum computer.";
			for (char& c : m_line) {
				std::cout << c;
				Sleep(30);
			}
			Sleep(1000);
			Console::ResetColor();
			Console::Clear();
			Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 2 +1);
			Console::ForegroundColor(DarkCyan);
			/*std::cout << "Wanna cheat? (Lctrl + Return) (Return to skip.)";
			Console::ResetColor();
			for (;;)
			{
				Console::FlushKeys();
				if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000f) && (GetAsyncKeyState(VK_RETURN) & 0x8000f))
				{
					Console::FlushKeys();
					CheatMenu();
					break;
				}
				else if ((GetAsyncKeyState(VK_RETURN) & 0x8000f))
				{
					Console::FlushKeys();
					break;
				}
			}*/
			Sleep(250);
			SetState(GAME_MENU);
			break;
		case GAME_MENU:
			// Insert menu code here.
			Console::FlushKeys();
#if MUSIC
			engine->setAllSoundsPaused(false);
#endif
			Console::Clear();
			//show title art
			m_title_art = ifstream(m_filename);
			if (m_title_art.is_open())
			{
				while (m_title_art.good())
				{
					std::string TempLine;
					std::getline(m_title_art, TempLine);
					TempLine += "\n";
					Console::ForegroundColor(rand() % (15-9) + 9);
					std::cout << TempLine;
				}
				m_title_art.close();
			}
			else
			{
				Console::Clear();
				Console::SetCursorPosition(Console::WindowWidth() / 3, Console::WindowHeight() / 2);
				std::cout << "Title Art File does not exist.";
			}

			Console::ResetColor();
			/*_¦¦¦¦¦¦_   _¦¦¦¦¦¦_          _¦¦¦¦¦¦¦¦  _¦     _¦¦¦¦¦¦¦¦    _¦    ¦_
				¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦        ¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦    ¦¦¦   ¦¦¦    ¦¦¦
				¦¦¦    ¦¯  ¦¦¦    ¦¦¦        ¦¦¦    ¦¯  ¦¦¦¦   ¦¦¦    ¦¯    ¦¦¦    ¦¦¦
				_¦¦¦        ¦¦¦    ¦¦¦       _¦¦¦___     ¦¦¦¦   ¦¦¦         _¦¦¦____¦¦¦__
				¯¯¦¦¦ ¦¦¦¦_  ¦¦¦    ¦¦¦      ¯¯¦¦¦¯¯¯     ¦¦¦¦ ¯¦¦¦¦¦¦¦¦¦¦¦ ¯¯¦¦¦¯¯¯¯¦¦¦¯
				¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦        ¦¦¦        ¦¦¦           ¦¦¦   ¦¦¦    ¦¦¦
				¦¦¦    ¦¦¦ ¦¦¦    ¦¦¦        ¦¦¦        ¦¦¦     _¦    ¦¦¦   ¦¦¦    ¦¦¦
				¦¦¦¦¦¦¦¦¯   ¯¦¦¦¦¦¦¯         ¦¦¦        ¦¯    _¦¦¦¦¦¦¦¦¯    ¦¦¦    ¦¯*/

			
			Console::SetCursorPosition(CURSORLEFT, STARTBUTTON);
			std::cout << ">>      " << "Start\n";
			Console::SetCursorPosition(CURSORLEFT, INTROBUTTON);
			std::cout << ">>      " << "Intro\n";
			Console::SetCursorPosition(CURSORLEFT, QUITBUTTON);
			std::cout << ">>      " << "Quit\n";
			Console::SetCursorPosition(CURSORLEFT, QUITBUTTON + 1);
			std::cout << "Try Lctrl + Return";
			Console::SetCursorPosition(CURSORLEFT, STARTBUTTON);
			MenuCursor();
			Console::FlushKeys();
#if MUSIC
			engine->setAllSoundsPaused(true);
#endif
			break;
		case GAME_PLAY:
			// Insert game play code here.
			Console::CursorVisible(false);
			for (int m_currPlayer = 0; m_currPlayer <= m_numPlayers; m_currPlayer++)
			{
				if (m_currPlayer == m_numPlayers) //reset players let them take turns
					m_currPlayer = 0;

				if (0 == m_players[m_currPlayer]->GetNumCards() && m_Deck.IsEmpty())
				{
					m_players[m_currPlayer]->SetIsPlaying(false);
				}
				// dummy game over condition without allowing quiting game
				if (m_Deck.IsEmpty())
				{
					bool keep = false;
					for (int i = 0; i < m_numPlayers; i++)
					{
						if (m_players[i]->GetNumCards() != 0)
							keep = true;
					}

					if (!keep)
					{
						SetState(GAME_END);
						break;
					}
				}
				
				if (m_players[m_currPlayer]->IsPlaying())
				{
					
					

#if QUICK_TEST
					system("pause");
#else
					Sleep(1500);
#endif
					Console::Lock(true);
					Console::Clear();
					//show each player's hand
					for (int i = 0; i < m_numPlayers; i++)
					{
						if (i == m_currPlayer)
							m_players[i]->Show(true);
						else
							m_players[i]->Show(false);
					}
					Console::Lock(false);
					// test if a player is run out of cards
					if (0 == m_players[m_currPlayer]->GetNumCards())
					{
						
						for (size_t i = 0; i < 7; i++)
						{
							if (m_Deck.Draw(m_temp_card1))
								m_players[m_currPlayer]->AddCard(m_temp_card1);
							else
								break;
						}	
					}

					
					while (AskCard(m_players[m_currPlayer], m_players)) // if ask card fails draw from deck
						{
							
						}
					/*if (m_Deck.Draw(m_temp_card1))
					{
						m_players[m_currPlayer]->AddCard(m_temp_card1);
						Console::SetCursorPosition(Console::CursorLeft(), 24);
						std::cout << "\r" << m_players[m_currPlayer]->GetName() << " draws from the deck. a " << m_temp_card1 << endl;
					}*/
					//Score(m_players[m_currPlayer]); // check pairs 
				}
			}
			//Match result
			Console::Clear();
			Console::SetCursorPosition(Console::WindowWidth() / 3, Console::WindowHeight() / 3);
			std::cout << "Game ENDs!" << endl;
			Sleep(1500);
			for (int i = 0; i < m_numPlayers; i++)
			{
				if (m_players[i]->GetScore() >= m_MaxScore)
				{
					m_MaxScore = m_players[i]->GetScore();
					m_Winner = i;
				}
				Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
				//do a type machine trick
				std::string str1 = m_players[i]->GetName();
				std::string str2 = "'s FINAL SCORE is: ";
				std::string str3 = std::to_string(m_players[i]->GetScore());
				std::string str = str1 + str2 + str3;
				for (char& c : str) {
					std::cout << c;
					Sleep(60);
				}

				Sleep(1500);
				Console::Clear();

			}
			Console::ForegroundColor(Red);
			Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
			std::cout << "The Winner is : " << m_players[m_Winner]->GetName() << " , scored " << m_players[m_Winner]->GetScore() << endl;

			//read old leaderboard
			strcpy_s(Winner.m_name, strlen(m_players[m_Winner]->GetName()) + 1, m_players[m_Winner]->GetName());
			Winner.m_score = m_players[m_Winner]->GetScore();
			Read(m_TempLB);
			//add new winner
			m_TempLB.push_back(Winner);
			std::sort(m_TempLB.begin(), m_TempLB.end(), Winner);
			//write a new leaderboard
			Write(m_TempLB);
			Sleep(4000);
			SetState(Replay());
			Console::CursorVisible(true);
			break;
		case GAME_END:
			// The game is over, change the bool to stop the loop.
#if MUSIC
			engine->drop(); // stop the music
#endif
			bRun = false;
			Console::ResetColor();
			Console::Clear();
			Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
			Console::ForegroundColor(rand() % (15 - 9) + 9);
			std::string str = "Bye Bye!";
			for (char& c : str) {
				std::cout << c;
				Sleep(150);
			}
			break;
		}
	}
}



int Game::Score(Player* _player)
{
	int iPairs{ 0 };
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
	_player->SortCardsbySuit();
	Sleep(700);
	Console::Lock(true);
	Console::Clear();
	//show each player's hand
	for (int i = 0; i < m_numPlayers; i++)
	{
		if (m_players[i] == _player)
			m_players[i]->Show(true);
		else
			m_players[i]->Show(false);
	}
	Console::Lock(false);
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
		if (!_current_player->GetCheat2())
		{
			//Human player behavior
			//check if the card the player asking for is in its hand or not
			bool inHand = false;
			Console::SetCursorPosition(Console::CursorLeft(), 23);
			std::cout << "\r" << _current_player->GetName() << " What do you want? _\b";
			for (;;)
			{
				std::cin >> iFace;
				for (int i = 0; i < _current_player->GetNumCards(); i++)
				{
					_current_player->GetCard(i, m_temp_card2);
					if (iFace == m_temp_card2.GetFace())
					{
						inHand = true;
						std::cin.clear();
						std::cin.sync();
					}
				}
				if (inHand || _current_player->GetCheat3())
				{
					std::cin.clear();
					std::cin.sync();
					break;
				}
				else
				{
					Console::SetCursorPosition(Console::CursorLeft(), 23);
					std::cout << "\r" << "Sorry! " << _current_player->GetName() << " You don't have that card in hand! _\b";
				}
			}

			// validation for choice of player index


			do
			{
				std::cin.clear();
				std::cin.sync();
				for (int i = 0; i < m_numPlayers; i++)
				{

					if (m_players[i] != _current_player)
						std::cout << i << ") " << m_players[i]->GetName() << endl;
				}
				Console::SetCursorPosition(Console::CursorLeft(), 23);
				std::cout << "\r" << "Choose a player to ask for  _\b";
			} while (!(std::cin >> p) || (p < 0 || p >= m_numPlayers || _next_player[p] == _current_player));


			//jump out when player's is being asked hand is empty
			if (0 == _next_player[p]->GetNumCards())
				return false;
			
			std::cout << "\r" << _current_player->GetName() << " is asking " << _next_player[p]->GetName() << " for: ";
			switch (iFace)
			{
			case 11:
				cout << 'J' << endl;
				break;
			case 12:
				cout << 'Q' << endl;
				break;
			case 13:
				cout << 'K' << endl;
				break;
			case 14:
				cout << 'A' << endl;
				break;
			default:
				cout << iFace << endl;
				break;
			}

			for (int i = 0; i < _next_player[p]->GetNumCards(); i++)
			{
				_next_player[p]->GetCard(i, m_temp_card2);
				if (m_temp_card2.GetFace() == iFace)
				{
					_next_player[p]->Discard(i, m_temp_card2);
					_current_player->AddCard(m_temp_card2);
					std::cout << "Keep asking.";
					Score(_current_player);
					return true;
				}
			}
			std::cout << _next_player[p]->GetName() << " : Go Fish!" << endl;
	}
		if (m_Deck.Draw(m_temp_card1))
		{
			m_players[m_currPlayer]->AddCard(m_temp_card1);
			Console::SetCursorPosition(Console::CursorLeft(), 24);
			std::cout << m_players[m_currPlayer]->GetName() << " draws from the deck. a " << m_temp_card1 << endl;
			if (m_temp_card1.GetFace() == iFace)
			{
				
				std::cout << "Keep asking.";
				Score(_current_player);
				return true;
			}
		}
		Score(_current_player);
		return false;
	}
	else
	{
		if (!_current_player->GetCheat2())
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
			std::cout << _current_player->GetName() << " is asking " << _next_player[p]->GetName() << " for: ";
			switch (iFace)
			{
			case 11:
				std::cout << 'J' << ' ' << endl;
				break;
			case 12:
				std::cout << 'Q' << ' ' << endl;
				break;
			case 13:
				std::cout << 'K' << ' ' << endl;
				break;
			case 14:
				std::cout << 'A' << ' ' << endl;
				break;
			default:
				std::cout << iFace << ' ' << endl;
				break;
			}

			for (int i = 0; i < _next_player[p]->GetNumCards(); i++)
			{
				_next_player[p]->GetCard(i, m_temp_card2);
				if (m_temp_card2.GetFace() == iFace)
				{
					_next_player[p]->Discard(i, m_temp_card2);
					_current_player->AddCard(m_temp_card2);
					std::cout << "Keep asking.";
					Score(_current_player);
					return true;
				}
			}
			std::cout << _next_player[p]->GetName() << " : Go Fish!" << endl;
		}
		if (m_Deck.Draw(m_temp_card1))
		{
			m_players[m_currPlayer]->AddCard(m_temp_card1);
			Console::SetCursorPosition(Console::CursorLeft(), 24);
			std::cout << m_players[m_currPlayer]->GetName() << " draws from the deck. a " << m_temp_card1 << endl;
			if (m_temp_card1.GetFace() == iFace)
			{
				std::cout << "Keep asking.";
				Score(_current_player);
				return true;
			}
		}
		Score(_current_player);
		return false;
	}
}

void Game::MenuCursor()
{
	bool held = false;
	//get keyboard input 
	while (true)
	{
		//a pause in case loops too quick before user release the key
		Sleep(250);
		if ((GetAsyncKeyState(VK_UP) & 0x8000f))
		{
			if (Console::CursorTop() == QUITBUTTON)
			{
				Console::SetCursorPosition(CURSORLEFT, INTROBUTTON);
			}
			else if (Console::CursorTop() == INTROBUTTON)
			{
				Console::SetCursorPosition(CURSORLEFT, STARTBUTTON);
			}
			else
			{
				Console::SetCursorPosition(CURSORLEFT, QUITBUTTON);
			}
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000f))
		{
			if (Console::CursorTop() == STARTBUTTON)
			{
				Console::SetCursorPosition(CURSORLEFT, INTROBUTTON);
			}
			else if (Console::CursorTop() == INTROBUTTON)
			{
				Console::SetCursorPosition(CURSORLEFT, QUITBUTTON);
			}
			else
			{
				Console::SetCursorPosition(CURSORLEFT, STARTBUTTON);
			}
		}
		else if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000f) && (GetAsyncKeyState(VK_RETURN) & 0x8000f))
		{
			CheatMenu();
			break;
		}
		else if ((GetAsyncKeyState(VK_RETURN) & 0x8000f))
		{
			if (QUITBUTTON == Console::CursorTop())
			{
				SetState(GAME_END);
				break;
			}
			else if (INTROBUTTON == Console::CursorTop())
			{
				Intro();
				SetState(GAME_MENU);
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

void Game::CheatMenu()
{
	Console::Clear();
	Console::SetCursorPosition(Console::WindowWidth() / 5, Console::WindowHeight() / 3);
	std::cout << "You are in cheat menu";
	Console::SetCursorPosition(Console::WindowWidth() / 5, Console::WindowHeight() / 3 + 1);
	std::cout << "Which Player are you?";
	for (int i = 0; i < m_numPlayers; i++)
	{
		Console::SetCursorPosition(Console::WindowWidth() / 5, Console::CursorTop() + 1);
		std::cout << i + 1 << "). " << m_players[i]->GetName() << endl;
	}
	int iChoice = 5;
	for (;;)
	{
		if (std::cin >> iChoice || iChoice <= 4 || iChoice > 0)
		{
			std::cin.clear();
			std::cin.sync();
			break;
		}
		std::cin.clear();
		std::cin.sync();
	}
	Console::Clear();
	for (;;)
	{
		Console::SetCursorPosition(Console::WindowWidth() / 5, Console::WindowHeight() / 3);
		std::cout << "1) See other's cards.\tLctrl + Numpad 1 (Press again to turn off)";
		Console::SetCursorPosition(Console::WindowWidth() / 5, Console::WindowHeight() / 3 + 1);
		std::cout << "2) Force other's to draw.\tLctrl + Numpad 2 (Press again to turn off)";
		Console::SetCursorPosition(Console::WindowWidth() / 5, Console::WindowHeight() / 3 + 2);
		std::cout << "3) Draw cards not in your hands.\tLctrl + Numpad 3 (Press again to turn off)";
		Console::SetCursorPosition(Console::WindowWidth() / 5, Console::WindowHeight() / 3 + 3);
		std::cout << "Lctrl + Return to exit cheats menu.";
		Console::FlushKeys();
		Console::Lock(true);
		if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000f) && (GetAsyncKeyState(VK_NUMPAD1) & 0x8000f))
		{
			for (int i = 0; i < m_numPlayers; i++)
			{
				if (i != (iChoice - 1))
				{
					m_players[i]->SetCheats(1);
					m_players[i]->SetCheat1(!m_players[i]->GetCheat1());
				}
					
			}
			Console::Clear();
			Console::Lock(false);
			
			for (int i = 0; i < m_numPlayers; i++)
			{
				if (i != (iChoice - 1))
				{
					if (m_players[i]->GetCheat1())
					{
						Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
						std::cout << "See other's cards. ON";
					}
					else
					{
						Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
						std::cout << "See other's cards. OFF";
					}
				}
			}
			Sleep(1000);
		}
		if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000f) && (GetAsyncKeyState(VK_NUMPAD2) & 0x8000f))
		{
			for (int i = 0; i < m_numPlayers; i++)
			{
				if (i != iChoice - 1)
				{
					m_players[i]->SetCheats(2);
					m_players[i]->SetCheat2(!m_players[i]->GetCheat2());
				}
			}
			Console::Clear();
			Console::Lock(false);
			Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
			for (int i = 0; i < m_numPlayers; i++)
			{
				if (i != (iChoice - 1))
				{
					if (m_players[i]->GetCheat2())
					{
						Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
						std::cout << "Force other's to draw. ON";
					}
					else
					{
						Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
						std::cout << "Force other's to draw. OFF";
					}
				}
			}
			
			Sleep(1000);
		}
		if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000f) && (GetAsyncKeyState(VK_NUMPAD3) & 0x8000f))
		{
			m_players[iChoice - 1]->SetCheats(3);
			m_players[iChoice - 1]->SetCheat3(!m_players[iChoice - 1]->GetCheat2());
			Console::Clear();
			Console::Lock(false);
			Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
			if (m_players[iChoice - 1]->GetCheat3())
			{
				Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
				std::cout << "Draw cards not in your hands. ON";
			}
			else
			{
				Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 3);
				std::cout << "Draw cards not in your hands. OFF";
			}
			Sleep(1000);
		}
		if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000f) && (GetAsyncKeyState(VK_RETURN) & 0x8000f))
		{
			Console::Lock(false);
			Sleep(1000);
			break;
		}
	}

}

void Game::Read(std::vector<Leaderboard>& _in)
{
	std::ifstream fin;
	fin.open("High Score.txt");
	if (fin.is_open())
	{
		Leaderboard temp;
			for (;;)
			{
				if (fin.peek() == '\n')
					break;
				if (fin.eof())
					break;
				fin.get(temp.m_name, sizeof temp.m_name, '\t');
				fin >> temp.m_score;
				fin.ignore(LLONG_MAX, '\n');
				_in.push_back(temp);
			}
		fin.close();
	}
	else
	{
		std::cout << "Can't read the 'High Score.txt' file.\n";
	}
}

void Game::Write(std::vector<Leaderboard>& _in)
{
	std::ofstream fout("High Score.txt");
	if (fout.is_open())
	{
		for (size_t i = 0; fout.good() && i < _in.size(); i++)
		{
			fout << _in[i].m_name << '\t' << _in[i].m_score << '\n';
		}
		if (!fout.good())
			std::cerr << "Problem writing name and score!\n";

		fout.close();
	}
	else
	{
		std::clog << "Couldn't open 'High Score.txt' for writing!\n";
	}
}

GAMESTATE Game::Replay()
{
	int iChoice = 5;
	Console::Clear();
	Console::SetCursorPosition(Console::WindowWidth() / 4, Console::WindowHeight() / 2);
	std::cout << "Do you wanna play again? 1) Yes 2)No";
	for (;;)
	{
		if (std::cin >> iChoice || 1 == iChoice || 2 == iChoice)
		{
			std::cin.clear();
			std::cin.sync();
			break;
		}
		std::cin.clear();
		std::cin.sync();
	}
	if (1 == iChoice)
	{
		m_Deck.Initialize();
		//initialize player's hands
		for (int i = 0; i < m_numPlayers; i++)
		{
			//draw 7 card for the player 
			m_players[i]->Clear();
			m_players[i]->SetIsPlaying(true);
			for (int j = 0; j < 7; j++)
			{
				m_Deck.Draw(m_temp_card1);
				m_players[i]->AddCard(m_temp_card1);
			}
		}
		return GAME_PLAY;
	}
	else
	{
		m_Deck.Initialize();
		for (int i = 0; i < m_numPlayers; i++)
		{
			delete m_players[i];
			m_players[i] = nullptr;
		}
		return GAME_MENU;
	}
}

void Game::Intro()
{
	
	Console::Clear();
	ifstream Intro = ifstream("Intro.txt");
	if (Intro)
	{
		while (Intro.good())
		{
			std::string TempLine;
			std::getline(Intro, TempLine);
			TempLine += "\n";
			std::cout << TempLine;
		}
	}
	else
	{
		Console::Clear();
		Console::SetCursorPosition(Console::WindowWidth() / 3, Console::WindowHeight() / 2);
		std::cout << "Intro File does not exist.";
	}
	system("pause");
}