#ifndef STRING_H
#define STRING_H
#include <iostream>

class string
{
private:
	char *data;
	int length;
	int size;
	void expand();
public:
	string(int l = 100);
	string(char *s);
	string(const string & s);
	~string();
	string & assign(const string & target);
	string & assign(char *target);
	string & operator=(const string & target);
	string & operator=(char *target);
	bool operator==(const string & target) const;
	bool operator==(char *target) const;
	bool operator!=(const string & target) const;
	bool operator!=(char *target) const;
	bool operator>(char *target) const;
	bool operator<(char *target) const;
	bool operator>(const string & target) const;
	bool operator<(const string & target) const;
	friend string operator+(const string & s1, const string & s2);
	friend string operator+(const string & s, const char c);
	void concat(const string & target);
	void concat(char target);
	string substring(int startIndex, int endIndex);
	friend std::istream & operator >>(std::istream & input, string & s);
	friend std::ostream & operator <<(std::ostream & output, string & a);
	int indexOf(const string & childString);
	int indexOf(char c, int start_index = 0);
	char & operator [](int index);
	char* ctr()
	{
		return data;
	}
	int getLength()
	{
		return length;
	}
};

static bool isChineseSymbol(string & s)
{
	if (s == u8"，" || s == u8"。" || s == u8"《" || s == u8"》" || s == u8"（" || s == u8"）" || s == u8"【"
		|| s == u8"】" || s == u8"！" || s == u8"？" || s == u8"；" || s == u8"：" || s == u8"……" || s == u8"、" 
		|| s == u8"‘" || s == u8"’" || s == u8"“" || s == u8"”" || s == u8"「" || s == u8"」")
		return true;
	else
		return false;
}

#endif
