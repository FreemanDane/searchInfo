#include "string.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

string::string(int l)
{
	size = l;
	data = (char *)malloc(size * sizeof(char));
	length = 0;
	data[0] = '\0';
}

string::string(char *s)
{
	int l = strlen(s);
	size = l + 100;
	data = (char *)malloc(size * sizeof(char));
	length = l;
	for (int i = 0; i < length; ++i)
	{
		data[i] = s[i];
	}
	data[length] = '\0';
}

string::string(const string & s)
{
	size = s.size;
	length = s.length;
	data = (char *)malloc(size * sizeof(char));
	for (int i = 0; i < length + 1; ++i)
		data[i] = s.data[i];
}

string::~string()
{
	free(data);
}

void string::expand()
{
	size *= 2;
	data = (char *)realloc(data, size * sizeof(char));
}

string & string::assign(const string & target)
{
	while (size <= target.length)
		expand();
	length = target.length;
	for (int i = 0; i < length; ++i)
	{
		data[i] = target.data[i];
	}
	data[length] = '\0';
	return (*this);
}

string & string::assign(char * target)
{
	int l = strlen(target);
	while (size <= l)
		expand();
	length = l;
	for (int i = 0; i < length; ++i)
		data[i] = target[i];
	data[length] = '\0';
	return (*this);
}

string & string::operator=(const string & target)
{
	assign(target);
	return (*this);
}

string & string::operator=(char *target)
{
	assign(target);
	return (*this);
}

bool string::operator==(const string & target) const
{
	if (strcmp(data, target.data) == 0)
		return true;
	else
		return false;
}

bool string::operator==(char *target) const
{
	if (strcmp(data, target) == 0)
		return true;
	else
		return false;
}

bool string::operator!=(char *target) const
{
	if (strcmp(data, target) == 0)
		return false;
	else
		return true;
}

bool string::operator!=(const string & target) const
{
	if (strcmp(data, target.data) == 0)
		return false;
	else
		return true;
}

string operator+(const string & s1, const string & s2)
{
	string result = s1;
	result.length = s1.length + s2.length;
	while (result.length >= result.size)
		result.expand();
	for (int i = 0; i < s2.length; ++i)
	{
		result.data[s1.length + i] = s2.data[i];
	}
	result.data[result.length] = '\0';
	return result;
}

string operator+(const string & s, const char c)
{
	string result = s;
	if (result.length >= result.size)
		result.expand();
	result.data[result.length] = c;
	result.length++;
	result.data[result.length] = '\0';
	return result;
}

void string::concat(const string & target)
{
	int l = length;
	length += target.length;
	while (length >= size)
		expand();
	for (int i = 0; i < target.length; ++i)
	{
		data[l + i] = target.data[i];
	}
	data[length] = '\0';
}

string string::substring(int startIndex, int endIndex)
{
	string result;
	result.length = endIndex - startIndex + 1;
	while (result.size <= result.length)
		result.expand();
	for (int i = 0; i < result.length; ++i)
	{
		result.data[i] = data[startIndex + i];
	}
	result.data[result.length] = '\0';
	return result;
}

char & string::operator[](int index)
{
	return data[index];
}

int string::indexOf(const string & childString)
{
	if (childString.length == 0)
		return -1;
	if (childString.length == 1)
	{
		for (int i = 0; i < length; ++i)
		{
			if (childString.data[0] == data[i])
				return i;
		}
		return -1;
	}
	int *next, *nextVal;
	next = new int[childString.length + 1];
	nextVal = new int[childString.length + 1];
	next[0] = -1;
	nextVal[0] = -1;
	int j = 0, k = -1;
	while (j < childString.length)
	{
		if (k == -1 || childString.data[k] == childString.data[j])
		{
			j++;
			k++;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
	for (int i = 1; i < childString.length; ++i)
	{
		if (childString.data[next[i]] == childString.data[i])
			nextVal[i] = nextVal[next[i]];
		else
			nextVal[i] = next[i];
	}
	j = -1;
	k = -1;
	while (j < length && k < childString.length)
	{
		if (k == -1 || data[j] == childString.data[k])
		{
			j++;
			k++;
		}
		else
			k = nextVal[k];
	}
	delete[] next;
	delete[] nextVal;
	if (k >= childString.length)
		return j - childString.length;
	else
		return -1;
}

int string::indexOf(char c, int start_index)
{
	for (int i = start_index; i < length; ++i)
	{
		if (data[i] == c)
			return i;
	}
	return -1;
}

std::istream & operator >> (std::istream & input, string & s)
{
	input >> s.data;
	s.length = strlen(s.data);
	return input;
}

std::ostream & operator << (std::ostream & output, string & s)
{
	output << s.data;
	return output;
}

void string::concat(char target)
{
	int l = length;
	length += 1;
	if (length >= size)
		expand();
	data[l] = target;
	data[length] = '\0';
}

bool string::operator>(char *target) const
{
	return (strcmp(data, target) == 1);
}
bool string::operator<(char *target) const
{
	return (strcmp(data, target) == -1);
}
bool string::operator>(const string & target) const
{
	return (strcmp(data, target.data) == 1);
}
bool string::operator<(const string & target) const
{
	return (strcmp(data, target.data) == -1);
}