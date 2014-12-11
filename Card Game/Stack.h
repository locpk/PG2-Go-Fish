#pragma once
#include "stdafx.h"
/*
	Stacks use FILO (First In, Last Out) ordering
			   LIFO (Last In, First Out)

		Ex:	PEZ dispenser, Magic:The Gathering, gun magazine

*/

//typedef Card Item;// A way to provide an alias for a datatype

// A FILO sequence implemented using a singly-linked list
template<typename Item>
class Stack
{
private:

	struct Node
	{
		Item m_data;	// A piece of information
		Node* m_next;	// Next node in the list
		// Ctor
		Node(const Item& _info);
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


// Node Ctor
template<typename Item>
Stack<Item>::Node::Node(const Item& _info)
{
	// Fill in the data members
	m_data = _info;
	m_next = NULL;	// Since this is going to the end of the list,
	// it will always be NULL
}

// Default ctor
// Create an empty stack
template<typename Item>
Stack<Item>::Stack()
{
	m_top = NULL;
	m_currSize = 0;
}

// Dtor
template<typename Item>
Stack<Item>::~Stack()
{
	Clear();
}

// Add something to the top of the stack
// In:	_info		The value to add
// 
// Return: True, if something was added
template<typename Item>
bool Stack<Item>::Push(const Item& _info)
{
	// Need to allocate memory every time we add something
	Node* newTop = new Node(_info);

	newTop->m_next = m_top;
	// Did we run out of memory?
	if (NULL == newTop)
		return false;


	// Update the top ptr
	m_top = newTop;

	// Success
	++m_currSize;
	return true;
}

// Remove the top-most value from the stack
// In:	_info		A 'blank' value
//
// Out:	_info		The value that was at the top
// Return: True, if something was removed
template<typename Item>
bool Stack<Item>::Pop(Item& _info)
{
	// Is the list empty?
	if (!m_top)
		return false;

	// Copy the value over
	_info = m_top->m_data;

	// Need a temporary ptr to avoid a memory leak
	Node* temp = m_top;
	m_top = m_top->m_next;
	delete temp;

	// Success!
	--m_currSize;
	return true;

}

// Clear out the stack for re-use
template<typename Item>
void Stack<Item>::Clear()
{
	// Clean up any left over dynamic memory
	while (m_top != NULL)
	{
		// Need a temporary ptr to avoid a memory leak
		Node* temp = m_top;
		m_top = m_top->m_next;
		delete temp;
	}

	m_currSize = 0;
}