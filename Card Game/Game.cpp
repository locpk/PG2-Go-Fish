#include "Game.h"

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
	m_deck_temp = new Card();
	m_player_temp = new Card();
	m_pair_check1 = new Card();
	m_pair_check2 = new Card();
	m_pair_discard1 = new Card();
	m_pair_discard2 = new Card();
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
		ifstream Reader("asc.txt");
		switch(m_state)
		{
		case GAME_INIT:
			// Insert initialization code here.
			m_players[0] = new Human();
			m_numPlayers++;
			m_players[1] = new Computer();
			m_numPlayers++;
			
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
			system("pause");
			SetState(GAME_PLAY);
			break;
		case GAME_PLAY:
			// Insert game play code here.
			for (int m_currPlayer = 0; m_currPlayer <= m_numPlayers; m_currPlayer++)
			{
				if (m_currPlayer == m_numPlayers || NULL == m_players[m_currPlayer] ) //reset players let them take turns
					m_currPlayer = 0;
				Score(m_players[m_currPlayer]); // check pairs
				if (m_Deck.IsEmpty()) // game over condition without allowing quiting game
				{
					SetState(GAME_END);
					break;
				}
				if (0 == m_players[m_currPlayer]->GetNumCards())
				{
					for (size_t i = 0; i < 7; i++)
					{
						if(m_Deck.Draw(*m_deck_temp))
							m_players[m_currPlayer]->AddCard(*m_deck_temp);
					}
				}
				if (1 == m_currPlayer) // for two players
				{
					if (!AskCard(m_players[m_currPlayer], m_players[m_currPlayer - 1])) // if askcard fails draw from deck
					{
						if (m_Deck.Draw(*m_deck_temp))
							m_players[m_currPlayer]->AddCard(*m_deck_temp);
						cout << endl << "Ask fails, Draw from deck" << endl;
					}
				}
				if (!AskCard(m_players[m_currPlayer], m_players[m_currPlayer + 1])) // if askcard fails draw from deck
				{
					if (m_Deck.Draw(*m_deck_temp))
						m_players[m_currPlayer]->AddCard(*m_deck_temp);
					cout << endl << "Ask fails, Draw from deck" << endl;
				}
				
			}
			SetState(GAME_END);
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
	cout << "Pair Checked for:" << _player->GetName() << endl;
	_player->SortCardsbySuit();
	_player->Show();
	return iPairs;
}

bool Game::AskCard(Player* _current_player, Player* _next_player)
{
	int iFace = 0;
	if (dynamic_cast<Computer*>(_current_player) == NULL)
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