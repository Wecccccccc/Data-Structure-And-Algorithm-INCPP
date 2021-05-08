#include <iostream>
using namespace std;
const int INFMIN = -999999;

class Node
{
	friend class IdxTab;
public:
		Node() :next(nullptr) {};
private:
	int  w;
	Node *next;
};

class IdxNode
{
	friend class IdxTab;
private:
	int  maxk;
	Node *fidx;
};

class IdxTab
{
public:
	void CreateList();
	void Prient_Elem_maxk();//输出查找表的元素
	void Print_Elem_w();//输出元素
	bool Find_Elem(int k);//查找值为k的元素
	bool Insert(int k);//插入元素k
	bool Delete(int k);//删除元素k
	~IdxTab();
private:
	IdxNode *elem;
	int len;
};

IdxTab::~IdxTab()
{
	Node *p,*q;
	for (int i = 0; i <= len; i++)
	{

		p = elem[i].fidx;
		if (p == nullptr) continue;
		q = p->next;
		delete p;
		if (q == nullptr) continue;
		else
			p = q;
	}
	for (int i = 0; i <= len; i++) elem[i].fidx = nullptr;
}

void IdxTab::CreateList()
{
	Node *p;
	int n;
	int N;
	cout << "请输入要存储的数的个数" << endl;
	cin >> n;
	cout << "请输入每大块中每小块的数目是多少" << endl;
	cin >> N;
	int m = (n / N) + 1;
	len = m;
	elem = new IdxNode[m + 1];
	for (int i = 0; i < m + 1; i++) elem[i].fidx = nullptr;
	int cnt = 0;//计数器
	cout << "请依次输入要存储的数" << endl;
	for (int i = 1; i <= len; i++)
	{
		elem[i].maxk = INFMIN;
		for (int j = 1; j <= N && cnt < n; j++)//因为可能输入的n不够整除，查找表最后一个节点可能连的节点比较少，用
												//cnt<n，来处理这种情况
		{
			cnt++;
			p = new Node;
			int tmp;
			cin >>tmp;
			p->w = tmp;
			p->next = elem[i].fidx;
			elem[i].fidx = p;
			if (tmp > elem[i].maxk) elem[i].maxk = tmp;//更新maxk
		}
	}
	for (int i = 1; i <= len-1; i++)//选择排序给查找表排序
	{
		int minv = i;
		for (int j = i + 1; j <= len; j++)
			if (elem[minv].maxk > elem[j].maxk)
				minv = j;
			if (i != minv)
			{
				int tmp = elem[i].maxk;
				elem[i].maxk = elem[minv].maxk;
				elem[minv].maxk = tmp;
				Node *s;
				s = elem[i].fidx;
				elem[i].fidx = elem[minv].fidx;
				elem[minv].fidx = s;
			}
	}
}

bool IdxTab::Find_Elem(int k)
{
	if (k > elem[len].maxk) return false;//如果输入的k直接大于最大的元素，直接return false；
	int j = 1;
	while (elem[j].maxk < k) j++;
	Node *p;
	for (p = elem[j].fidx;p;p = p->next)
	{
		if ((p->w) == k) return true;
	}
	return false;
}

bool IdxTab::Insert(int k)
{
	Node *s;
	int j = 1;
	if (k > elem[len].maxk)//如果k大于最大元素，直接处理查找表最后一个节点
	{
		s = new Node;
		s->w = k;
		s->next = elem[len].fidx;
		elem[len].fidx = s;
		elem[len].maxk = k;
		return true;
	}
	else
		while (elem[j].maxk < k) j++;
	s = new Node;
	s->w = k;
	s->next = elem[j].fidx;
	elem[j].fidx = s;
	return true;
}

bool IdxTab::Delete(int k)
{
	if (k > elem[len].maxk) return false;
	int j = 1;
	while (elem[j].maxk < k) j++;
	Node *p, *q;
	p = elem[j].fidx;
	bool flag = false;//用flag表示有没有值为k这个元素
	if ((p->w) == k)//因为没有空白头节点，所以要特别判断一下要删除的是fidx
	{
		flag = true;
		elem[j].fidx = p->next;
		delete p;
	}
	else
		for (q = elem[j].fidx; q->next; q = q->next)
		{
			if ((q->next->w) == k)
			{
				flag = true;
				p = q->next;
				q->next = p->next;
				delete p;
				break;
			}
		}
	if (k == elem[j].maxk)//判断删除的是不是更好是值为最大关键字
	{
		elem[j].maxk = INFMIN;
		for (p = elem[j].fidx; p; p = p->next)
		{
			if ((p->w) > elem[j].maxk) elem[j].maxk = p->w;
		}
		if (j == len) return true;
		for (int i = 1; i <= len - 1; i++)//选择排序给查找表排序
		{
			int minv = i;
			for (int j = i + 1; j <= len; j++)
				if (elem[minv].maxk > elem[j].maxk)
					minv = j;
			if (i != minv)
			{
				int tmp = elem[i].maxk;
				elem[i].maxk = elem[minv].maxk;
				elem[minv].maxk = tmp;
				Node *s;
				s = elem[i].fidx;
				elem[i].fidx = elem[minv].fidx;
				elem[minv].fidx = s;
			}
		}
		if (flag) return true;
		return false;
	}
}

void IdxTab::Print_Elem_w()
{
	Node *p;
	for (int i = 1; i <= len; i++)
	{
		for (p = elem[i].fidx; p; p = p->next) cout << p->w << " ";
	}
	cout << endl;
}

void IdxTab::Prient_Elem_maxk()
{
	for (int i = 1; i <= len; i++) cout << elem[i].maxk << " ";
	cout << endl;
}



int main()
{
	IdxTab l;
	l.CreateList();
	l.Prient_Elem_maxk();
	l.Print_Elem_w();
	int k;
	cin >> k;
	l.Insert(k);
	l.Prient_Elem_maxk();
	l.Print_Elem_w();
	cin >> k;
	l.Insert(k);
	l.Prient_Elem_maxk();
	l.Print_Elem_w();
	cin >> k;
	l.Delete(k);
	l.Prient_Elem_maxk();
	l.Print_Elem_w();
	cin >> k;
	l.Delete(k);
	l.Prient_Elem_maxk();
	l.Print_Elem_w();
	return 0;
}

