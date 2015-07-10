// Implemented by David Tooley April 2013


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "board.h"
#include "positionlist.h"
#include <sstream>
#include "ScoreList.h"

using namespace std;

void pause(bool have_newline);
int getNum(int min, int max, string Question);
Position GetPos(int wid, int hid);
void getHeightAndWidth(int &hei, int &wid);

/* Position GetPos(int wid, int hid) - gets a valid X and Y value for the MineSweeperBoard
*
* Description:
*	Prompts the user asking for either the X value, then the Y value. If either is out of range 
*	or not an integer then it will prompt the user again until correct input is given.
*
* Inputs:
*   int wid -> The width of the MineSweeperBoard, This is used to check in the given value is valid
*	int hid -> The height of the MineSweeperBoard, This is used to check in the given value is valid
*	
*   
* Outputs:
*   Prompts user asking for an X or Y value, then if the user input was incorrect,
*	informs the user and allows the user to re-enter the value
*	returns the user given position
*/

Position GetPos(int wid, int hid){



	cout<< "What position (x y)?  ";
	int Xspot;
	int Yspot;
	string responce;
	getline(cin,responce);
	int FirstSpace;
	FirstSpace = responce.find_first_of(' ');

	
	stringstream ss(responce);

	if (FirstSpace >0){
		string first;
		ss>>first;
		string second;
		ss>>second;

		istringstream convert(first); 
                             

		if ( !(convert >> Xspot) ){
			cout<< "Please enter two numbers separated by a space."<<endl;
			return GetPos(wid,hid);
		}
		else {
			istringstream convert(second);
			if ( !(convert >> Yspot) ){
				cout<< "Please enter two numbers separated by a space."<<endl;
				return GetPos(wid,hid);
			}
			else{
				if(!(Xspot>=0)){
					cout<<"I'm sorry, the X value cannot be less than 0."<<endl;
					return GetPos(wid,hid);
				}
				else if (!(Xspot<wid)){
					cout<<"I'm sorry, the X value cannot be greater than "<<(wid-1)<<"."<<endl;
					return GetPos(wid,hid);
				}
				else if (!(Yspot>=0)){
					cout<<"I'm sorry, the Y value cannot be less than 0."<<endl;
					return GetPos(wid,hid);
				}
				else if (!(Yspot<hid)){
					cout<<"I'm sorry, the Y value cannot be greater than "<<(hid-1)<<"."<<endl;
					return GetPos(wid,hid);
				}
			
			}
	
		}
	}
	else {
		cout<<"Please enter two numbers separated by a space."<<endl;
		return GetPos(wid,hid);
	}
	return Position(Xspot,Yspot);
	






}

/* void getHeightAndWidth(int &hei, int &wid) - gets a valid height and width value for the MineSweeperBoard
*
* Description:
*	Prompts the user asking for the height and width. If either is out of range 
*	or not an integer then it will prompt the user again until correct input is given.
*
* Inputs:
*   int wid -> The width of the MineSweeperBoard
*	int hid -> The height of the MineSweeperBoard
*	
*   
* Outputs:
*   Prompts user asking for a  height and width, then if the user input was incorrect,
*	informs the user and allows the user to re-enter the value
*	returns nothing, but wid and hei are by reference
*/

void getHeightAndWidth(int &hei, int &wid){
	//Must be between 5 and 20 inclusive
	cout<< "How large should the board be (width height)?  ";
	string responce;
	getline(cin,responce);
	int FirstSpace;
	FirstSpace = responce.find_first_of(' ');

	
	stringstream ss(responce);

	if (FirstSpace >0){
		string first;
		ss>>first;
		string second;
		ss>>second;

		istringstream convert(first); 
                             

		if ( !(convert >> wid) ){
			cout<< "Please enter two numbers separated by a space."<<endl;
			getHeightAndWidth(hei, wid);
		}
		else {
			istringstream convert(second);
			if ( !(convert >> hei) ){
				cout<< "Please enter two numbers separated by a space."<<endl;
				getHeightAndWidth(hei, wid);
			}
			else{
				if(!(wid>=5)){
					cout<<"I'm sorry, the width cannot be less than 5."<<endl;
					getHeightAndWidth(hei, wid);
				}
				else if (!(wid<=20)){
					cout<<"I'm sorry, the width cannot be greater than 20."<<endl;
					getHeightAndWidth(hei, wid);
				}
				else if (!(hei>=5)){
					cout<<"I'm sorry, the height cannot be less than 5."<<endl;
					getHeightAndWidth(hei, wid);
				}
				else if (!(hei<=20)){
					cout<<"I'm sorry, the height cannot be greater than 20."<<endl;
					getHeightAndWidth(hei, wid);
				}
			
			}
	
		}
	}
	else {
		cout<<"Please enter two numbers separated by a space."<<endl;
		getHeightAndWidth(hei, wid);
	}
	
	


}

/* getNum(int min, int max,string Question) - gets a number from the user between the given values
*
* Description:
*	Prompts the user with the given string, then waits for an expected input between the given maximum
*	and minimum values. The function then proceeds to check the values to ensure that it exists and is
*	within the specified range.
*
* Inputs:
*   int min -> The lowest number that is acceptable to be returned INCLUDING the given number
*	int max -> the largest number that is acceptable to be returned INCLUDING the given number
*	string Question -> The string that is printed to the user so that he/she knows what the program expects as input.
*   
* Outputs:
*   Prompts user with the given Question string, then if the user input was incorrect, informs the user and allows the 
*	user to re-enter the value
*/

int getNum(int min, int max,string Question){
	int responce=0;
	while(true){
		
		cout << Question;
		cin >> responce;

		if(cin.fail()){
			cin.clear();
			cin.ignore(200,'\n');
			cout << "That is not a number, please give me a number between " << min << " and " << max << "." << endl;
		}
		else if(responce <min){
			cout<< "That number is too small, please give me a value greater than or equal to "<<min<<"."<<endl<<endl;
		}
		else if(responce >max) {
			cout << "That number is too large, please give me a values less than or equal to " << max <<"."<<endl<<endl;
		}
		else {
			cin.clear();
			cin.ignore(200,'\n');
			return responce;
		
		}
	}
}

/* int main() - driver code to create a MineSweeperBoard
*
* Description:
*	Calls the proper functions to get the required information to create a MineSweeperBoard
*	
*
* Inputs:
*   No direct input to main, takes some user input such as:
*	The MineSweeperBoard width, height, and number of mines to include.
*	Then allows user to input what move they want to take.
*	Then calls GetPos() to get the position for this action to occur at.
*   
* Outputs:
*   Calls the MineSweeperBoard's display method and prompts the user with multiple instructions
*	returns a 1 for an erraneous run, 0 for a sucessful run.
*/

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	// TODO: Ask for the board size (between 5 and 20 in each direction)
	// and the number of mines.
	int w,h;
	bool NeedPause =false;
	getHeightAndWidth(h,w);
	int a = w*h;
	stringstream GetMines;
	GetMines << "How many mines would you like to have in your game? (Maximum of " << a << ") ";
	int mines = getNum(0,a,GetMines.str());
	// Create a board of that size.
	MineSweeperBoard board(w, h, mines);
	
	cout<<endl<< "Begining the game!"<<endl<<endl;
	time_t start = time(NULL);
	
	while (!board.lost() && !board.won())
	{
		board.display(cout);
		// Ask the user to [R]eveal, [F]lag, or [G]ive up.
		// The first two commands also require a Position, so
		// you may need to ask for x and y coordinates as well.
		char responce;
		bool NoGood = true;
		do{
			cout << "[R]eveal or [F]lag a square or [G]ive up ";
			cin >> responce;
			cout<<endl;
			if(cin.fail()){
				cin.clear();
				cin.ignore(200,'\n');
				cout<<"That is an unacceptable input"<<endl;
			}
			else if(responce == 'R' || responce =='r'){
				NoGood=false;
				cin.clear();
				cin.ignore(200,'\n');
				Position temp = GetPos(board.get_width(),board.get_height());
				board.reveal(temp);
			}
			else if (responce == 'F' || responce == 'f'){
				NoGood=false;
				cin.clear();
				cin.ignore(200,'\n');
				Position temp = GetPos(board.get_width(),board.get_height());
				board.flag(temp);
			}
			else if (responce == 'G' || responce == 'g'){
				NoGood=false;
				board.give_up();
				NeedPause=true;
			}
			else{
				cout<<"unknown command \""<<responce<<"\"."<<endl;
			}
		}while(NoGood);
		

	}
	time_t finish = time(NULL);

	string username;
	ScoreList HighScores;

	//board.lost()
	if(board.lost()){
		board.give_up();// used to unflag all items and set every item on the board to revealed.
		board.display(cout);
		cout <<endl;

		cout<< "You lost!"<<endl;
		cout <<"Your game took " << (finish-start) << " seconds."<<endl<<endl;// Compute and display how much time the game took.
	}
	else{
		board.give_up(); // used to unflag all items and set every item on the board to revealed.
		board.display(cout);
		cout <<endl;
		cout<< "Congrats, you win!"<<endl;
		cout <<"Your game took " << (finish-start) << " seconds."<<endl<<endl;// Compute and display how much time the game took.


		cout<< "What is your name? ";
		cin>> username;
		cout <<endl;
		cout <<"Saving game to HighScores..."<<endl<<endl;
		HighScores.AddNewScore(username, (finish-start), a, mines);
		NeedPause = true;
		
	}
	
	
	
	
	
	HighScores.DisplayList();
	HighScores.Save();
	
	pause(NeedPause);
	return 0;
}

/* Pause() - wait for user to hit enter
*
* Description:
*   Pauses program code, waits for the user to press the enter key
*
* Inputs:
*   a bool value, true if there is input in the buffer, false if there is not
*   
* Outputs:
*   prints a statement "Press ENTER to continue."
*/
void pause(bool have_newline)
{
    if (have_newline) {
        // Ignore the newline after the user's previous input.
        cin.ignore(200, '\n');
    }

    // Prompt for the user to press ENTER, then wait for a newline.
    cout << endl << "Press ENTER to continue." << endl;
    cin.ignore(200, '\n');
}
