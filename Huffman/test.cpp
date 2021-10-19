//#include<iostream>
//#include"TreeLib.h"
//using namespace std;
//void createBTree(BTree<int>& tree)
//{
//	int x, Left, Right;
//	cout << "\nNhap x: ";
//	cin >> x;
//	tree.Root = createTNode(x);
//	cout << "\nNhap node trai: ";
//	cin >> Left;
//	if (insertTNodeLeft(tree.Root, Left) == 0)
//	{
//		cout << "Node da ton tai!" << endl;
//	}
//	cout << "\nNhap node phai: ";
//	cin >> Right;
//	if (insertTNodeRight(tree.Root, Right) == 0)
//	{
//		cout << "Node da ton tai!" << endl;
//	}
//}
//void connectTree(BTree<int> a[], int n)
//{
//	int k = 0;
//	TNode<int>* p, * tmp;
//	for (int i = 1; i < n; i++)
//	{
//		p = a[i].Root;
//		a[k].Root = p;
//		/*if (insertTNodeLeft(p, L->info) == 0)
//		{
//			cout << "Node da ton tai!" << endl;
//		}
//		if (insertTNodeRight(p, R->info) == 0)
//		{
//			cout << "Node da ton tai!" << endl;
//		}*/
//	}
//}
//
//void main()
//{
//	//BTree<int> tree;
//	//BTree<int> a[100];
//	//int array[100];
//	//for (int i = 0; i < 3; i++)
//	//{
//	//	cout << "\nCay thu " << i ;
//	//	initBTree(a[i]);
//	//	createBTree(a[i]);
//	//}
//	///*createBTree(tree);*/
//	//for (int i = 0; i < 3; i++)
//	//{
//	//	cout << " " << a[i].Root->info;
//	//}
//	//connectTree(a,3);
//	char a[10] = { "dasdsffaf" };
//	char b[10] = { "a" };
//	cout << strcmp(a, b);
//}