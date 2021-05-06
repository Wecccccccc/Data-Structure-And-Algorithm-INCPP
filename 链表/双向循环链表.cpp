//写Delete_all的时候注意一下就好了，先判断空白头结点是不是为NULL

#include <iostream>
using namespace std;
typedef int ElemType;
#define NO 0

class Node {
		friend class LinkList;
	public:
		Node(): next(NULL), prior(NULL) {
		};
	private:
		ElemType data;
		Node *next;
		Node *prior;
};

class LinkList {
	public:
		LinkList(): head(NULL) {
		};
		~LinkList() {
			Delete_all();
		}
		void Init();
		void TailCreateList(int n);
		Node *Locate_i(int i);
		Node *Locate_e(ElemType e);
		ElemType Get(int i);
		bool Insert(ElemType e, int i);
		bool Delete(int i);
		void Delete_all();
		void PrintList();

	private:
		Node *head;
};


void LinkList::Init() {
	Delete_all();
	head = NULL;
}

void LinkList::TailCreateList(int n) {
	Node *p, *s, *r;
	Delete_all();
	p = new Node();
	r = p;
	for (int i = 1; i <= n; i++) {
		s = new Node();
		cin >> s->data;
		r->next = s;
		s->prior = r;
		r = s;
	}
	r->next = p;
	p->prior = r;
	head = p;
}

Node *LinkList::Locate_i(int i) {
	if (i == 0)
		return head;
	Node *p;
	p = head->next;
	int j = 1;
	while ((p != head) && (j < i)) {
		j++;
		p = p->next;
	}
	if (i == j)
		return p;
	else {
		cout << "position is not correct!!!" << endl;
		return  NULL;
	}
}

Node *LinkList::Locate_e(ElemType e) {
	Node *p;
	p = head->next;
	while ((p != head) && (p->data != e))
		p = p->next;
	if (p != head)
		return p;
	else {
		cout << e << " is not exist!!!" << endl;
		return NULL;
	}
}

bool LinkList::Insert(ElemType e, int i) {
	Node *p, *s;
	p = Locate_i(i - 1);
	if (p != NULL) {
		s = new Node();
		s->data = e;
		s->next = p->next;
		p->next->prior = s;
		p->next = s;
		s->prior = p;
		return true;
	} else {
		cout << "position is not correct!!!" << endl;
		return false;
	}
}

bool LinkList::Delete(int i) {
	Node *p;
	p = Locate_i(i);
	if (p != NULL) {
		p->prior->next = p->next;
		p->next->prior = p->prior;
		delete p;
		return true;
	} else {
		cout << "position is not correct!!!" << endl;
		return false;
	}
}

ElemType LinkList::Get(int i) {
	Node *p;
	p = head->next;
	int j = 1;
	while ((p != head) && (j < i)) {
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


void LinkList::Delete_all() {
	Node *p, *q;
	p = head;
	if (p == NULL) {
		head = NULL;
		return;
	}
	q = p->prior;
	q->next = NULL;
	while (p != NULL) {
		q = p->next;
		delete p;
		p = q;
	}
	head = NULL;
}


void LinkList::PrintList() {
	Node *p;
	p = head->next;
	while (p != head) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}


int main() {
	LinkList l;
	l.Init();
	int n;
	cin >> n;
	l.TailCreateList(n);
	l.PrintList();
	l.Insert(30, 3);
	l.PrintList();
	l.Delete(4);
	l.PrintList();
	cout << l.Get(2) << endl;
	l.PrintList();
	return 0;
}
