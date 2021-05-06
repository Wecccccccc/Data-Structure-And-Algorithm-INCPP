#include <iostream>
using namespace std;
const int maxsize = 100;
typedef char  ElemType;

class QbTree {
	public:
		void CreateBTree(int n);
		int vislchild(int i);
		int visrchild(int i);
		int visparent(int i);
		ElemType viselem(int i);
		void LevelOrder();
	private:
		ElemType elem[maxsize];
		int n;
};

void QbTree::CreateBTree(int m) {
	for (int i = 1; i <= m; i++) {
		cin >> elem[i];
	}
	n = m;
}

int QbTree::vislchild(int i) {
	if (i == 0 || i > n)
		return 0;
	int vis = 2 * i;
	if (vis > n) {
		cout << "lchild is not exist!!!" << endl;
		return 0;
	}
	return vis;
}

int QbTree::visrchild(int i) {
	if (i == 0 || i > n)
		return 0;
	int vis = 2 * i + 1;
	if (vis > n) {
		cout << "rchild is not exist!!!" << endl;
		return 0;
	}
	return vis;
}

int QbTree::visparent(int i) {
	if (i == 0 || i > n)
		return 0;
	int vis  = i / 2;
	if (vis == 0) {
		cout << "parent is not exist!!!" << endl;
		return 0;
	}
	return vis;
}

ElemType QbTree::viselem(int i) {

	if (i == 0) {
		cout << "position is not correct!!!" << endl;
		return 0;
	}
	return elem[i];
}

void QbTree::LevelOrder() {
	for (int i = 1; i <= n; i++)
		cout << elem[i] << " ";
	cout << endl;
}

int main() {
	QbTree t;
	int n;
	cin >> n;
	getchar();
	t.CreateBTree(n);
	int ch, lch, rch, par;
	cin >> ch;
	lch = t.vislchild(ch);
	rch = t.visrchild(ch);
	par = t.visparent(ch);
	cout << lch << " " << rch << " " << par << endl;
	cout << t.viselem(lch) << endl;
	cout << t.viselem(rch) << endl;
	cout << t.viselem(par) << endl;
	t.LevelOrder();
	return 0;

}
