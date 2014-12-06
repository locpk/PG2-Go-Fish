#include "Computer.h"

// Default ctor
Computer::Computer(const char* _name)
{
	/* TODO Lab2:
			Implement this method.
	
			Send back the appropriate information to the parent/base class.
	*/
	Player::SetName(_name);
}

// Display the computer's name and card backs
void Computer::Show() const
{
	/* TODO Lab2:
			Implement this method.
	
			Should display the name of the player as well as their card backs.

			Example:		Computer
							XX XX XX XX

	*/
	cout << Player::GetName() << endl;
	Card tempCard;
	for (int i = 0; i < Player::GetNumCards(); i++)
	{
		Player::GetCard(i, tempCard);
		cout << "XX" << "\t";
	}
}
