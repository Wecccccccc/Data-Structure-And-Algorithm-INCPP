#include <iostream>
using namespace std;
typedef int ElemType;

class QueueNode {
		friend class LinkQueue;
	public:
		QueueNode(): next(NULL) {
		};
	private:
		ElemType data;
		QueueNode *next;
};

class LinkQueue {
	public:
		LinkQueue(): front(NULL), rear(NULL) {
		};
		~LinkQueue() {
			QueueNode *p, *q;
			p = front;
			while (p) {
				q = p;
				p = p->next;
				delete q;
			}
			front = NULL;
			rear = NULL;
		};
		int Empty_Queue();
		int En_Queue(ElemType e);
		int De_Queue(ElemType &e);
		int Front_Queue(ElemType &e);
	private:
		QueueNode *front;
		QueueNode *rear;
};

int LinkQueue::Empty_Queue() {
	return (front == NULL && rear == NULL);
}

int LinkQueue::En_Queue(ElemType e) {
	QueueNode *p;
	p = new QueueNode();
	if (p) {
		p->data = e;
		if (rear) {
			rear->next = p;
			rear = p;
		} else
			front = rear = p;
		return 1;
	} else
		return 0;
}

int LinkQueue::De_Queue(ElemType &e) {
	QueueNode *p;
	if (!Empty_Queue()) {
		p = front;
		e = p->data;
		front = front->next;
		if (!front)
			rear = NULL;
		delete p;
		return 1;
	} else
		return 0;
}

int LinkQueue::Front_Queue(ElemType &e) {
	if (!Empty_Queue()) {
		e = front->data;
		return 1;
	} else
		return 0;
}

int main() {
	LinkQueue l;
	l.En_Queue(23);
	l.En_Queue(45);
	l.En_Queue(452);
	l.En_Queue(12);
	int x;
	l.De_Queue(x);
	cout << x << endl;
	l.Front_Queue(x);
	cout << x << endl;
	cout << l.Empty_Queue() << endl;
	l.De_Queue(x);
	cout << x << endl;
	l.De_Queue(x);
	cout << x << endl;
	l.Front_Queue(x);
	cout << x << endl;
	l.De_Queue(x);
	cout << l.Empty_Queue() << endl;
	return 0;
}
