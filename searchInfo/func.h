#ifndef FUNC_H
#define FUNC_H
#include "tree.h"
#include "list.h"
#include "stack.h"
#include "string.h"
#include "dictionary.h"
#include "document.h"
#include "AVLtree.h"
#include <fstream>
#include <io.h>
using std::ifstream;
using std::ofstream;

tree* extractInfo(char *file);//todo: extract information from a file and set a tree with it
void outputTree(tree *root, ofstream & fout);//todo: output a node of tree and all its descendant
void deleteTree(tree *root);//todo: delete a tree
void lineDivideWords(string & content, list<string> & word_list, dictionary & dic);//todo: divide words in a line
void lineDivideWords(string & content, list<string> & word_list, AVLtree<string> & dic);
void articalDivideWords(char *fileName, dictionary & dic, list<string> & word_list);//todo: divide words of an artical
void articalDivideWords(char *fileName, AVLtree<string> & dic, list<string> & word_list);
void outputDividedWords(list<string> & word_list, char *fileName);//todo: receive a word list and output all words in it to a file
void divideWords();//todo: divide words
void addChild(tree *father, tree *child);//todo: add a child to a node
string getLabel(string & s, int start = 0);//todo: get a label from the index of start
string getType(string & s, int start = 0);//todo: get the type of label from the index of start
bool hasLabel(string & s);//todo: judge whether a line  has label
bool meaningfulLabel(string & s);//todo: judge whether a label need to set a new node
void outputTitle(tree *root, ofstream & fout);//todo: find titles from a tree and output them
void outputAuthor(tree *root, ofstream & fout);//todo: find authors from a tree and output it
void outputContent(tree *root, ofstream & fout);//todo: find contents from a tree and output it
void informationOut(tree *root, ofstream & fout, string out_file);//todo: receive a tree and output it's useful information
void getInfomation();//todo: get information of a html file and output it
void getFileName(string path, list <string> &);//todo: get all files in a path
void searchData();
void findAritical(string & a, dictionary & dic, ofstream & fout, docTree & doc_list);
#endif