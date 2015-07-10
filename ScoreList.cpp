#include "ScoreList.h"
#include <fstream>
#include <sstream>
#include <iostream>

/* ScoreList::ScoreList() - Basic constructor for a ScoreList
*
* Description:
*   tests to see if the file "HighScores.txt" exists and can be opened. If so the constructor
*	proceeds to read every line and save it in a vector. This vector is then read and the lines
*	are tested to ensure that they are of the proper format. If the line passes all of the tests 
*	the the line is used to create a score. This score is then .push_back into a vector of Scores (The ScoreList)
* Inputs:
*  None
* Outputs:
*   None
*/
ScoreList::ScoreList(){
	string File = "HighScores.txt";
	string CurrentLine;
	vector<string> WholeLine;
	ifstream HighScoreFile;
	HighScoreFile.open(File);
	if(HighScoreFile.fail()){
		HighScoreFile.clear();
	}
	else{
		while(getline(HighScoreFile,CurrentLine)){
			WholeLine.push_back(CurrentLine);
		}
	}
	
	string tempName;
	string tempNumString;
	int tempSize;
	int tempMines;
	time_t temptime;
	bool Failed = false;
	int FirstSpace,SecondSpace,ThirdSpace;
	for(int i=0;i<WholeLine.size();i++){
		string easy = WholeLine[i];
		stringstream ss(easy);
		FirstSpace = easy.find_first_of(' ');
		easy = easy.substr(FirstSpace+1,easy.length());
		SecondSpace = easy.find_first_of(' ');
		easy = easy.substr(SecondSpace+1,easy.length());
		ThirdSpace = easy.find_first_of(' ');
		if(ThirdSpace>0){
			ss >> tempName;
			ss >> tempNumString;
			istringstream convert(tempNumString);
			if(!(convert >> tempSize)){
				Failed=true;
			}
			else{
				ss >>tempNumString;
				istringstream convert(tempNumString);
				if(!(convert >> tempMines)){
					Failed=true;
				}
				else{
				ss>> temptime;

				}
			}
		}
		else
			Failed=true;
		if(!Failed){
			if(temptime >= 0 && tempSize>=tempMines && tempSize<=400){ //ensures that the size, mines, and time are acceptable
				Score NextScore(tempName,temptime,tempSize,tempMines);
				MyList.push_back(NextScore);
			}
		}
		Failed=false;
	}
	SortByTime();

}
/* void ScoreList::AddNewScore(string user, time_t GameTime, int GameSize, int GameMines) - adds a new score to the ScoreList Vector
*
* Description:
*   Takes the parameters of a new score object, creates the score, then .push_back the score into the ScoreList vector
*	then the SortByTime method is called to place it in the correct spot
* Inputs:
*   string user -> the name to be saved in the new score
*	time_t GameTime -> the time to be saved in the new score
*	int GameSize -> the size of the MineSweeperBoard to be saved in the score
*	int GameMines -> the number of mines on the MineSweeperBoard to be saved in the score
* Outputs:
*   None
*/
//creates a new score, adds it to the score list and then sorts them in time order
void ScoreList::AddNewScore(string user, time_t GameTime, int GameSize, int GameMines){
	Score temp(user,GameTime,GameSize,GameMines);
	MyList.push_back(temp);
	SortByTime();

}

/* ScoreList::~ScoreList() - destructor for the ScoreList class
*
* Description:
*	It would do something if it were needed.. saddly it is not, so it basically does nothing
* Inputs:
*   None
* Outputs:
*   None
*/
ScoreList::~ScoreList(){}
/* bool ScoreList::empty() const - tells the call if this ScoreList is empty
*
* Description:
*	if the ScoreList vector is empty returs true, else returns false
* Inputs:
*   None
* Outputs:
*   bool -> true for an empty vector false for one with scores saved in it
*/
bool ScoreList::empty() const{return MyList.size()==0;}
/* int ScoreList::getSize() const - Acessor for the Size of the ScoreList
*
* Description:
*	returns the number of Scores saved in the ScoreList
* Inputs:
*   None
* Outputs:
*   int -> the number of Scores in ScoreList
*/
int ScoreList::getSize() const{return MyList.size();}
/* void ScoreList::SortByTime() - Sorts the ScoreList from least time to the most
*
* Description:
*	Sorts the ScoreList (using selection sort) to put the score with the least time taken at position
*	and the score that took the most time at position MyList.size() -1
* Inputs:
*   None
* Outputs:
*   None
*/
void ScoreList::SortByTime(){
	//Slow old selection sort
	int next; // The next position to be set to the minimum
	for (next = 0; next < MyList.size(); next++)
	{
		// Find the position of the minimum
		int min_pos = min_position(next,MyList.size()-1);
		if (min_pos != next)
		{
		   swap(MyList[min_pos], MyList[next]);
		}
	}


}
/* int ScoreList::min_position(int from, int to) - Used by selection sort, finds smallest value
*
* Description:
*	Finds smallest time value that is between the given index values in the ScoreList vector
* Inputs:
*   int from -> the first index to check for a min time value
*	int to -> the value to which the array should check for a smaller value
* Outputs:
*   int - > the index of the smallest time value
*/
int ScoreList::min_position(int from, int to)
{
	int min_pos = from;
	for (int i = from + 1; i <= to; i++)
	{
		if (MyList[i].RtnTime() < MyList[min_pos].RtnTime()) { min_pos = i; }
	}
	return min_pos;
}
/* void ScoreList::DisplayList() - Displays the ScoreList
*
* Description:
*	If the ScorList is not empty then the High Scores are displayed
*	
* Inputs:
*   None
* Outputs:
*   prints to cout the High Scores or that there are no saved high scores
*/
void ScoreList::DisplayList(){
	if(!empty()){
		cout<<"High Scores!!"<<endl<<"-------------------"<<endl;
		for(int i=0;i<MyList.size();i++){
			cout << MyList[i].RtnName() << "   " << MyList[i].RtnTime()<<endl;
	
		}
	}
	else
		cout<<"There are no High Scores saved."<<endl;

}
/* void ScoreList::Save() - Saves all the items in ScoreList to a text file
*
* Description:
*	Saves all the items in ScoreList to a text file in the proper format to be read from in
*	future runs of the program
*	
* Inputs:
*   None
* Outputs:
*   prints the HighScores and all data saved in each Score to a text file "HighScores.txt"
*/
void ScoreList::Save(){
	string outfile = "HighScores.txt";


	fb.open(outfile,ios::out);
	ostream SaveFile (&fb);
	for(int i=0;i<MyList.size();i++){
		SaveFile << MyList[i].RtnName()<<' '<<	MyList[i].RtnSize()<<' '<<MyList[i].RtnMines()<< ' '<<MyList[i].RtnTime()<<endl;
	}
	fb.close();

}