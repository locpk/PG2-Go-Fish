#pragma once
#include "Card.h"
/*
	Stacks use FILO (First In, Last Out) ordering
			   LIFO (Last In, First Out

		Ex:	Toilet paper, boxes, Pringles, bullets in a magazine

*/

// Provides an alias for a datatype
typedef Card Item;	// similar to "#define Item float"

// A singly-linked list using FILO ordering
class Stack
{
private:

	struct node
	{
		Item m_data;	// The thing we're storing (the "element")
		node* m_next;	// The next node in the list
	};

	// Initializing a struct
	// node n = { 5, NULL };

	node* m_top;		// Newest thing in the list
	int m_currSize;		// Size of the list

public:

	// Def ctor
	// Creates an empty list
	Stack();

	// Dtor
	~Stack();

	// Get the current size
	int GetCurrSize() const { return m_currSize;  }

	// Add something to the top of the stack
	// In:	_info		The value to add
	//
	// Return: True, if successful
	bool Push(const Item& _info);

	// Remove the top thing from the stack
	// In:	_info		A "blank" value
	//
	// Out: _info		The value that was at the top
	// Return: True, if something was removed
	bool Pop(Item& _info);

	// Clear the stack for re-use
	void Clear();

	// Look at the top-most piece of data without removing it
	const Item* Peek() const;
};

