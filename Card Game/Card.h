#pragma once
#include "stdafx.h"


class Card
{
	// Needed for unit tests
	// DO NOT REMOVE OR RENAME
	int m_face;		// 2-14, with 14 being the Ace
	char m_suit;	// 3-6 (3 = Hearts, 4 = Diamonds, 5 = Clubs, 6 = Spades)

public:

	// Default constructor
	// In:	_face			The face value of the card
	//		_suit			The suit of the card
	/* TODO Lab1:
			Make the default values for a card the 2 of hearts
	*/
	Card(int _face = 2, char _suit = 3);
	
	// Destructor
	~Card();

	/* Accessors */

	/* TODO:
			Define the two "Get" methods.  These should return the 
			corresponding values from the invoking object.

			These can be inlined if desired.
	*/
	int GetFace() const;
	char GetSuit() const;

	/* Mutators */

	/* TODO Lab1:
			Define the two "Set" methods.  These should set the
			corresponding value of the invoking object to the 
			value that is being passed in.

			These can be inlined if desired.
	*/
	void SetFace(int _face);
	void SetSuit(char _suit);

	// Display a card to the screen
	void Show() const;

	// Relational operators
	
	/* TODO Lab1:
			Prototype and define the six relational operators to compare cards.

			These methods will only be comparing the face of the cards, not the face and the suit.

			These can be inlined if desired.
	*/
#define CARD_REL_OP(op)\
	inline bool operator op(const Card& rhs) const\
	{\
		return this->m_face op rhs.m_face;\
	}
	
		CARD_REL_OP(==)
		CARD_REL_OP(!=)
		CARD_REL_OP(>)
		CARD_REL_OP(<)
		CARD_REL_OP(>=)
		CARD_REL_OP(<=)
	

	// Insertion operator to display Cards with cout (or any other ostream object)

	/* TODO Lab1:
			Prototype the insertion operator for the Card class.
	*/
	friend ostream& operator<<(ostream& os, const Card& rhs);





	// Needed for unit tests
	// DO NOT REMOVE
	friend class CTestManager;

};

