#pragma once
#include"Card.h"
#include"Player.h"
/*
	Stacks use FILO (First In, Last Out) ordering
			   LIFO (Last In, First Out)

		Ex:	PEZ dispenser, Magic:The Gathering, gun magazine

*/

typedef Card Item;// A way to provide an alias for a datatype

// A FILO sequence implemented using a singly-linked list
class Stack
{
private:

	struct Node
	{
		Item m_data;	// A piece of information
		Node* m_next;	// Next node in the list
	};

	Node* m_top;		// The newest node in the list

	int m_currSize;		// Keep track of the number allocated

public:

	// Default ctor
	// Create an empty stack
	Stack();

	// Dtor
	~Stack();

	int GetCurrSize() const { return m_currSize;  }

	// Add something to the top of the stack
	// In:	_info		The value to add
	// 
	// Return: True, if something was added
	bool Push(const Item& _info);

	// Remove the top-most value from the stack
	// In:	_info		A 'blank' value
	//
	// Out:	_info		The value that was at the top
	// Return: True, if something was removed
	bool Pop(Item& _info);

	// Clear out the stack for re-use
	void Clear();
};

