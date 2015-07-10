// CS 215, Spring 2013
// Programming assignment 4
// 13 April, 2013
#include "position.h"

/* Position::Position() - Basic constructor for a Position
*
* Description:
*   Holds an X and Y Coord, sets both to 0
*
* Inputs:
*   None
*   
* Outputs:
*   none
*/

Position::Position()
	: xcoord(0), ycoord(0)
{}

/* Position::Position(int xc, int yc) - Basic constructor for a Position, with given points
*
* Description:
*   Holds an X and Y Coord, sets both to the specified values
*
* Inputs:
*   int xc-> the XCoord of Position
*	int yc-> the YCoord of Position
*   
* Outputs:
*   none
*/

Position::Position(int xc, int yc)
	: xcoord(xc), ycoord(yc)
{}

/* int Position::x() const - Acessor to the x value stored in Position
*
* Description:
*   Acessor to the x value stored in Position
*
* Inputs:
*   None
*   
* Outputs:
*   int -> the x value stored in Position
*/

int Position::x() const
{
	return xcoord;
}


/* int Position::y() const - Acessor to the y value stored in Position
*
* Description:
*   Acessor to the y value stored in Position
*
* Inputs:
*   None
*   
* Outputs:
*   int -> the y value stored in Position
*/
int Position::y() const
{
	return ycoord;
}


/* void Position::setx() - Mutator to the x value stored in Position
*
* Description:
*   Mutator to the x value stored in Position
*
* Inputs:
*   int new_x -> the new value to save in x
*   
* Outputs:
*   None
*/
void Position::set_x(int new_x)
{
	xcoord = new_x;
}

/* void Position::sety() - Mutator to the y value stored in Position
*
* Description:
*   Mutator to the y value stored in Position
*
* Inputs:
*   int new_y -> the new value to save in x
*   
* Outputs:
*   None
*/
void Position::set_y(int new_y)
{
	ycoord = new_y;
}


/* bool Position::in_bounds(int width, int height)- Check if the position is in the given height and width
*
* Description:
*   Check if the position is in the given height and width
*	returns true if it is in the given values, false otherwise
*
* Inputs:
*   int width-> maximum x value
*	int height -> maximum y value
*   
* Outputs:
*   bool -> true if it is within bound false otherwise
*/
bool Position::in_bounds(int width, int height) const
{
	return 0 <= xcoord && xcoord < width
	    && 0 <= ycoord && ycoord < height;
}
