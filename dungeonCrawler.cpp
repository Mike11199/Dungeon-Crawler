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
int playGoblinGame();
int getValidGoblinNumber();
int getGoblinRandomNumber();

/*************************************************************************
 * Global variables
 ************************************************************************/
const int ARRAYSIZE = 15;
bool escaped = false;
bool gameover = false;
int playerCoins = 0;


/*************************************************************************
 * Main function for dungeon crawler starts here
 ************************************************************************/
int main()
{

	srand(time(0));



	cout << "You awake in a dungeon.  You have no memory of why you are here.  Your goal is to try to escape by finding the exit." << endl;
	//0 = not visited
	//1 = current location
	//2 = visited
    cout << endl << "You hastily scribble a map of the dungeon.  You appear to be in room 0." << endl << "* marks what rooms you've explored. "
    		" X is your current location in the dungeon." << endl << endl;

	//0 = not visited
	//1 = current location
	//2 = visited
	int dungeonTracker[ARRAYSIZE];
	InitializeDungeonMap(dungeonTracker);

	int dungeonObstacles[ARRAYSIZE];
	int obstacleCount = 4;
	playerCoins = 0;
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



/*************************************************************************
 * This creates the original dungeon map and places the player in the 1st element of the array as the current location
 ************************************************************************/
void InitializeDungeonMap(int dungeonTracker[])
{
	for (int i = 0; i < ARRAYSIZE; i++ )
	{
		dungeonTracker[i] = 0;
	}

	//sets first spot of dungeon as current location
	dungeonTracker[0] = 1;
}



/*************************************************************************
 * Assign each of the dungeon obstacles an obstacle number.  The dungeonObstacles array is a parallel array to the dungeonTracker
 ************************************************************************/
void InitializeDungeonObstacles(int dungeonObstacles[], int obstacleCount)
{
	for (int i = 0; i < ARRAYSIZE; i++ )
	{
		dungeonObstacles[i] = getRandomArrayNumber(obstacleCount);

		//test comment out
//		cout << "obstacle " << i << " is " << dungeonObstacles[i] << endl;
	}

	//get a random number for a random position of the array to assign to the exit door
	int exitDoor = getRandomArrayExitNumber();

	//exit door is the number that is one greater than the obstacle count to make this a bit dynamic
	dungeonObstacles[exitDoor] = obstacleCount;

	//setting the first room to the first obstacles (grass - no effect on the player)
	dungeonObstacles[0] = 0;

	//TEST - COMMENT THESE OUT LATER
//	cout << endl << "obstacle " << 0 << " is changed to " << dungeonObstacles[0] << endl;
//	cout << endl << "obstacle " << exitDoor << " is changed to " << dungeonObstacles[exitDoor] << endl;

}


/*************************************************************************
 * This function allows the user to choose a room.  It marks the current room as visited and marks the new room as the current location
 ************************************************************************/
int chooseRoom(int dungeonTracker[])
{
	int roomNumber = getValidRoomNumber(dungeonTracker);
	cout << endl << "Moving to room " << roomNumber << " of the dungeon..." << endl;
	cout << "You currently have " << playerCoins << " coin(s)." << endl << endl;


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



/*************************************************************************
 * This function returns a bool that is true if the user already visited that room or if they are currently in it
 *
 *	//0 = not visited
 *	//1 = current location
 *	//2 = visited
 ************************************************************************/
bool preventSameRoomTwice(int dungeonTracker[], int roomNumber)
{
	bool alreadyVisited;

	if (dungeonTracker[roomNumber] >= 1)
	{
		alreadyVisited = true;
	}
	return alreadyVisited;
}



/*************************************************************************
 * This function gets the next room number the user wants to go into.  It uses input validation to make
 * sure it is valid and within the dungeonTracker array size.  It uses the preventSameRoomTwice function to prevent
 * the user from going to the room they are already in or an already visited room.
 *
 *	//0 = not visited
 *	//1 = current location
 *	//2 = visited
 ************************************************************************/
int getValidRoomNumber(int dungeonTracker[])
{
	int roomNumber = -1;
	while (roomNumber <= -1 || roomNumber >= ARRAYSIZE )
	{
		cout << "Enter what room you would like to go to next: " << endl;
		cin >> roomNumber;

		if (!(roomNumber <= -1 || roomNumber >= ARRAYSIZE))
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





/*************************************************************************
 * This function plays the game based on what obstacle is in the dungeontracker.
 * It loops through the dungeonObstacles array and reacts differently based on the obstacle.
 *
 *Each obstacle has different consequences for the player. The enemy encounter - goblin calls other functions
 *If you want to add more obstacles, change obstacleCount in main and add more IF statements here.
 ************************************************************************/
void roomGame(int dungeonObstacles[], int roomNumber, int obstacleCount)
{


//exit door number is the number of obstacles plus one.
//if the room is the exit door then set the escaped bool to true so that the game will be over

// 0 - grass = nothing
// 1 - drown and game over
// 2 - goblin ceo game.  30% to die, 70% to win.  If player has a coin can escape
// 3 - player finds a coin and leaves the room

	if (dungeonObstacles[roomNumber] == obstacleCount)
	{
		escaped = true;
		cout << "You found the exit door and escaped the dungeon!" << endl;
		cout << "You managed to escape with " << playerCoins << " gold coin(s).";
	}
	else if (dungeonObstacles[roomNumber] == 0)
	{
		cout << "You enter a room filled with lush green grass.  The room is otherwise empty.  Nothing happens." << endl;
	}
	else if (dungeonObstacles[roomNumber] == 1)
	{
		cout << "You enter a room that appears to be normal.  Suddenly, the floor disappears and you find yourself in a deep pool of water." << endl
			<< "You knew you should have brought your SCUBA gear when exploring dungeons.  You drown :(" << endl;
		cout << endl <<"GAME OVER";
		gameover = true;
	}

	else if (dungeonObstacles[roomNumber] == 2)
	{
		cout << "You enter a room that has a vicious goblin CEO in it.  He hates C++ and programming, and wants to lay off your entire department." << endl;
		cout << "The goblin CEO asks you to justify why you should keep your job.  He has a complicated accounting spreadsheet that looks intimidating." << endl << endl;
		int GoblinGameResult = playGoblinGame();

		if (GoblinGameResult == 0)
		{
			cout << endl << "GAME OVER";
			gameover = true;
		}

	}

	else if (dungeonObstacles[roomNumber] == 3)
	{
		cout << "You see an empty room with a box in it.  You open the box and find a single solid gold coin in it.  The coin has a picture of a goblin on it." << endl
			<< "You pocket the coin, just in case." << endl;
		playerCoins++;
	}

	if (gameover == false && escaped == false)
	{
		cout << endl << "You currently have " << playerCoins << " coin(s)." << endl;
		cout << "According to your map, you are in room " << roomNumber << " of the dungeon." << endl;
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


/*************************************************************************
 * This is an enemy encounter. The player can give up a coin to avoid the encounter if they have any  They can also choose to keep the coin.
 * Otherwise this will call a function where the player has a 70% chance of surviving and getting a coin; 30% chance of losing the game
 ************************************************************************/
int playGoblinGame()
{

	int goblinResult = -1;
	int goblinChoice = 0;

	if (playerCoins >= 1)
	{
		cout <<"You realize that the goblin CEO might be persuaded to let you escape if you give him the goblin coin you found earlier!" << endl;
		cout << "You also recall that the coin is solid gold and that you have student loans to pay off." << endl  << endl;

		cout << "Do you give the goblin one of your " << playerCoins << " coin(s)?" << endl;

		//player input whether to give up a coin
		goblinChoice = getValidGoblinNumber();

		if (goblinChoice == 1)
		{
			cout << "The goblin CEO accepts your coin and lets you leave the room.";
			playerCoins--;
			goblinResult = 1;
			return goblinResult;
		}
		else if (goblinChoice ==2)
		{
			cout << "A gold coin is probably worth a bit of money.  You decide to keep it." << endl;

		}
	}


	//get random # for survival 70% or game over 30%
	int goblinRandomNumber = getGoblinRandomNumber();

	if (goblinRandomNumber == 0)
	{
		cout << "You attempt to explain to the goblin how much money you create for the company, but he is not convinced." << endl;
		cout << "He announces you are fired on the spot." << " In shock, you have a heart attack and die :(" << endl;
		goblinResult = 0;
	}
	else if (goblinRandomNumber == 1)
	{
		cout << "You show the goblin CEO his Excel spreadsheet is incorrect. " <<
				"He realizes you make $2 million for the goblin company a year and are paid a hundredth of that." << endl <<
				"He lets you leave the room and gives you a coin since you are underpaid." << endl;
		playerCoins++;
		goblinResult = 1;
	}

	return goblinResult;
}


/*************************************************************************
 * Gets valid input from the player whether they want to give a coin to the goblin
 ************************************************************************/
int getValidGoblinNumber()
{
	int goblinNumber = -1;
	while (goblinNumber <= 0 || goblinNumber >= 3 )
	{
		cout << "Enter 1 to give a coin to the goblin.  Enter 2 to keep your coins, and attempt to convince the goblin to not fire you: " << endl;
		cin >> goblinNumber;
	}

	return goblinNumber;
}


/*************************************************************************
 * This function returns a random number from 1 to 10
 * If the number is 1, 2 or 3 (30% chance), then it will return the number 0 which will lead to the game over screen
 * Otherwise it will return 1 meaning the player survived the goblin (70% chance).
 ************************************************************************/
int getGoblinRandomNumber()
{
	int goblinEncounterResult = 50;

	int minVal = 1;
	int maxVal = 10;
	int randNumber = minVal + rand() % (maxVal - minVal +1);

	if (randNumber <= 3)
	{
		goblinEncounterResult = 0;
	}
	else if (randNumber > 3 && randNumber < 11 )
	{
		goblinEncounterResult = 1;
	}

	return goblinEncounterResult;
}
