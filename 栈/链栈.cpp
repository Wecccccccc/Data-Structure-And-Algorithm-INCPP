#include <iostream>
using namespace std;
typedef int ElemType;

class StackNode {
		friend class LinkStack;
	private:
		ElemType data;
		StackNode *next;
		StackNode(): next(NULL) {
		};
};

class LinkStack {
	public:
		LinkStack(): top(NULL) {
		};
		~LinkStack() {
			StackNode *p;
			while (top) {
				p = top;
				top = top->next;
				delete  p;
			}
			top = NULL;
		};
		int Empty_Stack();
		int Push_Stack(ElemType e);
		int Pop_Stack(ElemType &e);
		int GetTop_Stack(ElemType &e);
	private:
		StackNode *top;
};


int LinkStack::Empty_Stack() {
	return (!top);
}

int LinkStack::Push_Stack(ElemType e) {
	StackNode *p;
	p = new StackNode();
	if (p) {
		p->data = e;
		p->next = top;
		top = p;
		return 1;
	} else
		return 0;
}


int LinkStack::Pop_Stack(ElemType &e) {
	StackNode *p;
	if (top) {
		p = top;
		e = p->data;
		top = top->next;
		delete p;
		return 1;
	} else
		return 0;
}

int LinkStack::GetTop_Stack(ElemType &e) {
	if (top) {
		e = top->data;
		return 1;
	} else
		return 0;
}

int main() {
	LinkStack s;
	s.Push_Stack(23);
	s.Push_Stack(12);
	s.Push_Stack(89);
	int x;
	s.Pop_Stack(x);
	cout << x << endl;
	s.GetTop_Stack(x);
	cout << x << endl;
	return 0;
}
