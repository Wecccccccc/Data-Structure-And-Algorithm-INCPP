#include <iostream>
using namespace std;
const int MAX = 1e8;


class HuffmanNode
{
	friend class HuffmanTree;
private:
	double w;
	int par;
	int lch;
	int rch;
};

class HuffmanTree
{
	friend class HuffmanTree;
public:
	HuffmanTree() ;
	~HuffmanTree();
	void PrintCode();
private:
	void dfs(int i,int s);
	void Select(int n, int &s1, int &s2);
	HuffmanNode *HT;
	int *path;
	int m;
};


void HuffmanTree::Select(int n, int &s1, int &s2)
{
	s1 = s2 = 0;
	HT[0].w = MAX;
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].par==-1 && HT[i].w!=0)
		if (HT[i].w < HT[s1].w)
		{
			s2 = s1;
			s1 = i;
		}
		else
			if (HT[i].w < HT[s2].w) s2 = i;
	}
}

HuffmanTree::HuffmanTree() :HT(nullptr), path(nullptr)
{
	cout << "Please input node:" << endl;
	int n;
	cin >> n;
	 m = 2 * n - 1;
	HT = new HuffmanNode[m + 1];
	for (int i = 1; i <= m; i++)
	{
		HT[i].par = -1;
		HT[i].lch = -1;
		HT[i].rch = -1;
		HT[i].w = 0;
	}
	for (int i = 1; i <= n; i++) cin >> HT[i].w;
	for (int i = n + 1; i <= m; i++)
	{
		int s1, s2;
		Select(i - 1, s1, s2);
		HT[s1].par = i;
		HT[s2].par = i;
		HT[i].lch = s1;
		HT[i].rch = s2;
		HT[i].w = HT[s1].w + HT[s2].w;
		cout << HT[i].w << " " << "(" << HT[s1].w << "," << HT[s2].w << ")" << endl;
	}
}

void HuffmanTree::dfs(int i,int s)
{
	if (HT[i].lch == -1 && HT[i].rch == -1)
	{
		cout << HT[i].w << " = ";
		for (int i = 0; i < s; i++) cout << path[i];
		cout << endl;
		return;
	}
	if (HT[i].lch != -1)
	{
		path[s] = 0;
		dfs(HT[i].lch, s + 1);
	}
	if (HT[i].rch != -1)
	{
		path[s] = 1;
		dfs(HT[i].rch, s + 1);
	}
}

void HuffmanTree::PrintCode()
{
	path = new int[m + 1];
	for (int i = 0; i < m + 1; i++) path[i] = 0;
	dfs(m,0);
	delete[]path;
	path = nullptr;
}

HuffmanTree::~HuffmanTree()
{
	delete[] HT;
	HT = nullptr;
}

int main()
{
	HuffmanTree t;
	t.PrintCode();
	return 0;
}
