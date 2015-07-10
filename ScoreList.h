#ifndef INCLUDED_SCORELIST
#define INCLUDED_SCORELIST

#include <fstream>
#include <vector>
#include "Score.h"

class ScoreList{

public:
	//checks to see if there is a highscore file
	//creates a blank list if it does not
	//fills list with all properly formatted lines
	ScoreList();

	//destructor
	~ScoreList();

	// returns true if it is empty, false otherwise
	bool empty() const;

	//returns the size of the ScoreList;
	int getSize() const;

	// uses selection sort based on the time saved in the scores
	void SortByTime();

	//adds a new score to the scorelist and then calls the sortbytime method
	void AddNewScore(string user, time_t GameTime, int GameSize, int GameMines);

	//saves the high score information to a text file in the proper foramt
	void Save();

	//if the list is not empty is prints out the name and time of each score in the list
	// if it is empty it prints that to the user
	void DisplayList();

private:
	// used by the selectin sort in sortbytime, find the minimum value in the vector between two indicies
	int min_position(int from, int to);
	vector<Score> MyList;//holds all the scores
	filebuf fb;//used for file output

};

#endif