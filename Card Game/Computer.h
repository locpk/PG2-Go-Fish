#pragma once
#include "stdafx.h"
#include "Player.h"
/* TODO Lab2:
		Make Computer a child of Player
*/
class Computer : public Player
{

public:
	// Default ctor
	// In:	_name		The name of the computer player
	
	/* TODO Lab2:
			Set the default value of _name to "Computer"
	*/
	Computer(const char* _name = "Computer");

	// Display the computer's name and card backs
	void Show(bool is_current) const;
	
	// Needed for unit tests
	// DO NOT REMOVE
	friend class CTestManager;
};

