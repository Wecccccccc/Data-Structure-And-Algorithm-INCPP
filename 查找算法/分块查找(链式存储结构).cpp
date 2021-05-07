#include <iostream>
using namespace std;
const int INFMIN = -1e8;

class Node
{
	friend class Idxtab;
private:
	int w;
	Node *next;
};

class IdxNode
{
	friend class Idxtab;
private:
	int maxk;
	Node *fidx;//块链头指针
};

class Idxtab
{
public:
	void CreateList();
	void PrintList();
	bool Find_Node(int k);//查找是否有元素k,有则返回true，无则返回false
private:
	IdxNode *elem;
	int len;
	int N;
};

void Idxtab::CreateList()
{
	Node *p;
	cout << "请输入要输入的数的个数" << endl;
	int n;
	cin >> n;
	cout << "请输入每大份中有多少小份" << endl;
	cin >> N;
	int m = (n / N) + 1;//计算查找表要用的节点个数
	int ms = n % N;//查找表最后的那个要用的节点要连的数的个数
	elem = new IdxNode[m+1];
	len = m;
	for (int i = 1; i <= len; i++)
	{
		elem[i].fidx = nullptr;
	}
	int cnt = 0;
	int j = 1;
	Node *q;
	Node *head = new Node;
	q = head;
	int maxv = INFMIN;
	cout << "请依次输入" << n << "个要存储的数" << endl;
	for (int i = 0; i < n; i++)
	{
		cnt++;
		p = new Node;
		cin >> p->w;
		if ((p->w) > maxv) maxv = p->w;
		q->next = p;
		q = p;
		if (cnt%N == 0 && cnt< n-ms)/*cnt >= n-ms,就说明要连的是查找表最后一个要用的节点，
									我们就特殊处理最后查找表那个节点的情况*/
		{
			elem[j].maxk = maxv;
			maxv = INFMIN;
			elem[j].fidx = head->next;
			q->next = nullptr;
			q = head;
			j++;
		}
	}
	j++;
	elem[j].maxk = maxv;
	maxv = INFMIN;
	elem[j].fidx = head->next;
	q->next = nullptr;
	delete head;
	head = nullptr;
}

bool Find_Node(int k)
{

}

void Idxtab::PrintList()
{
	Node *p;
	cout << len << endl;
	for (int i = 1; i <= len; i++)
	{
		for (p = elem[i].fidx; p; p = p->next)
			cout << p->w << " ";
	}
	cout << endl;
}


int main()
{
	Idxtab l;
	l.CreateList();
	l.PrintList();
	return 0;
}


