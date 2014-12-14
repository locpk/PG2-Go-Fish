#include "Computer.h"

// Default ctor
Computer::Computer(const char* _name)
	: Player(_name)
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
	Console::ForegroundColor(Red);
	cout << endl << "\t" << Player::GetName() << "'s Current score is:" << Player::GetScore() << endl;
	Card tempCard;
	int currentheight = Console::CursorTop();
	for (int i = 0; i < Player::GetNumCards(); i++)
	{
		Player::GetCard(i, tempCard);
		std::wcout.imbue(std::locale(".OCP"));
		wchar_t const *DoubleLine = L"╔═╗║╚╝";
		Console::BackgroundColor(White);
		if (5 == tempCard.GetSuit() || 6 == tempCard.GetSuit())
			Console::ForegroundColor(Red);
		else
			Console::ForegroundColor(Black);
		//uncomment following lines to display computer's cards
		/*switch (tempCard.GetFace())
		{
		case 10:
			cout << setw(2)<< tempCard.GetFace();
			break;
		case 11:
			cout << 'J';
			break;
		case 12:
			cout << 'Q';
			break;
		case 13:
			cout << 'K';
			break;
		case 14:
			cout << 'A';
			break;
		default:
			cout << tempCard.GetFace();
			break;
		}*/
		cout << '?';
		wcout  << DoubleLine[1] << DoubleLine[1] << DoubleLine[1] << DoubleLine[2];
		Console::SetCursorPosition(Console::CursorLeft() - 5, Console::CursorTop() + 1);
		wcout << DoubleLine[3];
		
		cout << " " << tempCard.GetSuit() << " ";
		wcout << DoubleLine[3];
		Console::SetCursorPosition(Console::CursorLeft() - 5, Console::CursorTop() + 1);
		wcout << DoubleLine[4] << DoubleLine[1] << DoubleLine[1] << DoubleLine[1];
		//uncomment following lines to display computer's cards
		/*switch (tempCard.GetFace())
		{
		case 11:
			cout << 'J';
			break;
		case 12:
			cout << 'Q';
			break;
		case 13:
			cout << 'K';
			break;
		case 14:
			cout << 'A';
			break;
		default:
			cout << tempCard.GetFace();
			break;
		}*/
		cout << '?';
		Console::ResetColor();
		cout << " ";
		Console::SetCursorPosition(Console::CursorLeft(), currentheight);
	}
	cout <<"\n\n\n\n";
	Console::ResetColor();
}
