#pragma once
#include <iostream>
using namespace std;

#include "Player.h"
#include "Deck.h"
#include "Human.h"
#include "Computer.h"
// Enum of gamestates, you can add and remove from this if you need additional ones (examples include: GAME_TITLE, GAME_MENU, GAME_OPTIONS, etc).
enum GAMESTATE { GAME_INIT, GAME_TITLE, GAME_MENU, GAME_PLAY, GAME_END, ROUND_INIT, ROUND_END};
struct Leaderboard
{
	char m_name[20];
	unsigned int m_score{0};
	bool operator ()(Leaderboard _lhs, Leaderboard _rhs) { return _lhs.m_score > _rhs.m_score; }
};

class Game
{
	// Necessary data members
	Player* m_players[4];	// The players in the game
	Deck m_Deck;			// The deck of cards
	int m_currPlayer;		// Keeps track of which index is currently taking their turn
	int m_numPlayers;		// The number of players playing in the game


	// If you're coding UNO, this data member is necessary as well
	/*
		bool m_reversed;			// Keeps track of the order of play
	*/

	// GAMESTATE object to store the game's current state.
	GAMESTATE m_state;

	// Add game data members as necessary
	int isComputer;
	ifstream m_title_art;
	const char* m_filename;
	Card m_temp_card1;
	Card m_temp_card2;
	ISoundEngine* engine;
	int m_Winner;
	int m_MaxScore;
	std::string m_line;
	std::vector<Leaderboard> m_TempLB; //a array of leader board info
	Leaderboard Winner;
public:
	// Default ctor
	Game();

	// Dtor
	~Game();

	// The main function of the game, this loops until a certain gamestate is set.
	void Run();

	// Modifier for the gamestate data member.
	void SetState(GAMESTATE _state) { m_state = _state; }

	// Get the score for the game
	//	For Go Fish, this will take care of pairing
	//  For UNO, this will be used for end of round scoring.
	 int Score(Player* _player);
	 bool AskCard(Player* _current_player, Player** _next_player);
	 void MenuCursor();
	 void CheatMenu();
	 void Read(std::vector<Leaderboard>& _in);
	 void Write(std::vector<Leaderboard>& _in);
	 GAMESTATE Replay();
	 void Intro();
};