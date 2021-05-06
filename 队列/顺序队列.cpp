#include <iostream>
using namespace std;
typedef int ElemType;

class SeqQueue {
	public:
		SeqQueue(int Queuesize = 100) {
			base = new ElemType[Queuesize];
			front = 0;
			rear = 0;
			size = Queuesize;
		};
		~SeqQueue() {
			delete[] base;
		};
		int Empty_Queue();
		int En_Queue(ElemType e);
		int De_Queue(ElemType &e);
		int Front_Queue(ElemType &e);
	private:
		ElemType *base;
		int front;
		int rear;
		int size;
};

int SeqQueue::Empty_Queue() {
	return (front == rear);
}

int SeqQueue::En_Queue(ElemType e) {
	if (((rear + 1) % size) != front) {
		rear = (rear + 1) % size;
		base[rear] = e;
		return 1;
	} else
		return 0;
}

int SeqQueue::De_Queue(ElemType &e) {
	if (rear != front) {
		front = (front + 1) % size;
		e = base[front];
		return 1;
	} else
		return 0;
}


int SeqQueue::Front_Queue(ElemType &e) {
	if (rear != front) {
		e = base[(front + 1) % size];
		return 1;
	} else
		return 0;
}

int main() {
	SeqQueue q(5);
	q.En_Queue(13);
	q.En_Queue(23);
	int x;
	q.De_Queue(x);
	cout << x << endl;
	q.Front_Queue(x);
	cout << x << endl;
	cout << q.Empty_Queue() << endl;
	return 0;
}
