#include "Human.h"

// Default ctor
Human::Human(const char* _name) 
	: Player(_name,52)
{
	/* TODO Lab2:
	Implement this method.

	Send back the appropriate information to the parent/base class.
	*/
}

// Display the computer's name and card backs
void Human::Show() const
{
	/* TODO Lab2:
	Implement this method.

	Should display the name of the player as well as their card faces

	Example:		Human
					7♥ 3♣ 5♦ 9♥

	*/
	Console::ForegroundColor(Cyan);
	cout << endl << Player::GetName() << "'s Current score is:" << Player::GetScore() << endl;
	Card tempCard;
	for (int i = 0; i < Player::GetNumCards(); i++)
	{
		Player::GetCard(i, tempCard);
		cout << tempCard.GetFace() << tempCard.GetSuit() << "\t";
	}
	cout << endl;
	Console::ResetColor();
}