#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <string>
#include <ctime>
using namespace std;


class Score{
public:
	//creates a basic score with name, time, size, and number of mines
	Score(string nm, time_t tm, int sz, int nummine);
	// returns the name in the score
	string RtnName() const;
	//returns the time in the score
	time_t RtnTime() const;
	//returns the size that the minesweeperboard was in the score
	int RtnSize() const;
	//returns the  number of mines that the minesweeperboard contained
	int RtnMines() const;

private:
	//name, time, size, and number of mines
	string name;
	time_t myTime;
	int mySize;
	int myMines;
};


#endif