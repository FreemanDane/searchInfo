#ifndef TREE_H
#define TREE_H
#include "string.h"

struct tree
{
	string data;
	string label;
	string type;
	tree *next;
	tree *child;
};

#endif
