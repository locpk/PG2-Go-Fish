#include "Stack.h"
#include "stdafx.h"

// Def ctor
// Creates an empty list
Stack::Stack()
{
	m_top = NULL;
	m_currSize = 0;
}

// Dtor
Stack::~Stack()
{
	Clear();
}


// Add something to the top of the stack
// In:	_info		The value to add
//
// Return: True, if successful
bool Stack::Push(const Item& _info)
{
	// Every time you add something to a list, you need
	// to allocate the space for it
	node* newTop = new node;

	// Did we run out of memory?
	if (NULL == newTop)
		return false;

	// Fill in the node
	newTop->m_data = _info;

	// Link it into the list
	newTop->m_next = m_top;

	m_top = newTop;

	// Success
	m_currSize++;
	return true;
}

// Remove the top thing from the stack
// In:	_info		A "blank" value
//
// Out: _info		The value that was at the top
// Return: True, if something was removed
bool Stack::Pop(Item& _info)
{
	// Check to see if the list is empty
	if (!m_top)
		return false;

	// Copy over the value
	_info = m_top->m_data;

	// Store the top pointer so that we don't leak memory
	node* temp = m_top;

	// Update the top pointer
	m_top = m_top->m_next;

	// Clean up the memory
	delete temp;

	// Success
	--m_currSize;
	return true;
}

// Clear the stack for re-use
void Stack::Clear()
{
	while (m_top)
	{
		// Store the top pointer so that we don't leak memory
		node* temp = m_top;

		// Update the top pointer
		m_top = m_top->m_next;

		// Clean up the memory
		delete temp;
	}

	// Reset the size
	m_currSize = 0;
}

// Look at the top-most piece of data without removing it
const Item* Stack::Peek() const
{
	// Send back the Item at the top, or NULL if the list is empty
	return (m_top ? &m_top->m_data : NULL);
}