//**************************************************************************************************//
//									  --=Bai tap nang cao=--										//
//										Tac gia: Vu Ngo Dat											//
//										 MSSV: 2001202045											//
//								      De Bai: Ma Hoa Huffman										//
//									Chay tren: Visual Studio 2019									//
//**************************************************************************************************//
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include"TreeLib.h"
using namespace std;
//==================================================================================================//
//Struct and Constant
struct Data
{
	char kiTu[27];
	int trongSo;
};
struct HuffmanCode
{
	char kiTu[2];
	char maHuffman[10];
};
//==================================================================================================//
//Prototype
void interchangeSort_Ascending(char* str);
void thucHienChuongTrinh();
void menu();
void showStr(char* str);
void showTable(Data* table, int n);
void showHuffmanCoding(HuffmanCode* table, int n);
void createLookupTable(Data* table, int& n, char* str);
void traverseNLR(TNode<Data>* root);
void searchNodeLeaf(TNode<Data>* root, char* x, char* code);
void interchangeSort_Ascending_Data(Data* table, int n);
void interchangeSort_Ascending_Tree(BTree<Data> a[], int n);
void interchangeSort_Ascending_HuffmanCode(HuffmanCode* table, int n);
void interchangeSort_Ascending_LookupTable(Data* table, int n);
void createNodeArray(BTree<Data> a[], Data* table, int& sla, int& n);
void updateLookupTable(BTree<Data> a[], Data* table, int& n);
void createHuffmanTree(BTree<Data> a[], BTree<Data>& tree, Data* table, int& n);
void createHuffmanCodingTable(BTree<Data> tree, HuffmanCode* huffmanTable, char* str);
char* checkCode_Encode(HuffmanCode* a, char* input, int n);
void Encoding(HuffmanCode* huffmanTable, char* input, char* output, int n);
char* checkCode_Decode(HuffmanCode* a, char* input, int n, int& vt, int& dem);
void Decoding(HuffmanCode* huffmanTable, char* input, char* output, int n);
void Driver(BTree<Data>& tree, Data* table, int& n, char* str);
void BGcolor(int code);
int SumOfBits(Data* lookup, HuffmanCode* huffman, int length);
int Saving(char* str, Data* lookup, HuffmanCode* huffman, int length);
float CompressRate(char* str, Data* lookup, HuffmanCode* huffman, int length);

//==================================================================================================//
//Main
void main()
{
	thucHienChuongTrinh();
}
//==================================================================================================//
//Functions
void thucHienChuongTrinh()
{
	int n = 0, chon;
	BTree<Data> tree;
	initBTree(tree);
	Data table[100];
	HuffmanCode code_table[48];
	char str[100] = ""; //= { "ABABBCBBDEEEABABBAEEDDCCABBBCDEEDCBCCCCDBBBCAAA" };
	char tmp[100] = "";
	char empty[100] = "";
	char output[1000] = "";
	//----------------------
	SetConsoleTitle(L"Huffman Program");
	do
	{
		system("cls");
		system("color 0F");
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "F: ";
		showStr(str);
		menu();
		cout << "Chon chuc nang: ";
		cin >> chon;	
		cout << "----------------------------------------------------------------------------" << endl;
		switch (chon)
		{
		case 1:	
			//----------------------//
			//Reset data
			n = 0;
			strcpy(str, empty);
			strcpy(tmp, empty);
			strcpy(output, empty);
			//----------------------//		
			do
			{
				cout << "Nhap Chuoi (Do dai chuoi > 1): ";
				cin >> str;
			} while (strlen(str) <= 1);			
			break;
		case 2:	
			//----------------------//
			//Reset data
			n = 0;
			strcpy(output, empty);
			//----------------------//
			strcpy(output, empty);
			if (strcmp(str, "") == 0)
			{
				system("color 47");
				cout << "Vui long nhap chuoi truoc!" << endl;
				break;
			}
			strcpy(tmp, str);
			Driver(tree, table, n, tmp);
			createLookupTable(table, n, tmp);
			createHuffmanCodingTable(tree, code_table, tmp);
			cout << endl;
			Encoding(code_table, str, output, n);
			cout << "\nF-Encode: ";
			showStr(output);
			cout << "\nTiet kiem: " << Saving(str, table, code_table, --n) << " Bits";
			cout << "\nTy le nen: " << CompressRate(str, table, code_table, n) << " %";
			break;
		case 3:
			if (strcmp(output, "") == 0)
			{
				system("color 47");
				cout << "Vui long chon B2 truoc!" << endl;
				break;
			}
			char a[100];
			cout << "\nF-Encode: ";
			showStr(output);
			createHuffmanCodingTable(tree, code_table, tmp);
			cout << endl;
			Decoding(code_table, output, a, n);
			cout << "\nF-Decode: ";
			showStr(a);
			break;
		default:
			cout << "EXIT!" << endl;
			break;
		}
		cout << endl;
		system("pause");
	} while (chon >= 1 && chon <= 3);
	
	

	
}
void menu()
{
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "=======Chuc nang=======" << endl;
	cout << "0. Thoat Chuong Trinh" << endl;
	cout << "1. Nhap Chuoi" << endl;
	cout << "2. Ma Hoa Chuoi" << endl;
	cout << "3. Giai Ma Chuoi" << endl;
}
//-----------------
//Show
void showStr(char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		cout << str[i];
	}
	cout << endl;
}
void showTable(Data* table, int n)
{
	printf("\n--------------------");
	cout << "\nKy Tu\tTan Suat" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << " " << table[i].kiTu << "\t  " << table[i].trongSo << endl;
	}
}
void showHuffmanCoding(HuffmanCode* table, int n)
{
	printf("\n--------------------");
	printf("\n%5s%15s","Ky Tu","Ma Huffman");
	for (int i = 0; i < n; i++)
	{
		printf("\n%5s%15s", table[i].kiTu, table[i].maHuffman);
	}
	printf("\n--------------------");
}
//-----------------
//Sorting
void interchangeSort_Ascending(char* str)
{
	for (int i = 0; i < strlen(str) - 1; i++)
	{
		for (int j = i + 1; j < strlen(str); j++)
		{
			if (str[i] > str[j])
			{
				swap(str[i], str[j]);
			}
		}
	}
}
void interchangeSort_Ascending_Data(Data* table, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (table[i].trongSo < table[j].trongSo)
			{
				swap(table[i], table[j]);
			}
		}
	}
}
void interchangeSort_Ascending_Tree(BTree<Data> a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i].Root->info.trongSo < a[j].Root->info.trongSo)
			{
				swap(a[i], a[j]);
			}
		}
	}
}
void interchangeSort_Ascending_HuffmanCode(HuffmanCode* table, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (strcmp(table[i].kiTu, table[j].kiTu) == 1)
			{
				swap(table[i], table[j]);
			}
		}
	}
}
void interchangeSort_Ascending_LookupTable(Data* table, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (strcmp(table[i].kiTu, table[j].kiTu) == 1)
			{
				swap(table[i], table[j]);
			}
		}
	}
}
//-----------------
//Modules
void createLookupTable(Data* table, int& n, char* str)
{
	int k = 0;
	interchangeSort_Ascending(str);
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] != str[i + 1])
		{
			table[k].kiTu[0] = str[i];	
			table[k].kiTu[1] = '\0';
			table[k].trongSo = 0;
			n++; k++;
		}
	}
	k = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == table[k].kiTu[0])
		{
			table[k].trongSo++;
		}
		else
		{
			k++; i--;
		}
	}
	interchangeSort_Ascending_Data(table, n);

}
template<class T>
void coppyArray(T* source, T* dest, int length)
{
	for (int i = 0; i < length; i++)
	{
		dest[i] = source[i];
	}
}
void traverseNLR(TNode<Data>* root)
{
	if (root == NULL)
	{
		return;
	}
	cout << " " << root->info.kiTu;
	traverseNLR(root->Left);
	traverseNLR(root->Right);
}
void searchNodeLeaf(TNode<Data>* root, char* x, char* code)//Ham tim Node la duoc chi dinh va gan ma Huffman vao bang ma
{
	if (root == NULL)
	{
		return;
	}
	if (strcmp(root->info.kiTu, x) == 0)
	{
		return;
	}
	if (root->Left != NULL && strstr(root->Left->info.kiTu, x))
	{
		strcat(code, "0");
		searchNodeLeaf(root->Left, x, code);	
	}
	else
	{
		if (root->Right != NULL)
		{
			strcat(code, "1");
			searchNodeLeaf(root->Right, x, code);
		}	
	}
}

void updateLookupTable(BTree<Data> a[], Data* table, int& n)//Ham cap nhat bang Tra va noi cay
{
	//Cap nhat bang Tra
	strcat(table[n - 2].kiTu, table[n - 1].kiTu);
	table[n-2].trongSo = table[n - 2].trongSo + table[n - 1].trongSo;
	//Noi cay
	TNode<Data>* L = a[n - 1].Root; 
	TNode<Data>* R = a[n - 2].Root; 
	a[n - 2].Root = createTNode(table[n - 2]);
	a[n - 2].Root->Left = L;
	a[n - 2].Root->Right = R;
	n--;
}
void createHuffmanTree(BTree<Data> a[], BTree<Data>& tree, Data* table, int& n)//Tao cay Huffman
{
	interchangeSort_Ascending_Data(table, n);
	interchangeSort_Ascending_Tree(a, n);
	updateLookupTable(a, table, n);
}
void createNodeArray(BTree<Data> a[], Data* table,int &sla, int& n)//Khoi tao cac cay con co 1 goc
{
	BTree<Data> tree;
	for (int i = 0; i < n; i++)
	{
		tree.Root = createTNode(table[i]);
		a[i] = tree;
	}
}
void createHuffmanCodingTable(BTree<Data> tree, HuffmanCode* huffmanTable, char* str)//Khoi tao bang Ma Huffman
{
	Data table[48];
	int n = 0;
	createLookupTable(table, n, str);//Tao bang tra
	//Neu bang tra chi co duy nhat 1 phan tu (truong hop chuoi chi co duy nhat 1 ki tu hoac toan bo ki tu trung lap voi nhau)
	//Thi gan cho cay duy nhat do Ma Huffman = 0
	//Nguoc lai thi thuc hien viec tra cay
	if (n == 1)
	{
		strcpy(huffmanTable[0].kiTu, table[0].kiTu);
		strcpy(huffmanTable[0].maHuffman, "0");
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			char code[10] = "";
			strcpy(huffmanTable[i].kiTu, table[i].kiTu);
			searchNodeLeaf(tree.Root, huffmanTable[i].kiTu, code);
			strcpy(huffmanTable[i].maHuffman, code);
		}
		interchangeSort_Ascending_HuffmanCode(huffmanTable, n);//Sap xep bang Ma Huffman tang dan theo ki tu
	}	
	showHuffmanCoding(huffmanTable, n);//Xuat bang Ma Huffman
}
char* checkCode_Encode(HuffmanCode* a, char* input, int n)//Duyet bang Ma Huffman de nen
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(a[i].kiTu, input) == 0)
		{
			return a[i].maHuffman;
		}
	}
}
void Encoding(HuffmanCode* huffmanTable, char* input, char* output, int n)//Ma hoa ki tu dau vao
{
	for (int i = 0; i < strlen(input); i++)
	{
		char tmp[2] = { input[i] };
		strcat(output, checkCode_Encode(huffmanTable, tmp, n));
	}
}
char* checkCode_Decode(HuffmanCode* a, char* input, int n, int& vt, int& dem)//Duyet bang Ma Huffman giai ma
{
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		dem = strlen(a[i].maHuffman);
		char tmp[10] = "";
		for (int j = vt; j < vt + dem; j++)
		{
			tmp[k++] = input[j];
		}
		if (strcmp(a[i].maHuffman, tmp) == 0)
		{
			vt += dem;
			return a[i].kiTu;
		}
		k = 0;
	}
}
void Decoding(HuffmanCode* huffmanTable, char* input, char* output, int n)//Giai ma doan ma dau vao
{
	int dem = 0, vt = 0;
	char tmp[1000] = "";
	for (int i = 0; i < strlen(input); i++)
	{
		strcat(tmp, checkCode_Decode(huffmanTable, input, n, vt, dem));
		i = vt - 1;
	}
	strcpy(output, tmp);
}
//----------------------------
//Compression Data
void Driver(BTree<Data>& tree, Data* table, int& n, char* str)//Moldule chay cac ham con
{
	char tmp[100];
	BTree<Data> a[48];
	Data tmptable[100];
	int sl = 0;
	strcpy(tmp, str);
	cout << "\nF :";
	//showStr(str);
	puts(str);


	interchangeSort_Ascending(tmp);
	createLookupTable(table, n, tmp);
	coppyArray(table, tmptable, n);


	sl = n;
	createNodeArray(a, table, sl, n);
	showTable(table, n);
	while (n > 1)
	{
		createHuffmanTree(a, tree, table, n);
		/*showTable(table, n);*/
	}
	tree = a[0];
}
//Graphic
void BGcolor(int code)
{
	static HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, code);
}
//Calculating
int SumOfBits(Data* lookup, HuffmanCode* huffman, int length)
{
	interchangeSort_Ascending_LookupTable(lookup, length);
	int sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum += lookup[i].trongSo * strlen(huffman[i].maHuffman);
	}
	return sum;
}
int Saving(char* str, Data* lookup, HuffmanCode* huffman, int length)
{
	return 8 * strlen(str) - SumOfBits(lookup, huffman, length);
}
float CompressRate(char* str, Data* lookup, HuffmanCode* huffman, int length)
{
	return (1 - SumOfBits(lookup, huffman, length) / (8.0 * strlen(str))) * 100;
}