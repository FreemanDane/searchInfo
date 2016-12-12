#include "document.h"

bool doc::operator==(const doc & d) const
{
	return (docID == d.docID);
}

bool doc::operator!=(const doc & d) const
{
	return (docID != d.docID);
}

bool doc::operator>(const doc & d) const
{
	return (occurTime > d.occurTime);
}

bool doc::operator<(const doc & d) const
{
	return (occurTime < d.occurTime);
}

bool doc::operator>=(const doc & d) const
{
	return (occurTime >= d.occurTime);
}

bool doc::operator<=(const doc & d) const
{
	return (occurTime <= d.occurTime);
}

ofstream & operator << (ofstream & fout, const doc & d)
{
	fout << '(' << d.docID << ',' << d.occurTime << ')';
	return fout;
}

bool docLink::operator == (const docLink & d) const
{
	return (word == d.word);
}

bool docLink::operator != (const docLink & d) const
{
	return (word != d.word);
}

bool docLink::operator > (const docLink & d) const
{
	return (word > d.word);
}

bool docLink::operator < (const docLink & d) const
{
	return (word < d.word);
}

void docLink::addDoc(int doc_num)
{
	doc d;
	d.docID = doc_num;
	d.occurTime = 1;
	int index = docs.search(d);
	if (index == -1)
	{
		docs.add(d);
	}
	else
	{
		docs[index].occurTime++;
		docs.sort();
	}
}

void docLink::delDoc(int num)
{
	doc d;
	d.docID = num;
	d.occurTime = 1;
	int index = docs.search(d);
	if (index == -1)
		return;
	docs.remove(d);
}

void docTree::addWord(const string & word)
{
	docLink d;
	d.word = word;
	t.insert(d);
}

bool docTree::hasWord(const string & word)
{
	docLink d;
	d.word = word;
	return (t.find(d));
}

docLink & docTree::findWord(const string & word)
{
	docLink d;
	d.word = word;
	if (hasWord(word))
		return (t.search(d));
	else
	{
		addWord(word);
		return findWord(word);
	}
}