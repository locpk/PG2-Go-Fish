#include "Player.h"

/* TODO Lab5:
		Initialize m_maxCards in all constructors
*/

// Default ctor
// In:	_name			The player's name
//		_maxCards		The maximum number of cards they can store

Player::Player(const char* _name, int _maxCards)
{
	/* TODO Lab2/4:
			Fill out the constructor body.

			Keep in mind that there are more than two data members.
			*/
	SetName(_name);
	m_maxCards = _maxCards;
	m_numCards = 0;
	m_score = 0;
}

/* TODO Lab4:
		Define and implement the copy constructor.

		Make sure to copy all data members (using deep copies when necessary).
*/

// Dtor
Player::~Player()
{
	/* TODO Lab4:
			Clean up any dynamic memory
	*/
}

/* TODO Lab4:
		Define and implement the assignment operator.

		Make sure to copy all data members (using deep copies when necessary).

		* There will be a small change to this in Lab5 where you will have to comment out
		  the m_maxCards assignment, but go ahead and make the copy for now.
*/

/* Accessors */

/* TODO Lab2:
		Define the accessors if they were not inlined.
*/

// Access a Card from the player's hand
// In:	_index		The index of the card being accessed
//		_card		A reference to store that value in
//
// Return: True if there was a card actually stored at that index.
//		   False if the index was "empty"
bool Player::GetCard(int _index, Card& _card) const
{
	/* TODO Lab2:
			Implement this method.
	*/
	if (0 <= _index &&_index < m_numCards)
	{
		_card = m_hand[_index];
		return true;
	}	

	return false;

	// Just here for compilation
	

}

/* Mutators */

// Change the player's name to the value passed in
void Player::SetName(const char* _name)
{
	/* TODO Lab2/4:
			Implement this method.
	*/
	strcpy_s(m_name, sizeof m_name / sizeof m_name[0], _name); 
}

// Update the player's score by some amount
void Player::AddToScore(int _add)
{
	/* TODO Lab2:
			Implement this method.

			Increase their score by the amount passed in.
	*/
	m_score += _add;
}

// Add a Card to the player's hand
// In:	_card		The card being added
//
// Return: True if the card was successfully added to their hand
//		   False if the player's hand was already full
bool Player::AddCard(const Card& _card)
{
	/* TODO Lab2:
			Implement this method.

			Should store the passed card in the next available empty index (if there is one).
			You should know how many cards are in the hand to know where that
			index will be.
	*/
	if (m_numCards < m_maxCards)
	{
		m_hand[m_numCards] = _card;
		m_numCards++;
		return true;
	}
		return false;
	// Just here for compilation
	
}

// Remove a Card from the player's hand
// In:	_index		The index of the card to remove from the array
//		_card		A reference to store that value in
//
// Return: True if there was a card actually stored at that index.
//		   False if the index was "empty"
bool Player::Discard(int _index, Card& _discard)
{
	/* TODO Lab2:
			Implement this method.
	
			Should store the requested card into the reference being passed in.
			After that, "shift" the array back to show this card has been removed.

			Example:
			[ 7♥ 3♣ 5♦ 9♥ ]		m_numCards: 4

					* discarding index 1 (the 3♣) *

			[ 7♥ 5♦ 9♥ 9♥ ]		m_numCards: 3

					* Even though it looks like there are two 9♥, we won't ever be displaying
					  that to the user, and it will be the first one that gets overwritten if 
					  another card is added to the hand. *
	*/
	if (0 <= _index && _index < m_numCards)
	{
		_discard = m_hand[_index];
		for (int i = _index; i < m_numCards; i++)
		{
			m_hand[i] = m_hand[i + 1];
		}
		m_numCards--;
		return true;

	}
	
	return false;
	// Just here for compilation
	
}

// Clear the player's hand so that they are holding 0 cards
void Player::Clear()
{
	/* TODO Lab2:
			Implement this method.
	*/
	m_numCards = 0;
}

// Display method (empty for this class)
void Player::Show() const
{

}