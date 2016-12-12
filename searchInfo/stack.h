#ifndef STACK_H
#define STACK_H

#include <cstdlib>

template<typename T>
class stack
{
private:
	int length;
	int size;
	T *data;
public:
	stack(int s = 200)
	{
		length = 0;
		size = s;
		data = (T *)malloc(size * sizeof(T));
	}
	~stack()
	{
		free(data);
	}
	void push(T n)
	{
		if (length == size)
		{
			data = (T *)realloc(data, size * 2 * sizeof(T));
			size *= 2;
		}
		data[length] = n;
		length++;
	}
	void pop()
	{
		length--;
	}
	T top()
	{
		return data[length - 1];
	}
	bool empty()
	{
		if (length <= 0)
			return true;
		else
			return false;
	}
};

#endif