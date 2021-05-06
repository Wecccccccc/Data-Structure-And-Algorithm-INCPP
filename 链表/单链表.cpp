#include <iostream>
using namespace std;
typedef int ElemType;
#define NO 0

class Node {
		friend class LinkList;
	private:
		ElemType data;
		Node *next;
		Node (): next(NULL) {
		};
};

class LinkList {
	private:
		Node *head;
	public:
		LinkList(): head(NULL) {
		};
		~LinkList() {
			Delete_all();
		}
		void Init();
		void HeadCreateList(int n);
		void TailCreateList(int n);
		int length();
		Node *Locate_i(int i);
		Node *Locate_e(ElemType e);
		ElemType Get(int i);
		bool Insert(ElemType e, int i);
		bool Delete(int i);
		void PrintList();
		void Delete_all();
};


void LinkList::Init() {
	Delete_all();
	head = NULL;
}


void LinkList::HeadCreateList(int n) {
	//从表尾到表头建立单链表
	Node *s, *p;
	Delete_all();
	p = new Node();
	p->next = NULL;
	for (int i = 1; i <= n; i++) {
		s = new Node();
		cin >> s->data;
		s->next = p->next;
		p->next = s;
	}
	head = p;
}


void LinkList::TailCreateList(int n) {
	//从表头到表尾建立单链表
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
	r->next = NULL;
	head = p;
}

int LinkList::length() {
	Node *p;
	int j = 0;
	p = head->next;
	while (p != NULL) {
		j++;
		p = p->next;
	}
	return j;
}

Node *LinkList::Locate_i(int i) {
//按序号查找
	if (i == 0)
		return head;
	int j = 1;
	Node *p ;
	p = head->next;
	while ((p != NULL) && (j < i)) {
		p = p->next;
		j++;
	}
	if (j == i)
		return p;
	else {
		cout << "position is not correct!!!" << endl;
		return NULL;
	}
}

Node *LinkList::Locate_e(ElemType e) {
//按值查找
	Node *p;
	p = head->next;
	while ((p != NULL) && (p->data != e))
		p = p->next;
	if (p)
		return p;
	else {
		cout << e << "is not exist!!!" << endl;
		return NULL;
	}
}

ElemType LinkList::Get(int i) {
	//读取第i个位置上的元素值
	int j = 1;
	Node *p;
	p = head->next;
	while ((j < i) && (p != NULL)) {
		j++;
		p = p->next;
	}
	if ((p == NULL) || ( j > i)) {
		cout << "position is not correct!!!" << endl;
		return NO;
	} else
		return p->data;
}

bool LinkList::Insert(ElemType e, int i) {
	Node *p, *s;
	p = Locate_i(i - 1);
	if (p == NULL) {
		cout << "position is not correct!!!" << endl;
		return false;
	}
	s = new Node();
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

bool LinkList::Delete(int i) {
	Node *p = Locate_i(i - 1);
	Node *q;
	if (p == NULL) {
		cout << "position is not correct!!!" << endl;
		return NULL;
	}
	q = p->next;
	if (q != NULL) {
		p->next = q->next;
		delete q;
		return true;
	} else {
		cout << "position is not correct!!!" << endl;
		return false;
	}
}

void LinkList::PrintList() {
	Node *p;
	p = head->next;
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

void LinkList::Delete_all() {
	Node *p = head, *q;
	while (p != NULL) {
		q = p->next;
		delete p;
		p = q;
	}
	head = NULL;
}
