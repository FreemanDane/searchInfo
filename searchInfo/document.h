#ifndef DOCUMENT_H
#define DOCOMENT_H
#include <iostream>
#include "list.h"
#include "string.h"
#include "AVLtree.h"
using std::ofstream;

struct doc
{
	int docID;
	int occurTime;
	bool operator != (const doc & d) const;
	bool operator == (const doc & d) const;
	bool operator > (const doc & d) const;
	bool operator < (const doc & d) const;
	bool operator >= (const doc & d) const;
	bool operator <= (const doc & d) const;
	friend ofstream & operator << (ofstream & fout, const doc & d);
};

struct docLink
{
	string word;
	list<doc> docs;
	bool operator < (const docLink & d) const;
	bool operator > (const docLink & d) const;
	bool operator == (const docLink & d) const;
	bool operator != (const docLink & d) const;
	void addDoc(int doc_num);
	void delDoc(int doc_num);
};

class docTree
{
	AVLtree<docLink> t;
public:
	docTree(){}
	~docTree(){}
	void addWord(const string & word);
	bool hasWord(const string & word);
	docLink & findWord(const string & word);
};

#endif
