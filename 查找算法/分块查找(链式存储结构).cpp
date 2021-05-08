#include <iostream>
using namespace std;
const int INFMIN = -999999;


class Node
{
	friend class IdxTab;
public:
		Node() :next(nullptr) {};
private:
	int w;
	Node *next;
};

class IdxNode
{
	friend class IdxTab;
private:
	int maxk;
	Node *fidx;
};

class IdxTab
{
public:
	void CreateList();
	void Prient_Elem_maxk();
	void Print_Elem_w();
	bool Find_Elem(int k);
	bool Insert(int k);
	bool Delete(int k);
private:
	IdxNode *elem;
	int len;
};

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
	for (int i = 1; i <= len; i++)
	{
		elem[i].maxk = INFMIN;
		for (int j = 1; j <= N && cnt < n; j++)
		{
			cnt++;
			p = new Node;
			int tmp;
			cin >>tmp;
			p->w = tmp;
			p->next = elem[i].fidx;
			elem[i].fidx = p;
			if (tmp > elem[i].maxk) elem[i].maxk = tmp;
		}
	}
}

bool IdxTab::Find_Elem(int k)
{
	if (k > elem[len].maxk) return false;
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
	if (k > elem[len].maxk)
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
	if ((p->w) == k)
	{
		elem[j].fidx = p->next;
		delete p;
		if (k == elem[j].maxk)
		{
			elem[j].maxk = INFMIN;
			for (p = elem[j].fidx; p; p = p->next)
			{
				if ((p->w) > elem[j].maxk) elem[j].maxk = p->w;
			}
			if (j == len) return true;
			int d = 1;
			while (elem[d].maxk > elem[d + 1].maxk && d <= len-1)
			{
				int tmp_e = elem[d].maxk;
				elem[d].maxk = elem[d + 1].maxk;
				elem[d + 1].maxk = tmp_e;
				Node *s;
				s = elem[d].fidx;
				elem[d].fidx = elem[d + 1].fidx;
				elem[d + 1].fidx = s;
				d++;
			}
			return true;
		}
	}
	else
		for (q = elem[j].fidx; q->next; q = q->next)
		{
			if ((q->next->w) == k)
			{
				p = q->next;
				q->next = p->next;
				delete p;
				if (k == elem[j].maxk)
				{
					elem[j].maxk = INFMIN;
					for (p = elem[j].fidx; p; p = p->next)
					{
						if ((p->w) > elem[j].maxk) elem[j].maxk = p->w;
					}
					if (j == len) return true;
					int d = 1;
					while (elem[d].maxk > elem[d + 1].maxk && d <= len - 1)
					{
						int tmp_e = elem[d].maxk;
						elem[d].maxk = elem[d + 1].maxk;
						elem[d + 1].maxk = tmp_e;
						Node *s;
						s = elem[d].fidx;
						elem[d].fidx = elem[d + 1].fidx;
						elem[d + 1].fidx = s;
						d++;
					}
				}
				return true;
			}
		}
	return false;
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




