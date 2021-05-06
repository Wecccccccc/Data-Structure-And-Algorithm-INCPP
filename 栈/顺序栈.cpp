#include <iostream>
using namespace std;
typedef int ElemType;

class SeqStack {
	public:
		SeqStack(int stacksize = 100) {
			base = new ElemType[stacksize];
			top = base;
			size = stacksize;
		};
		~SeqStack() {
			delete[] base;
			top = NULL;
			base = NULL;
		};
		int Empty_Stack();
		int Push_Stack(ElemType e);
		int Pop_Stack(ElemType &e);
		int GetTop_Stack(ElemType &e);
	private:
		ElemType *top;
		ElemType *base;
		int size;
};

int SeqStack::Empty_Stack() {
	return ((top <= base));
}

int SeqStack::Push_Stack(ElemType e) {
	if (top - base < size) {
		*top = e;
		top++;
		return 1;
	} else
		return 0;
}

int SeqStack::Pop_Stack(ElemType &e) {
	if (top > base) {
		top--;
		e = *top;
		return 1;
	} else
		return 0;
}

int SeqStack::GetTop_Stack(ElemType &e) {
	if (top > base) {
		e = *(top - 1);
		return 1;
	} else
		return 0;
}

int main() {
	SeqStack s(5);
	s.Push_Stack(89);
	s.Push_Stack(90);
	s.Push_Stack(13);
	s.Push_Stack(878);
	s.Push_Stack(78);
	s.Push_Stack(12);
	int x;
	s.Pop_Stack(x);
	cout << x << endl;
	s.GetTop_Stack(x);
	cout << x << endl;
	return 0;
}
