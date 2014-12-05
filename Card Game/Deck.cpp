#include "Deck.h"

// Default ctor
Deck::Deck()
{
	/* TODO Lab3:
			Implement this method.

			Get everything set up by calling Initialize.
	*/
	Initialize();
}

// Sets up the array of cards to be a unique deck
void Deck::Initialize()
{
	/* TODO Lab3:
			Implement this method.
	
			Set the values in the m_cards array to be the appropriate values for your game.

			For Go Fish: 13 cards of each of the 4 suits
	*/
	
	int index = 0;
	for (size_t i = 2; i <= 14; i++)
	{
		m_cards[index] = Card(i, 3);
		index++;
	}
	for (size_t i = 2; i <= 14; i++)
	{
		m_cards[index] = Card(i, 4);
		index++;
	}
	for (size_t i = 2; i <= 14; i++)
	{
		m_cards[index] = Card(i, 5);
		index++;
	}
	for (size_t i = 2; i <= 14; i++)
	{
		m_cards[index] = Card(i, 6);
		index++;
	}
}


// Clears any cards that are already in the stack, shuffles the array, and then pushes
// all of the shuffled cards onto the stack.
void Deck::Shuffle()
{
	/* TODO Lab3:
			Implement this method.
	*/
	m_Stack.Clear();

	Card temp;
	int index;
	for (size_t i = 0; i < 52; i++)
	{
		do
		{
			index = rand() % 52 + i;
		} while (index >= 52);
		//swap 
		temp = m_cards[i];
		m_cards[i] = m_cards[index];
		m_cards[index] = temp;
	}
	for (size_t i = 0; i < 52; i++)
	{
		m_Stack.Push( m_cards[i]);
	}

}

// Draw the top-most card off of the stack
// In:	_card			A reference to store the drawn card
//
// Return: True if a card was removed
//		   False if the deck was empty
bool Deck::Draw(Card& _card)
{
	/* TODO Lab3:
			Implement this method.
	*/

	// Just here for compilation
	return true;
}

// Clear the stack for re-use
void Deck::Clear()
{
	/* TODO Lab3:
			Implement this method.
	*/
}

// Check to see if there are any cards left in the stack
//
// Return: True if the stack is empty
//		   False if there are any cards left in the stack
bool Deck::IsEmpty() const
{
	/* TODO Lab3:
			Implement this method.
	*/

	// Just here for compilation
	return true;
}