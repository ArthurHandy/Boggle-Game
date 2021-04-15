#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct Node 
{
	struct Node* letters[26] = { nullptr };
	bool isWord;
};

class Dictionary
{
public:
	Dictionary();
	Dictionary(string file);
	void addWord(string word);
	bool isWord(string word);
	bool isPrefix(string word);
	void printWords(string prefix);
	int wordCount();

private:
	Node* root;
	int numWords;
};
