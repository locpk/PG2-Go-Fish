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
	m_deck_temp = new Card;
	m_player_temp = new Card;
	m_pair_check1 = new Card;
	m_pair_check2 = new Card;
	m_pair_discard1 = new Card;
	m_pair_discard2 = new Card;
	m_title_art = ifstream(m_filename);
}

// Dtor
Game::~Game()
{
	delete m_deck_temp;
	m_deck_temp = nullptr;
	delete m_player_temp;
	m_player_temp = nullptr;
	delete m_pair_check1;
	m_pair_check1 = nullptr;
	delete m_pair_check2;
	m_pair_check2 = nullptr;
	delete m_pair_discard1;
	m_pair_discard1 = nullptr;
	delete m_pair_discard2;
	m_pair_discard2 = nullptr;
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
			m_players[0] = new Human;
			m_numPlayers++;
			m_players[1] = new Computer;
			m_numPlayers++;

			m_Deck.Shuffle();
			
			//draw 7 card for player 0
			for (size_t i = 0; i < 7; i++)
			{
				m_Deck.Draw(*m_deck_temp);
				m_players[0]->AddCard(*m_deck_temp);
			}
			

			//draw 7 card for player 1
			for (size_t i = 0; i < 7 && !m_Deck.IsEmpty(); i++)
			{
				m_Deck.Draw(*m_deck_temp);
				m_players[1]->AddCard(*m_deck_temp);
			}
			
			
			
			SetState(GAME_MENU);
			break;
		case GAME_MENU:
			// Insert menu code here.
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
			break;
		case GAME_PLAY:
			// Insert game play code here.
			for (int m_currPlayer = 0; m_currPlayer <= m_numPlayers; m_currPlayer++)
			{
				if (m_currPlayer == m_numPlayers || NULL == m_players[m_currPlayer] ) //reset players let them take turns
					m_currPlayer = 0;

				Score(m_players[m_currPlayer]); // check pairs
				Sleep(1500);
				Console::Clear();
				cout << "Pairs Checked!" << endl;
				if (1 == m_currPlayer)
				{
					ShowHands(m_players[m_currPlayer]);
					ShowHands(m_players[m_currPlayer - 1]);
				}
				else
				{
					ShowHands(m_players[m_currPlayer]);
					ShowHands(m_players[m_currPlayer + 1]);
				}

				if (0 == m_players[m_currPlayer]->GetNumCards())
				{
					for (size_t i = 0; i < 7; i++)
					{
						if(m_Deck.Draw(*m_deck_temp))
							m_players[m_currPlayer]->AddCard(*m_deck_temp);
					}
				}
				if (m_Deck.IsEmpty() && 0 == m_players[0]->GetNumCards() || 0 == m_players[1]->GetNumCards()) // game over condition without allowing quiting game
				{
					SetState(GAME_END);
					break;
				}

				if (1 == m_currPlayer) // if current player is the second player
				{
					if (!AskCard(m_players[m_currPlayer], m_players[m_currPlayer - 1])) // if ask card fails draw from deck
					{
						if (m_Deck.Draw(*m_deck_temp))
							m_players[m_currPlayer]->AddCard(*m_deck_temp);
						cout << endl << m_players[m_currPlayer]->GetName() << " draws from the deck." << endl;
					}
				}
				// if current player is the first player
				else
				{
					if (!AskCard(m_players[m_currPlayer], m_players[m_currPlayer + 1])) // if ask card fails draw from deck
					{
						if (m_Deck.Draw(*m_deck_temp))
							m_players[m_currPlayer]->AddCard(*m_deck_temp);
						cout << endl << m_players[m_currPlayer]->GetName() << " draws from the deck." << endl;
					}
				}
				
			}
			Console::BackgroundColor(Blue);
			cout << "Game ENDs!" << endl;
			for (int i = 0; i < m_numPlayers; i++)
			{
				cout << m_players[i]->GetName() << "'s FINAL SCORE is: ";
				cout << m_players[i]->GetScore() << endl;
			}
			Console::ResetColor();
			Sleep(6000);
			SetState(GAME_END);
			break;
		case GAME_END:
			// The game is over, change the bool to stop the loop.
			bRun = false;
			Console::Clear();
			cout << "Bye Bye!" << endl;
			Console::Lock(false);
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
int Game::Score(Player* _player)
{
	int iPairs{0};
	//pair checking
	for (int i = 0; i < _player->GetNumCards(); i++)
	{
		_player->GetCard(i, *m_pair_check1);
		for (int j = i + 1; j < _player->GetNumCards(); j++)
		{
			
			_player->GetCard(j, *m_pair_check2);
			if (m_pair_check1->GetFace() == m_pair_check2->GetFace())
			{
				_player->Discard(i, *m_pair_discard1);
				_player->Discard(--j, *m_pair_discard2);
				iPairs++;
				i = 0;
				_player->AddToScore(1);
				break;
			}
		}
	}
	_player->SortCardsbySuit();
	return iPairs;
}

bool Game::AskCard(Player* _current_player, Player* _next_player)
{
	int iFace = 0;
	if (NULL == dynamic_cast<Computer*>(_current_player))
	{
		//Human player behavior
		cout << "What do you want? _\b";
		while (!(cin >> iFace))
		{
			cin.clear();
			cin.sync();
		}
		for (int i = 0; i < _next_player->GetNumCards(); i++)
		{
			if (_next_player->GetCard(i, *m_player_temp))
			{
				if (m_player_temp->GetFace() == iFace)
				{
					_next_player->Discard(i, *m_player_temp);
					for (int j = 0; j < _current_player->GetNumCards(); j++)
					{
						_current_player->GetCard(j, *m_player_temp);
						if (m_player_temp->GetFace() == iFace)
							_current_player->Discard(j, *m_player_temp);
					}
					_current_player->AddToScore(1);
					return true;
				}
			}
		}
		return false;
	}
	else if (NULL == _next_player)
		return false;
	else
	{
		// Computer behavior
		int iMin{ 0 }, iMax{ 0 };
		_current_player->SortCardsbyNum();
		_current_player->GetCard(0, *m_player_temp);
		iMin = m_player_temp->GetFace();
		_current_player->GetCard(_current_player->GetNumCards() - 1, *m_player_temp);
		iMax = m_player_temp->GetFace();

		iFace = rand() % iMax + iMin;
		for (int i = 0; i < _next_player->GetNumCards(); i++)
		{
			if (_next_player->GetCard(i, *m_player_temp))
			{
				if (m_player_temp->GetFace() == iFace)
				{
					_next_player->Discard(i, *m_player_temp);
					for (int j = 0; j < _current_player->GetNumCards(); j++)
					{
						_current_player->GetCard(j, *m_player_temp);
						if (m_player_temp->GetFace() == iFace)
							_current_player->Discard(j, *m_player_temp);
					}
					_current_player->AddToScore(1);
					return true;
				}
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
		Console::Lock(false);
	}
}

void Game::ShowHands(Player* _player)
{
	if (0 != _player->GetNumCards())
	{
		cout << endl << _player->GetName() << " currently has:" << endl;
		_player->Show();
	}
}