
#include "Score.h"

/* Score::Score(string nm, time_t tm, int sz, int nummine) - Basic constructor for a Score
*
* Description:
*   take the given name, time, size, and the number of mines, then saves these values in 
*	the proper private data members
* Inputs:
*   string nm -> The name of the user that obtained the score
*	time_t tm -> the time the user posted
*	int sz-> the size of the MineSweeperBoard
*	int nummine -> The number of mines on the board for that game
* Outputs:
*   none
*/
	Score::Score(string nm, time_t tm, int sz, int nummine)
		:name(nm),myTime(tm),mySize(sz),myMines(nummine)
	{}
	/* string Score::RtnName() const - Acessor for the name data member
*
* Description:
*   returns the string containing the name of the user who
*	posted this score in MineSweeper
* Inputs:
*  None
* Outputs:
*   The string containing the user's name
*/
	string Score::RtnName() const{
		return name;
	}
	/* time_t Score::RtnTime() const - Acessor for the time data member
*
* Description:
*   returns the  time_t containing the legth of the user's game
*	for this score in MineSweeper
* Inputs:
*  None
* Outputs:
*   The time_t time of the game
*/
	time_t Score::RtnTime() const{
		return myTime;
	}
/* int Score::RtnSize() const - Acessor for the time size member
*
* Description:
*   returns the int containing the size of the gameboard for the posted score
* Inputs:
*  None
* Outputs:
*   The int size of the board (between 25 and 400 inclusive)
*/
	int Score::RtnSize() const{
		return mySize;
	}
/* int Score::RtnMines() const - Acessor for the time myMines data member
*
* Description:
*   returns the int containing the number of mines on the gameboard for the posted score
* Inputs:
*  None
* Outputs:
*   The int number of mines on the board
*/
	int Score::RtnMines() const{ 
		return myMines;
	}


