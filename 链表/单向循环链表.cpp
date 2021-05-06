#include <iostream>
using namespace std;
typedef int ElemType;
#define  NO 0

class Node {
		friend class LinkList;
	public:
		Node(): next(NULL) {
		};
	private:
		ElemType data;
		Node *next;
};

class LinkList {
	public:
		LinkList(): tail(NULL) {
		};
		~LinkList() {
			Delete_all();
		}
		void Init();
		void TailCreateList(int n);
		void HeadCreateList(int n);
		void PrintList();
		Node *Locate_i(int i);
		Node *Locate_e(ElemType e);
		ElemType Get(int i);
		bool Insert(ElemType e, int i);
		bool Delete(int i);
		void Delete_all();
	private:
		Node *tail;
};

void LinkList::Init() {
	Delete_all();
	tail = NULL;
}

void LinkList::TailCreateList(int n) {
	Node *s, *r, *p;
	Delete_all();
	p = new Node();
	p->next = NULL;
	r = p;
	for (int i = 1; i <= n; i++) {
		s = new Node();
		cin >> s->data;
		r->next = s;
		r = s;
	}
	r->next = p;
	tail = r;
}


void LinkList::HeadCreateList(int n) {
	Node *p, *s;
	Delete_all();
	p = new Node();
	p->next = p;
	bool flag = true;
	for (int i = 1; i <= n; i++) {
		s = new Node();
		cin >> s->data;
		if (flag) {
			tail = s;
			flag = false;
		}
		s->next = p->next;
		p->next = s;
	}
}


void LinkList::PrintList() {
	Node *p;
	p = tail->next->next;
	while (p != tail->next) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

Node *LinkList::Locate_i(int i) {
	if (i == 0)
		return tail;
	Node *p;
	p = tail->next->next;
	int j = 1;
	while ((p != tail->next) && (j < i)) {
		j++;
		p = p->next;
	}
	if (j == i)
		return p;
	else {
		cout << "position is not correct!!!" << endl;
		return NULL;
	}
}

Node *LinkList::Locate_e(ElemType e) {
	Node *p;
	p = tail->next->next;
	while ((p != tail->next) && (p->data != e))
		p = p->next;
	if (p != tail->next)
		return p;
	else {
		cout << e << " is not exist!!!" << endl;
		return NULL;
	}
}


ElemType LinkList::Get(int i) {
	Node *p;
	p = tail->next->next;
	int j = 1;
	while ((p != tail->next) && (j < i)) {
		j++;
		p = p->next;
	}
	if (j == i)
		return p->data;
	else {
		cout << "position is not correct!!!" << endl;
		return NO;
	}
}


bool LinkList::Insert(ElemType e, int i) {

	Node *p, *s;
	p = Locate_i(i - 1);
	if (p != NULL) {
		s = new Node();
		s->data = e;
		s->next = p->next;
		p->next = s;
		if (tail->next == s)
			tail = s;
		return true;
	} else {
		cout << "position is not correct!!!" << endl;
		return false;
	}
}


bool LinkList::Delete(int i) {
	Node *p, *q;
	p = Locate_i(i - 1);
	if (p != NULL) {
		q = p->next;
		if (q == tail)
			tail = p;
		p->next = q->next;
		delete q;
		return true;
	} else {
		cout << "position is not correct!!!" << endl;
		return false;
	}
}

//注意!!! 先判断tail是否为空，只有不为空时才能拿某个指针指向其next域
void LinkList::Delete_all() {
	Node *p, *q;
	q = tail;//注意，这里要先判断tail是不是NULL
	if (q == NULL) {
		tail = NULL;
		return ;
	}
	p = tail->next;//只有tail不是NULL的时候，p才能指向tail->next，否则会出错。
	q->next = NULL;
	while (p != NULL) {
		q = p->next;
		delete p;
		p = q;
	}
	tail = NULL;
}

int main() {
	LinkList l;
	l.Init();
	int n;
	cin >> n;
	l.TailCreateList(n);
	l.PrintList();
	l.Delete(3);
	l.PrintList();
	l.Insert(99, 2);
	l.PrintList();
	cout << l.Get(3) << endl;
	l.PrintList();
	cin >> n;
	l.HeadCreateList(n);
	l.PrintList();
	l.Delete(4);
	l.PrintList();
	l.Insert(99, 3);
	l.PrintList();
	cout << l.Get(4) << endl;
	l.PrintList();
	return 0;
}
