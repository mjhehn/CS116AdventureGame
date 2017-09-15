/*
Final Project- Text Based Adventure Game
Matt H. & Christian M.
5/13/2013
Description:

In this game, a player can input two word command combinations (as described in the help function output) to manipulate
and move through the game's mazes and look/use puzzles.


*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int guardRoom(string itemsArray[7], int navigate);			//the guard room portion of game. 
int tortureRoom(string itemsArray[7], int navigate);		//the torture room portion of game.	
int cellBlock(string itemsArray[7], int navigate);			//the cell room portion of game.
int cavernFork1(string itemsArray[7], int navigate); 		//the first room in the cavern maze.
void playHelp();											//function for printing out the help information.
int cavernForkRight1(string itemsArray[7], int navigate);	//part one of right half of maze.
int cavernForkLeft1(string itemsArray[7], int navigate);	//part one of left half of maze.
int cavernForkRight2(string itemsArray[7], int navigate);	//part two of right half of maze.
int cavernForkLeft2(string itemsArray[7], int navigate);	//part two of left half of maze.
int cavernForkRight3(string itemsArray[7], int navigate);	// part three of right half of maze.
int cavernForkLeft3(string itemsArray[7], int navigate);	//part three of left half of maze.
int cavernCornerLeft(string itemsArray[7], int navigate);	//dead end on left half of maze.
int cavernCornerRight(string itemsArray[7], int navigate);	//dead end on right half of maze.
int cavernFork2(string itemsArray[7], int navigate);		//point in maze where right/left rejoin and lead to final room.
int finalRoom(string itemsArray[7], int navigate);			//final room in game.
int gameOver(int endGame);									//game over function for printing final dialogue

/**************************************
commands function to return a value for the room function to process as per their instructions
parameters: string itemsArray and navigate.
return: 0
**************************************/
int commands(string &commandString, string &commandString2, string itemsArray[7], int &navigate)
{
	navigate = 0;
	int commandLoop = 0;		//if a command was good- for returning
								//Look- up, left, etc. Go- North, South, East, West. use- item check-inventory
	cout<<"\t-";
	cin>>commandString;
	cin>>commandString2;
	cout<<endl;

	if (commandString == "go")
	{
		if (commandString2 == "north")
		{
			cout<<"You go north..."<<endl;
			commandLoop = 1;
			navigate = 1;
		}
		else if (commandString2 == "south")
			{
				cout<<"You go south..."<<endl;
				commandLoop = 1;
				navigate = 3;
			}
			else if (commandString2 == "east")
				{
					cout<<"You go east..."<<endl;
					commandLoop = 1;
					navigate = 2;
				}
				else if (commandString2 == "west")
					{
						cout<<"You go west..."<<endl;
						commandLoop = 1;
						navigate = 4;
					}
					else
					{
						cout<<"Invalid command, please try again."<<endl;
					}

	}
	else if (commandString == "look")
		{
			commandLoop = 2;
		}
		else if (commandString == "take")
			{
				commandLoop = 3;
			}
			else if (commandString == "use")
				{
					commandLoop = 4;
				}
				else if (commandString == "check")
					{
						if (commandString2 == "inventory")
						{
							cout<<endl<<"~INVENTORY~"<<endl;
							for (int i = 0; i < 6; i++)			//i is variable for looping
							{
								cout<<itemsArray[i]<<endl;
								commandLoop = 0;
							}
						}
						else if (commandString2 == "help")
						{
							playHelp();
							commandLoop = 0;
						}
					}
					else
					{
						cout<<"Invalid command, please try again."<<endl;
					}
	cout<<endl;
	return commandLoop;
}

/**************************************
playHelp function is called from commands to read out what the available commands there are for the game.
parameters: n/a
return: n/a
**************************************/
void playHelp()
{
		cout<<"All main commands are two word commands: \n \t Take [item] \n \t Use [item]";
		cout<<"\n \t Go [north, south, east west] \n \t Check [inventory]";
		cout<<"\n \t Look [object] \n";
		cout<<" \n \t All commands are lower case, and in case of special commands\n";
		cout<<"\t follow prompts in the lower case. \n";
		cout<<"\n if a command fails to work and does not return an invalid \n";
		cout<<"\n then enter the command again. \n\n";
		cout<<"\n \t Type check help at any time to be reminded of the commands\n";
}

/**************************************
startRoom function will output the startRoom text file and process user input in game to move to another room.
parameters: string itemsArray and navigate.
return: 0
**************************************/

int startRoom(string itemsArray[7], int navigate)
{
	
	string testString, checkString;				//strings for storing and outputting the text file.
	ifstream infile;
	ofstream outfile;
	int index;									//an increment cap for the output file loop.
	infile.open("startRoom.txt");
	index = 0;

	do{
		checkString = testString;
		infile>>testString;
		index ++;
		if (testString == checkString)
		{
			testString = " ";
		}
		else
		{
			cout<<testString<<" ";
		}
	}while(!infile.fail() && index <59);
	cout<<endl<<endl;
	infile.close();

	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 3)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:
			cout<<"\n There's nothing to look at there.\n";
			commandLoop=0;
			break;

		case 3:
			cout<<"\n there's nothing to take\n";
			commandLoop=0;
			break;

		case 4:
			cout<<"\n there's nothing to use in here\n";
			commandLoop=0;
			break;

		default:
			;
		}
	}

	switch (navigate)
	{	case 1:
			cellBlock(itemsArray, navigate);
			break;
		case 2:
			tortureRoom(itemsArray, navigate);
			break;
		case 4:
			guardRoom(itemsArray, navigate);
			break;
		default:
			;}

	return 0;
}

/**************************************
guardRoom function will output the guardRoom text file and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for later progression. 
parameters: string itemsArray and navigate.
return: 0
**************************************/

int guardRoom(string itemsArray[7], int navigate)
{
	string testString, checkString;			//strings for outputting text file
	ifstream infile;
	ofstream outfile;
	int index;								//index cap for text output
	infile.open("guardRoom.txt");
	index = 0;

	do{
		checkString = testString;
		infile>>testString;
		index ++;
		if (testString == checkString)
		{
			testString = " ";
		}
		else
		{
			cout<<testString<<" ";
		}
	}while(!infile.fail() && index <65);
	cout<<endl<<endl;
	infile.close();

	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	int commandLoop = 0;				//condition for looping and for switch/if statements
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 1 || navigate == 3 || navigate == 4)
		{
			commandLoop = 0;
			cout<<"...OW! Running into a wall hurts!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:		//look
			while (commandLoop == 2)
			{
				if(commandString2 == "shield")
				{
					if (itemsArray[2] != "Shield")
					{
						cout<<"\n It's an old shield with a hawk on it. It seems to be bolted to the wall. \n";
						commandLoop = commands(commandString, commandString2, itemsArray, navigate);
						if (commandLoop == 4 && commandString2 == "wrench" && itemsArray[1] == "Wrench")
						{
							cout<<"\n You unbolt the shield from the wall with your wrench, revealing a button.\n";
							cout<<"Do you want to push the button? Enter Yes or No.\n";
							string button;					//to confirm if player wants to press the button.
							cin>>button;
							if (button == "Yes"  || button == "yes")
							{
								cout<<"\n The chest on the other side of the room makes an odd sound.\n";
								itemsArray[2] = "Shield";
							}
							else
							{
								cout<<"\n You replace the shield on the wall. \n";
								itemsArray[2] = "   ";
							}
							commandLoop=0;
						}
						else
						{
							commandLoop=0;
						}
					}

					else
					{
						cout<<"\n You already pushed the button here and took the shield.\n ";
						commandLoop = 0;
					}
				}
				else 
				{
					commandLoop=0;
				}
					
				if (commandString2 == "chest")
				{
					if (itemsArray[2] != "Shield")
					{
						cout<<"\n The chest is locked, and there does not appear to be a keyhole.\n";
						commandLoop=0;
					}
					else
					{
						cout<<"\n You lift the chest's now open lid, and find a key, which you take. \n";
						itemsArray[0] = "Bronze Key";
						commandLoop=0;
					}
				}
				else{;} 
					
				if (commandString2 == "table")
				{
					cout<<"\n You see a mancala board on the table- no playing pieces though. \n";
					commandLoop=0;
				}
				else{;}

				if (commandString2 == "cot")
				{
					cout<<"\n It looks as though it has not been slept on in a long time.\n";
					commandLoop=0;
				}
				else{;}
			}
			break;

		case 3:
			cout<<"\n there's nothing to take\n";
			commandLoop=0;
			break;

		case 4:
			if (itemsArray[1] == "Wrench")
			{
				cout<<"\n Nothing seems to happen.\n";
			}
			else
			{
				cout<<"\n there's nothing to use in here\n";
			}
			commandLoop=0;
			break;

		default:
			;
		}

	}


	switch (navigate)
	{	case 2:
			startRoom(itemsArray, navigate);
			break;
		default:
			;}

	return 0;
}

/**************************************
tortureRoom function will output the tortureRoom text file and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for later progression. 
parameters: string itemsArray and navigate.
return: 0
**************************************/

int tortureRoom(string itemsArray[7], int navigate)
{
	string testString, checkString;					//strings for outputting text file
	ifstream infile;
	ofstream outfile;
	int index;										//cap for text output
	infile.open("tortureRoom.txt");
	index = 0;

	do{
		checkString = testString;
		infile>>testString;
		index ++;
		if (testString == checkString)
		{
			testString = " ";
		}
		else
		{
			cout<<testString<<" ";
		}
	}while (!infile.fail() && index < 53);
	cout<<endl<<endl;
	infile.close();

	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate != 4 && commandLoop == 1)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:
			while (commandLoop ==2) 
			{
				if (commandString2 == "table")
				{
					cout<<"It's a table. there's a wrench on it. \n";
					commandLoop = commands(commandString, commandString2, itemsArray, navigate);
					if (commandLoop == 3 && itemsArray[1] != "Wrench")		//3 is take
					{
						itemsArray[1] = "Wrench";
						cout<<"wrench taken \n";
						commandLoop=0;
					}
					else if (itemsArray[1] == "Wrench")
					{
						cout<<"You already got the wrench that was here. Nothing else of interest. \n";
						commandLoop=0;
					}
						else
						{
							commandLoop=0;
						}
				}
				if (commandString2 == "rack")
				{
					cout<<"It looks as though it was once used heavily. \n";
					commandLoop=0;
				}
				else{;}

				if (commandString2 == "shackles")
				{
					cout<<"A row of old, rusty shackles.\n";
					commandLoop=0;
				}
				else
				{
					commandLoop=0;
				}
			}
			break;
		case 3:
			cout<<"\n there's nothing to take\n";
			commandLoop=0;
			break;

		case 4:
			cout<<"\n there's nothing to use in here\n";
			commandLoop=0;
			break;
		default:
			;
		}

	}

	switch (navigate)
	{	
		case 4:
			startRoom(itemsArray, navigate);
			break;
		default:
			;}

	return 0;
}

/**************************************
cellBlock function will output the cellBlock text file and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for later progression. 
parameters: string itemsArray and navigate.
return: 0
**************************************/

int cellBlock(string itemsArray[7], int navigate)
{

	string testString, checkString;				//strings for outputting text file
	ifstream infile;
	ofstream outfile;
	int index;									//cap for text file output.
	infile.open("cellRoom.txt");
	index = 0;

	do{
		checkString = testString;
		infile>>testString;
		index ++;
		if (testString == checkString)
		{
			testString = " ";
		}
		else
		{
			cout<<testString<<" ";
		}
	}while (!infile.fail() && index < 53);
	cout<<endl<<endl;
	infile.close();
	cout<<endl;

	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 2 || navigate == 1 || navigate == 4)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:		//look
			if (commandString2 == "door")
			{
				cout<<"\n It's a large wooden door with a slot for a key.\n";
				if(itemsArray[0] == "Bronze Key")
				{
					commandLoop = commands(commandString, commandString2, itemsArray, navigate);
					if (commandLoop == 4)
					{
						cout<<"\n The door opens, revealing a passageway carved into the rock, which you eagerly follow. \n";
						cout<<"\n You exit the cell block and enter a cavern lit by convienent torches. ";
						cavernFork1(itemsArray, navigate);
					}
				}
				else
				{
					commandLoop = 0;
				}
			}
			else
			{
				cout<<"\n There's nothing to look at there.\n";
				commandLoop=0;
			}
			
			break;

		case 3:
			cout<<"\n there's nothing to take\n";
			commandLoop=0;
			break;

		case 4:
			cout<<"\n there's nothing to use in here\n";
			commandLoop=0;
			break;

		default:
			;
		}
	}

	


	switch (navigate)
	{	
		case 3:
			startRoom(itemsArray, navigate);
			break;
		default:
			;}

	return 0;
}

/**************************************
maze/cavern functions will output the text information and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for later progression. 
parameters: string itemsArray and navigate.
return: 0
**************************************/

int cavernFork1(string itemsArray[7], int navigate)
{
	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	cout<<"The room branches into a T shape- which has passages going off to the east and west, with the cell block back to the south. \n";
	
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 1)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:		//look
			cout<<"\n There's nothing to look at there.\n";
			commandLoop=0;
			break;

		case 3:
			cout<<"\n there's nothing to take\n";
			commandLoop = 0;
			break;

		case 4:
			cout<<"\n there's nothing to use in here\n";
			commandLoop = 0;
			break;

		default:
			;
		}
	}

	switch (navigate)
	{	
	case 3:
		cellBlock(itemsArray, navigate);
		break;
	case 2:
		cavernForkRight1(itemsArray, navigate);
		break;
	case 4:
		cavernForkLeft1(itemsArray, navigate);
		break;
	default:
		;}
	return 0;
}

/**************************************
maze/cavern functions will output the text information and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for later progression. 
parameters: string itemsArray and navigate.
return: 0
**************************************/

int cavernForkRight1(string itemsArray[7], int navigate)
{
	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	cout<<"\n the passage runs to the south and the main cavern from the cell block is to the west.\n";
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 1 || navigate == 2)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:		//look
			cout<<"\n There's nothing to look at there.\n";
			commandLoop = 0;
			break;

		case 3:
			cout<<"\n there's nothing to take\n";
			commandLoop = 0;
			break;

		case 4:
			cout<<"\n there's nothing to use in here\n";
			commandLoop = 0;
			break;

		default:
			;
		}
	}

	switch (navigate)
	{	
	case 4:
		cavernFork1(itemsArray, navigate);
		break;
	case 3:
		cavernForkRight2(itemsArray, navigate);
		break;
	default:
		;}
	return 0;
}

/**************************************
maze/cavern functions will output the text information and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for later progression. 
parameters: string itemsArray and navigate.
return: 0
**************************************/

int cavernForkLeft1(string itemsArray[7], int navigate)
{
	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	cout<<"\n the passage meanders the south, and the main cavern from the cell block is to the east.\n";
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 1 || navigate == 4)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:		//look
			cout<<"\n There's nothing to look at there.\n";
			commandLoop = 0;
			break;

		case 3:
			cout<<"\n there's nothing to take\n";
			commandLoop = 0;
			break;

		case 4:
			cout<<"\n there's nothing to use in here\n";
			commandLoop = 0;
			break;

		default:
			;
		}
	}

	switch (navigate)
	{	
	case 2:
		cavernFork1(itemsArray, navigate);
		break;
	case 3:
		cavernForkLeft2(itemsArray, navigate);
		break;
	default:
		;}
	return 0;
}

/**************************************
maze/cavern functions will output the text information and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for later progression. 
parameters: string itemsArray and navigate.
return: 0
**************************************/

int cavernForkRight2(string itemsArray[7], int navigate)
{
	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	cout<<"\n Another passage branches off to the east. The main passage runs south and north\n";
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 4)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:		//look
			cout<<"\n There's nothing to look at there.\n";
			commandLoop=0;
			break;

		case 3:
			cout<<"\n there's nothing to take\n";
			commandLoop=0;
			break;

		case 4:
			cout<<"\n there's nothing to use in here\n";
			commandLoop=0;
			break;

		default:
			;
		}
	}

	switch (navigate)
	{	
	case 1:
		cavernForkRight1(itemsArray, navigate);
		break;
	case 3:
		cavernForkRight3(itemsArray, navigate);
		break;
	case 2:
		cavernCornerRight(itemsArray, navigate);
		break;
	default:
		;}
	return 0;
}

/**************************************
maze/cavern functions will output the text information and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for later progression. 
parameters: string itemsArray and navigate.
return: 0
**************************************/

int cavernForkLeft2(string itemsArray[7], int navigate)
{
	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	cout<<"\n Another passage branches off to the west. The main passage runs south and north\n";
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 2)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:		//look
			cout<<"\n There's nothing to look at there.\n";
			commandLoop=0;
			break;

		case 3:
			cout<<"\n there's nothing to take\n";
			commandLoop=0;
			break;

		case 4:
			cout<<"\n there's nothing to use in here\n";
			commandLoop=0;
			break;

		default:
			;
		}
	}
	switch (navigate)
	{	
	case 1:
		cavernForkLeft1(itemsArray, navigate);
		break;
	case 3:
		cavernForkLeft3(itemsArray, navigate);
		break;
	case 4:
		cavernCornerLeft(itemsArray, navigate);
		break;
	default:
		;}
	return 0;
}

/**************************************
maze/cavern functions will output the text information and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for later progression. 
parameters: string itemsArray and navigate.
return: 0
**************************************/

int cavernForkRight3(string itemsArray[7], int navigate)
{
	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	cout<<"\n the passage goes off to the west or north. \n";
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 3 || navigate == 2)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:		//look
			cout<<"\n There's nothing to look at there.\n";
			commandLoop = 0;
			break;

		case 3:
			cout<<"\n there's nothing to take\n";
			commandLoop = 0;
			break;

		case 4:
			cout<<"\n there's nothing to use in here\n";
			commandLoop = 0;
			break;

		default:
			;
		}
	}
	switch (navigate)
	{	
	case 1:
		cavernForkRight2(itemsArray, navigate);
		break;
	case 4:
		cavernFork2(itemsArray, navigate);
		break;
	default:
		;}
	return 0;
}

/**************************************
maze/cavern functions will output the text information and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for later progression. 
parameters: string itemsArray and navigate.
return: 0
**************************************/

int cavernForkLeft3(string itemsArray[7], int navigate)
{
	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	cout<<"\n the passage goes to the east or north \n";
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 3 || navigate == 4)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:		//look
			cout<<"\n There's nothing to look at there.\n";
			commandLoop = 0;
			break;

		case 3:
			cout<<"\n there's nothing to take\n";
			commandLoop=0;
			break;

		case 4:
			cout<<"\n there's nothing to use in here\n";
			commandLoop=0;
			break;

		default:
			;
		}
	}
	switch (navigate)
	{	
	case 1:
		cavernForkLeft2(itemsArray, navigate);
		break;
	case 2:
		cavernFork2(itemsArray, navigate);
		break;
	default:
		;}
	return 0;
}

/**************************************
maze/cavern functions will output the text information and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for later progression. 
parameters: string itemsArray and navigate.
return: 0
**************************************/

int cavernCornerLeft(string itemsArray[7], int navigate)
{
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],	
	if (itemsArray[6] != "lever")
	{
		cout<<"\n It's a dead end. One of the walls here looks odd, maybe there's a lever somewhere \n the main passage is back to the east. \n";
	}
	else
	{
		cout<<"\n A chest is revealed behind the secret door- now swung back onto the wall. \n";
	}
	
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 1 || navigate == 3 || navigate == 4)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:		//look
			if (itemsArray[6] == "lever")
			{
				if (commandString2 == "chest" && itemsArray[5] != "Silver Key")
				{
					cout<<"\n You open the chest and take the key within. \n";
					itemsArray[5] = "Silver Key";
					commandLoop=0;
				}
				else if (itemsArray[5] == "Silver Key")
				{
					cout<<"\n You already got the key here. \n";
					commandLoop=0;
				}
					else
					{
						commandLoop=0;
					}
			}
			else
			{
				cout<<"\n There's nothing to look at there.\n";
				commandLoop=0;
			}
			break;

		case 3:
			cout<<"\n there's nothing to take\n";
			commandLoop=0;
			break;

		case 4:
			cout<<"\n there's nothing to use in here\n";
			commandLoop=0;
			break;

		default:
			;
		}
	}
	switch (navigate)
	{	
	case 2:
		cavernForkLeft2(itemsArray, navigate);
		break;
	default:
		;}
	return 0;
}

/**************************************
maze/cavern functions will output the text information and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for later progression. 
parameters: string itemsArray and navigate.
return: 0
**************************************/

int cavernCornerRight(string itemsArray[7], int navigate)
{
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	cout<<"\n You enter a dead-end to see a pile of dirt piled against the wall, and a decrepit skeleton with shovel in hand next to it \n the main passage is back to the west. \n";
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 3 || navigate == 1 || navigate == 2)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:		
			if (commandString2 == "dirt" && itemsArray[4] != "Shovel")
			{
				cout<<"\n It looks like there is something in there, but there's too much rubble in the way. \n";
				commandLoop = 0;
			}
			else if (commandString2 == "dirt")
				{
					cout<<"\n You think the shovel may be able to clear the dirt.\n";
					commandLoop = commands(commandString, commandString2, itemsArray, navigate);
					if (commandLoop == 4 && commandString2 == "shovel")
					{
						cout<<"\n You clear away the dirt enough to find a lever, which you pull. \n";
						itemsArray[6] = "lever";
						commandLoop = 0;
					}
					else
					{
						commandLoop = 0;
					}
				}
				else
				{
					;
				}
			if (commandString2 == "shovel" && itemsArray[4] != "Shovel")
			{
				cout<<"\n It looks as though you might be able to pry it loose from the skeleton's hands. \n";
				commandLoop = 0;
			}
			else
			{
				if (commandString2 != "dirt")
				{
				cout<<"\n There's nothing there.\n";
				}
				else{;}
				commandLoop=0;
			}
			break;

		case 3:
			if (commandString2 == "shovel")
			{
				cout<<"\n You take the shovel. \n";
				itemsArray[4] = "Shovel";
				commandLoop = 0;
			}
			else
			{
				cout<<"\n you can't take that\n";
				commandLoop = 0;
			}
			break;

		case 4:
			cout<<"\n there's nothing to use right now\n";
			commandLoop=0;
			break;

		default:
			;
		}
	}
	switch (navigate)
	{	
	case 4:
		cavernForkRight2(itemsArray, navigate);
		break;
	default:
		;}
	return 0;
}

/**************************************
maze/cavern functions will output the text information and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for later progression. 
parameters: string itemsArray and navigate.
return: 0
**************************************/

int cavernFork2(string itemsArray[7], int navigate)
{
	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	cout<<"\n you see the passages come together in a T. One passage goes to the south and towards daylight, and two others lead off to the east and west.\n";
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 1)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:		
			cout<<"\n There's nothing to look at there.\n";
			commandLoop=0;
			break;

		case 3:
			cout<<"\n there's nothing to take\n";
			commandLoop=0;
			break;

		case 4:
			cout<<"\n there's nothing to use in here\n";
			commandLoop=0;
			break;

		default:
			;
		}
	}
	switch (navigate)
	{	
	case 4:
		cavernForkLeft3(itemsArray, navigate);
		break;
	case 2:
		cavernForkRight3(itemsArray, navigate);
		break;
	case 3:
		finalRoom(itemsArray, navigate);
		break;
	default:
		;}
	return 0;
}

/**************************************
the final room function will output the finalRoom text file and process user input in game to move to another room.
and has a few interactions defined by input and switch or if statements for completion or return to other rooms
parameters: string itemsArray and navigate.
return: 0
**************************************/

int finalRoom(string itemsArray[7], int navigate)
{

	string testString, checkString;		//strings for outputting text file and preventing duplication of words through the loop
	ifstream infile;
	ofstream outfile;
	int index;							//word max for the text file
	infile.open("finalRoom.txt");
	index = 0;

	do{
		checkString = testString;
		infile>>testString;
		index ++;
		if (testString == checkString)
		{
			testString = " ";
		}
		else
		{
			cout<<testString<<" ";
		}
	}while(!infile.fail() && index <65);
	cout<<endl<<endl;
	infile.close();

	string commandString;				//general command. (Take, Look, Go, Use)
	string commandString2;				//specific command. (Take- item [specific name- one word],
	string choice;						//door choice- yes or no.
	int commandLoop = 0;				//loop condition and how some of the if statements and switchs choose their actions
	while (commandLoop == 0)
	{
		commandLoop = commands(commandString, commandString2, itemsArray, navigate);
		if (navigate == 3)
		{
			commandLoop = 0;
			cout<<"... and smack into a wall. You can't go that way!"<<endl;
		}
		else{;}

		switch (commandLoop)
		{
		case 2:		//look
			if(commandString2 == "door")
			{
				cout<<"\n Which door would you like to look at? \n";
				cin>>choice;
				if (choice == "wolf" || choice == "east")
				{
					cout<<"\n The wolf is up on its hind feet, looking rather vicious.";
					cout<<" There is a keyhole here ";
					
					if (itemsArray[5] == "Silver Key")
					{
						cout<<"that the key from the cave might fit. \n";
						cout<<"\n Do you want to use the silver key to open the door? If you pick the wrong door you may be in for a nasty surprise! \n";
						cin>>choice;
						if (choice == "yes")
						{
							commandLoop = 10;
						}
						else
						{
							cout<<"\n you go back to the center of the courtyard. \n";
							commandLoop = 0;
						}
						}
					else
					{
						cout<<"but your key from the guard room doesn't seem to fit. There must be another key somewhere. \n";
						cout<<"\n you go back to the center of the courtyard. \n";
						commandLoop = 0;
					}
					
				}
				else if (choice == "hawk" || choice == "west")
				{
					cout<<"\n The Hawk is spread wide. The talons and beak almost look sharp.";
					cout<<" There is a keyhole here ";
					
					if (itemsArray[5] == "Silver Key")
					{
						cout<<"that the key from the cave might fit. \n";
						cout<<"\n Do you want to use the silver key to open the door? If you pick the wrong door you may be in for a nasty surprise! \n";
						cin>>choice;
						if (choice == "yes")
						{
							commandLoop = 11;
						}
						else
						{
							cout<<"\n you go back to the center of the courtyard. \n";
							commandLoop = 0;
						}
						}
					else
					{
						cout<<"but your key from the guard room doesn't seem to fit. There must be another key somewhere. \n";
						cout<<"\n you go back to the center of the courtyard. \n";
						commandLoop = 0;
					}
				}
					else
					{
						cout<<"\n There's no door there. \n";
						commandLoop =0;
					}
			}
			else
			{
			cout<<"\n There's nothing to look at there.\n";
			commandLoop=0;
			}
			break;

		case 3:	
			cout<<"\n there's nothing to take\n";
			commandLoop=0;
			break;

		case 4:		
			cout<<"\n there's nothing to use here in the middle of the courtyard. \n";
			commandLoop=0;
			break;

		default:
			;
		}
		switch (navigate)
		{	
		case 1:
			cavernFork2(itemsArray, navigate);
			break;
		default:
			;
		}
	}
	gameOver(commandLoop);
	return 0;
}

/**************************************
function will check and output the text dependent on winning or losing.
parameters: endGame
return: 0
**************************************/

int gameOver(int endGame)
{
	for (int i = 0; i < 73; i++)		//i =variable for looping
	{
		cout<<"*";
	}
	cout<<endl;

	if (endGame == 10)
	{
		cout<<"\n You open the door, and walk through. The door slams shut behind you as a sharp pain is felt on the back of your head... \n \n";
		cout<<" You awaken to find yourself in a hallway, torches lining the roof... \n \n";

		cout<<"You didn't make it out of the dungeon, better luck next time. \n\n";
	}
	else if (endGame == 11)
	{
		cout<<"\n You open the door, and walk through. The door slams shut behind you as you take in a breath of clear air";
		cout<<" from the mountian forest outside. \n \n You managed to escape! \n \n";
	}
		else if (endGame != 11 || endGame != 10)
		{
			cout<<"\n Something went wrong. Please restart the game. \n";
		}

	for (int i = 0; i < 60; i++)				//i =variable for looping
	{
		cout<<"*";
		if (i == 30)
		{
			cout<<"~ GAME OVER ~";
		}
		else{;}
	}
	return 0;
}

int main()
{	
	string itemsArray[7] = {" ", " ", " ", " ", " "};					//containing list for items found in-game
	int navigate = 0;													//variable for directional movement
	for (int i = 0; i < 40; i++)				//i =variable for looping
	{
		cout<<"*";
		if (i == 20)
		{
			cout<<" ~ Escape from the dungeon of Rhombus ~ ";
		}
		else{;}
	}
	cout<<endl;
	playHelp();
	cout<<"\n You awaken to find yourself in a hallway, torches lining the roof, casting \n flickering shadows all about";
	cout<<" the room. A rat scurries by your feet as ";
	startRoom(itemsArray, navigate);
	cout<<endl;
	system("pause");
	return 0;
}
//Problems: Not much.