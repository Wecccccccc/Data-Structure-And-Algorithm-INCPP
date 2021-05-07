#include <iostream>
using namespace std;
const int Maxsize = 1000;
const int MINNUM = -1e8;
class Index_table
{
	friend class SeqList;
private:
	int key;
	int address;
};

class SeqList
{
//该顺序表从下标为0开始
public:
	~SeqList()
	{
		delete[] elem;
		delete[] idxtab;
	};
	void CreateList();
	int  Find_Elem(int k);//查找值为k的序号
private:
	Index_table *idxtab;
	int max(int a, int b)
	{
		if (a >= b) return a;
		else return b;
	}
	int *elem;
	int len;
	int N;
};

void SeqList::CreateList()
{
	cout << "请输入要输入多少数" << endl;
	int n;
	cin >> n;
	elem = new int[n];
	cout << "请依次输入顺序表中的数" << endl;
	for (int i = 0; i < n; i++) cin >> elem[i];
	cout << "请输入每大份中有多少小份" << endl;
	cin >> N;
	int m = (n/N)+1;
	idxtab = new Index_table[m];
	for (int i = 0; i < m; i++) idxtab[i].address = i * N;
	for (int i = 0; i < m; i++)
	{
		int maxv = MINNUM;
		for (int j = 0 + i * N; j < N*(i + 1) && j < n; j++)
		{
			maxv = max(maxv, elem[j]);
		}
		idxtab[i].key = maxv;
	}
}

int SeqList::Find_Elem(int k)
{
	int j = 0;
	while (idxtab[j].key < k) j++;
	int f = idxtab[j].address;
		for (int i = idxtab[j].address; i < f + N; i++)
			if (elem[i] == k) return i;
	return -1;
}

int main()
{
	SeqList l;
	l.CreateList();
	int k;
	cin >> k;
	cout<<l.Find_Elem(k)<<endl;
	return 0;
}
