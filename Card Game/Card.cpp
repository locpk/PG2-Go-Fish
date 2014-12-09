#include "Card.h"

// Default constructor
// In:	_face			The face value of the card
//		_suit			The suit of the card

Card::Card(int _face, char _suit)
{
	/* TODO Lab1: 
			Fill out the constructor body
	*/
	m_face = _face;
	m_suit = _suit;
}
Card& Card::operator =(const Card& _obj)
{
	m_face = _obj.m_face;
	m_suit = _obj.m_suit;
	return *this;
}
Card::~Card()
{

}


/* Accessors */

/* TODO Lab1:
		Define the two accessors if they were not inlined.
*/
int Card::GetFace() const
{
	return m_face;
}

char Card::GetSuit() const
{
	return m_suit;
}
/* Mutators */

/* TODO Lab1:
		Define the two mutators if they were not inlined.
*/

void Card::SetFace(int _face)
{
	m_face = _face;
}
void Card::SetSuit(char _suit)
{
	m_suit = _suit;
}
// Display a card to the screen
void Card::Show() const
{
	/* TODO Lab1:
			Display the Card object.  

			Make sure that "face" cards (Jack-Ace) display as 'J', 'Q', 'K', 'A'
			or something similar instead of their numeric value.

			*Note - This unit test is not automated, so make sure you verify 
			the face card is displaying correctly.
	*/
	switch (m_face)
	{
	case 11:
		cout << 'J' << ' ' << m_suit;
		break;
	case 12:
		cout << 'Q' << ' ' << m_suit;
		break;
	case 13:
		cout << 'K' << ' ' << m_suit;
		break;
	case 14:
		cout << 'A' << ' ' << m_suit;
		break;
	default:
		cout << m_face << ' ' << m_suit;
		break;
	}
}

// Relational operators

/* TODO Lab1:
		Define the six relational operators if they were not inlined.
*/

// Insertion operator to display Cards with cout (or any other ostream object)

/* TODO Lab1:
		Define the insertion operator to display a card.

		Make sure that "face" cards (Jack-Ace) display as 'J', 'Q', 'K', 'A'
		or something similar instead of their numeric value.

		*Note - This unit test is not automated, so make sure you verify
		the face card is displaying correctly.
*/
ostream& operator<<(ostream& os, const Card& rhs)
{	
	switch (rhs.m_face)
	{
	case 11:
		os << 'J' << ' ' << rhs.m_suit;
		break;
	case 12:
		os << 'Q' << ' ' << rhs.m_suit;
		break;
	case 13:
		os << 'K' << ' ' << rhs.m_suit;
		break;
	case 14:
		os << 'A' << ' ' << rhs.m_suit;
		break;
	default:
		os << rhs.m_face << ' ' << rhs.m_suit;
		break;
	}
	
	return os;
}