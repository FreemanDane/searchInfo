#include "dictionary.h"
#include <fstream>
using std::ifstream;

dictionary::dictionary() {}

dictionary::dictionary(string & fileName)
{
	ifstream fin;
	fin.open(fileName.ctr());
	char content[100];
	while (fin.getline(content, 100))
	{
		string new_word(content);
		int k = key(new_word);
		data[k].add(new_word);
	}
}

dictionary::dictionary(char *fileName)
{
	ifstream fin;
	fin.open(fileName);
	char content[100];
	while (fin.getline(content, 100))
	{
		string new_word(content);
		int k = key(new_word);
		data[k].add(new_word);
	}
}

dictionary::~dictionary(){}

int dictionary::key(string & word)
{
	int k1 = static_cast<int>(word[1] + 128) << 10;
	int k2 = static_cast<int>(word[4] + 128) << 3;
	int k3 = static_cast<int>(word[2] + 128) >> 4;
	int k = k1 + k2 + k3;
	return k;
}

void dictionary::addWords(string & fileName)
{
	ifstream fin;
	fin.open(fileName.ctr());
	char content[100];
	while (fin.getline(content, 100))
	{
		string new_word(content);
		int k = key(new_word);
		if (k > 65535)
		{
			std::cout << "键值越界\n";
			exit(2);
		}
		data[k].add(new_word);
	}
}

void dictionary::addWords(char *fileName)
{
	ifstream fin;
	fin.open(fileName);
	char content[100];
	while (fin.getline(content, 100))
	{
		string new_word(content);
		int k = key(new_word);
		data[k].add(new_word);
		if (k > 65535)
		{
			std::cout << "键值越界\n";
			exit(2);
		}
	}
}

bool dictionary::findWords(string & fileName)
{
	int k = key(fileName);
	if (k > 65535)
		return false;
	int result = data[k].search(fileName);
	if (result == -1)
		return false;
	else
		return true;
}