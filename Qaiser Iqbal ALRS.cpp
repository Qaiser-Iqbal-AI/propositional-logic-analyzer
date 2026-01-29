/*Arithmetic Logical Reasoning System */

#include<iostream>
#include<windows.h>
#include<iomanip>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<cmath>
#include<ctime>

using namespace std;

//All other constant values (int literals) are based around this value so it should not be changed in order to prevent a type of "stack overflow" 
const int MAX_TOKENS = 256;

//I have used snake naming case and camel naming case for all variable and function names
//Constants are capatalized

//32 Functions in total (counted)
void drawMenu();
void drawMainMenu();
void generateTruthTable();
string takeInput();
int uniqueVars(string, char[]);
bool isVar(char);
bool isOperator(char, int=0);
bool isBracket(char, int=0);
void NOT(int[], int[], int);
void AND(int[], int[], int[], int);
void OR(int[], int[], int[], int);
void IMPLIES(int[], int[], int[], int);
string subExpression(string);
void expressionSolver(string, int, int[], char[], int);
int tokenizer(string, char[]);
int infix_to_postfix(char[], int, char[]);
int precedence(char);
void initVarValues(int[5][32], int, int);
void copyArrayVal(int[], int[][5], int, int);
int getIndex(char[], char);
int arrSum(int[], int);
void saveResultTable(int[5][32], int[], int[], int, string, string);
void displaySavedResults();
void equivalenceCheck();
void argumentValidator();
void saveResultArgument(string[], string, char[], int, int, bool, int[], string);
void saveResultEquivalence(bool, string, string, int[], int[], int);
void displaySavedTables();
void displaySavedArguments();
void displaySavedEquivalences();
void reasoningChain();
bool checkRepetition(string, string[], int);
void BICONDITIONAL(int[], int[], int[], int);
string erase(string, int);
int length(string);

// Color codes
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;
// Function to set console text and background color
void setColor(int textColor, int bgColor) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

//I have treated '=' operator as bi-conditional
//No string functions used

int main()
{

	drawMenu();
	return 0;
		
}

//String alternative
string erase(string input, int index)
{
	string output="";
	for(int i=0;i<length(input);i++)
	{
		if(i!=index)
		{
			output += input[i];
		}
	}
	
	return output;
	
}

//String alternative
int length(string exp)
{
	int count=0;
	while(exp[count]!='\0')
	{
		count++;
	}
	return count;
}

bool checkRepetition(string check, string checkFrom[], int length)
{
	for(int i=0;i<length;i++)
	{
		if(checkFrom[i]==check)
			return true;	
	}
	return false;
}

void reasoningChain()
{
	
	system("cls");
	
	int premise_count;
	string conclusions[256];
	int conclusion_index = 0;
	//Arbritrary Value
	const int max_premise = 100;
	conclusions[conclusion_index] = "";
	
	cout<<"Reasoning Chain!"<<endl<<endl;
	
	cout<<"\tEnter Number of Premises ("<<max_premise<<" Maximum): ";
	cin>>premise_count;
	
	//cin.ignore because otherwise '\n' is passed to my input function causing trouble
	cin.ignore(1,'\n');
	
	while(premise_count<1 || premise_count>max_premise)
	{
		cout<<"\tInvalid! Enter Again: ";
		
		//So that when character is entered, program doesn't freak out
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(1,'\n');
		}
		
		cin>>premise_count;
		cin.ignore(1,'\n');
	}
	
	cout<<endl;
	
	//Maximum number of expressions
	string expressions[256];
	int expression_count=premise_count;
	int count[premise_count];
	char vars[premise_count][5];
	bool brackets=false, implies = true;
	int op_count, iterator=0;
	
	for(int i=0;i<premise_count;i++)
		for(int j=0;j<5;j++)
			vars[i][j] = '\0';
	
	cout<<"\tMaximum 2 Variables Per Premise | No Brackets | Maximum 1 Operator"<<endl;
	
	cout<<endl;
	
	for(int i=0;i<premise_count;i++)
	{	
		brackets = false;
		op_count=0;
		cout<<"\tEnter Premise "<<i+1<<": ";
		expressions[i] = takeInput();
		count[i] = uniqueVars(expressions[i], vars[i]);
		
		for(int j=0;j<length(expressions[i]);j++)
		{
			if(expressions[i][j]=='(' || expressions[i][j]==')')
				brackets = true;
			if(isOperator(expressions[i][j]))
				op_count++;	
		}
		
		if(count[i]>2 || brackets || op_count>1)
		{
			cout<<"Invalid! Maximum 2 Variables Per Premise | No Brackets | Maximum 1 Operator"<<endl;	
			cout<<"Press Any Key to Return to Main Menu . . ."<<endl;	
			getch();
			drawMainMenu();
		}	
	}
	
	bool finalDepth = false;
	
	//Each new conclusion becomes a new expression/premise for the next loop
	do{
		int no_of_implications = 0;
		int copy = expression_count;
		iterator++;
		
		for(int i=0;i<expression_count;i++)
		{
			if(expressions[i][1]=='>')
				no_of_implications++;
		}
		
		if(no_of_implications == 0)
			implies = false;
		
		char implicationMatrix[no_of_implications][2];
		
		for(int i=0;i<expression_count;i++)
		{
			if(expressions[i][1]=='>')
			{
				implicationMatrix[i][0] = expressions[i][0];
				implicationMatrix[i][1] = expressions[i][2];
				
			}
			
		}
		
		//Modus Ponens
		if(no_of_implications>0)
		for(int i=0;i<expression_count;i++)
		{
			if(length(expressions[i])==1)
			{
				for(int j=0;j<no_of_implications;j++)
				{
					if(implicationMatrix[j][0] == expressions[i][0])
					{
						conclusions[conclusion_index] += implicationMatrix[j][1];
						if(!checkRepetition(conclusions[conclusion_index], expressions, expression_count))
						{
							expressions[expression_count] = conclusions[conclusion_index];
							expression_count++;
						}
						conclusions[conclusion_index] += " -MP";
						conclusion_index++;
						
						if(checkRepetition(conclusions[conclusion_index-1], conclusions, conclusion_index-1))
							conclusion_index--;
						
						conclusions[conclusion_index] = "";
					}
				}
			}
		}
		
		//Modus Tollens
		if(no_of_implications>0)
		for(int i=0;i<expression_count;i++)
		{
			if(length(expressions[i])==2)
			{
				for(int j=0;j<no_of_implications;j++)
				{
					if(expressions[i][1] == implicationMatrix[j][1])
					{
						conclusions[conclusion_index] += '!';
						conclusions[conclusion_index] += implicationMatrix[j][0];
						if(!checkRepetition(conclusions[conclusion_index], expressions, expression_count))
						{
							expressions[expression_count] = conclusions[conclusion_index];
							expression_count++;
						}
						conclusions[conclusion_index] += " -MT";
						conclusion_index++;
						
						if(checkRepetition(conclusions[conclusion_index-1], conclusions, conclusion_index-1))
							conclusion_index--;
						
						conclusions[conclusion_index] = "";
					}
				}
			}
		}
		
		//Hypothetical Syllogism
		if(no_of_implications>0)
		for(int i=0;i<expression_count;i++)
		{
			if(length(expressions[i])==3 && expressions[i][1] == '>')
			{
				for(int j=0;j<no_of_implications;j++)
				{
					if(implicationMatrix[j][0] == expressions[i][2])
					{
						conclusions[conclusion_index] += expressions[i][0];
						conclusions[conclusion_index] += '>';
						conclusions[conclusion_index] += implicationMatrix[j][1];
						if(!checkRepetition(conclusions[conclusion_index], expressions, expression_count))
						{
							expressions[expression_count] = conclusions[conclusion_index];
							expression_count++;
						}
						conclusions[conclusion_index] += " -HS";
						conclusion_index++;
						
						if(checkRepetition(conclusions[conclusion_index-1], conclusions, conclusion_index-1))
							conclusion_index--;
						
						conclusions[conclusion_index] = "";
					}
				}
			}
		}
		
		//Disjunctive Syllogism
		for(int i=0;i<expression_count;i++)
		{
			if(length(expressions[i])==3 && expressions[i][1] == '|')
			{
				for(int j=0;j<expression_count;j++)
				{
					//Commutative so both sides
					if(length(expressions[j])==2 && expressions[j][1] == expressions[i][0])
					{
						conclusions[conclusion_index] += expressions[i][2];
						if(!checkRepetition(conclusions[conclusion_index], expressions, expression_count))
						{
							expressions[expression_count] = conclusions[conclusion_index];
							expression_count++;
						}
						conclusions[conclusion_index] += " -DS";
						conclusion_index++;
						
						if(checkRepetition(conclusions[conclusion_index-1], conclusions, conclusion_index-1))
							conclusion_index--;
						
						conclusions[conclusion_index] = "";
					}
					else if(length(expressions[j])==2 && expressions[j][1] == expressions[i][2])
					{
						conclusions[conclusion_index] += expressions[i][0];
						if(!checkRepetition(conclusions[conclusion_index], expressions, expression_count))
						{
							expressions[expression_count] = conclusions[conclusion_index];
							expression_count++;
						}
						conclusions[conclusion_index] += " -DS";
						conclusion_index++;
						
						if(checkRepetition(conclusions[conclusion_index-1], conclusions, conclusion_index-1))
							conclusion_index--;
						
						conclusions[conclusion_index] = "";
					}
				}
			}
		}
		
		//Simplification
		for(int i=0;i<expression_count;i++)
		{
			if(length(expressions[i])==3 && expressions[i][1] == '&')
			{
				conclusions[conclusion_index] += expressions[i][0];
				if(!checkRepetition(conclusions[conclusion_index], expressions, expression_count))
				{
					expressions[expression_count] = conclusions[conclusion_index];
					expression_count++;
				}
				conclusions[conclusion_index] += " -Simp";
				conclusion_index++;
				
				if(checkRepetition(conclusions[conclusion_index-1], conclusions, conclusion_index-1))
					conclusion_index--;
				
				conclusions[conclusion_index] = "";
				
				conclusions[conclusion_index] += expressions[i][2];
				if(!checkRepetition(conclusions[conclusion_index], expressions, expression_count))
				{
					expressions[expression_count] = conclusions[conclusion_index];
					expression_count++;
				}
				conclusions[conclusion_index] += " -Simp";
				conclusion_index++;
				
				if(checkRepetition(conclusions[conclusion_index-1], conclusions, conclusion_index-1))
					conclusion_index--;
				
				conclusions[conclusion_index] = "";
			}
		}
		
		if(copy==expression_count)
			finalDepth=true;
	
	}while(!finalDepth);
	
	cout<<"\t(MP - Modus Ponens, MT - Modus Tollens, HS - Hypothetical Syllogism, DS - Disjunctive Syllogism, Simp - Simplification)\n\tConclusions: "<<endl<<"\t";
	
	if(conclusion_index<=0)
	{
		cout<<"No new inferences to be made!"<<endl;
	}
		
	bool contradiction=false;
	char contra = '\0';
	
	for(int i=0;i<expression_count;i++)
	{
		if(length(expressions[i])==1)
		{
			for(int j=0;j<expression_count;j++)
			{
				if(length(expressions[j])==2 && expressions[j][1]==expressions[i][0])
				{
					contradiction = true;
					contra = expressions[i][0];	
				}
			}	
		}	
	}	
	
	if(!contradiction)	
	{
		for(int i=0;i<conclusion_index;i++)
		{
			if(i!=conclusion_index-1)
			{
				cout<<conclusions[i]<<", ";	
			}
			else
				cout<<conclusions[i];
		}
	}
	else
	{
		cout<<"Contradiction! "<<contra<<" cannot be true when !"<<contra<<" is true and vice-versa.";
	}
	
	cout<<endl<<endl;
	
	cout<<"Press Any Key to Return to Main Menu . . ."<<endl;
	getch();
	drawMainMenu();
	
} 

void argumentValidator()
{
	
	system("cls");
	
	
	int premise_count, maxCount;
	//Arbritrary values
	int max_premise = 100;
	bool isValid = true;
	
	cout<<"Argument Validator!"<<endl<<endl;
	
	cout<<"\tEnter Number of Premises ("<<max_premise<<" Maximum): ";
	cin>>premise_count;
	
	//cin.ignore because otherwise '\n' is passed to my input function causing trouble
	cin.ignore(1,'\n');
	
	while(premise_count<1 || premise_count>max_premise)
	{
		cout<<"\tInvalid! Enter Again: ";
		
		//So that when character is entered, program doesn't freak out
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(1,'\n');
		}
		
		cin>>premise_count;
		cin.ignore(1,'\n');
	}
	
	cout<<endl;
	
	string expressions[premise_count], conclusion;
	char maxVars[5] = {'\0','\0','\0','\0','\0'};		
			
	for(int i=0;i<premise_count;i++)
	{	
		cout<<"\tEnter Premise "<<i+1<<": ";
		expressions[i] = takeInput();	
	}
	
	cout<<endl;
	
	cout<<"\tEnter Conclusion: ";		
	conclusion = takeInput();
	
	string check="";
	for(int i=0;i<premise_count;i++)
		check += expressions[i];
	check += conclusion;
	
	maxCount = uniqueVars(check, maxVars);
	
	if(maxCount<=0)
	{
		cout<<"Invalid! 5 Maximum Variables"<<endl;	
		cout<<"Press Any Key to Return to Main Menu . . ."<<endl;	
		getch();
		drawMainMenu();
	}
		
	
	
	int no_of_rows = pow(2, maxCount);		
	int solveConclusion[no_of_rows];
	int solveExpression[premise_count][no_of_rows];
	int storage[5][32];
	
	initVarValues(storage, no_of_rows, maxCount);
	
	for(int i=0;i<premise_count;i++)
		expressionSolver(expressions[i], no_of_rows,solveExpression[i], maxVars, maxCount);
	
	expressionSolver(conclusion, no_of_rows,solveConclusion, maxVars, maxCount);
	
	bool premisesTrue = false;
	int falseRow=-1;
	
	//When all the premises are true, these loops check if the conclusion is also true, else argument is invalid
	for(int i=0;i<no_of_rows;i++)
	{
		premisesTrue = true;
		for(int j=0;j<premise_count;j++)
		{
			if(solveExpression[j][i]==0)
				premisesTrue = false;
		}
		
		if(premisesTrue)
		{
			if(solveConclusion[i] == 0)
			{
				isValid = false;
				falseRow = i;
				break;
			}
		}
		
	}
	
	int counterexample[maxCount];
	string output="";
	
	if(isValid)
	{
		cout<<"\tArgument is Valid!"<<endl;
	}
	else
	{

		cout<<"\tArgument is Invalid!"<<endl;
		cout<<"\tCounterexample: "<<endl;
		for(int i=0;i<maxCount;i++)
		{
			cout<<"\t"<<maxVars[i]<<" = "<<storage[i][falseRow]<<endl;
			counterexample[i] = storage[i][falseRow];	
		}
		
		cout<<endl;
		
		for(int i=0;i<maxCount;i++)
		{
			cout<<"\t"<<maxVars[i];
			output += "\t";
			output += maxVars[i];
		}
			
			
		for(int i=0;i<premise_count;i++)
		{
			cout<<"\t"<<expressions[i];
			output += "\t";
			output += expressions[i];
		}	
			
				
		cout<<"\t| "<<conclusion<<endl;
		output += "\t|";
		output += conclusion + "\n";
		
		for(int i=0;i<maxCount;i++)
		{
			cout<<"\t"<<counterexample[i];
			output += "\t";
			output += static_cast<char>(counterexample[i]+48);
		}
		
		for(int i=0;i<premise_count;i++)
		{
			cout<<"\t"<<solveExpression[i][falseRow];
			output += "\t";
			output += static_cast<char>(solveExpression[i][falseRow]+48);
		}
		
		cout<<"\t| "<<solveConclusion[falseRow]<<endl;
		output+="\t|";
		output+=static_cast<char>(solveConclusion[falseRow]+48);
	}
	
	cout<<endl;
	
	char select;
	cout<<"Do you want to save results (Y/N)?"<<endl;
	select = getch();
	
	while(select != 'Y' && select != 'y' && select != 'N' && select != 'n')
	{
		cout<<"Invalid! Enter Again: ";
		select = getche();
		cout<<endl;
	}
	
	if(select=='Y'||select=='y')
		saveResultArgument(expressions, conclusion, maxVars, maxCount, premise_count, isValid, counterexample, output);
	
	cout<<"Press Any Key to Return to Main Menu . . ."<<endl;
	getch();
	drawMainMenu();
	
}


void saveResultArgument(string expressions[], string conclusion, char vars[], int count, int premise_count, bool isValid, int counterexample[], string table)
{
	
	int break_length = 60;
	
	ofstream Results("ArgumentResults.txt", ios::app | ios::ate);
	
	if(Results.is_open())
	{
		cout<<"\nResults Saved!"<<endl;
		time_t timestamp;
		time(&timestamp);
		Results<<"\tTimestamp: "<<ctime(&timestamp);
		Results<<"\tVariables: ";
		for(int i=0;i<count;i++)
			Results<<vars[i]<<" ";
		Results<<endl;
		
		Results<<"\tPremises: ";
		for(int i=0;i<premise_count;i++)
			if(i!=premise_count-1)
				Results<<expressions[i]<<", ";
			else	
				Results<<expressions[i]<<". ";
				
		Results<<endl;
		
		Results<<"\tConclusion: "<<conclusion<<endl;
			
		if(isValid)
		{
			Results<<"\tArgument was Valid!"<<endl;
		}	
		else
		{
			Results<<"\tArgument was Invalid!"<<endl;
			Results<<"\tCounterexample: ";
			for(int i=0;i<count;i++)
			{
				if(i!=count-1)
					Results<<vars[i]<<" = "<<counterexample[i]<<", ";
				else	
					Results<<vars[i]<<" = "<<counterexample[i]<<".";
			}
			
			Results<<endl;
			
			Results<<table;
			
			Results<<endl;
			
		}
		
		for(int i=0;i<break_length;i++)
		{
			Results<<"- ";
		}
		
		Results<<endl;
		
		Results.close();
				
	}
	else
	{
		cout<<"\nError Storing Results! Could not open file"<<endl;
	}
	
}

void saveResultEquivalence(bool isEqual, string expression1, string expression2, int solveExpression1[], int solveExpression2[], int no_of_rows)
{
	int break_length = 60;
	ofstream Results("EquivalenceResults.txt", ios::app | ios::ate);
	
	if(Results.is_open())
	{
		cout<<"\nResults Saved!"<<endl;
		time_t timestamp;
		time(&timestamp);
		Results<<"\tTimestamp: "<<ctime(&timestamp);
		Results<<"\tExpressions: "<<expression1<<", "<<expression2<<endl;
		
		if(isEqual)
		{
			Results<<"\tThe Two Expressions are Equal!"<<endl;
		}
		else
		{
			Results<<"\tThe Two Expressions are Not Equal!"<<endl;
		}
		
		Results<<endl;
		
		//Displaying truth table values
		Results<<"\t"<<expression1<<"\t"<<expression2<<endl;	
			
		for(int i=0;i<no_of_rows;i++){
			Results<<setw(length(expression1)/2+8)<<solveExpression1[i]<<setw(length(expression2)/2+8)<<solveExpression2[i]<<endl;
		}	
		
		for(int i=0;i<break_length;i++)
		{
			Results<<"- ";
		}
		
		Results<<endl;
		Results.close();
	}
	else
	{
		cout<<"\nError Storing Results! Could not open file"<<endl;
	}
	
}

void equivalenceCheck()
{
	system("cls");
	
	
	char vars1[5] = {'\0','\0','\0','\0','\0'}, vars2[5] = {'\0','\0','\0','\0','\0'};
	int count1, count2, no_of_rows;
	string expression1, expression2;
	bool isEqual=true;
	
	cout<<"Equivalence Checker"<<endl;
	
	do
	{
		//Taking input
		cout<<"\tEnter First Expression: ";
		expression1 = takeInput();
		cout<<"\tEnter Second Expression: ";
		expression2 = takeInput();
		
		count1 = uniqueVars(expression1, vars1);
		count2 = uniqueVars(expression2, vars2);
		
		if(count1!=count2)
		{
			cout<<"Invalid! Expressions must have same number of Variables."<<endl;	
		}		
	}while(count1 != count2);
	
	no_of_rows = pow(2,count1);
	
	int solveExpression1[no_of_rows] = {0}, solveExpression2[no_of_rows] = {0};
	
	//Solving Expressions and generating there final truth table values
	expressionSolver(expression1, no_of_rows, solveExpression1, vars1, count1);
	expressionSolver(expression2, no_of_rows, solveExpression2, vars2, count2);
	
	//Checking if equal
	for(int i=0;i<no_of_rows;i++)
	{
		if(solveExpression1[i] != solveExpression2[i])
			isEqual = false;
	}
	
	if(isEqual)
	{
		cout<<"\tThe Two Expressions are Equal!"<<endl;
	}
	else
	{
		cout<<"\tThe Two Expressions are Not Equal!"<<endl;
	}
	
	cout<<endl;
	
	//Displaying truth table values
	cout<<"\t"<<expression1<<"\t"<<expression2<<endl;
	
	for(int i=0;i<35;i++)
		cout<<"- ";
	cout<<endl;	
		
	for(int i=0;i<no_of_rows;i++)
	{
		cout<<setw(length(expression1)/2+8)<<solveExpression1[i]<<setw(length(expression2)/2+8)<<solveExpression2[i]<<endl;
	}	
	
	cout<<endl;

	char select;
	cout<<"Do you want to save results (Y/N)?"<<endl;
	select = getch();
	
	while(select != 'Y' && select != 'y' && select != 'N' && select != 'n')
	{
		cout<<"Invalid! Enter Again: ";
		select = getche();
		cout<<endl;
	}
	
	if(select=='Y'||select=='y')
		saveResultEquivalence(isEqual, expression1, expression2, solveExpression1, solveExpression2, no_of_rows);
		
	cout<<endl;	
	
	cout<<"Press Any Key to Return to Menu . . ."<<endl;
	getch();
	drawMainMenu();
	
}

//All display functions just print from the file line by line

void displaySavedEquivalences()
{
	string temp;
	system("cls");
	
	ifstream Results("EquivalenceResults.txt");
	
	if(Results.is_open())
	{
		while(getline(Results,temp))
		{
			cout<<temp<<endl;	
		}
		Results.close();	
	}
	else
	{
		cout<<"\nError Viewing Results! Could not open file"<<endl;
	}	
}

void displaySavedTables()
{
	string temp;
	system("cls");
	
	ifstream Results("TableResults.txt");
	
	if(Results.is_open())
	{
		
		
		while(getline(Results,temp))
		{
		
			cout<<temp<<endl;
			
		}	
		Results.close();
	}
	else
	{
		cout<<"\nError Viewing Results! Could not open file"<<endl;
	}
}

void displaySavedArguments()
{
	string temp;
	system("cls");
	
	ifstream Results("ArgumentResults.txt");
	
	if(Results.is_open())
	{
		while(getline(Results,temp))
		{
			cout<<temp<<endl;	
		}
		Results.close();	
	}
	else
	{
		cout<<"\nError Viewing Results! Could not open file"<<endl;
	}
}

void displaySavedResults()
{
	system("cls");
	char select;
	cout<<"Choose:"<<endl;
	setColor(RED, BLACK);
	cout<<"\t1.";
	setColor(WHITE, BLACK);
	cout<<"Display Truth Tables\t\t";
	setColor(RED, BLACK);
	cout<<"2.";
	setColor(WHITE, BLACK);
	cout<<"Display Arguments\t\t";
	setColor(RED, BLACK);
	cout<<"3.";
	setColor(WHITE, BLACK);
	cout<<"Display Equivalences\n\t";
	setColor(RED, BLACK);
	cout<<"4.";
	setColor(WHITE, BLACK);
	cout<<"Return to Menu"<<endl;
	select = getch();
	
	while(select!='1' && select!='2' && select!='3' && select!='4')
	{
		cout<<"Invalid! Enter Again: ";
		select = getche();
		cout<<endl;
	}
	
	switch(select)
	{
		case '1':
			displaySavedTables();
			break;
		case '2':
			displaySavedArguments();
			break;
		case '3':
			displaySavedEquivalences();	
			break;
		case '4':
			drawMainMenu();
		default:
			cout<<"Error!"<<endl;		
	}
	
	cout<<"Press Any Button to Return to Menu . . ."<<endl;
	getch();
	drawMainMenu();
}

void saveResultTable(int storage[5][32], int solveExpression1[], int solveExpression2[], int no_of_rows, string input, string subInput)
{
	bool subExpression=false;
	char vars[5] = {'\0','\0','\0','\0','\0'};
	int count = uniqueVars(input, vars);
	int break_length = 50;

	for(int i=0;i<no_of_rows;i++)
	{
		if(solveExpression2[i] != 0)
			subExpression = true;
	}

	ofstream Results("TableResults.txt", ios::app | ios::ate);
	
	if(Results.is_open())
	{
		cout<<"\nResults Saved!"<<endl;
		time_t timestamp;
		time(&timestamp);
		//Exact same output as in generateTruthTable but I have replaced cout with ofstream object
		//I have also made some changes. For example it doesn't print line break between variables and truth table values
		Results<<"\tTimestamp: "<<ctime(&timestamp);
		Results<<"\tVariables: ";
		
		for(int i=0;i<count;i++)
		{
			Results<<vars[i]<<" ";
		}
		
		Results<<endl;
		
		Results<<"\tExpression: "<<input;
		
		Results<<endl<<endl;
			
		for(int i=0;i<count;i++)
		{
			Results<<"\t"<<vars[i];
		}
		
		if(subExpression)
		{	
			Results<<setw(length(subInput)+8)<<subInput<<setw(length(input)+8)<<input;
		}
		else
		{
			Results<<setw(length(input)+8)<<input;
		}
		
		Results<<endl;
		
		for(int i=0;i<no_of_rows;i++)
		{
			for(int j=0;j<count;j++)
			{
				Results<<"\t"<<storage[j][i];
			}
			
			if(subInput!="")
			{
				Results<<setw(length(subInput)/2+9)<<solveExpression1[i]<<setw(length(input)/2+9)<<solveExpression2[i];
			}
			else
			{
				Results<<setw(length(input)/2+9)<<solveExpression1[i];
			}
			
			Results<<endl;
		}
		
		for(int i=0;i<break_length;i++)
		{
			Results<<"- ";
		}
		Results<<endl;
		Results.close();
	}
	else
	{
		cout<<"\nError Storing Results! Could not open file"<<endl;
	}
}

int arrSum(int arr[], int no_of_rows)
{
	int sum=0;
	for(int i=0;i<no_of_rows;i++)
		sum+=arr[i];
	return sum;	
}

int getIndex(char vars[], char check)
{
	for(int i=0;i<5;i++)
		if(check==vars[i])
			return i;
	return -1;		
}

void copyArrayVal(int arr1[], int arr2[][5], int no_of_rows, int index)
{
	for(int i=0;i<no_of_rows;i++)
		arr1[i] = arr2[i][index];
}

void initVarValues(int storage[5][32], int no_of_rows, int count)
{
	int limit=0, iterator=0;
	bool flip = false;
	
	for(int i=0;i<count;i++)
	{
		flip = false;
		iterator = 0;
		limit = pow(2,count-(i+1));
		for(int j=0;j<no_of_rows;j++)
		{
		
			iterator++;		
			
			if(flip)
				storage[i][j] = 1;
			else
				storage[i][j] = 0;
			
			if(iterator>=limit && !flip)
			{
				flip = true;
				iterator = 0;	
			}
			else if(iterator>=limit && flip)
			{
				flip = false;
				iterator = 0;	
			}
					
		}
	}	
}

bool isVar(char check)
{
	if(check>='A' && check<='Z')
		return true;
	else
		return false;	
}

bool isOperator(char check, int i)
{
	if(i==0)
		if(check=='!' || check=='&' || check=='|' || check=='>' || check=='=')
			return true;
		else
			return false;	
	else if(i==1)
		if(check=='&' || check=='|' || check=='>' || check=='=')
			return true;
		else
			return false;
		
	return false;				
}

bool isBracket(char check, int i)
{
	
	if(i==0)
		if(check=='(' || check==')')
			return true;
		else
			return false;	
	else if(i==1)
		if(check==')')
			return true;
		else
			return false;
	else if(i==2)
		if(check=='(')
			return true;
		else
			return false;		
			
	return false;				
}

int precedence(char input)
{
	//Since NOT has higher priority then AND and so on
	switch(input)
	{
		case '!':
			return 5;
			break;
		case '&':
			return 4;
			break;
		case '|':
			return 3;
			break;
		case '>':
			return 2;
			break;	
		case '=':
			return 1;
			break;			
	}
	return 0;
}

int infix_to_postfix(char token[], int length, char postfix[])
{
	//Shunting Yard Algorithm
	//Also, I have no valdation within the tokens as I validate everything at the time of input
	//Each Operator will have a precedence
	//In operator stack, if current token operator has precedence greater than or equal to the one before it, first one will pop
	char op_stack[255];
	int postfix_index=0;
	//By default I will have no operators so there will be no "top"
	//Top is required since Shunting Yard Algorithm usually includes "popping" from stack
	int op_stack_top=-1;
	
	for(int i=0;i<length;i++)
	{
		//All operands are passed straight through to stack
		if(isVar(token[i]))
		{
			postfix[postfix_index] = token[i];
			postfix_index++;
		}
		//If it encounter left brace, it is added to stack as a marker
		else if(isBracket(token[i],2))
		{
			op_stack_top++;
			op_stack[op_stack_top] = token[i];
		}
		//When right brace is encountered, it pop operators until it reach left brace and we dont pop left brace
		else if(isBracket(token[i],1))
		{
			while(op_stack_top>=0 && op_stack[op_stack_top]!='(')
			{
				postfix[postfix_index] = op_stack[op_stack_top];
				postfix_index++;
				op_stack_top--;
			}
			//Inorder to remove the left bracket
			op_stack_top--;
		}
		//I have dealt with NOT separately as unary operators are dealt differently in Shunting Yard Algorithm
		//Here not only does NOT have highest precedence, but it also is right associative so it will always be pushed to stack
		else if(token[i] == '!'){
			op_stack_top++;
			op_stack[op_stack_top] = token[i];		
		}
		//First operator is always added to stack and incase of left brace always added as well
		else if((isOperator(token[i]) && op_stack_top==-1) || (isOperator(token[i]) && op_stack[op_stack_top]=='('))
		{
			op_stack_top++;
			op_stack[op_stack_top] = token[i];
		}
		//If precedence of operator is greater than that of top, it is added to stack
		else if(isOperator(token[i]) && isOperator(op_stack[op_stack_top]) && precedence(token[i])>precedence(op_stack[op_stack_top]))
		{
			op_stack_top++;
			op_stack[op_stack_top] = token[i];
		}
		//If it encounters operator it checks if it has precedence less than the top and if so it "pops" elements until it has higher precedence than all those operators before it
		else if(isOperator(token[i]) && isOperator(op_stack[op_stack_top]) && precedence(token[i])<=precedence(op_stack[op_stack_top]))
		{
			while(op_stack_top>=0 && isOperator(op_stack[op_stack_top]) && precedence(token[i])<=precedence(op_stack[op_stack_top]))
			{
				postfix[postfix_index] = op_stack[op_stack_top];
				postfix_index++;
				op_stack_top--;
			}
			op_stack_top++;
			op_stack[op_stack_top] = token[i];	
		}
	}
	
	//Dumping operators remaining in operator stack
	while(op_stack_top>=0 && isOperator(op_stack[op_stack_top]))
	{
		postfix[postfix_index] = op_stack[op_stack_top];
		postfix_index++;
		op_stack_top--;	
	}
	
	postfix[postfix_index] = '\0';
	
	return postfix_index;
}

string subExpression(string input)
{

	string subset="", copy_input;
	int left_count=0, right_count=0, temp_count=0;
	
	copy_input = input;
	
	//Counting brackets mainly for knowing if we have any bracket sub expression withing the main expression
	for(int i=0;i<length(copy_input);i++)
	{
		if(copy_input[i]=='(')
		{	
			left_count++;
			for(int j=i;j<length(copy_input);j++)
			{
				if(copy_input[j]==')')
				{
					copy_input[j] = '*';
					right_count++;
					break;
				}
			}
		}
	}
	
	//If there are brackets, sub expression will simply be the insides of the brackets
	if(left_count!=0 && left_count==right_count)
	{
		for(int i=0;i<length(input);i++)
		{
			if(input[i]=='(')
			{
				for(int j=i+1;j<length(input);j++)
				{
					if(input[j]==')' && temp_count!=left_count)
					{
						temp_count++;
						subset+=input[j];
					}
					else if(temp_count!=left_count)
						subset+=input[j];
					else	
						break;	
				}
				break;
			}	
		}
		
		//Removing last bracket
		subset = erase(subset, length(subset)-1);
		
		//Checking to see if it was an expression in the form ( XX ) X ( XX ) and if so then sending it off again recursively
		string copy_subset = subset;
		int cLeft = 0, cRight = 0;
		
		for(int i=0;i<length(copy_subset);i++)
		{
			if(copy_subset[i]=='(')
			{	
				cLeft++;
				for(int j=i;j<length(copy_subset);j++)
				{
					if(copy_subset[j]==')')
					{
						copy_subset[j] = '*';
						cRight++;
						break;
					}
				}
			}
		}
		
		if(cLeft!=cRight)
			return subExpression(subset);
	}
	else
	{
		//If there are no brackets, sub expression will be a simple pair of operand, operator, and operand
		for(int i=0;i<length(input)-2;i++)
		{
			//For all variable after first position, I will check if previous operator is not NOT
			if(i==0)
			{
				if(isVar(input[i]) && isOperator(input[i+1],1) && input[i+1] != '>' && input[i+1] != '=' && isVar(input[i+2]))
				{
					subset += input[i];
					subset += input[i+1];
					subset += input[i+2];
					break;
				}		
			}
			else
			{
				if((isOperator(input[i-1],1) || isBracket(input[i-1],2)) && isVar(input[i]) && isOperator(input[i+1],1) && isVar(input[i+2]))
				{
					subset += input[i];
					subset += input[i+1];
					subset += input[i+2];
					break;
				}
				else if(isVar(input[i]) && input[i-1]=='!')
				{
					subset += input[i-1];
					subset += input[i];
					break;
				}
			}
		}
	}
	
	if(left_count!=0)
		//If brackets cover all of the expression such as (P|Q|R), I send it back to the function (recursion) to get something else
		if(length(subset)!=length(input)-2)
			return subset;
		else
			return subExpression(subset);
	else 
		//If there are no brackets and sub expression is equal to expression then that means there will be no sub expression as in P&Q or P|Q
		if(length(subset)!=length(input))
			return subset;
		else
			return "";
}

void expressionSolver(string input, int no_of_rows, int arr[], char vars[], int no_vars)
{
	char tokenized[MAX_TOKENS];
	//Creating tokens as in Shunting yard algorithm
	int token_length = tokenizer(input, tokenized);
	//Postfix can be smaller than token length but token length is maximum because of brackets being removed
	//I have used +1 since I set last element to \0 so it is just to be safe
	//I set last element as null character because sometimes artifacts were appearing when outputting the postfix
	char postfix[token_length+1];
	//Given that 5 maximum variables and 32 rows maximum
	int storage[5][32];
	int var_index[2];
	char output_stack[256];
	int top = -1;
	
	//An array for storing all the temporary results
	int temp[512][no_of_rows];
	int temp_index = 0;
	int index = 0, index1, index2;
	
	
	//Initializing default values
	initVarValues(storage, no_of_rows, no_vars);
	
	//Initializing temp array to zero
	for(int i=0;i<512;i++)
		for(int j=0;j<no_of_rows;j++)
			temp[i][j] = 0;
	
	int length_postfix = infix_to_postfix(tokenized, token_length, postfix);
	
	//Evaluating postfix expression
   //Also all functions are commutative except implilcation
  //NOT is right associative and unary
	for(int i=0;i<length_postfix;i++)
	{
		if(isVar(postfix[i]))
		{
			top++;
			output_stack[top] = postfix[i];
		}
		else if(isOperator(postfix[i]))
		{
			if(postfix[i]=='!' && top>=0)
			{
				if(isVar(output_stack[top]))
				{
					var_index[0] = getIndex(vars, output_stack[top]);
					NOT(storage[var_index[0]], temp[temp_index], no_of_rows);
					//Setting stack top 100 plus the index of the temp array so that I can later retrieve it and the ASCII does not match any variables
					output_stack[top] = 100+temp_index;
					temp_index++;
				}
				else
				{
					//To use the results of temporary storage, I simply subtract 100 from the position where its stores
					index = output_stack[top]-100;
					NOT(temp[index], temp[temp_index], no_of_rows);
					output_stack[top] = 100+temp_index;
					temp_index++;
				}
			}
			else if(postfix[i]=='&' && top>0)
			{
				if(isVar(output_stack[top]) && isVar(output_stack[top-1]))
				{
					var_index[0] = getIndex(vars, output_stack[top]);
					var_index[1] = getIndex(vars, output_stack[top-1]);
					AND(storage[var_index[0]], storage[var_index[1]], temp[temp_index], no_of_rows);
					//Here I reduce top by one as two variables turn to one
					top--;
					output_stack[top] = 100+temp_index;
					temp_index++;
				}
				else
				{
					if(isVar(output_stack[top]))
					{
						var_index[0] = getIndex(vars, output_stack[top]);
						index = output_stack[top-1]-100;
						AND(storage[var_index[0]], temp[index], temp[temp_index], no_of_rows);
						//Here I reduce top by one as two variables turn to one
						top--;
						output_stack[top] = temp_index+100;
						temp_index++;
					}
					else if(isVar(output_stack[top-1]))
					{
						var_index[0] = getIndex(vars, output_stack[top-1]);
						index = output_stack[top]-100;
						AND(storage[var_index[0]], temp[index], temp[temp_index], no_of_rows);
						//Here I reduce top by one as two variables turn to one
						top--;
						output_stack[top] = temp_index+100;
						temp_index++;
					}
					else
					{
						index1 = output_stack[top]-100;
						index2 = output_stack[top-1]-100;
						AND(temp[index1], temp[index2], temp[temp_index], no_of_rows);
						//Here I reduce top by one as two variables turn to one
						top--;
						output_stack[top] = temp_index+100;
						temp_index++;
					}
				}
			}
			else if(postfix[i]=='|' && top>0)
			{
				if(isVar(output_stack[top]) && isVar(output_stack[top-1]))
				{
					var_index[0] = getIndex(vars, output_stack[top]);
					var_index[1] = getIndex(vars, output_stack[top-1]);
					OR(storage[var_index[0]], storage[var_index[1]], temp[temp_index], no_of_rows);
					//Here I reduce top by one as two variables turn to one
					top--;
					output_stack[top] = temp_index+100;
					temp_index++;
				}
				else
				{
					if(isVar(output_stack[top]))
					{
						var_index[0] = getIndex(vars, output_stack[top]);
						index = output_stack[top-1]-100;
						OR(storage[var_index[0]], temp[index], temp[temp_index], no_of_rows);
						//Here I reduce top by one as two variables turn to one
						top--;
						output_stack[top] = temp_index+100;
						temp_index++;
					}
					else if(isVar(output_stack[top-1]))
					{
						var_index[0] = getIndex(vars, output_stack[top-1]);
						index = output_stack[top]-100;
						OR(storage[var_index[0]], temp[index], temp[temp_index], no_of_rows);
						//Here I reduce top by one as two variables turn to one
						top--;
						output_stack[top] = temp_index+100;
						temp_index++;
					}
					else
					{
						index1 = output_stack[top]-100;
						index2 = output_stack[top-1]-100;
						OR(temp[index1], temp[index2], temp[temp_index], no_of_rows);
						//Here I reduce top by one as two variables turn to one
						top--;
						output_stack[top] = temp_index+100;
						temp_index++;
					}
				}
			}
			else if(postfix[i]=='>' && top>0)
			{
				if(isVar(output_stack[top]) && isVar(output_stack[top-1]))
				{
					var_index[0] = getIndex(vars, output_stack[top]);
					var_index[1] = getIndex(vars, output_stack[top-1]);
					//top-1 implies top
					IMPLIES(storage[var_index[1]], storage[var_index[0]], temp[temp_index], no_of_rows);
					//Here I reduce top by one as two variables turn to one
					top--;
					output_stack[top] = temp_index+100;
					temp_index++;
				}
				else 
				{
					if(isVar(output_stack[top]))
					{
						var_index[0] = getIndex(vars, output_stack[top]);
						index = output_stack[top-1]-100;
						
						IMPLIES(temp[index], storage[var_index[0]], temp[temp_index], no_of_rows);
						//Here I reduce top by one as two variables turn to one
						top--;
						output_stack[top] = temp_index+100;
						temp_index++;
					}
					else if(isVar(output_stack[top-1]))
					{
						var_index[0] = getIndex(vars, output_stack[top-1]);
						index = output_stack[top]-100;
						IMPLIES(storage[var_index[0]], temp[index], temp[temp_index], no_of_rows);
						//Here I reduce top by one as two variables turn to one
						top--;
						output_stack[top] = temp_index+100;
						temp_index++;
					}
					else
					{
						index1 = output_stack[top]-100;
						index2 = output_stack[top-1]-100;
						IMPLIES(temp[index2], temp[index1], temp[temp_index], no_of_rows);
						//Here I reduce top by one as two variables turn to one
						top--;
						output_stack[top] = temp_index+100;
						temp_index++;
					}
				}
			}
			else if(postfix[i]=='=' && top>0)
			{
				if(isVar(output_stack[top]) && isVar(output_stack[top-1]))
				{
					var_index[0] = getIndex(vars, output_stack[top]);
					var_index[1] = getIndex(vars, output_stack[top-1]);
					//top-1 implies top
					BICONDITIONAL(storage[var_index[1]], storage[var_index[0]], temp[temp_index], no_of_rows);
					//Here I reduce top by one as two variables turn to one
					top--;
					output_stack[top] = temp_index+100;
					temp_index++;
				}
				else 
				{
					if(isVar(output_stack[top]))
					{
						var_index[0] = getIndex(vars, output_stack[top]);
						index = output_stack[top-1]-100;
						
						BICONDITIONAL(temp[index], storage[var_index[0]], temp[temp_index], no_of_rows);
						//Here I reduce top by one as two variables turn to one
						top--;
						output_stack[top] = temp_index+100;
						temp_index++;
					}
					else if(isVar(output_stack[top-1]))
					{
						var_index[0] = getIndex(vars, output_stack[top-1]);
						index = output_stack[top]-100;
						BICONDITIONAL(storage[var_index[0]], temp[index], temp[temp_index], no_of_rows);
						//Here I reduce top by one as two variables turn to one
						top--;
						output_stack[top] = temp_index+100;
						temp_index++;
					}
					else
					{
						index1 = output_stack[top]-100;
						index2 = output_stack[top-1]-100;
						BICONDITIONAL(temp[index2], temp[index1], temp[temp_index], no_of_rows);
						//Here I reduce top by one as two variables turn to one
						top--;
						output_stack[top] = temp_index+100;
						temp_index++;
					}
				}
			}
		}
	}
	
	//In case variable is left over in stack
	if(isVar(output_stack[top]))
	{
    	index = getIndex(vars, output_stack[top]);
    	for(int i=0;i<no_of_rows;i++)
    	    arr[i] = storage[index][i];
    	return;
	}
	
	temp_index--;
	
	//Retrieving last temp value
	if(temp_index>=0)
		for(int i=0;i<no_of_rows;i++)
		{
			arr[i] = temp[temp_index][i];
		}
	
}

int tokenizer(string input, char arr[])
{
	//Length of expression is given to be <= MAX_TOKENS as I validate while taking input
	for(int i=0;i<length(input);i++)
	{
		arr[i] = input[i];
	}
	return length(input);
}

void generateTruthTable()
{
	
	string input="", subInput="";
	int count, no_of_rows;
	char vars[5]={'\0','\0','\0','\0','\0'};
	char subVars[5]={'\0','\0','\0','\0','\0'};
	
	system("cls");
	cout<<"Welcome to Truth Table Generation!"<<endl;
	cout<<"\tEnter Your Expression: ";
	
	input = takeInput();
	count = uniqueVars(input, vars);
	no_of_rows = pow(2,count);
	
	if(length(input)!=1)
		subInput = subExpression(input);
	
	int storage[5][32];
	int solveExpression1[no_of_rows] = {0};
	int solveExpression2[no_of_rows] = {0};
			
	//Initializing values of variables in storage
	initVarValues(storage, no_of_rows, count);
	
	//Printing Header
	setColor(RED, BLACK);
	for(int i=0;i<count;i++)
	{
		cout<<"\t"<<vars[i];
	}	
	
	//Checking if input was broken down into another expression and displaying output appropriately
	if(subInput!="")
	{	
		cout<<setw(length(subInput)+8)<<subInput<<setw(length(input)+8)<<input;
		
		//Expression and sub expression have same number of rows and variables since we are only calculating "part" of the expression
		expressionSolver(subInput, no_of_rows, solveExpression1, vars, count);
		expressionSolver(input, no_of_rows, solveExpression2, vars, count);
	}
	else
	{
		cout<<setw(length(input)+8)<<input;
		
		if(length(input)!=1)
			expressionSolver(input, no_of_rows, solveExpression1, vars, count);
		else
			for(int i=0;i<no_of_rows;i++)
				solveExpression1[i] = storage[0][i];
	}	
	
	setColor(WHITE, BLACK);
	
	cout<<endl;
	
	//Printing Line Break
	int length_of_break=1;
	
	for(int i=0;i<count;i++)
		length_of_break+=4;
	
	if(subInput!="")
	{
		length_of_break+=length(input);
		length_of_break+=6;
	}
	
	length_of_break+=length(input);
	length_of_break+=6;
	
	for(int i=0;i<length_of_break;i++)
	{
		cout<<"- ";
	}
	
	cout<<endl;
	
	//Outputting truth table values
	for(int i=0;i<no_of_rows;i++)
	{
		for(int j=0;j<count;j++)
		{
			cout<<"\t"<<storage[j][i];
		}
		
		if(subInput!="")
		{
			cout<<setw(length(subInput)/2+9)<<solveExpression1[i]<<setw(length(input)/2+9)<<solveExpression2[i];
		}
		else
		{
			cout<<setw(length(input)/2+9)<<solveExpression1[i];
		}
		
		cout<<endl;
	}
	
	cout<<endl;
	char select;
	cout<<"Do you want to save results (Y/N)?"<<endl;
	select = getch();
	
	while(select != 'Y' && select != 'y' && select != 'N' && select != 'n')
	{
		cout<<"Invalid! Enter Again: ";
		select = getche();
		cout<<endl;
	}
	
	if(select=='Y'||select=='y')
		saveResultTable(storage, solveExpression1, solveExpression2, no_of_rows, input, subInput);
	
	cout<<"Press Any Key to Return to Menu . . ."<<endl;
	getch();
	drawMainMenu();
	
}

//These operator functions are my favourite as the simplest but most elegant in form and implementation
void NOT(int arr1[], int output[], int no_of_rows)
{
	for(int i=0;i<no_of_rows;i++)
	{
		output[i] = 1-arr1[i]; 	
	} 
}

void AND(int arr1[], int arr2[], int output[], int no_of_rows)
{
	for(int i=0;i<no_of_rows;i++)
	{
		output[i] = arr1[i]*arr2[i]; 	
	}
}

void OR(int arr1[], int arr2[], int output[], int no_of_rows)
{
	for(int i=0;i<no_of_rows;i++)
	{
		output[i] = arr1[i] + arr2[i] - arr1[i]*arr2[i]; 	
	}
}

void IMPLIES(int arr1[], int arr2[], int output[], int no_of_rows)
{
	for(int i=0;i<no_of_rows;i++)
	{
		output[i] = 1-arr1[i]*(1-arr2[i]); 	
	}
}

void BICONDITIONAL(int arr1[], int arr2[], int output[], int no_of_rows)
{
	for(int i=0;i<no_of_rows;i++)
	{
		if(arr1[i]==arr2[i])
			output[i] = 1;
		else
			output[i] = 0; 	
	}
}


//Works pretty well considering I wrote it all in one go. Very reliable and solid function
int uniqueVars(string input, char arr[])
{
	int count = 0;
	bool isUnique;
	const int MAX_VARIABLES=5;
	
	for(int i=0;i<length(input);i++)
	{
		isUnique = true;
		if(isVar(input[i]))
		{
			for(int j=0;j<MAX_VARIABLES;j++)
			{
				if(input[i]==arr[j])
				{
					isUnique = false;
				}
			}
			if(isUnique && count < MAX_VARIABLES)
			{
				arr[count] = input[i];
				count++;
			}
			else if(isUnique && count == MAX_VARIABLES)
			{
				count = -1;			
			}
		}		
	}
	
	//Sorting just for consistency since if Q is encountered first I still want P to be in first place
	for(int i=0;i<count;i++)
	{
		for(int j=0;j<count-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				char temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	
	return count;
}


string takeInput()
{
	string current_expression="";
	string current_expression_original="";
	int countUniqueVars=0;
	bool isValid = true;
	bool trailingOperator=false, operandMismatch=false, emptyBrackets=false, bracketMismatch=false, varError=false, operatorMismatch=false, invalidCharacters=false, invalidLength=false;
	
	do
	{
		char vars[5]={'\0','\0','\0','\0','\0'};
		isValid = true;
		trailingOperator=false;
		operandMismatch=false;
		emptyBrackets=false;
		bracketMismatch=false; 
		varError=false; 
		operatorMismatch=false; 
		invalidCharacters=false; 
		invalidLength=false;
		
		getline(cin,current_expression);
		
		if(!current_expression.empty())
		{
			//Converting all Characters to capital
			for(int i=0;i<length(current_expression);i++)
			{
				if(current_expression[i]>='a' && current_expression[i]<='z')
					current_expression[i]-=32;
			}	
			
			//Removing Spaces
			for(int i=0;i<length(current_expression);i++)
			{
				if(current_expression[i]==' '){
					current_expression = erase(current_expression, i);
					//We need to check next one. Without i-- it skips element immediately after it
					i--;
				}
			}
			
			//In bracket verification, I remove right brackets to ensure right count. So I make a copy to check unique variables later
			current_expression_original = current_expression;
			countUniqueVars = uniqueVars(current_expression_original, vars);
			
			//For data validation
			int left_count=0, right_count=0;
			
			//Checking for max tokens 
			if(length(current_expression)>MAX_TOKENS)
			{
				invalidLength = true;
			}
			
			//Checking for Invalid Characters, All letter variables allowed
			for(int i=0;i<length(current_expression);i++)
			{
				if(!isVar(current_expression[i]) && !isOperator(current_expression[i]) && !isBracket(current_expression[i]))
					invalidCharacters = true;
			}
			
			for(int i=0;i<length(current_expression);i++)
			{
				if(current_expression[i]=='(')
				{	
					left_count++;
					for(int j=i;j<length(current_expression);j++)
					{
						if(current_expression[j]==')')
						{
							current_expression[j] = '*';
							right_count++;
							break;
						}
					}
				}
				//Here only checking for trailing operators
				else if(isOperator(current_expression[i]))
				{
					//NOT can come at the start but not end
					if(current_expression[i]=='!')
					{
						if(i+1>=length(current_expression))
							trailingOperator = true;
					}
					//All other operators can not come at the start or end
					else if(i-1<0 || i+1>=length(current_expression))	
						trailingOperator = true;			
				}
			}
			
			if(left_count != right_count)
				bracketMismatch = true;	
				
			//Checking for Two Side-by-Side Variables; Variable with Bracket; Operators Together
			for(int i=0;i<length(current_expression_original)-1;i++)
			{
				if(isVar(current_expression_original[i]) && isVar(current_expression_original[i+1]))
					operandMismatch = true;
				else if(isVar(current_expression_original[i]) && isBracket(current_expression_original[i+1],2))	
					operandMismatch = true;
				else if(isBracket(current_expression_original[i],1) && isVar(current_expression_original[i+1]))
					operandMismatch = true;
					
				if(isOperator(current_expression_original[i],1) && isOperator(current_expression_original[i+1],1))
					operatorMismatch = true;	
				else if(isOperator(current_expression_original[i]) && isBracket(current_expression_original[i+1],1))
					operatorMismatch = true;
				//Checking if current one is NOT and next is not NOT		
				else if((!isOperator(current_expression_original[i],1) && isOperator(current_expression_original[i])) && isOperator(current_expression_original[i+1],1))	
					operatorMismatch = true;
				else if(isBracket(current_expression_original[i],1) && isBracket(current_expression_original[i+1],2))
					operatorMismatch = true;
				//NOT between two operators 	
				else if(!trailingOperator && (!isOperator(current_expression_original[i],1) && isOperator(current_expression_original[i])) && isVar(current_expression_original[i-1]))
					operatorMismatch = true; 
				
					
				if(isBracket(current_expression_original[i],2) && isBracket(current_expression_original[i+1],1))
					emptyBrackets = true;	
			}	
				
			//Checking Variable Count Errors
			if(countUniqueVars<1 || countUniqueVars>5)
				varError = true;	
				
			if(bracketMismatch || invalidLength || trailingOperator || operandMismatch || varError || operatorMismatch || emptyBrackets || invalidCharacters)	
				isValid = false;	
		}
		else
		{
			isValid = false;
		}
		
		if(isValid)
			cout<<'\0'<<endl;
		else{
			cout<<"\t";
			
			if(invalidCharacters)
				cout<<"Invalid Variables or Operators"<<endl;
			else if(invalidLength)
				cout<<"Invalid Length"<<endl;	
			else if(bracketMismatch)
				cout<<"Invalid Brackets"<<endl;
			else if(emptyBrackets)
				cout<<"Invalid Empty Brackets"<<endl;	
			else if(operandMismatch)	
				cout<<"Invalid Operand Positions"<<endl;
			else if(operatorMismatch)
				cout<<"Invalid Operator Positions"<<endl;			
			else if(trailingOperator)	
				cout<<"Invalid Trailing Operators"<<endl;
			else if(varError)
				cout<<"Invalid Number of Variables"<<endl;
			else
				cout<<"Error!"<<endl;
				
			cout<<"\tEnter Again: ";		
		}
	}while(!isValid);
	return current_expression_original;
}

void drawMenu()
{
	
	char select;
	system("cls");
	setColor(GREEN, BLACK);
	cout<<"================================================"<<endl<<endl;
	setColor(RED, BLACK);
	cout<<" WELCOME TO ALRS(Arithmetic Logical Reasoning System)"<<endl;
	cout<<"\t  By Qaiser Iqbal"<<endl;
	setColor(GREEN, BLACK);
	cout<<"================================================"<<endl<<endl;
	setColor(WHITE, BLACK);
	
	system("pause");
	system("cls");
	
	cout<<"Choose:\n\t";
	setColor(RED, BLACK);
	cout<<"1.";
	setColor(WHITE, BLACK);
	cout<<"Main Menu\t";
	setColor(RED, BLACK);
	cout<<"2.";
	setColor(WHITE, BLACK);
	cout<<"Exit"<<endl;
	select = getch();
	
	while(select!='1' && select!='2')
	{
		cout<<"Invalid! Enter Again: ";
		select = getche();
		cout<<endl;
	}
	
	if(select == '1')
		drawMainMenu();
	else
	{
		system("cls");
		cout<<"Good Bye!"<<endl;
		system("pause");
		exit(0);
	}
			
}

void drawMainMenu()
{
	char select;
	
	system("cls");
	cout<<"Choose:\n\t";
	setColor(RED, BLACK);
	cout<<"1.";
	setColor(WHITE, BLACK);
	cout<<"Generate Truth Table for Expression\t";
	setColor(RED, BLACK);
	cout<<"2.";
	setColor(WHITE, BLACK);
	cout<<"Validate an Argument\t";
	setColor(RED, BLACK);
	cout<<"3.";
	setColor(WHITE, BLACK);
	cout<<"Check Equivalence of two Expressions\n\t";
	setColor(RED, BLACK);
	cout<<"4.";
	setColor(WHITE, BLACK);
	cout<<"Reasoning Chain\t                ";
	setColor(RED, BLACK);
	cout<<"5.";
	setColor(WHITE, BLACK);
	cout<<"View Saved Results\t";
	setColor(RED, BLACK);
	cout<<"6.";
	setColor(WHITE, BLACK);
	cout<<"Exit"<<endl;
	
	cout<<right;
	
	select = getch();
	
	while(select!='1' && select!='2' && select!='3' && select!='4' && select!='5' && select!='6')
	{
		cout<<"Invalid! Enter Again: ";
		select = getche();
		cout<<endl;
	}
	
	switch(select)
	{
		case '1':
			generateTruthTable();
			break;
		case '2':
			argumentValidator();
			break;
		case '3':
			equivalenceCheck();
			break;
		case '4':
			reasoningChain();
			break;
		case '5':
			displaySavedResults();
			break;
		case '6':
			drawMenu();
			break;
		default:
			cout<<"Error!"<<endl;					
	}
	
	//tick tick tick tick
}



