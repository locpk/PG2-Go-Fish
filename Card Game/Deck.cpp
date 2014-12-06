#include "Deck.h"
struct SortByX
{
	bool operator () (Card const & L, Card const & R) { return L.GetSuit() < R.GetSuit(); }
};
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
	for (size_t i = 3; i <= 6; i++)
	{
		for (size_t j = 2; j <= 14; j++)
		{
			m_cards[index].SetSuit(i);
			m_cards[index].SetFace(j);
			index++;
		}
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
		swap(m_cards[i], m_cards[index]);
	}
	for (size_t i = 0; i < 52; i++)
	{
		m_Stack.Push(m_cards[i]);
	}

	cout << "Shuffling\n";
	for (int i = 0; i < 52; i++)
	{
		cout << m_cards[i] << "  ";

	}
	cout << "\n";
	//first sort by suit
	sort(m_cards, m_cards + 51, SortByX());
	int begin = 0;
	//loop to group different suits, set flags to the start index of different suit.
	for (size_t i = 0; i < 52; i++)
	{
		if (m_cards[begin].GetSuit() != m_cards[i].GetSuit())
		{
			sort(m_cards + begin, m_cards + (i - 1));

			begin = i;
		}
	}
	//sort the groups, within sorting by face.
	cout << "Sorting \n";
	for (int i = 0; i < 52; i++)
	{
		cout << m_cards[i] << "  ";

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
	
	if (FALSE == m_Stack.Pop(_card))
		return false;
	else
	{
		return true;
	}
	// Just here for compilation
	
}

// Clear the stack for re-use
void Deck::Clear()
{
	/* TODO Lab3:
			Implement this method.
	*/
		m_Stack.Clear();

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
	if (NULL == m_Stack.Peek())
		return true;
	// Just here for compilation
	else
		return false;
}