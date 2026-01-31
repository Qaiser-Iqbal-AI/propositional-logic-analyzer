#include<iostream>
#include<cmath>
#include<fstream>
#include<windows.h>
#include<cstdlib>
#include<conio.h>

using namespace std;

// Color codes
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;

//Default ship color
int shipColor = YELLOW;

// Function to set console text and background color
void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void print_cards();

void initilizeBoard(char board[10][10]);

void clearScreen();

void setRandomShips(char board[10][10]);

void vsComputer(char playerBoard[10][10], char computerBoard[10][10]);

void vsPlayer(char board1[10][10], char board2[10][10]);

void printBoard(char board[10][10], bool hideShips);

void playerAttack(char opponentBoard[10][10], int &playerScore);

void computerAttack(char opponentBoard[10][10], int &computerScore);

void updateScore(int &score);

void displayResult(int player1Score, int player2Score);

void clearBoard(char board[10][10]);

void showLeaderboard(const string playerNames[], const int scores[], int totalPlayers);

void showGameMenu();

//Our own functions
void advancedPrintBoard(char[10][10], char[10][10], char[10][10], char[10][10], bool);

int countShips(char [10][10]);

bool isSunken(char [10][10], char [10][10], int, int);

void setShipColor(char);

int main(){
	
	showGameMenu();
	
	return 0;
}

void showLeaderboard(const string playerNames[], const int scores[], int totalPlayers)
{
	system("cls");
	ifstream file("leaderboard.txt");
	string temp="";
	int score=0, count=0;
	
	if(file.is_open())
	{
		while(getline(file, temp))
		{
			count++;
		}
		
		file.close();
		
		if(count==0 && totalPlayers==2)
		{
			fstream file("leaderboard.txt", ios::app);
			if(scores[0]>=scores[1])
			{
				file<<playerNames[0]<<" "<<scores[0]<<endl;
				file<<playerNames[1]<<" "<<scores[1]<<endl;	
			}
			else
			{
				file<<playerNames[1]<<" "<<scores[1]<<endl;	
				file<<playerNames[0]<<" "<<scores[0]<<endl;
			}
			file.close();
		}
		else if(count==0 && totalPlayers==1 && scores[0]!=-999)
		{
			fstream file("leaderboard.txt", ios::app);
			file<<playerNames[0]<<" "<<scores[0]<<endl;
			file.close();
		}
		else if(scores[0]!=-999)
		{
			ifstream file("leaderboard.txt");
			ofstream tempFile("temp.txt", ios::trunc);
			bool highscore[2] = {false, false};
			
			for(int i=0;i<count;i++)
			{
				file>>temp>>score;
				if(score < scores[0] && !highscore[0])

				{
					tempFile<<playerNames[0]<<" "<<scores[0]<<endl;
					highscore[0] = true;
				}
				
				if(totalPlayers==2 && score<scores[1] && !highscore[1])
				{
					tempFile<<playerNames[1]<<" "<<scores[1]<<endl;
					highscore[1] = true;
				}
				
				tempFile<<temp<<" "<<score<<endl;
				
			}
			
			if(count==9)
			{
				if(totalPlayers==2 && scores[0]>=scores[1] && !highscore[0] && !highscore[1])
				{
					tempFile<<playerNames[0]<<" "<<scores[0]<<endl;
				}
				else if(totalPlayers==2 && scores[1]>=scores[0] && !highscore[0] && !highscore[1])
				{
					tempFile<<playerNames[1]<<" "<<scores[1]<<endl;
				}
				else if(!highscore[0])
				{
					tempFile<<playerNames[0]<<" "<<scores[0]<<endl;
				}
				else if(!highscore[1])
				{
					tempFile<<playerNames[1]<<" "<<scores[1]<<endl;
				}
			}
			else if(count<9)
			{
				if(totalPlayers==2 && scores[0]>=scores[1] && !highscore[0] && !highscore[1])
				{
					tempFile<<playerNames[0]<<" "<<scores[0]<<endl;
					tempFile<<playerNames[1]<<" "<<scores[1]<<endl;
				}
				else if(totalPlayers==2 && scores[1]>=scores[0] && !highscore[0] && !highscore[1])
				{
					tempFile<<playerNames[1]<<" "<<scores[1]<<endl;
					tempFile<<playerNames[0]<<" "<<scores[0]<<endl;
				}
				else if(!highscore[0])
				{
					tempFile<<playerNames[0]<<" "<<scores[0]<<endl;
				}
				else if(!highscore[1])
				{
					tempFile<<playerNames[1]<<" "<<scores[1]<<endl;
				}
			}
			
			tempFile.close();
			file.close();
			ofstream finalFile("leaderboard.txt", ios::trunc);
			
			int lines=0;
			
			ifstream tempFileInput("temp.txt");
			
			while(getline(tempFileInput, temp) && lines<10)
			{
				lines++;
				finalFile<<temp<<"\n";
			}
			
			file.close();
			tempFile.close();
			remove("temp.txt");
		}
		
	}
	else
	{
		cout<<"Results could not be saved! File could not open"<<endl;
		getch();
		file.close();
		return;
	}
	
	ifstream fileX("leaderboard.txt");
	
	int i=0;
	string output="";
	
	cout<<"=============== Leaderboard ==============="<<endl;
	
	while(getline(fileX,output))
	{
		i++;
		cout<<i<<". "<<output<<endl;
	}
	
	cout<<endl;
	
	fileX.close();
	
}

void setShipColor(char color)
{
	switch(color)
	{
		case '1':
			shipColor = YELLOW;
			break;
		case '2':
			shipColor = GREEN;
			break;
		case '3':
			shipColor = CYAN;
			break;
		case '4':
			shipColor = MAGENTA;
			break;
		default:
			shipColor = YELLOW;					
	}
}

void showGameMenu()
{  

	string player[1]={""};
	int scoreX[1] = {-999};
	clearScreen();
    char choice='\0';
    string playerName="";
    char gameMode='\0';
	cout<<"==================================================================="<<endl;
	cout<<endl;
	cout<<"\t\t   WELCOME TO BATTLESHIP GAME \t\t"<<endl;
	cout<<endl;
	
	cout<<"==================================================================="<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"\t\t\t  MAIN MENU\t\t\t"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	
	cout<<endl;
	cout<<"1.Start New Game"<<endl;
	cout<<"2.Instructions"<<endl;
	cout<<"3.View Learderboard"<<endl;
	cout<<"4.Exit"<<endl;
	cout<<endl;
	
	cout<<"-------------------------------------------------------------------"<<endl;
	
	cout<<endl;
	cout<<endl;
	cout<<"Enter your choice(1-4): ";
	cin>>choice;
	
	while(choice<'1' || choice>'4')
	{
		cout<<"Invalid! Enter Again: ";
		cin>>choice;
	}
	
	cout<<"-------------------------------------------------------------------"<<endl;
	
	clearScreen();
	
	switch(choice)
	{
		case '1':
			
			cout<<"\t\t\t START NEW GAME \t\t"<<endl;
			cout<<endl;
			cout<<"-------------------------------------------------------------------"<<endl;
			cout<<endl;
			
			cout<<"Choose your gamemode (1.Player Vs Player | 2.Player Vs Computer): ";
			cin>>gameMode;
			
			while(gameMode!='1' && gameMode!='2')
			{
				cout<<"Invalid! Enter Again: ";
				cin>>gameMode;
			}
			
			char board1[10][10];
			char board2[10][10];
			
			switch(gameMode)
			{
				case '1':
					vsPlayer(board1, board2);
					break;
				case '2':
					vsComputer(board1, board2);
					break;
				default:
					cout<<"Error!"<<endl;		
			}
			
			break;
		case '2':
			
			cout<<"-------------------------------------------------------------------"<<endl;
			cout<<endl;
			cout<<"\t\t INSTRUCTIONS \t\t"<<endl;
			cout<<endl;
			cout<<"-------------------------------------------------------------------"<<endl;
			
			cout<<"1.Place your ships on the board."<<endl;
			cout<<"2.You and the compiler take turns firing shots."<<endl;
			cout<<"3.'O' means MISS, 'X' means HIT."<<endl;
			cout<<"4.Sink all enemy ships to win!"<<endl;
			cout<<"5.Your score is based on acccuracy and speed."<<endl;
			
			cout<<"-------------------------------------------------------------------"<<endl;
			
			cout<<endl;
			cout<<"Press Any Key to Return to Main Menu..."<<endl;
			
			if(getch())
				showGameMenu();
				
			break;
		case '3':
			
			showLeaderboard(player, scoreX, 1);
			
			cout<<"Press Any Key to Continue"<<endl;
			getch();
			
			showGameMenu();
			
			break;
		case '4':
			exit(0);
			break;			
	}
	
}

void initilizeBoard(char board[10][10])
{
	for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            board[i][j] = '~';
}

void printBoard(char board[10][10], bool hideShips)
{
	// Print column headers (hardcoded)
    cout << "       0     1     2     3     4     5     6     7     8     9  " << endl;

    // Top border
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;

    // Row 0
    cout << "  0  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[0][i];
        if (cell == 'X') 
		{ 
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0); 
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else if(!hideShips && cell != '~')
		{
			setColor(7, shipColor);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+----- " << endl;

    // Row 1
    cout << "  1  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[1][i];
        if (cell == 'X') 
		{ 
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0); 
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else if(!hideShips && cell != '~')
		{
			setColor(7, shipColor);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+----- " << endl;

    // Row 2
    cout << "  2  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[2][i];
        if (cell == 'X') 
		{ 
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0); 
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else if(!hideShips && cell != '~')
		{
			setColor(7, shipColor);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+----- " << endl;

    // Row 3
    cout << "  3  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[3][i];
        if (cell == 'X') 
		{ 
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0); 
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else if(!hideShips && cell != '~')
		{
			setColor(7, shipColor);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+----- " << endl;

    // Row 4
    cout << "  4  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[4][i];
        if (cell == 'X') 
		{ 
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0); 
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else if(!hideShips && cell != '~')
		{
			setColor(7, shipColor);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+----- " << endl;

    // Row 5
    cout << "  5  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[5][i];
        if (cell == 'X') 
		{ 
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0); 
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else if(!hideShips && cell != '~')
		{
			setColor(7, shipColor);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+----- " << endl;

    // Row 6
    cout << "  6  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[6][i];
        if (cell == 'X') 
		{ 
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0); 
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else if(!hideShips && cell != '~')
		{
			setColor(7, shipColor);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+----- " << endl;

    // Row 7
    cout << "  7  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[7][i];
        if (cell == 'X') 
		{ 
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0); 
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else if(!hideShips && cell != '~')
		{
			setColor(7, shipColor);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+----- " << endl;

    // Row 8
    cout << "  8  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[8][i];
        if (cell == 'X') 
		{ 
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0); 
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else if(!hideShips && cell != '~')
		{
			setColor(7, shipColor);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+----- " << endl;

    // Row 9
    cout << "  9  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[9][i];
        if (cell == 'X') 
		{ 
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0); 
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else if(!hideShips && cell != '~')
		{
			setColor(7, shipColor);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  "<<cell<<"  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    cout << endl;

    // Bottom border
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;

}

void clearScreen()
{
	system("cls");
}

void clearBoard(char board[10][10])
{
	for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            board[i][j] = '~';
}

void print_cards()
{
	
		setColor(BLACK, BLUE);
		cout << " -------" <<endl;
		cout << " -     -" <<endl;
		cout << " -  5  -" <<endl;
		cout << " -     -" <<endl;
		cout << " -------"  <<endl;
		
}

void updateScore(int &score)
{
	score+=10;
}

void playerAttack(char board[10][10], int &score)
{
	int row=0, column=0;
	char inputRow='\0', inputColumn='\0';
	cout<<"Enter Co-ordinates (Row 0-9, Column 0-9): ";
		cin>>inputRow>>inputColumn;	
		
	column = inputColumn-48;
	row = inputRow-48;	
		
	while(inputRow<'0' || inputRow>'9' || inputColumn<'0' || inputColumn>'9' || board[row][column]=='X' || board[row][column]=='O')
	{
		cout<<"Invalid! Enter Again: ";
			cin>>inputRow>>inputColumn;	
			
		column = inputColumn-48;
		row = inputRow-48;	
	}	
	
	if(board[row][column] != '~')
	{
		board[row][column] = 'X';
		updateScore(score);
	}
	else
	{
		board[row][column] = 'O';
		score-=1;
	}
	
}

int countShips(char board[10][10])
{
	//A B D S P
	int arr[5] = {0};
	int count = 0;
	
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			switch(board[i][j])
			{
				case 'A':
					arr[0]++;
					break;
				case 'B':
					arr[1]++;
					break;
				case 'D':
					arr[2]++;
					break;
				case 'S':
					arr[3]++;
					break;
				case 'P':
					arr[4]++;
					break;				
			}
		}
	}
	
	for(int i=0;i<5;i++)
	{
		if(arr[i]>0)
			count++;
	}
	
	return count;
	
}

void displayResult(int player1Score, int player2Score)
{
	clearScreen();
	
	cout<<"==================== RESULTS ===================="<<endl;
	
	if(player1Score>player2Score)
	{
		cout<<"                  Player 1 WINS!                 "<<endl;
		cout<<"                   Score = "<<player1Score<<"    "<<endl;	
	}
	else if(player2Score>player1Score)
	{
		cout<<"                  Player 2 / Computer WINS!                 "<<endl;	
		cout<<"                   Score = "<<player2Score<<"    "<<endl;
	}
	else
	{
		cout<<"                    Its a DRAW!                 "<<endl;
		cout<<"                   Scores = "<<player1Score<<"    "<<endl;		
	}
	
}

void vsPlayer(char board1[10][10], char board2[10][10])
{
	
	string playerNames[2]={"",""};
	string shipNames[5] = {"Patrol Boat", "Submarine", "Destroyer", "Battleship", "Aircraft Carrier"};
	int shipLengths[5] = {2,3,3,4,5};
	char placementOption = '\0', colorOption = '\0';
	
	cout<<endl;
	
	cout<<"Enter Player 1 Name: ";
		cin>>playerNames[0];
		
	cout<<endl;	
		
	cout<<"Enter Player 2 Name: ";
		cin>>playerNames[1];
	
	initilizeBoard(board1);
	initilizeBoard(board2);
	
	clearScreen();
	
	cout<<"Enter Placement Option for Player 1 (1-Manual, 2-Random): ";
	placementOption = getche();
		
	while(placementOption!='1' && placementOption!='2')
	{
		cout<<"\nInvalid! Enter Again: ";
		placementOption = getche();
		cout<<endl;	
	}	
	
	cout<<endl;
	
	cout<<"\nEnter Color of Battleships:\n(1.Yellow    2.Green    3.Cyan    4.Magenta)"<<endl;
	colorOption = getche();
		
	while(colorOption<'1' || colorOption>'4')
	{
		cout<<"\nInvalid! Enter Again: ";
		colorOption = getche();
		cout<<endl;	
	}
	
	setShipColor(colorOption);
	
	//For Player 1
	if(placementOption=='1')
	{
		//I have set scope of these variable to this if only and initialized them with default values
		int row=0, column=0;
		char inputRow='\0', inputColumn='\0';
		char placement='H';
		bool checkVertical = false;
		
		for(int i=0;i<5;i++)
		{
			placement = 'H';
			
			if(!checkVertical)
				row=0, column=0;
				
			bool isValidVertical=true, isValidHorizontal=true;
			
			if(checkVertical)
			{
				isValidHorizontal = false;
			}
			
			clearScreen();
			cout<<"    ============== Placement of Ships for Player 1 =============="<<endl;
			printBoard(board1, false);	
			
			if(!checkVertical)
			{
				cout<<"Enter co-ordinates for "<<shipNames[i]<<" (ship length "<<shipLengths[i]<<"): "<<endl;
				cout<<"Enter Starting Row (0-9): ";
					cin>>inputRow;
				cout<<"Enter Starting Column (0-9): ";
					cin>>inputColumn;
				
				//If row, column, or placement is out of range, it will ask again eles it will move on to secondary validation
				while((inputRow<'0' || inputRow>'9') || (inputColumn<'0' || inputColumn>'9'))
				{	
					cout<<"Invalid! Enter Row-Column Again: ";
					cin>>inputRow>>inputColumn;	
				}	
			}
			
			column = inputColumn-48;
			row = inputRow-48;
						
			if(column+shipLengths[i]-1>9)
			{
				isValidHorizontal = false;
			}
			
			if(row+shipLengths[i]-1 > 9)
			{
				isValidVertical = false;
			}
			
			
			//If its still valid, I check for other ships in there
			if(isValidHorizontal)
			{
				//All cells must be default '~'
				for(int j=0;j<shipLengths[i];j++)
				{
					if(board1[row][column+j] != '~')
						isValidHorizontal = false;
				}
			}
			
			if(isValidVertical)
			{
				//Same but for vertical
				for(int j=0;j<shipLengths[i];j++)
				{
					if(board1[row+j][column] != '~')
						isValidVertical = false;
				}	
			}
			
			if(!isValidHorizontal && !isValidVertical)
			{
				//If I find it to be invalid, I decrement i so loop will repeat that iteration and continue to skip the actual changing of board part
				cout<<"Invalid! Ship cannot be placed horizontally or vertically | Press Any Key to Place Again"<<endl;
				getch();
				i--;
				continue;
			}		
				
			if(isValidHorizontal)
			{
				for(int j=0;j<shipLengths[i];j++)
				{
					switch(i)
					{
						case 0:
							board1[row][column+j] = 'P';
							break;
						case 1:
							board1[row][column+j] = 'S';
							break;
						case 2:
							board1[row][column+j] = 'D';
							break;
						case 3:
							board1[row][column+j] = 'B';
							break;
						case 4:
							board1[row][column+j] = 'A';
							break;
						default:
							cout<<"Something has gone horribly wrong!";
							getch();
							exit(0);				
					}
				}
			}
			else if(isValidVertical)
			{
				if(!checkVertical)
				{
					checkVertical=true;
				}
				for(int j=0;j<shipLengths[i];j++)
				{
					switch(i)
					{
						case 0:
							board1[row+j][column] = 'P';
							break;
						case 1:
							board1[row+j][column] = 'S';
							break;
						case 2:
							board1[row+j][column] = 'D';
							break;
						case 3:
							board1[row+j][column] = 'B';
							break;
						case 4:
							board1[row+j][column] = 'A';
							break;
						default:
							cout<<"Something has gone horribly wrong!";
							getch();
							exit(0);				
					}
				}
			}
			
			clearScreen();
			printBoard(board1, false);
			
			if(isValidVertical && !checkVertical)
			{
				cout<<"Press 'V' to place ship vertically or 'C' to continue"<<endl;
				placement = getch();	
				
				while(placement!='V' && placement!='C' && placement!='v' && placement!='c')
				{
					cout<<"Invalid! Enter Again: ";
					placement = getche();
					cout<<endl;
				}			
			}	
			else
			{
				cout<<"Press Any Key to Continue . . ."<<endl;
				getch();
			}
			
			//Resetting Value to make sure next ship placement is horizontal by default
			if(checkVertical)
			{
				checkVertical = false;
			}
				
			if(placement=='V' || placement=='v')
			{
				checkVertical = true;
				for(int j=0;j<10;j++)
				{
					for(int k=0;k<10;k++)
					{
						switch(i)
						{
							case 0:
								if(board1[j][k] == 'P')
									board1[j][k] = '~';
								break;
							case 1:
								if(board1[j][k] == 'S')
									board1[j][k] = '~';
								break;
							case 2:
								if(board1[j][k] == 'D')
									board1[j][k] = '~';
								break;
							case 3:
								if(board1[j][k] == 'B')
									board1[j][k] = '~';
								break;
							case 4:
								if(board1[j][k] == 'A')
									board1[j][k] = '~';
								break;
							default:
								cout<<"Something has gone horribly wrong!";
								getch();
								exit(0);				
						}
					}
				}
				//Restarting Placement of Ship With Vertical Placement
				i--;
				continue;
			}	
		}
	}
	else
	{
		setRandomShips(board1);
		cout<<"Ships Have Been Randomly Placed"<<endl<<endl;
		cout<<"Press Any Key to Continue"<<endl;
		getch();
	}
		
	
	clearScreen();
	
	cout<<"    =========== Final Placement of Ships for Player 1 ==========="<<endl;
	printBoard(board1, false);
	cout<<"Press Any Key to Continue"<<endl;
	getch();
	clearScreen();
	
	//For Player 2
	cout<<"Enter Placement Option for Player 2 (1-Manual, 2-Random): ";
	placementOption = getche();
		
	while(placementOption!='1' && placementOption!='2')
	{
		cout<<"\nInvalid! Enter Again: ";
		placementOption = getche();
		cout<<endl;	
	}	
	
	cout<<endl;
	
	cout<<"\nEnter Color of Battleships:\n(1.Yellow    2.Green    3.Cyan    4.Magenta)"<<endl;
	colorOption = getche();
		
	while(colorOption<'1' || colorOption>'4')
	{
		cout<<"\nInvalid! Enter Again: ";
		colorOption = getche();
		cout<<endl;	
	}
	
	setShipColor(colorOption);
	
	if(placementOption=='1')
	{
		//I have set scope of these variable to this if only and initialized them with default values
		int row=0, column=0;
		char inputRow='\0', inputColumn='\0';
		char placement='H';
		bool checkVertical = false;
		
		for(int i=0;i<5;i++)
		{
			placement = 'H';
			
			if(!checkVertical)
				row=0, column=0;
				
			bool isValidVertical=true, isValidHorizontal=true;
			
			if(checkVertical)
			{
				isValidHorizontal = false;
			}
			
			clearScreen();
			cout<<"    ============== Placement of Ships for Player 2 =============="<<endl;
			printBoard(board2, false);	
			
			if(!checkVertical)
			{
				cout<<"Enter co-ordinates for "<<shipNames[i]<<" (ship length "<<shipLengths[i]<<"): "<<endl;
				cout<<"Enter Starting Row (0-9): ";
					cin>>inputRow;
				cout<<"Enter Starting Column (0-9): ";
					cin>>inputColumn;
				
				//If row, column, or placement is out of range, it will ask again eles it will move on to secondary validation
				while((inputRow<'0' || inputRow>'9') || (inputColumn<'0' || inputColumn>'9'))
				{
					cout<<"Invalid! Enter Row-Column Again: ";
					cin>>inputRow>>inputColumn;	
				}	
			}
			
			column = inputColumn-48;
			row = inputRow-48;
						
			if(column+shipLengths[i]-1>9)
			{
				isValidHorizontal = false;
			}
			
			if(row+shipLengths[i]-1 > 9)
			{
				isValidVertical = false;
			}
			
			
			//If its still valid, I check for other ships in there
			if(isValidHorizontal)
			{
				//All cells must be default '~'
				for(int j=0;j<shipLengths[i];j++)
				{
					if(board2[row][column+j] != '~')
						isValidHorizontal = false;
				}
			}
			
			if(isValidVertical)
			{
				//Same but for vertical
				for(int j=0;j<shipLengths[i];j++)
				{
					if(board2[row+j][column] != '~')
						isValidVertical = false;
				}	
			}
			
			if(!isValidHorizontal && !isValidVertical)
			{
				//If I find it to be invalid, I decrement i so loop will repeat that iteration and continue to skip the actual changing of board part
				cout<<"Invalid! Ship cannot be placed horizontally or vertically | Press Any Key to Place Again"<<endl;
				getch();
				i--;
				continue;
			}		
				
			if(isValidHorizontal)
			{
				for(int j=0;j<shipLengths[i];j++)
				{
					switch(i)
					{
						case 0:
							board2[row][column+j] = 'P';
							break;
						case 1:
							board2[row][column+j] = 'S';
							break;
						case 2:
							board2[row][column+j] = 'D';
							break;
						case 3:
							board2[row][column+j] = 'B';
							break;
						case 4:
							board2[row][column+j] = 'A';
							break;
						default:
							cout<<"Something has gone horribly wrong!";
							getch();
							exit(0);				
					}
				}
			}
			else if(isValidVertical)
			{
				if(!checkVertical)
				{
					checkVertical=true;
				}
				for(int j=0;j<shipLengths[i];j++)
				{
					switch(i)
					{
						case 0:
							board2[row+j][column] = 'P';
							break;
						case 1:
							board2[row+j][column] = 'S';
							break;
						case 2:
							board2[row+j][column] = 'D';
							break;
						case 3:
							board2[row+j][column] = 'B';
							break;
						case 4:
							board2[row+j][column] = 'A';
							break;
						default:
							cout<<"Something has gone horribly wrong!";
							getch();
							exit(0);				
					}
				}
			}
			
			clearScreen();
			printBoard(board2, false);
			
			if(isValidVertical && !checkVertical)
			{
				cout<<"Press 'V' to place ship vertically or 'C' to continue"<<endl;
				placement = getch();	
				
				while(placement!='V' && placement!='C' && placement!='v' && placement!='c')
				{
					cout<<"Invalid! Enter Again: ";
					placement = getche();
					cout<<endl;
				}			
			}	
			else
			{
				cout<<"Press Any Key to Continue . . ."<<endl;
				getch();
			}
			
			//Resetting Value to make sure next ship placement is horizontal by default
			if(checkVertical)
			{
				checkVertical = false;
			}
				
			if(placement=='V' || placement=='v')
			{
				checkVertical = true;
				for(int j=0;j<10;j++)
				{
					for(int k=0;k<10;k++)
					{
						switch(i)
						{
							case 0:
								if(board2[j][k] == 'P')
									board2[j][k] = '~';
								break;
							case 1:
								if(board2[j][k] == 'S')
									board2[j][k] = '~';
								break;
							case 2:
								if(board2[j][k] == 'D')
									board2[j][k] = '~';
								break;
							case 3:
								if(board2[j][k] == 'B')
									board2[j][k] = '~';
								break;
							case 4:
								if(board2[j][k] == 'A')
									board2[j][k] = '~';
								break;
							default:
								cout<<"Something has gone horribly wrong!";
								getch();
								exit(0);				
						}
					}
				}
				//Restarting Placement of Ship With Vertical Placement
				i--;
				continue;
			}	
		}
	}
	else
	{
		setRandomShips(board2);
		cout<<"Ships Have Been Randomly Placed"<<endl<<endl;
		cout<<"Press Any Key to Continue"<<endl;
		getch();
	}
	
	
	clearScreen();
	
	cout<<"    =========== Final Placement of Ships for Player 2 ==========="<<endl;
	printBoard(board2, false);
	cout<<"Press Any Key to Continue"<<endl;
	getch();
	clearScreen();
	
	bool gameOver = false;
	int count=0, hits=0;
	int shipsPlayer1 = 5;
	int shipsPlayer2 = 5;
	int score[2]={0};
	
	//These are required for the way I check sunk ships
	//I first scan the normal board to see if a ship has sunk by the count of its letters, if its equal to zero then it has sunk
	//Then I compare while printing with the original board, if the position of X matches that of a letter of a sunk ship in the original boat, its color is pink
	char board1Copy[10][10];
	char board2Copy[10][10];
	
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			board1Copy[i][j] = board1[i][j];	
			board2Copy[i][j] = board2[i][j];
		}
	}	
	
	while(!gameOver)
	{
		count++;
		clearScreen();
		
		if(count%2!=0)
		{
			cout<<"  ================================================== Player 1's Turn =================================================="<<endl;
			//Printing All Board
			advancedPrintBoard(board1, board2, board1Copy, board2Copy, false);
			cout<<"   Player 1's Score: "<<score[0]<<"\t\t\t\t\t\t\t\t\t\t"<<"Player 2's Score: "<<score[1]<<endl<<endl;
			
			cout<<"You have a total of "<<shipsPlayer1+1<<" hits!"<<endl;
			
			for(int i=0;i<shipsPlayer1+1;i++)
			{
				playerAttack(board2, score[0]);
			}
			
			shipsPlayer2 = countShips(board2);
			
			if(shipsPlayer2==0)
			{
				gameOver=true;
			}
			
			clearScreen();
			
			advancedPrintBoard(board1, board2, board1Copy, board2Copy, false);
			cout<<"   Player 1's Score: "<<score[0]<<"\t\t\t\t\t\t\t\t\t\t"<<"Player 2's Score: "<<score[1]<<endl<<endl;
			cout<<"Press Any Key to Continue . . ."<<endl;
			getch();
		}
		else
		{
			cout<<"  ================================================== Player 2's Turn =================================================="<<endl;
			//Printing All Board
			advancedPrintBoard(board2, board1, board2Copy, board1Copy, false);
			cout<<"   Player 1's Score: "<<score[0]<<"\t\t\t\t\t\t\t\t\t\t"<<"Player 2's Score: "<<score[1]<<endl<<endl;
			cout<<"You have a total of "<<shipsPlayer2+1<<" hits!"<<endl;
			
			for(int i=0;i<shipsPlayer2+1;i++)
			{
				playerAttack(board1, score[1]);
			}
			
			shipsPlayer1 = countShips(board1);
			
			if(shipsPlayer1==0)
			{
				gameOver=true;
			}
			
			clearScreen();
			
			advancedPrintBoard(board2, board1, board2Copy, board1Copy, false);
			cout<<"   Player 1's Score: "<<score[0]<<"\t\t\t\t\t\t\t\t\t\t"<<"Player 2's Score: "<<score[1]<<endl<<endl;
			cout<<"Press Any Key to Continue . . ."<<endl;
			getch();
		}
	}
		
		displayResult(score[0], score[1]);
		
		cout<<"\nPress Any Key to Continue . . .";
		getch();
		clearBoard(board1);
		clearBoard(board2);
		
		showLeaderboard(playerNames, score, 2);
		
		cout<<"\nPress Any Key to Continue . . .";
		getch();
		
		showGameMenu();
		
}

bool isSunken(char board[10][10], char originalBoard[10][10], int row, int column)
{
	//A B D S P
	bool sunken[5] = {true, true, true, true, true};
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(originalBoard[i][j]=='A' && board[i][j]=='A')
				sunken[0] = false;
			if(originalBoard[i][j]=='B' && board[i][j]=='B')
				sunken[1] = false;
			if(originalBoard[i][j]=='D' && board[i][j]=='D')
				sunken[2] = false;
			if(originalBoard[i][j]=='S' && board[i][j]=='S')
				sunken[3] = false;
			if(originalBoard[i][j]=='P' && board[i][j]=='P')
				sunken[4] = false;				
		}
	}
	
	if(originalBoard[row][column]=='A' && sunken[0])
		return true;
	else if(originalBoard[row][column]=='B' && sunken[1])	
		return true;
	else if(originalBoard[row][column]=='D' && sunken[2])	
		return true;
	else if(originalBoard[row][column]=='S' && sunken[3])	
		return true;
	else if(originalBoard[row][column]=='P' && sunken[4])	
		return true;			
		
	return false;	
}

void advancedPrintBoard(char board[10][10], char enemyBoard[10][10], char boardCopy[10][10], char enemyBoardCopy[10][10], bool Computer)
{
	if(!Computer)
		cout<<"       Enemy Board\t\t\t\t         Opponent\t\t\t\t    Your Board"<<endl;
	else
		cout<<"       Enemy Board\t\t\t\t         Opponent\t\t\t\t    Computer Board"<<endl;
	
	cout << "			  	 0     1     2     3     4     5     6     7     8     9  " << endl;

    // Top border
    cout << "    \t\t\t\t\b\b+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
 
 	//Row 0   
    cout<<"   ";
    
    for(int i=0;i<10;i++)
    {
    	cout<<i<<" ";
	}
	
	cout<<"   ";
	
	cout << "  0  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = enemyBoard[0][i];
        if (cell == 'X' && isSunken(enemyBoard, enemyBoardCopy, 0, i)) 
		{ 
			setColor(15, MAGENTA); 
			cout << "  X  "; 
			setColor(7,0); 
		}
		else if(cell == 'X')
		{
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0);
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  ~  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    
    cout<<"     ";
	
	for(int i=0;i<10;i++)
    {
    	cout<<i<<" ";
	}
	
	cout << endl;
	
	cout<<" "<<0<<" ";
    
    for(int i=0;i<10;i++)
    {
    	if(enemyBoard[0][i]=='X')
    		cout<<"X ";
    	else if(enemyBoard[0][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
    cout << "    \t\b\b+-----+-----+-----+-----+-----+-----+-----+-----+-----+----- ";
    
    cout<<"   "<<0<<" ";
	
	for(int i=0;i<10;i++)
    {
    	if(board[0][i]=='X')
    		cout<<"X ";
    	else if(board[0][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
    
    cout<<endl;
    
    //Row 1
    cout<<" "<<1<<" ";
    
    for(int i=0;i<10;i++)
    {
    	if(enemyBoard[1][i]=='X')
    		cout<<"X ";
    	else if(enemyBoard[1][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
    
	cout<<"\t  ";
	
	cout << "  1  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = enemyBoard[1][i];
        if (cell == 'X' && isSunken(enemyBoard, enemyBoardCopy, 1, i)) 
		{ 
			setColor(15, MAGENTA); 
			cout << "  X  "; 
			setColor(7,0); 
		}
		else if(cell == 'X')
		{
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0);
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  ~  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    
    cout<<"   "<<1<<" ";
	
	for(int i=0;i<10;i++)
    {
    	if(board[1][i]=='X')
    		cout<<"X ";
    	else if(board[1][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
	cout << endl;
	
	cout<<" "<<2<<" ";
    
    for(int i=0;i<10;i++)
    {
    	if(enemyBoard[2][i]=='X')
    		cout<<"X ";
    	else if(enemyBoard[2][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
    cout << "    \t\b\b+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----  ";
    
    cout<<"  "<<2<<" ";
    
    for(int i=0;i<10;i++)
    {
    	if(board[2][i]=='X')
    		cout<<"X ";
    	else if(board[2][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
    
    cout<<endl;

	//Row 2
	cout<<" "<<3<<" ";
    
    for(int i=0;i<10;i++)
    {
    	if(enemyBoard[3][i]=='X')
    		cout<<"X ";
    	else if(enemyBoard[3][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
	cout<<"   ";
	
	cout << "  2  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = enemyBoard[2][i];
        if (cell == 'X' && isSunken(enemyBoard, enemyBoardCopy, 2, i)) 
		{ 
			setColor(15, MAGENTA); 
			cout << "  X  "; 
			setColor(7,0); 
		}
		else if(cell == 'X')
		{
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0);
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  ~  "; 
			setColor(7,0);
		}
        cout << " ";
    }
	
	cout<<"   "<<3<<" ";
	
	for(int i=0;i<10;i++)
    {
    	if(board[3][i]=='X')
    		cout<<"X ";
    	else if(board[3][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
	cout << endl;
	
	cout<<" "<<4<<" ";
    
    for(int i=0;i<10;i++)
    {
    	if(enemyBoard[4][i]=='X')
    		cout<<"X ";
    	else if(enemyBoard[4][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
    cout << "    \t\b\b+-----+-----+-----+-----+-----+-----+-----+-----+-----+----- ";
    
    cout<<"   "<<4<<" ";
	
	for(int i=0;i<10;i++)
    {
    	if(board[4][i]=='X')
    		cout<<"X ";
    	else if(board[4][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
    
    cout<<endl;
    
    //Row 3
	cout<<" "<<5<<" ";
    
    for(int i=0;i<10;i++)
    {
    	if(enemyBoard[5][i]=='X')
    		cout<<"X ";
    	else if(enemyBoard[5][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
	cout<<"   ";
	
	cout << "  3  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = enemyBoard[3][i];
        if (cell == 'X' && isSunken(enemyBoard, enemyBoardCopy, 3, i)) 
		{ 
			setColor(15, MAGENTA); 
			cout << "  X  "; 
			setColor(7,0); 
		}
		else if(cell == 'X')
		{
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0);
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  ~  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    
    cout<<"   "<<5<<" ";
	
	for(int i=0;i<10;i++)
    {
    	if(board[5][i]=='X')
    		cout<<"X ";
    	else if(board[5][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
	cout << endl;
	
	cout<<" "<<6<<" ";
    
    for(int i=0;i<10;i++)
    {
    	if(enemyBoard[6][i]=='X')
    		cout<<"X ";
    	else if(enemyBoard[6][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
    cout << "    \t\b\b+-----+-----+-----+-----+-----+-----+-----+-----+-----+----- ";
    
    cout<<"   "<<6<<" ";
	
	for(int i=0;i<10;i++)
    {
    	if(board[6][i]=='X')
    		cout<<"X ";
    	else if(board[6][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
    
    cout<<endl;
    
    //Row 4
    cout<<" "<<7<<" ";
    
    for(int i=0;i<10;i++)
    {
    	if(enemyBoard[7][i]=='X')
    		cout<<"X ";
    	else if(enemyBoard[7][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
	cout<<"   ";
	
	cout << "  4  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = enemyBoard[4][i];
        if (cell == 'X' && isSunken(enemyBoard, enemyBoardCopy, 4, i)) 
		{ 
			setColor(15, MAGENTA); 
			cout << "  X  "; 
			setColor(7,0); 
		}
		else if(cell == 'X')
		{
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0);
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  ~  "; 
			setColor(7,0);
		}
        cout << " ";
    }
	
	cout<<"   "<<7<<" ";
	
	for(int i=0;i<10;i++)
    {
    	if(board[7][i]=='X')
    		cout<<"X ";
    	else if(board[7][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
	cout << endl;
	
	cout<<" "<<8<<" ";
    
    for(int i=0;i<10;i++)
    {
    	if(enemyBoard[8][i]=='X')
    		cout<<"X ";
    	else if(enemyBoard[8][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
    cout << "    \t\b\b+-----+-----+-----+-----+-----+-----+-----+-----+-----+----- ";
    
    cout<<"   "<<8<<" ";
	
	for(int i=0;i<10;i++)
    {
    	if(board[8][i]=='X')
    		cout<<"X ";
    	else if(board[8][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
    
    cout<<endl;
    
    //Row 5
	cout<<" "<<9<<" ";
	
	for(int i=0;i<10;i++)
    {
    	if(enemyBoard[9][i]=='X')
    		cout<<"X ";
    	else if(enemyBoard[9][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
	cout<<"   ";
	
	cout << "  5  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = enemyBoard[5][i];
        if (cell == 'X' && isSunken(enemyBoard, enemyBoardCopy, 5, i)) 
		{ 
			setColor(15, MAGENTA); 
			cout << "  X  "; 
			setColor(7,0); 
		}
		else if(cell == 'X')
		{
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0);
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  ~  "; 
			setColor(7,0);
		}
        cout << " ";
    }
    
    cout<<"   "<<9<<" ";
	
	for(int i=0;i<10;i++)
    {
    	if(board[9][i]=='X')
    		cout<<"X ";
    	else if(board[9][i]=='O')
    		cout<<"O ";
    	else
			cout<<". ";		
	}
	
	cout << endl;
    cout << "    \t\t\t\t\b\b+-----+-----+-----+-----+-----+-----+-----+-----+-----+----- " << endl;
    
    //Row 6
	
	cout<<"\t\t\t  ";
	
	cout << "  6  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = enemyBoard[6][i];
        if (cell == 'X' && isSunken(enemyBoard, enemyBoardCopy, 6, i)) 
		{ 
			setColor(15, MAGENTA); 
			cout << "  X  "; 
			setColor(7,0); 
		}
		else if(cell == 'X')
		{
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0);
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  ~  "; 
			setColor(7,0);
		}
        cout << " ";
    }
	
	cout << endl;
    cout << "    \t\t\t\t\b\b+-----+-----+-----+-----+-----+-----+-----+-----+-----+----- " << endl;
    
    //Row 7
	
	cout<<"\t\t\t  ";
	
	cout << "  7  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = enemyBoard[7][i];
        if (cell == 'X' && isSunken(enemyBoard, enemyBoardCopy, 7, i)) 
		{ 
			setColor(15, MAGENTA); 
			cout << "  X  "; 
			setColor(7,0); 
		}
		else if(cell == 'X')
		{
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0);
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  ~  "; 
			setColor(7,0);
		}
        cout << " ";
    }
	
	cout << endl;
    cout << "    \t\t\t\t\b\b+-----+-----+-----+-----+-----+-----+-----+-----+-----+----- " << endl;
    
    //Row 8
	
	cout<<"\t\t\t  ";
	
	cout << "  8  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = enemyBoard[8][i];
        if (cell == 'X' && isSunken(enemyBoard, enemyBoardCopy, 8, i)) 
		{ 
			setColor(15, MAGENTA); 
			cout << "  X  "; 
			setColor(7,0); 
		}
		else if(cell == 'X')
		{
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0);
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  ~  "; 
			setColor(7,0);
		}
        cout << " ";
    }
	
	cout << endl;
    cout << "    \t\t\t\t\b\b+-----+-----+-----+-----+-----+-----+-----+-----+-----+----- " << endl;
    
    //Row 9
	
	cout<<"\t\t\t  ";
	
	cout << "  9  "; 
    for (int i = 0; i < 10; i++)
    {
        char cell = enemyBoard[9][i];
        if (cell == 'X' && isSunken(enemyBoard, enemyBoardCopy, 9, i)) 
		{ 
			setColor(15, MAGENTA); 
			cout << "  X  "; 
			setColor(7,0); 
		}
		else if(cell == 'X')
		{
			setColor(15, 12); 
			cout << "  X  "; 
			setColor(7,0);
		}
        else if(cell == 'O')
        {
        	setColor(0, 8); 
			cout << "  O  "; 
			setColor(7,0);
		}
		else
		{
			setColor(7, 1);
			cout << "  ~  "; 
			setColor(7,0);
		}
        cout << " ";
    }
	
	cout << endl;
    cout << "    \t\t\t\t\b\b+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
	
	cout<<endl;

}

void setRandomShips(char board[10][10])
{
    int shipLengths[5] = {2,3,3,4,5};
    string shipNames[5] = {"Patrol Boat", "Submarine", "Destroyer", "Battleship", "Aircraft Carrier"};
    for(int l=0;l<5;l++)
    {
    	int len=shipLengths[l];
    	bool isValid=true;
    	
    	int  placement =rand()%2;
		int  row =rand()%10;	
		int  column =rand()%10;
		
		//for Horizontal:
		if(placement == 1)
		{
			if(column+(len-1) > 9)
				isValid = false;
		}
		else
		{
			if(row+(len-1)>9)
				isValid = false;
		}
		
		if(!isValid)
		{
			l--;
			continue;	
		}
		
		
		if(placement == 1)
		{
			for(int i=0;i<len;i++)
			{
				if(board[row][column+i] != '~')
				{
					isValid = false;
					break;
				}	
			}
		}
		//for Vertical:
		else
		{
			for(int i=0;i<len;i++)
			{
				if(board[row+i][column] != '~')
				{
					isValid = false;
					break;
				}	
	    	}  
	   	}
	   	
		if(!isValid)
		{
			l--;
			continue;
		}
	
		if(placement==1)
		{
			for(int i=0;i<len;i++)
				switch(l)
				{
					case 0:
						board[row][column+i] = 'P';		
						break;
					case 1:
						board[row][column+i] = 'S';
						break;
					case 2:
						board[row][column+i] = 'D';
						break;
					case 3:
						board[row][column+i] = 'B';
						break;
					case 4:
						board[row][column+i] = 'A';
						break;
					default:
						cout<<"Error"<<endl;
						getch();
						exit(0);					
				}
		}
		else
		{
	 		for(int i=0;i<len;i++)
				switch(l)
				{
					case 0:
						board[row+i][column] = 'P';		
						break;
					case 1:
						board[row+i][column] = 'S';
						break;
					case 2:
						board[row+i][column] = 'D';
						break;
					case 3:
						board[row+i][column] = 'B';
						break;
					case 4:
						board[row+i][column] = 'A';
						break;
					default:
						cout<<"Error"<<endl;
						getch();
						exit(0);					
				}
		}
    }	
}

void computerAttack(char playerBoard[10][10], int &computerScore)
{
	int row=0, column=0;
    
	while(true)    
	{
		row =rand()%10;	
		column =rand()%10;
		
	    if (playerBoard[row][column]=='X' || playerBoard[row][column]=='O')
		{
			//New row and new column
		   continue;	
		}
		
		break;
	}
	
	cout<<"Computer attacks "<<row<<" "<<column<<endl;
	
	if(playerBoard[row][column] != '~')
	{
		playerBoard[row][column] = 'X';
		updateScore(computerScore);
	}
	else
	{
		playerBoard[row][column] = 'O';
		computerScore-=1;
	}
}

void vsComputer(char playerBoard[10][10], char computerBoard[10][10])
{

	string playerName[1]={""};
	string shipNames[5] = {"Patrol Boat", "Submarine", "Destroyer", "Battleship", "Aircraft Carrier"};
	int shipLengths[5] = {2,3,3,4,5};
	char placementOption = '\0';
	char colorOption = '\0';
	
	cout<<"Enter Player Name: ";
	cin>>playerName[0];
       
	initilizeBoard(playerBoard);
	initilizeBoard(computerBoard);
	
	clearScreen();
	
	//For Player	
	cout<<"Enter Placement Option for Player (1-Manual, 2-Random): ";
	placementOption = getche();
	
	while(placementOption!='1' && placementOption!='2')
	{
		cout<<"Invalid! Enter Again: ";
		placementOption = getche();
		cout<<endl;	
	}	
	
	cout<<endl;
	
	cout<<"\nEnter Color of Battleships:"<<endl;
	cout<<"(1.Yellow    2.Green    3.Cyan    4.Magenta)"<<endl;
	colorOption = getche();
		
	while(colorOption<'1' || colorOption>'4')
	{   
		cout<<"Invalid! Enter Again: ";
		colorOption = getche();
		cout<<endl;	
	}
	
	setShipColor(colorOption);
	
	//For Player 
	if(placementOption=='1')
	{
		int row=0, column=0;
		char placement='H';
		bool checkVertical = false;
		char inputRow='\0', inputColumn='\0';
		
		for(int i=0;i<5;i++)
		{
			placement = 'H';
			
			if(!checkVertical)
				row=0, column=0;
				
			bool isValidVertical=true, isValidHorizontal=true;
			
			if(checkVertical)
			{
				isValidHorizontal = false;
			}
			
			clearScreen();
			cout<<"    ============== Placement of Ships for Player 1 =============="<<endl;
			printBoard(playerBoard, false);	
			
			if(!checkVertical)
			{
				cout<<"Enter co-ordinates for "<<shipNames[i]<<" (ship length "<<shipLengths[i]<<"): "<<endl;
				cout<<"Enter Starting Row (0-9): ";
					cin>>inputRow;
				cout<<"Enter Starting Column (0-9): ";
					cin>>inputColumn;
				
				//If row, column, or placement is out of range, it will ask again eles it will move on to secondary validation
				while((inputRow<'0' || inputRow>'9') || (inputColumn<'0' || inputColumn>'9'))
				{
					cout<<"Invalid! Enter Row-Column Again: ";
					cin>>inputRow>>inputColumn;	
				}	
			}
			
			column = inputColumn-48;
			row = inputRow-48;	
						
			if(column+shipLengths[i]-1>9)
			{
				isValidHorizontal = false;
			}
			
			if(row+shipLengths[i]-1 > 9)
			{
				isValidVertical = false;
			}
			
			
			//If its still valid, I check for other ships in there
			if(isValidHorizontal)
			{
				//All cells must be default '~'
				for(int j=0;j<shipLengths[i];j++)
				{
					if(playerBoard[row][column+j] != '~')
						isValidHorizontal = false;
				}
			}
			
			if(isValidVertical)
			{
				//Same but for vertical
				for(int j=0;j<shipLengths[i];j++)
				{
					if(playerBoard[row+j][column] != '~')
						isValidVertical = false;
				}	
			}
			
			if(!isValidHorizontal && !isValidVertical)
			{
				//If I find it to be invalid, I decrement i so loop will repeat that iteration and continue to skip the actual changing of board part
				cout<<"Invalid! Ship cannot be placed horizontally or vertically | Press Any Key to Place Again"<<endl;
				getch();
				i--;
				continue;
			}		
				
			if(isValidHorizontal)
			{
				for(int j=0;j<shipLengths[i];j++)
				{
					switch(i)
					{
						case 0:
							playerBoard[row][column+j] = 'P';
							break;
						case 1:
							playerBoard[row][column+j] = 'S';
							break;
						case 2:
							playerBoard[row][column+j] = 'D';
							break;
						case 3:
							playerBoard[row][column+j] = 'B';
							break;
						case 4:
							playerBoard[row][column+j] = 'A';
							break;
						default:
							cout<<"Something has gone horribly wrong!";
							getch();
							exit(0);				
					}
				}
			}
			else if(isValidVertical)
			{
				if(!checkVertical)
				{
					checkVertical=true;
				}
				for(int j=0;j<shipLengths[i];j++)
				{
					switch(i)
					{
						case 0:
							playerBoard[row+j][column] = 'P';
							break;
						case 1:
							playerBoard[row+j][column] = 'S';
							break;
						case 2:
							playerBoard[row+j][column] = 'D';
							break;
						case 3:
							playerBoard[row+j][column] = 'B';
							break;
						case 4:
							playerBoard[row+j][column] = 'A';
							break;
						default:
							cout<<"Something has gone horribly wrong!";
							getch();
							exit(0);				
					}
				}
			}
			
			clearScreen();
			printBoard(playerBoard, false);
			
			if(isValidVertical && !checkVertical)
			{
				cout<<"Press 'V' to place ship vertically or 'C' to continue"<<endl;
				placement = getch();	
				
				while(placement!='V' && placement!='C' && placement!='v' && placement!='c')
				{
					cout<<"Invalid! Enter Again: ";
					placement = getche();
					cout<<endl;
				}			
			}	
			else
			{
				cout<<"Press Any Key to Continue . . ."<<endl;
				getch();
			}
			
			//Resetting Value to make sure next ship placement is horizontal by default
			if(checkVertical)
			{
				checkVertical = false;
			}
				
			if(placement=='V' || placement=='v')
			{
				checkVertical = true;
				for(int j=0;j<10;j++)
				{
					for(int k=0;k<10;k++)
					{
						switch(i)
						{
							case 0:
								if(playerBoard[j][k] == 'P')
									playerBoard[j][k] = '~';
								break;
							case 1:
								if(playerBoard[j][k] == 'S')
									playerBoard[j][k] = '~';
								break;
							case 2:
								if(playerBoard[j][k] == 'D')
									playerBoard[j][k] = '~';
								break;
							case 3:
								if(playerBoard[j][k] == 'B')
									playerBoard[j][k] = '~';
								break;
							case 4:
								if(playerBoard[j][k] == 'A')
									playerBoard[j][k] = '~';
								break;
							default:
								cout<<"Something has gone horribly wrong!";
								getch();
								exit(0);				
						}
					}
				}
				//Restarting Placement of Ship With Vertical Placement
				i--;
				continue;
			}	
		}
	}
	else
	{
		setRandomShips(playerBoard);
		getch();
	}
		
	
	clearScreen();
	
	cout<<"    =========== Final Placement of Ships for Player ==========="<<endl;
	printBoard(playerBoard, false);
	cout<<"Press Any Key to Continue"<<endl;
	getch();
	clearScreen();
	
	//For Computer
	setRandomShips(computerBoard);	
    cout<<"Computer: ";
    clearScreen();
    
	cout<<"    ============== Computer is placing ships =============="<<endl;
	cout<<endl<<endl;
	cout<<"    ========== Computer Ships placed successfully!========="<<endl;
	cout<<endl<<endl;
	cout<<"Press Any Key to Continue"<<endl;
	getch();
	clearScreen();
	
	bool gameOver = false;
	int count=0, hits=0;
	int shipsPlayer = 5;
	int shipsComputer = 5;
	int score[2]={0};

	char playerBoardCopy[10][10];
	char computerBoardCopy[10][10];
	
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			playerBoardCopy[i][j] = playerBoard[i][j];	
			computerBoardCopy[i][j] = computerBoard[i][j];
		}
	}	
	
	while(!gameOver)
	{
		count++;
		clearScreen();
		
		if(count%2!=0)
		{
			cout<<"  ================================================== Player's Turn ==================================================="<<endl;
			//Printing All Board
			advancedPrintBoard(playerBoard, computerBoard, playerBoardCopy, computerBoardCopy, false);
			cout<<"   Player 's Score: "<<score[0]<<"\t\t\t\t\t\t\t\t\t\t"<<"Computer 's Score: "<<score[1]<<endl<<endl;
			
			cout<<"You have a total of "<<shipsPlayer+1<<" hits!"<<endl;
			
			for(int i=0;i<shipsPlayer+1;i++)
			{
				playerAttack(computerBoard, score[0]);
			}
			
			shipsComputer = countShips(computerBoard);
			
			if(shipsComputer==0)
			{
				gameOver=true;
			}
			
			clearScreen();
			
			advancedPrintBoard(playerBoard, computerBoard, playerBoardCopy, computerBoardCopy, false);
			cout<<"   Player 's Score: "<<score[0]<<"\t\t\t\t\t\t\t\t\t\t"<<"Computer's Score: "<<score[1]<<endl<<endl;
			cout<<"Press Any Key to Continue . . ."<<endl;
			getch();
		}
		else
		{
			cout<<"  ================================================== Computer's Turn =================================================="<<endl;
			//Printing All Board
			advancedPrintBoard(computerBoard, playerBoard, computerBoardCopy, playerBoardCopy, true);
			cout<<"   Player 's Score: "<<score[0]<<"\t\t\t\t\t\t\t\t\t\t"<<"Computer's Score: "<<score[1]<<endl<<endl;
			cout<<"You have a total of "<<shipsComputer+1<<" hits!"<<endl;
			
			for(int i=0;i<shipsComputer+1;i++)
			{
				computerAttack(playerBoard, score[1]);
			}
			
			shipsPlayer = countShips(playerBoard);
			
			if(shipsPlayer==0)
			{
				gameOver=true;
			}
			
			cout<<"\nPress Any Key to Continue"<<endl;
			getch();
			clearScreen();
			
			advancedPrintBoard(computerBoard, playerBoard, computerBoardCopy, playerBoardCopy, true);
			cout<<"   Player 's Score: "<<score[0]<<"\t\t\t\t\t\t\t\t\t\t"<<"Computer's Score: "<<score[1]<<endl<<endl;
			cout<<"Press Any Key to Continue . . ."<<endl;
			getch();
		}
	}
		
		displayResult(score[0], score[1]);
		
		cout<<"\nPress Any Key to Continue . . .";
		getch();
		
		clearBoard(playerBoard);
		clearBoard(computerBoard);
		
		showLeaderboard(playerName, score, 1);
		
		showGameMenu();
		
}


