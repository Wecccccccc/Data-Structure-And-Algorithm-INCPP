#include <iostream>
using namespace std;
typedef int ElemType;
const int MAXSIZE = 1010;
#define  NO 0

class SequenList {
	public:
		void Init();
		int Length();
		int Insert(ElemType e, int i);
		int Delete(int i);
		int Locate(ElemType e);
		ElemType Get(int i);
		void PrintList();

	private:
		ElemType data[MAXSIZE];
		int len;
};

void SequenList::Init() {
	len = 0;
}

int SequenList::Length() {
	return len;
}

int SequenList::Insert(ElemType e, int i) {
	//在线性表的第i个元素之前插入一个新元素e
	if (len >= MAXSIZE) {
		cout << "overflow!!!" << endl;
		return 0;
	} else if ((i < 1) || (i > len + 1)) {
		cout << "position is not correct!!!" << endl;
		return 0;
	} else {
		for (int j = len ; j >= i ; j--)
			data[j] = data[j - 1];
		data[i - 1] = e;
		len++;
		return 1;
	}
}

int SequenList::Delete(int i) {
	//删除顺序表的第i个元素
	if ((i < 1) || (i > len)) {
		cout << "position is not correct!!!" << endl;
		return 0;
	} else {
		for (int j = i; j < len ; j++)
			data[j - 1] = data[j];
		len--;
		return 1;
	}
}

int SequenList::Locate(ElemType e) {
	//返回值为e的数据元素的位序值
	int j = 0;
	while ((j < len) && data[j] != e)
		j++;
	if (j < len)
		return j + 1;
	else
		return 0;
}

ElemType SequenList::Get(int i) {
	if ((i < 1) || (i > len)) {
		cout << "position is not correct!!!" << endl;
		return NO;
	} else
		return data[i - 1];
}

void SequenList::PrintList() {
	for (int i = 0; i < len; i++)
		cout << data[i] << " ";
	cout << endl;
}

