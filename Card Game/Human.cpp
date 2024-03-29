﻿#include "Human.h"

// Default ctor
Human::Human(const char* _name) 
	: Player(_name)
{
	/* TODO Lab2:
	Implement this method.

	Send back the appropriate information to the parent/base class.
	*/
}

// Display the computer's name and card backs
void Human::Show(bool is_current) const
{
	/* TODO Lab2:
	Implement this method.

	Should display the name of the player as well as their card faces

	Example:		Human
					7♥ 3♣ 5♦ 9♥

	*/
	Console::ForegroundColor(Cyan);
	cout << endl << "\t" << Player::GetName() << "'s Current score is:" << Player::GetScore() << endl;
	Card tempCard;
	int currentheight = Console::CursorTop();
	for (int i = 0; i < Player::GetNumCards(); i++)
	{
		Console::BackgroundColor(White);
		Player::GetCard(i, tempCard);
		std::wcout.imbue(std::locale(".OCP"));
		wchar_t const *DoubleLine = L"╔═╗║╚╝";
		if (5 == tempCard.GetSuit() || 6 == tempCard.GetSuit())
			Console::ForegroundColor(Red);
		else
			Console::ForegroundColor(Black);
		if (is_current || m_cheat1)
		{
			switch (tempCard.GetFace())
			{
			case 10:
				cout << setw(2) << tempCard.GetFace();
				wcout << DoubleLine[1] << DoubleLine[1] << DoubleLine[2];
				break;
			case 11:
				cout << 'J';
				wcout << DoubleLine[1] << DoubleLine[1] << DoubleLine[1] << DoubleLine[2];
				break;
			case 12:
				cout << 'Q';
				wcout << DoubleLine[1] << DoubleLine[1] << DoubleLine[1] << DoubleLine[2];
				break;
			case 13:
				cout << 'K';
				wcout << DoubleLine[1] << DoubleLine[1] << DoubleLine[1] << DoubleLine[2];
				break;
			case 14:
				cout << 'A';
				wcout << DoubleLine[1] << DoubleLine[1] << DoubleLine[1] << DoubleLine[2];
				break;
			default:
				cout << tempCard.GetFace();
				wcout << DoubleLine[1] << DoubleLine[1] << DoubleLine[1] << DoubleLine[2];
				break;
			}
		}
		else
		{
			cout << '?';
			wcout << DoubleLine[1] << DoubleLine[1] << DoubleLine[1] << DoubleLine[2];
		}
		
		Console::SetCursorPosition(Console::CursorLeft() - 5, Console::CursorTop() + 1);
		wcout << DoubleLine[3];
		cout << " " << tempCard.GetSuit() << " ";
		wcout << DoubleLine[3];
		Console::SetCursorPosition(Console::CursorLeft() - 5, Console::CursorTop() + 1);
		if (is_current || m_cheat1)
		{
			switch (tempCard.GetFace())
			{
			case 10:
				wcout << DoubleLine[4] << DoubleLine[1] << DoubleLine[1];
				cout << tempCard.GetFace();
				break;
			case 11:
				wcout << DoubleLine[4] << DoubleLine[1] << DoubleLine[1] << DoubleLine[1];
				cout << 'J';
				break;
			case 12:
				wcout << DoubleLine[4] << DoubleLine[1] << DoubleLine[1] << DoubleLine[1];
				cout << 'Q';
				break;
			case 13:
				wcout << DoubleLine[4] << DoubleLine[1] << DoubleLine[1] << DoubleLine[1];
				cout << 'K';
				break;
			case 14:
				wcout << DoubleLine[4] << DoubleLine[1] << DoubleLine[1] << DoubleLine[1];
				cout << 'A';
				break;
			default:
				wcout << DoubleLine[4] << DoubleLine[1] << DoubleLine[1] << DoubleLine[1];
				cout << tempCard.GetFace();
				break;
			}
		}
		else
		{
			wcout << DoubleLine[4] << DoubleLine[1] << DoubleLine[1] << DoubleLine[1];
			cout << '?';
		}
		Console::ResetColor();
		cout << " ";
		Console::SetCursorPosition(Console::CursorLeft(), currentheight);
	}
	cout << "\n\n\n\n";
	Console::ResetColor();
}