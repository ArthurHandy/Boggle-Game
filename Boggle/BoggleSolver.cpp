#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Precondition and Postcondition are just your assumptions
// Function: Definition
// Pre: What has to be true for this function to work
// Post: What happends

bool verbose = false;
int numofwords = 0;
void SolveBoard(string board[4][4], int steps[][4], Dictionary& dict, Dictionary& wordsFound, bool printBoard);
void SearchForWord(int row, int col, string board[][4], int steps[][4], Dictionary dict, Dictionary wordsFound, int numofsteps, string currProgress, bool printBoard, ofstream& output);
void PrintingBoard(string board[][4], int steps[][4], ofstream& output);

int main()
{
	string board[4][4];
	int steps[4][4];

	cout << "----------" << "\n";
	cout << "| BOGGLE |" << "\n";
	cout << "----------" << "\n" << endl;

	Dictionary dict("Dictionary.txt");
	cout << dict.wordCount() << " words loaded." << "\n" << endl;

	cout << "Enter board" << endl;
	cout << "-----------" << endl;


	string userInput;

	// Row 0: _ _ _ _
	// Row 1: _ _ _ _
	// Row 2: _ _ _ _
	// Row 3: _ _ _ _
	for (int r = 0; r < 4; r++)
	{
		cout << "Row " << r << ": ";
		cin >> userInput;
		for (int c = 0; c < userInput.length(); c++)
		{
			board[r][c] = userInput[c];
		}
	}

	cout << "\n";

	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			steps[r][c] = 0;
		}
	}

	Dictionary wordsFound;
	SolveBoard(board, steps, dict, wordsFound, true);

	return 0;
}

// Function: This is the wrapper function for SearchForWord
// Post: user input of y or n
// Pre: Show the board
void SolveBoard(string board[4][4], int steps[][4], Dictionary& dict, Dictionary& wordsFound, bool printBoard)
{
	string currProgress;
	string output_file = "output.txt";

	ofstream output(output_file);

	char userInput;
	cout << "Show the board? (y/n): ";
	cin >> userInput;

	if (userInput == 'y')
	{
		printBoard = true;
	}
	else if (userInput == 'n')
	{
		printBoard = false;
	}
	else if (userInput == 'Y')
	{
		cout << "Error! Please enter lower case y!" << endl;
		exit(EXIT_FAILURE);
	}
	else if (userInput == 'N')
	{
		cout << "Error! Please enter lower case n!" << endl;
		exit(EXIT_FAILURE);
	}
	else if (userInput == 'yes')
	{
		cout << "Error! Please enter lower case y!" << endl;
		exit(EXIT_FAILURE);
	}
	else if (userInput == 'no')
	{
		cout << "Error! Please enter lower case n!" << endl;
		exit(EXIT_FAILURE);
	}
	else if (userInput == 'Yes')
	{
		cout << "Error! Please enter lower case y!" << endl;
		exit(EXIT_FAILURE);
	}
	else if (userInput == 'No')
	{
		cout << "Error! Please enter lower case n!" << endl;
		exit(EXIT_FAILURE);
	}

	int numofsteps = 0;

	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			SearchForWord(r, c, board, steps, dict, wordsFound, numofsteps, currProgress, printBoard, output);
		}
	}

	cout << "Test runs are printed on the outputfile: " << output_file << endl;
}

// Function: Heavy lifting of the recursion
// Pre: Depends on user input for y and n
// Post: If no, this will only print the number and word. If yes, It will print out words, number of words, and the 4 by 4 grid
void SearchForWord(int row, int col, string board[][4], int steps[][4], Dictionary dict, Dictionary wordsFound, int numofsteps, string currProgress, bool printBoard, ofstream& output)
{
	if (row < 0 || col < 0 || row >= 4 || col >= 4) //Bounds checking
		return;

	if (steps[row][col] != 0)
		return;

	if (!dict.isPrefix(currProgress))
		return;

	if (dict.isWord(currProgress))
	{
		if (!wordsFound.isWord(currProgress))
		{
			if (!printBoard) // If option is no, this will only print the number and word -> 1       word
																						 //  2       words
			{
				wordsFound.addWord(currProgress);
				cout << ++numofwords << "          " << currProgress << endl;
				output << numofwords << "          " << currProgress << endl;
			}
			else            // Else option yes, this will print out the word, number of words, and the 4 by 4 grid
			{
				wordsFound.addWord(currProgress);
				cout << "Word: " << currProgress << endl;
				output << "Word: " << currProgress << endl;
				cout << "Number of Words: " << ++numofwords << endl;
				output << "Number of Words: " << numofwords << endl;
				PrintingBoard(board, steps, output);
			}
		}
	}

	currProgress = currProgress + board[row][col];
	steps[row][col] = ++numofsteps;

	// Eight Recursive Calls
	SearchForWord(row - 1, col, board, steps, dict, wordsFound, numofsteps, currProgress, printBoard, output); // Up
	SearchForWord(row + 1, col, board, steps, dict, wordsFound, numofsteps, currProgress, printBoard, output); // Down
	SearchForWord(row, col - 1, board, steps, dict, wordsFound, numofsteps, currProgress, printBoard, output); // Left
	SearchForWord(row, col + 1, board, steps, dict, wordsFound, numofsteps, currProgress, printBoard, output); // Right
	SearchForWord(row - 1, col - 1, board, steps, dict, wordsFound, numofsteps, currProgress, printBoard, output);
	SearchForWord(row + 1, col + 1, board, steps, dict, wordsFound, numofsteps, currProgress, printBoard, output);
	SearchForWord(row + 1, col - 1, board, steps, dict, wordsFound, numofsteps, currProgress, printBoard, output);
	SearchForWord(row - 1, col + 1, board, steps, dict, wordsFound, numofsteps, currProgress, printBoard, output);


	steps[row][col] = 0; // The breadcrumb from maze example
}

// Function: This will print out the 4 by 4 grid
// Pre: User input of y or n
// Post: Prints the steps on 4 by 4 grid
void PrintingBoard(string board[][4], int steps[][4], ofstream& output)
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (steps[r][c] != 0)
			{
				cout << " \'" << board[r][c] << "\' ";
				output << " \'" << board[r][c] << "\' ";
			}
			else
			{
				cout << "  " << board[r][c] << "  ";
				output << "  " << board[r][c] << "  ";
			}
		}
		cout << endl;
		output << endl;
	}
	cout << "\n";
	output << "\n";


	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			cout << "  " << steps[r][c] << "  ";
			output << "  " << steps[r][c] << "  ";
		}
		cout << endl;
		output << endl;
	}

	cout << "---------" << endl;
	output << "--------" << endl;
}
