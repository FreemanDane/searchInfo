#ifndef AVLTREE_H
#define AVLTREE_H
#include <fstream>

template<typename T>
class AVLtree
{
	struct node
	{
		T data;
		int depth;
		node *left;
		node *right;
	};
private:
	node *root;
private:
	int getDepth(node *t)
	{
		if (t == nullptr)
			return 0;
		else if (t->left == nullptr && t->right == nullptr)
			return 1;
		else if (t->left == nullptr)
			return t->right->depth + 1;
		else if (t->right == nullptr)
			return t->left->depth + 1;
		else
			return t->left->depth > t->right->depth ? t->left->depth + 1 : t->right->depth + 1;
	}
	int getBalance(node *t)
	{
		if (t == nullptr)
			return 0;
		int l, r;
		if (t->left == nullptr)
			l = 0;
		else
			l = t->left->depth;
		if (t->right == nullptr)
			r = 0;
		else
			r = t->right->depth;
		return l - r;
	}
	node* rotateRight(node *p)
	{
		if (p == nullptr || p->left == nullptr)
			return nullptr;
		node *q = p->left;
		node *temp = q->right;
		q->right = p;
		p->left = temp;
		p->depth = getDepth(p);
		q->depth = getDepth(q);
		return q;
	}
	node* rotateLeft(node *p)
	{
		if (p == nullptr || p->right == nullptr)
			return nullptr;
		node *q = p->right;
		node *temp = q->left;
		q->left = p;
		p->right = temp;
		p->depth = getDepth(p);
		q->depth = getDepth(q);
		return q;
	}
	node* insertNode(node *p, const T & data)
	{
		if (p == nullptr)
		{
			p = new node;
			p->data = data;
			p->left = nullptr;
			p->right = nullptr;
			p->depth = 1;
			return p;
		}
		else if (p->data < data)
		{
			p->right = insertNode(p->right, data);
			p->depth = getDepth(p);
			if (getBalance(p) < -1)
			{
				if (getBalance(p->right) < 0)
				{
					return rotateLeft(p);
				}
				else
				{
					p->right = rotateRight(p->right);
					return rotateLeft(p);
				}
			}
		}
		else if (p->data > data)
		{
			p->left = insertNode(p->left, data);
			p->depth = getDepth(p);
			if (getBalance(p) > 1)
			{
				if (getBalance(p->right) < 0)
				{
					p->left = rotateLeft(p->left);
					return rotateRight(p);
				}
				else
				{
					return rotateRight(p);
				}
			}
		}
		return p;
	}
	void deleteNode(node *p)
	{
		if (p == nullptr)
			return;
		deleteNode(p->left);
		deleteNode(p->right);
		delete p;
	}
public:
	AVLtree()
	{
		root = nullptr;
	}
	~AVLtree()
	{
		deleteNode(root);
	}
public:
	bool find(const T & target)
	{
		node *p = root;
		while (p != nullptr)
		{
			if (target < p->data)
				p = p->left;
			else if (target > p->data)
				p = p->right;
			else
				return true;
		}
		return false;
	}
	T & search(const T target)
	{
		node *p = root;
		while (p != nullptr)
		{
			if (target < p->data)
				p = p->left;
			else if (target > p->data)
				p = p->right;
			else
				break;
		}
		if (p == nullptr)
		{
			exit(5);
		}
		return p->data;
	}
	void insert(const T & data)
	{
		root = insertNode(root, data);
	}
	void addWords(char *fileName)
	{
		ifstream fin;
		fin.open(fileName);
		char content[100];
		while (fin.getline(content, 100))
		{
			string new_word(content);
			insert(new_word);
		}
	}
};

#endif
