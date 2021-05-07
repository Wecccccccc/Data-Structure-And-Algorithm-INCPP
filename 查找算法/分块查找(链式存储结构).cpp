#include <iostream>
#include <algorithm>
using namespace std;
const int INFMIN = -999999;
const int Maxsize = 30;
bool cmp1(IdxNode a, IdxNode b);
class Node
{
	friend bool cmp1(IdxNode a, IdxNode b);
	friend class Idxtab;
private:
	int w;
	Node *next;
};

class IdxNode
{
	friend bool cmp1(IdxNode a, IdxNode b);
	friend class Idxtab;
private:
	int maxk;
	Node *fidx;//块链头指针
};

class Idxtab
{
	friend bool cmp1(IdxNode a, IdxNode b);
public:
	void CreateList();
	void PrintList();
	bool Find_Node(int k);//查找是否有元素k,有则返回true，无则返回false
	int Idx_Node(int k);//得到元素k的序号，序号从1开始
	bool Insert_Node_front(int k, int w);//往第一个值为k的元素前面插入元素w
	bool Insert_Node_back(int k, int w);//往第一个值为k的元素后面插入元素w
	bool Delete_Node(int k);//删除第一个值为k的元素
private:
	IdxNode elem[Maxsize];
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

bool Idxtab::Find_Node(int k)
{
	Node *p;
	int j = 1;
	while (elem[j].maxk < k) j++;
	if (j > len) return false;
	for (p = elem[j].fidx; p; p = p->next)
	{
		if (p->w == k) return true;
	}
	return false;
}

int Idxtab::Idx_Node(int k)
{
	Node *p;
	if (k > elem[len].maxk) return 0;
	int j = 1;
	for (int i = 1; i <= len; i++)
	{
		for (p = elem[i].fidx; p; p = p->next)
		{
			if ((p->w) == k) return j;
			j++;
		}
	}
	return 0;
}

bool Idxtab::Insert_Node_front(int k,int w)
{
	Node *p,*q;
	int j = 1;
	if (k > elem[len].maxk) return false;
	while (elem[j].maxk < k)j++;
	p = elem[j].fidx;
	if ((p->w) == k)//因为没有空白头节点，特判一下最开始这个节点
	{
		q = new Node;
		q->w = w;
		q->next = elem[j].fidx;
		elem[j].fidx = q;
		if (w > elem[j].maxk)
		{
			elem[j].maxk = w;//更新最大关键字
			sort(elem + 1, elem + 1 + len, cmp1);
		}
		return true;
	}
	else
	{
		while (p->next && p->next->w!=k)
			p = p->next;
		if (p->next)
		{
			q = new Node;
			q->w = w;
			q->next = p->next;
			p->next = q;
			if (w > elem[j].maxk)
			{
				elem[j].maxk = w;//更新最大关键字
				sort(elem + 1, elem +1 + len, cmp1);
			}
		}
		else
			return false;
	}
}

bool cmp1(IdxNode a, IdxNode b)
{
	return a.maxk < b.maxk;
}

bool Idxtab::Insert_Node_back(int k, int w)
{
	Node *p;
	int j = 1;
	if (elem[len].maxk < k) return false;
	while (elem[j].maxk < k) j++;
	for (p = elem[j].fidx; p; p = p->next)
	{
		if ((p->w) == k)
		{
			Node *q = new Node;
			q->w = w;
			q->next = p->next;
			p->next = q;
			if (w > elem[j].maxk)
			{
				elem[j].maxk = w;//更新最大关键字
				sort(elem + 1, elem + 1 + len, cmp);
			}
			return true;
		}
	}
	return false;
}


bool Idxtab::Delete_Node(int k)
{
	Node *p,*q;
	int j = 1;
	if (k > elem[len].maxk) return false;
	while (elem[j].maxk < k) j++;
	p = elem[j].fidx;
	int tmp = p->w;
	if ((p->w) == k)//因为没有空白头节点，特判一下最开始这个节点
	{
		q = p->next;
		elem[j].fidx = q;
		delete p;
		if (tmp == elem[j].maxk)
		{
			Node *s;
			int maxv = INFMIN;
			for (s = elem[j].fidx; s; s = s->next)
			{
				if (s->w > maxv) maxv = s->w;
			}
			elem[j].maxk = maxv;
			sort(elem + 1, elem + 1 + len, cmp);
		}
		return true;
	}
	else
	{
		while (p->next && p->next->w != k)
			p = p->next;
		int tmp = p->next->w;
		if (p->next)
		{
			q = p->next;
			p->next = q->next;
			delete q;
			if (tmp == elem[j].maxk)
			{
				Node *s;
				int maxv = INFMIN;
				for (s = elem[j].fidx; s; s = s->next)
				{
					if (s->w > maxv) maxv = s->w;
				}
				elem[j].maxk = maxv;
				sort(elem + 1, elem + 1 + len, cmp);
			}
			return true;
		}
		else
			return false;
	}
}

void Idxtab::PrintList()
{
	Node *p;
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
	int k;
	cin >> k;
	if (l.Find_Node(k)) cout << "yes" << endl;
	else cout << "no" << endl;
	cin >> k;
	if (l.Find_Node(k)) cout << "yes" << endl;
	else cout << "no" << endl;
	cin >> k;
	cout << l.Idx_Node(k) << endl;
	cin >> k;
	cout << l.Idx_Node(k) << endl;
	int w;
	cin >> k >> w;
	l.Insert_Node_front(k, w);
	l.PrintList();
	cin >> k >> w;
	l.Insert_Node_back(k, w);
	l.PrintList();
	cin >> k;
	l.Delete_Node(k);
	l.PrintList();
	cin >> k;
	l.Delete_Node(k);
	l.PrintList();
	return 0;
}




