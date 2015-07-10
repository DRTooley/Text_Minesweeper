// CS 215, Spring 2013
// Programming assignment 4
// 13 April, 2013
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "board.h"
using namespace std;

/* MineSweeperBoard(int board_width, int board_height, int mine_count) - Basic constructor for a MineSweeperBoard
*
* Description:
*   take the width,height, and number of mines and implements the revealed and flagged arrays to be false.
*	then randomly selects which squares are to be set as mines
*
* Inputs:
*   int board_width -> the width of the created board
*	int board_height-> the height of the created board
*	int mine_count -> the number of mines to be set to true;
*   
* Outputs:
*   none
*/

MineSweeperBoard::MineSweeperBoard(int board_width, int board_height, int mine_count)
	:width(board_width), height(board_height)
{
	//create the 2D arrays with height and width
	revealed= new bool*[board_height];
	for(int i=0;i<board_height;i++){revealed[i] = new bool[board_width];}
	flagged = new bool*[board_height];
	for(int i=0;i<board_height;i++){flagged[i] = new bool[board_width];}
	mined = new bool*[board_height];
	for(int i=0;i<board_height;i++){mined[i] = new bool[board_width];}
	
	for(int y = 0;y<height;y++){
		for (int x = 0; x<width;x++){
			revealed[y][x] = false;
			flagged[y][x] = false;
			mined[y][x]=false;
		}
	}
	// Create a vector with some numbers in it.
    vector<int> numbers;
    for (int i = 0; i < board_width*board_height; i++)
        numbers.push_back(i);

    // Randomize the vector.
	srand(time(NULL));
    random_shuffle(numbers.begin(), numbers.end());
	
	 for (int i = 0; i < (board_width*board_height-mine_count); i++)
        numbers.pop_back();
	 for (int i = 0; i< mine_count;i++){
		int bh = numbers[i]/board_width;
		int bw = numbers[i]%board_width;
		mined[bh][bw] = true;
	 }

}

/* MineSweeperBoard::~MineSweeperBoard() - Basic destructor for a MineSweeperBoard
*
* Description:
*   deletes all synamically allocated arrays
*
* Inputs:
*   None
*   
* Outputs:
*   none
*/
MineSweeperBoard::~MineSweeperBoard(){
	delete[] revealed;
	delete[] mined;
	delete[] flagged;
} 

/*int MineSweeperBoard::get_width() const - Acessor for the width of the MineSweeperBoard
*
* Description:
*   allows acess to the width of the MineSweeperBoard
*
* Inputs:
*   None
*   
* Outputs:
*   returns the width
*/
int MineSweeperBoard::get_width() const{return width;}
/*int MineSweeperBoard::get_height() const - Acessor for the height of the MineSweeperBoard
*
* Description:
*   allows acess to the height of the MineSweeperBoard
*
* Inputs:
*   None
*   
* Outputs:
*   returns the height
*/
int MineSweeperBoard::get_height() const{return height;}

/*bool MineSweeperBoard::flag(Position p)- sets the flag to true/false at the given position
*
* Description:
*   sets the flag at the given position to true if false or false if true
*	unless the space is already revealed, in which case flag should already 
*	be false, and false is set again to false
*
* Inputs:
*   Position p -> the space at which you wish to flag/unflag the position
*   
* Outputs:
*   bool -> the value that the flag was set to
*/

bool MineSweeperBoard::flag(Position p){
	// Put a flag on a square, or remove a flag that is
	// already there.  Returns true if we placed a flag, false if
	// we removed one or if the spot was already revealed.
	if(!revealed[p.y()][p.x()]){
		if(flagged[p.y()][p.x()]){
			flagged[p.y()][p.x()] = false;
			return false;
		}
		else
			flagged[p.y()][p.x()] = true;
		return true;
	}
	else{
		flagged[p.y()][p.x()] = false;
		return false;
	}

}

/*char MineSweeperBoard::appearance(Position p) const - returns the correct appearance of the given position
*
* Description:
*   takes the arrays of flagged,mined, and reavealed then finds the correct char representation
*	'/' for flagged, '*' for mined and revealed '.' for not revealed and nor flagged and the number of adjacent mines if it is revealed
*
* Inputs:
*   Position p -> the space at which you wish to have the character representation of
*   
* Outputs:
*   char - > the visual of that space on the board
*/

char MineSweeperBoard::appearance(Position p) const
{
	int x = p.x();
	int y = p.y();

	if (flagged[y][x]) {
		return '/';
	} else if (revealed[y][x]) {
		if (mined[y][x]) {
			// Boom!
			return '*';
		} else {
			// At most 8 adjacent mines, so one digit.
			int adjmines = adjacent_mines(p);
			// Convert a number to a digit character.
			return '0' + adjmines;
		}
	} else {
		// Unrevealed, unflagged.
		return '.';
	}
}



// Display the entire board to an output stream.  Prints
	// a header with the column numbers, and prints the row
	// number on each line.  For example,
	//     |  0  1  2  3  4
	//  ---+---------------
	//   0 |  1  /  .  .  .
	//   1 |  1  2  .  .  .
	//   2 |  0  1  .  .  .
	//   3 |  0  1  2  1  1
	//   4 |  0  0  0  0  0

/*void MineSweeperBoard::display(ostream &out) - displays the entire MineSweeperBoard to the given ostream
*
* Description:
*   Takes the given ostream and prints out the MineSweeperBoard
*	This calls the apearence method to get the character represenation and prints each item to the board
*	
*
* Inputs:
*   ostream &out -> the stream, passed by reference, which is going to have the board output to it
*   
* Outputs:
*   None
*/


void MineSweeperBoard::display(ostream &out) const{
	out << "   |  0  1  2  3  4";
	for(int i = 5; i< width;i++){
		if(i<10)
			out <<"  "<<i;
		else
			out <<" "<<i;
	}
	out<<endl;
	out << "---+---------------";
	for(int i = 5; i< width;i++){
		out <<"---";
	}
	out<<endl;
	for(int i =0;i<height;i++){
		if(i<10)
			out<< " "<<i<<" |";
		else
			out<< " "<<i<<"|";
		for(int j =0;j<width;j++){
			out<<"  "<<appearance(Position(j,i));
		}
		out<< endl;
	}
	out<<endl;
} 

/*bool MineSweeperBoard::won() const - Checks to see if the user has won the game
*
* Description:
*   Checks to see if the user won the game of MineSweeper.
*	To do this all spaces that are not mines must be revealed
*
* Inputs:
*   None
*   
* Outputs:
*   None
*/


bool MineSweeperBoard::won() const
{
	// Check every square.  If we see a square that is mined but
	// not flagged, or unmined but not revealed, return false
	// immediately.  If we get to the end, every square is correct,
	// so the user won and we return true.
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (mined[y][x] && !flagged[y][x]) {
				return false;
			} else if (!mined[y][x] && !revealed[y][x]) {
				return false;
			}
		}
	}
	return true;
}


/*PositionList MineSweeperBoard::adjacent(Position p) const- returns a position list of all positions on the board that are adjacent to the given position
*
* Description:
*   returns a position list of all positions on the board that are adjacent to the given position.
*
* Inputs:
*   Position p -> the position of which to find all other surrounding positions
*   
* Outputs:
*   PositionList -> of all adjacent positions
*/
PositionList MineSweeperBoard::adjacent(Position p) const
{
	PositionList result;

	// Loop over the 3x3 block centered around p.
	for (int adj_y = p.y() - 1; adj_y <= p.y() + 1; adj_y++) {
		for (int adj_x = p.x() - 1; adj_x <= p.x() + 1; adj_x++) {
			// Make a position out of the new coordinates.
			Position adj(adj_x, adj_y);
			// Skip out-of-bounds squares
			if (!adj.in_bounds(width, height))
				continue;
			// Also skip the center.
			if (adj.x() == p.x() && adj.y() == p.y())
				continue;

			// If we get here, it's really adjacent, so add it to the list.
			result.push_front(adj);
		}
	}
	return result;
}

/*PositionList MineSweeperBoard::adjacent(Position p) const- returns an int of the number of adjacent mines
*
* Description:
*   returns an int of the number of adjacent mines. This uses a call to adjacent and then checks to see if mined at those positions is true
*
* Inputs:
*   Position p -> the position of which to find the number of surrounding mines
*   
* Outputs:
*   int -> number of mines adjacent to the given position
*/

int MineSweeperBoard::adjacent_mines(Position p) const
{
	PositionList neighbors = adjacent(p);

	// Loop over the neighbors.
	int adjacent_count = 0;
	for (int i = 0; i < neighbors.size(); i++) {
		Position adj = neighbors.get(i);
		// If it's mined, increase the count.
		if (mined[adj.y()][adj.x()])
			adjacent_count++;
	}
	return adjacent_count;
}

/*void MineSweeperBoard::reveal(Position p) - recursivly reveals the spaces, until a number is found.
*
* Description:
*   recursivly reveals each space around the given position IF the position is a zero. otherwise only sets the given positions reveal to true
*
* Inputs:
*   Position p -> the position of which to startthe recursive reveal
*   
* Outputs:
*   None
*/

void MineSweeperBoard::reveal(Position p){
	// Reveal a square.
	// If this square wasn't already revealed, and if the number of
	// adjacent mines equals the number of adjacent flags, recursively
	// reveal all the surrounding squares that aren't flagged.
	int posX = p.x();
	int posY = p.y();
	if(!revealed[posY][posX]&& !flagged[posY][posX]){
		revealed[posY][posX] = true;
		PositionList adja = adjacent(p);
		int sz = adja.size();
		int numFlag=0;
		int numMine=0;
		for(int i = 0; i <sz; i++){
			Position NewPos = adja.get(i);
			if(mined[NewPos.y()][NewPos.x()])
				numMine++;
			if(flagged[NewPos.y()][NewPos.x()])
				numFlag++;
		}
		if(numFlag==numMine){
			for(int j =0; j<sz;j++){
				Position RecurReveal = adja.get(j);
				if(!flagged[RecurReveal.y()][RecurReveal.x()])
					reveal(RecurReveal);
			}
		}
	}
}

/*void MineSweeperBoard::give_up() - allows the user to quit playing and reveals the entire board
*
* Description:
*   called when the suer wishes to quit.
*	sets all reveals to true, flagged to false
*
* Inputs:
*   None
*   
* Outputs:
*   None
*/


void MineSweeperBoard::give_up(){
	for(int y =0;y<height;y++){
		for(int x=0; x<width;x++){
			flagged[y][x]=false;
			revealed[y][x]=true;
		}
	}
}

/*bool MineSweeperBoard::lost() const - checks to see if the user has lost the game
*
* Description:
*   Checks to see if any revealed areas are also mined
*	If this is true then the user has lost
*
* Inputs:
*   None
*   
* Outputs:
*   Bool -> true if the user has lost, false if not.
*/

bool MineSweeperBoard::lost() const{
	for( int y =0; y<height;y++){
		for(int x =0; x<width;x++){
			if(revealed[y][x]&&mined[y][x])
				return true;
		}
	}
	return false;
}