#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "list.h"
#include "string.h"

//a hash table

class dictionary
{
private:
	list<string> data[65536];
	int key(string & word);
public:
	dictionary();
	dictionary(string & fileName);
	dictionary(char* fileName);
	~dictionary();
	void addWords(string & fileName);
	void addWords(char* fileName);
	bool findWords(string & fileName);
};

#endif