#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Dictionary::Dictionary() // Constructor that establishes an empty Node
{
	root = new Node();
	numWords = 0;
}

// Constructor that takes in a string file and read the file line by 
// line and uses the addWord method to add words to the dictionary
Dictionary::Dictionary(string file)
{
	ifstream InFile("C:\\PathToDictionary\\dictionary.txt");

	root = new Node();
	numWords = 0;

	while (!InFile.eof()) // End of File
	{
		string line;
		string word;
		int start;
		start = 0;
		int end;
		end = line.find(" ");
		getline(InFile, line);
		while (end != string::npos)
		{
			addWord(word);
			start = end + 1;
			end = line.find(" ", start);
			word = line.substr(start, end - start);
		}
		word = line.substr(start, end);
		addWord(word);
	}
}


// Adds word to a tree by reading each word character by character.
// Doing so will create a path for the word if it does not exist.
void Dictionary::addWord(string word)
{
	Node* currNode = root;
	for (int i = 0; i < word.length(); ++i) // Traverse
	{

		if (currNode->letters[(int)word[i] - (int)'a'] == NULL)
		{
			currNode->letters[(int)word[i] - (int)'a'] = new Node();
			(currNode->letters[(int)word[i] - (int)'a'])->isWord = false;
		}
		currNode = currNode->letters[(int)word[i] - (int)'a'];
	}
	currNode->isWord = true; // Set the flag at the currNode to true 
	++numWords;
}

bool Dictionary::isWord(string word)
{
	Node* currNode = root;
	for (int i = 0; i < word.length(); ++i) // Traverse
	{
		if (currNode->letters[(int)word[i] - (int)'a'] == NULL) // If NULL, returns false
			return false;
		currNode = currNode->letters[(int)word[i] - (int)'a'];
	}
	return (currNode != NULL && currNode->isWord == true);
}

bool Dictionary::isPrefix(string word)
{
	Node* currNode = root;
	for (int i = 0; i < word.length(); ++i) // Traverse
	{
		if (currNode->letters[(int)word[i] - (int)'a'] == NULL) // If NULL, returns false
			return false;
		currNode = currNode->letters[(int)word[i] - (int)'a'];
	}
	return true;
}

void Dictionary::printWords(string prefix)
{
	Node* currNode = root;
	for (int i = 0; i < prefix.length(); ++i) // Traverse
	{
		if (currNode->letters[(int)prefix[i] - (int)'a'] == NULL)
			return;
		currNode = currNode->letters[(int)prefix[i] - (int)'a'];
	}
}

int Dictionary::wordCount()
{
	return numWords;		// Returns the total number of words in the dictionary
}
