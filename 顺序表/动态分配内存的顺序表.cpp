#include <iostream>
using namespace std;
typedef int ElemType;
#define NO 0

class SequenList {
	public:
		void Init();
		int Length();
		ElemType Get(int i);
		int Locate(ElemType e);
		int Insert(ElemType e, int i);
		int Delete(int i);
		void PrintList();

	private:
		int len;
		ElemType *data;
		int MAXSIZE;
};

void SequenList::Init() {
	cout << "请输入创建该顺序表要开辟的大概空间为多少？" << endl;
	cin >> MAXSIZE;
	data = new ElemType[MAXSIZE];
	len = 0;
}

int SequenList::Length() {
	return len;
}

ElemType SequenList::Get(int i) {
	if ((i < 1) || (i > len)) {
		cout << "position is not correct!!!" << endl;
		return NO;
	} else
		return data[i - 1];
}

int SequenList::Locate(ElemType e) {
	int j = 0;
	while (j < len && data[j] != e)
		j++;
	if (j < len)
		return j + 1;
	else
		return 0;
}

int SequenList::Insert(ElemType e, int i) {
	if (len >= MAXSIZE) {
		cout << "overflow!!!" << endl;
		return 0;
	} else if ((i < 1) || ( i > len + 1)) {
		cout << "position is not correct!!!" << endl;
		return 0;
	} else {
		for (int j = len ; j >= i; j--)
			data[j] = data[j - 1];
		len++;
		data[i - 1] = e;
		return 1;
	}
}

int SequenList::Delete(int i) {
	if ((i < 1) || ( i > len)) {
		cout << "position is not correct!!!" << endl;
		return 0;
	} else {
		for (int j = i; j < len; j++)
			data[j - 1] = data[j];
		len--;
		return 1;
	}
}

void SequenList::PrintList() {
	for (int i = 0; i < len; i++)
		cout << data[i] << " ";
	cout << endl;
}

