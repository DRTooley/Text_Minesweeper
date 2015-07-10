// CS 215, Spring 2013
// Lab 11
// 13 April, 2013
#include <cstdlib>
#include "positionlist.h"
using namespace std;


/* Node(Position p) - Initialize a node with no next node and the given position.
*
* Description:
*   Creates a Node that contains only a position
*
* Inputs:
*   the position to be stored within the node
*   
* Outputs:
*   None
*/
Node::Node(Position p)
	: next(NULL), pos(p)
{}


/* PositionList() - Default constructor: initialize an empty list
*
* Description:
*   Creates an empty PositionList
*
* Inputs:
*   None
*   
* Outputs:
*   None
*/
PositionList::PositionList()
	
{
	first=NULL;
}


/* Empty() const - Test whether the list is empty.
*
* Description:
*   tests to see if the pointer to the first spot in the Position List is pointing to NULL
*	If this is true then the list is empty
*
* Inputs:
*   None
*   
* Outputs:
*   Bool: true if it is empty, false if it has atleast one position in the list
*/
bool PositionList::empty() const
{
	if(first==NULL)
		return true;
	return false;
}


/* size() const - Calculate the size of the list.
*
* Description:
*   Calculates and returns the size of the PositionList
*
* Inputs:
*   None
*   
* Outputs:
*   an int value that is the size of the PositionList
*/
int PositionList::size() const 
{
	int i = 0;
	for (Node *curr = first; curr != NULL; curr = curr->next) {
		i++;
	}
	return i;
}



/* get() const - Return the Position at the given index.
*
* Description:
*   Return the Position at the given index.  If the index is out of
*	bounds, return Position(-1, -1).
*
* Inputs:
*   int index -> which position in the position list you wish to access.
*   
* Outputs:
*   returns the Position that is in the given index, or a position(-1,-1) if is out of bounds.
*/
Position PositionList::get(int index) const
{
	Node *curr = first;
	for (int i=0; i < index; i++){
		if(curr == NULL)
			return Position(-1, -1);
		curr = curr->next;
	}
	if(curr == NULL)
			return Position(-1, -1);
	return curr->pos;
	
}



/* push_front() - Add a new Position object to the beginning of the list.
*
* Description:
*   Add a new Position object to the beginning of the list.
*
* Inputs:
*   Position pos  -> the position to add to the front of the PositionList
*   
* Outputs:
*   None
*/

void PositionList::push_front(Position pos)
{
	Node *to_insert = new Node(pos);
	to_insert->next = first;
	first = to_insert;
}



/* pop_front() - Remove the first element, freeing its node.
*
* Description:
*   Remove the first element, freeing its node.
*
* Inputs:
*   None
*   
* Outputs:
*   None
*/
void PositionList::pop_front()
{
	Node *to_del = first;
	first = to_del->next;
	delete to_del;
}




/* PositionList(const PositionList &origonal) - Initialize a copy of a list using the copy_nodes helper function.
*
* Description:
*   Initialize a copy of a list using the copy_nodes helper function. creates a deep copy of the list
*
* Inputs:
*   The PositionList to create a copy of
*   
* Outputs:
*   None
*/
PositionList::PositionList(const PositionList &original)
{
	first = copy_nodes(original.first);
}



/* copy_nodes(const Node *in) const - Initialize a copy of a list using the copy_nodes helper function.
*
* Description:
*   Helper function: recursively copy "in" and all the nodes that follow.
*	As a base case, "copying" NULL should return NULL (and not copy anything).
*
* Inputs:
*   The first node is a list of nodes, such that they are called recusivly until the last one returns NULL
*   
* Outputs:
*   copy -> a pointer to the first node of a new list
*/

Node *PositionList::copy_nodes(const Node *in) const
{
	if (in == NULL)
		return NULL;

	Node *copy = new Node(in->pos);
	copy->next = copy_nodes(in->next);
	return copy;
}

// Clean up this list by freeing all its nodes.
PositionList::~PositionList()
{
	while(first != NULL){
	pop_front();
	}
}

// Store the contents of another list in this one, replacing the old
// contents of this list (and freeing those nodes).  Returns the
// implicit parameter by reference (return *this;)
//
// This method implements assignment:   poslist = otherposlist;
//
PositionList &PositionList::operator=(const PositionList &other) 
{
	if (this == &other)
		return *this;

	while(first != NULL){
	pop_front();
	}

	first = copy_nodes(other.first);

	return *this;
}
