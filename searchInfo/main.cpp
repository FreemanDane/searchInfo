#include "func.h"
#include <iostream>
#include <ctime>
using std::cin;
using std::cout;

int main(int argc, char *args[])
{
	clock_t c = clock();
	system("mkdir content");
	getInfomation();
	divideWords();
	searchData();
	cout << "total cost " << clock() - c << " ms" << std::endl;
	return 0;
}