//Library by Dat
#include<iostream>
using namespace std;
//Struct
template <class Data>
struct TNode
{
	Data info;
	TNode* Left;
	TNode* Right;
};
template <class T>
struct BTree
{
	TNode<T>* Root;
};
//Functions
template <class T>
void initBTree(BTree<T>& bt)
{
	bt.Root = NULL;
}
template <class T>
TNode<T>* createTNode(T x)
{
	TNode<T>* p = new TNode<T>;
	if (p == NULL)
	{
		return NULL;
	}
	p->info = x;
	p->Left = NULL;
	p->Right = NULL;
	return p;
}
template <class T>
int insertTNodeLeft(TNode<T>* q, T x)
{
	if (q == NULL)
	{
		return 0;
	}
	if (q->Left != NULL)
	{
		return 0;
	}
	TNode<T>* p = createTNode(x);
	q->Left = p;
	return 1;
}
template <class T>
int insertTNodeRight(TNode<T>* q, T x)
{
	if (q == NULL)
	{
		return 0;
	}
	if (q->Right != NULL)
	{
		return 0;
	}
	TNode<T>* p = createTNode(x);
	q->Right = p;
	return 1;
}
template <class T>
int deleteTree(TNode<T>*& root)
{
	if (!root)
	{
		return 0;
	}
	deleteTree(root->Left);
	deleteTree(root->Right);
	delete root;
	return 1;
}


