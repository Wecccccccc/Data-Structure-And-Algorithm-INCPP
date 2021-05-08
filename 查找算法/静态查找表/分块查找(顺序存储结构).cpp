#include <iostream>
using namespace std;
const int Maxsize = 1000;
const int MINNUM = -999999;
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
	void Print_Elem_k();
	void Print_Elem_w();
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
	int len_w;
	int N;
};


void SeqList::CreateList()
{
	cout << "请输入要输入多少数" << endl;
	int n;
	cin >> n;
	elem = new int[n];
	len_w = n;
	cout << "请依次输入顺序表中的数" << endl;
	for (int i = 0; i < n; i++) cin >> elem[i];
	cout << "请输入每大份中有多少小份" << endl;
	cin >> N;
	int m = (n / N) + 1;
	idxtab = new Index_table[m];
	len = m;
	for (int i = 0; i < m; i++) idxtab[i].address = i * N;
	for (int i = 0; i < m; i++)
	{
		int maxv = MINNUM;
		for (int j = 0 + i * N; j < N*(i + 1) && j < n; j++)
			maxv = max(maxv, elem[j]);
		idxtab[i].key = maxv;
	}
	for (int i = 0; i < len - 1; i++)//选择排序给查找表排序
	{
		int minv = i;
		for (int j = i + 1; j < len; j++)
			if (idxtab[j].key < idxtab[minv].key) minv = j;
		if (i != minv)
		{
			int tmp1 = idxtab[i].key;
			int tmp2 = idxtab[i].address;
			idxtab[i].key = idxtab[minv].key;
			idxtab[i].address = idxtab[minv].address;
			idxtab[minv].key = tmp1;
			idxtab[minv].address = tmp2;
		}
	}
}


void SeqList::Print_Elem_k()
{
	for (int i = 0; i < len; i++) cout << idxtab[i].key << " ";
	cout << endl;
	for (int i = 0; i < len; i++) cout << idxtab[i].address << " ";
	cout << endl;
}

void SeqList::Print_Elem_w()
{
	for (int i = 0; i < len_w; i++) cout << elem[i] << " ";
	cout << endl;
}


int SeqList::Find_Elem(int k)
{
	int j = 0;
	if (k > idxtab[len - 1].key) return -1;
	if (k < idxtab[0].key)//如果k小于查找表的最小值，则要遍历全部。
	{
		for (int i = 0; i < len_w; i++)
			if (elem[i] == k) return i;
	}
	else
	{
		while (idxtab[j].key < k) j++;
		int f = idxtab[j].address;
		for (int i = idxtab[j].address; i < f + N; i++)
			if (elem[i] == k) return i;
	}
	return -1;
}

int main()
{
	SeqList l;
	l.CreateList();
	int k;
	cin >> k;
	cout << l.Find_Elem(k) << endl;
	l.Print_Elem_w();
	l.Print_Elem_k();
	return 0;
}



