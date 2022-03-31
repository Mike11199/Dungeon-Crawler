#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

/*************************************************************************
 * Function Prototypes
 ************************************************************************/
int getRandomArrayNumber(int);
int getRandomArrayExitNumber();
void PrintDungeonMap(int[]);
void InitializeDungeonMap(int[]);
void InitializeDungeonObstacles(int[], int);
int chooseRoom(int[]);
bool preventSameRoomTwice(int[], int);
int getValidRoomNumber(int[]);
void roomGame(int[], int, int);

//global variable for Array size or else need to pass into too many functions
const int ARRAYSIZE = 15;
bool escaped = false;
bool gameover = false;

int main()
{

	srand(time(0));



	cout << "You awake in a dungeon.  You have no memory of why you are here.  Your goal is to try to escape by finding the exit." << endl  << endl;
	//0 = not visited
	//1 = current location
	//2 = visited
    cout << endl << "You hastily scribble a map of the dungeon." << endl << "* marks what rooms you've explored. "
    		" X is your current location in the dungeon." << endl << endl;

	//0 = not visited
	//1 = current location
	//2 = visited
	int dungeonTracker[ARRAYSIZE];
	InitializeDungeonMap(dungeonTracker);

	int dungeonObstacles[ARRAYSIZE];
	int obstacleCount = 4;
	InitializeDungeonObstacles(dungeonObstacles, obstacleCount);

	while (escaped == false && gameover == false)

	{
		PrintDungeonMap(dungeonTracker);
		int roomNumber = chooseRoom(dungeonTracker);
		roomGame(dungeonObstacles, roomNumber, obstacleCount);
	}


}

/*************************************************************************
 * This function prints a map of the dungeon using the dungeon tracker
 ************************************************************************/
void PrintDungeonMap(int dungeonTracker[])
{
	const char FILL = '-';
	const int WIDTH = 75;


    //print array of map so user knows dungeon location here
	//	0 = not visited
	//	1 = current location
	//	2 = visited

    cout << setfill(FILL) << setw(WIDTH) << "" << endl;
    for (int i = 0; i < ARRAYSIZE; i++ )
	{
		cout << " | ";
		if	(dungeonTracker[i] == 0)
		{
			cout << " ";
		}
		else if (dungeonTracker[i] == 1)
		{
				cout << "X";
		}
		else if (dungeonTracker[i] == 2)
		{
				cout << "*";
		}
	}
    cout << " |";

	cout << endl;
    cout << setfill(FILL) << setw(WIDTH) << "" << endl;
}




void InitializeDungeonMap(int dungeonTracker[])
{
	for (int i = 0; i < ARRAYSIZE; i++ )
	{
		dungeonTracker[i] = 0;
	}

	//sets first spot of dungeon as current location
	dungeonTracker[0] = 1;
}




void InitializeDungeonObstacles(int dungeonObstacles[], int obstacleCount)
{
	for (int i = 0; i < ARRAYSIZE; i++ )
	{
		dungeonObstacles[i] = getRandomArrayNumber(obstacleCount);
		cout << "obstacle " << i << " is " << dungeonObstacles[i] << endl;
	}

	int exitDoor = getRandomArrayExitNumber();

	//exit door is the number that is one greater than the obstacle count
	dungeonObstacles[exitDoor] = obstacleCount;
	cout << endl << "obstacle " << exitDoor << " is changed to " << dungeonObstacles[exitDoor] << endl;

}



int chooseRoom(int dungeonTracker[])
{
	int roomNumber = getValidRoomNumber(dungeonTracker);
	cout << "Moving to room " << roomNumber << " of the dungeon..." << endl;


	//loop through map
	for (int i =0; i< ARRAYSIZE; i++)
	{
		//if current location, mark as visited
		if (dungeonTracker[i] == 1)
		{
			dungeonTracker[i] = 2;
		}
		//then set roomNumber as current location
		if (i == roomNumber)
		{
			dungeonTracker[i] = 1;
		}
	}

	return roomNumber;

}




bool preventSameRoomTwice(int dungeonTracker[], int roomNumber)
{
	bool alreadyVisited;

	if (dungeonTracker[roomNumber] >= 1)
	{
		alreadyVisited = true;
	}
	return alreadyVisited;
}




int getValidRoomNumber(int dungeonTracker[])
{
	int roomNumber = 0;
	while (roomNumber <= 0 || roomNumber >= ARRAYSIZE )
	{
		cout << "Enter what room you would like to go next: " << endl;
		cin >> roomNumber;

		if (!(roomNumber <= 0 || roomNumber >= ARRAYSIZE))
		{
			bool alreadyVisited = preventSameRoomTwice(dungeonTracker, roomNumber);

			if (alreadyVisited == true)
			{
				cout << "You've already visited this part of the dungeon!" << endl << endl;
				roomNumber = -4;
			}
		}

	}

	return roomNumber;
}



void roomGame(int dungeonObstacles[], int roomNumber, int obstacleCount)
{

//	if exit door then set the exit door bool to true so that the game will be over
	if (dungeonObstacles[roomNumber] == obstacleCount)
	{
		escaped = true;
		cout << "You found the exit door!  You escaped the dungeon!";
	}

}



/*********************************************************************************************************************
 * This function assigns the exit door to a random position in the array.  This way there can only be one exit door.
 ********************************************************************************************************************/
int getRandomArrayExitNumber()
{
	int minVal = 1;
	int maxVal = ARRAYSIZE - 1;

	int randNumber = minVal + rand() % (maxVal - minVal + 1);
	return randNumber;
}


/*********************************************************************************************************************
 * This function gets a number from between 1 and the obstacle count to assign obstacles randomly to the dungeon map
 ********************************************************************************************************************/
int getRandomArrayNumber(int obstacleCount)
{
	int randNumber = rand() % (obstacleCount);
	return randNumber;
}
