#pragma once
#include "stdafx.h"
#include "Card.h"

/* TODO Lab7:
		Turn the Player class into an ABC.

		Make any methods used in all child classes pure virtual.
*/

class Player
{

private:

	// Needed for unit tests
	// DO NOT REMOVE OR RENAME

	/* TODO Lab4:
			Turn the name and hand data members into dynamic arrays.
	*/
	char* m_name;			// Can change size of array if needed
	Card* m_hand;				// Can change size of array if needed

	int m_numCards;				// The number of cards the player is currently holding
	
	/* TODO Lab5:
			Update m_maxCards to be a const data member
	*/
	const int m_maxCards;				// The number of cards the player can store (the number of elements in Hand)
	int m_score;				// For "Go Fish," this will represent the number of pairs.  For "UNO," it will be the player's accumulated score
	bool isPlaying;
protected:
	bool m_cheat1;
	bool m_cheat2;
	bool m_cheat3;
	
public:
	static unsigned char m_bytes;
	// Default ctor
	// In:	_name			The player's name
	//		_maxCards		The maximum number of cards they can store
	
	/* TODO Lab2:
			Make the default values "Player" and 7
	*/
	Player(const char* _name = "Player", int _maxCards = 20);

	/* TODO Lab4:
			Prototype the copy constructor
	*/
	Player(const Player& _obj);



	// Dtor
	/*
		TODO Lab2:
			Make sure that all destructors are called in the case of upcast objects.
	*/
	virtual ~Player() = 0;

	/* TODO Lab4:
			Prototype the assignment operator
	*/
	Player& operator =(const Player& _obj);
	/* Accessors */

	/* TODO Lab2:
			Define the "Get" methods.  These should return the
			corresponding values from the invoking object.

			These can be inlined if desired.
	*/
	inline bool IsPlaying() const { return isPlaying; }
	inline const char* GetName() const { return m_name; }
	inline int GetNumCards() const { return m_numCards; }
	inline int GetMaxCards() const { return m_maxCards; }
	inline int GetScore() const { return m_score; }
	inline bool GetCheat1() const { return m_cheat1; }
	inline bool GetCheat2() const { return m_cheat2; }
	inline bool GetCheat3() const { return m_cheat3; }
	// Do not inline this next method
	
	// Access a Card from the player's hand
	// In:	_index		The index of the card being accessed
	//		_card		A reference to store that value in
	//
	// Return: True if there was a card actually stored at that index.
	//		   False if the index was "empty"
	bool GetCard(int _index, Card& _card) const;

	/* Mutators */

	// Change the player's name to the value passed in
	void SetName(const char* _name); 

	inline void SetIsPlaying(bool flag) { isPlaying = flag; }
	void SetCheats(unsigned int in);
	void Player::SetCheat1(bool _in);
	void Player::SetCheat2(bool _in);
	void Player::SetCheat3(bool _in);
	// Update the player's score by some amount
	void AddToScore(int _add);

	// Add a Card to the player's hand
	// In:	_card		The card being added
	//
	// Return: True if the card was successfully added to their hand
	//		   False if the player's hand was already full
	bool AddCard(const Card& _card);
	
	// Remove a Card from the player's hand
	// In:	_index		The index of the card to remove from the array
	//		_card		A reference to store that value in
	//
	// Return: True if there was a card actually stored at that index.
	//		   False if the index was "empty"
	bool Discard(int _index, Card& _discard);

	// Clear the player's hand so that they are holding 0 cards
	void Clear();

	// Display method (empty for this class)
	

	bool SortCardsbySuit();
	bool SortCardsbyNum();


	/* TODO Lab2:
			Allow this method to be overridden in child classes.
	*/
	virtual	void Show(bool is_current) const = 0;
	
	// Needed for unit tests
	// DO NOT REMOVE
	friend class CTestManager;
	
};

