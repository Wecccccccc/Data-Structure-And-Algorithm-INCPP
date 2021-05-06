#include <iostream>
#include <string>
using namespace std;
const unsigned int n = 8;//字符数NUM，这里的字符数为8
const unsigned int m = 2 * n - 1;//结点总数
const float MAX = 1e8;


class HTNode
{
	friend class HuffmanTree;
private:
	float weight;
	int parent;
	int lchild;
	int rchild;
};

class HuffmanTree
{
public:
	HuffmanTree();
	~HuffmanTree() = default;
	void PrintCode();
private:
	void DFS(int i, int step);
	void Select(int k, int  &s1, int  &s2);
	HTNode HT[m + 1];
	int code[m + 1];
};

HuffmanTree::HuffmanTree()
{
	int s1, s2;
	for (int i = 1; i <= m; i++)
	{
		HT[i].weight = 0;
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
	}
	cout << "Please input the weight" << endl;
	for (int i = 1; i <= n; i++)cin >> HT[i].weight;
	for (int i = n + 1; i <= m; i++)
	{
		Select(i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		cout << HT[i].weight << " " << "(" << HT[s1].weight << "," << HT[s2].weight << ")" << endl;//该输出为测试数据使用
	}
}


void HuffmanTree::Select(int k, int &s1, int &s2)
{
	HT[0].weight = MAX;
	s1 = s2 = 0;
	for (int i = 1; i <= k; i++)
		if (HT[i].weight != 0 && HT[i].parent == -1)
		{
			if (HT[i].weight < HT[s1].weight)
			{
				s2 = s1;
				s1 = i;
			}
			else
				if (HT[i].weight < HT[s2].weight) s2 = i;
		}
}

void HuffmanTree::DFS(int i,int step)
{
	if (HT[i].lchild == -1 && HT[i].rchild == -1)
	{
		cout << HT[i].weight << " = ";
		for (int i = 0; i < step; i++)
			cout << code[i];
		cout << endl;
		return;
	}
	if (HT[i].lchild != -1 )
	{
		code[step] = 0;
		DFS(HT[i].lchild,step+1);
	}
	if (HT[i].rchild != -1 )
	{
		code[step] = 1;
		DFS(HT[i].rchild, step+1);
	}
}

void HuffmanTree::PrintCode()
{
	for (int i = 0; i < m + 1; i++) code[i] = false;
	DFS(m, 0);
}

int main()
{
	HuffmanTree t;
	cout << endl;
	t.PrintCode();
	return 0;
}

