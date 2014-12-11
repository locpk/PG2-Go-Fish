#include "Stack.h"
#include "stdafx.h"

// Default ctor
// Create an empty stack
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
// Return: True, if something was added
bool Stack::Push(const Item& _info)
{
	// Need to allocate memory every time we add something
	Node* newTop = new Node;

	// Did we run out of memory?
	if (NULL == newTop)
		return false;

	// Fill in the node
	newTop->m_data = _info;
	// Put this node on top of all the other nodes
	newTop->m_next = m_top;

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
bool Stack::Pop(Item& _info)
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
void Stack::Clear()
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