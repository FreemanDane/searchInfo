#ifndef LIST_H
#define LIST_H
#include <iostream>

template <typename T>
struct Node
{
	T point;
	Node *prev;
	Node *next;
};

template <typename T>
class list
{
private:
	Node<T> *head;
	Node<T> *tail;
	int length;
public:
	list()
	{
		head = tail = nullptr;
		length = 0;
	}
	list(const list<T> & l)
	{
		head = tail = nullptr;
		length = 0;
		Node<T> *p = l.head;
		while (p != nullptr)
		{
			add(p->point);
			p = p->next;
		}
	}
	~list()
	{
		Node<T> *p = head, *q;
		while (p != nullptr)
		{
			q = p->next;
			delete p;
			p = q;
		}
	}
	T & operator[](int index)
	{
		Node<T> *p = head;
		for (int i = 0; i < index; ++i)
		{
			p = p->next;
		}
		return (p->point);
	}
	void add(T & content)
	{
		Node<T> *p = new Node<T>;
		p->next = nullptr;
		p->prev = nullptr;
		p->point = content;
		if (head == nullptr)
		{
			head = p;
			tail = p;
			length = 1;
		}
		else
		{
			tail->next = p;
			p->prev = tail;
			tail = p;
			length++;
		}
	}
	void sort()
	{
		Node<T> *p = head, *q;
		while (p != nullptr)
		{
			q = head;
			while (q != p)
			{
				if (q == head && q->point < p->point)
					break;
				if (q != head && q->prev->point >= p->point && q->point < p->point)
					break;
				q = q->next;
			}
			if (q != p)
			{
				if (p != tail)
					p->next->prev = p->prev;
				else
					tail = p->prev;
				if (p != head)
					p->prev->next = p->next;
				else
					head = p->next;
				if (q == head)
				{
					p->next = q;
					q->prev = p;
					head = p;
				}
				else
				{
					p->next = q;
					p->prev = q->prev;
					q->prev->next = p;
					q->prev = p;
				}
			}
			p = p->next;
		}
	}
	void remove(T & content)
	{
		Node<T> *p = head;
		while (p->point != content)
		{
			p = p->next;
			if (p == nullptr)
				return;
		}
		if (p != tail)
			p->next->prev = p->prev;
		else
			tail = p->prev;
		if (p != head)
			p->prev->next = p->next;
		else
			head = p->next;
		delete p;
		length--;
	}

	void remove(int index)
	{
		Node<T> *p = head;
		if (index < 0 || index >= length)
			return;
		for (int i = 0; i < index; ++i)
			p = p->next;
		if (p != tail)
			p->next->prev = p->prev;
		else
			tail = p->prev;
		if (p != head)
			p->prev->next = p->next;
		else
			head = p->next;
		delete p;
		length--;
	}

	int search(T & content)
	{
		if (head == nullptr)
			return -1;
		Node<T> *p = head;
		int i = 0;
		while (p->point != content)
		{
			p = p->next;
			i++;
			if (p == nullptr)
				return -1;
		}
		return i;
	}

	int size()
	{
		return length;
	}

	void swap(int index1, int index2)
	{
		int count = index1 > index2 ? index1 : index2;
		Node<T> *p = head, *q = head;
		for (int i = 0; i < count; ++i)
		{
			if (i < index1)
				p = p->next;
			if (i < index2)
				q = q->next;
		}
		T temp = p->point;
		p->point = q->point;
		q->point = p->point;
	}
};

#endif
