#include <iostream>
#include <stack>
#include <queue>
using namespace std;
typedef char ElemType;
int InOrder_count = 0;


class BinTreeNode {
		friend class BinaryTree;
	public:
		BinTreeNode(): lchild(NULL), rchild(NULL) {
		};
	private:
		ElemType data;
		BinTreeNode *lchild;
		BinTreeNode *rchild;
};


class BinaryTree {
	public:
		BinaryTree(): root(NULL) {
		};
		~BinaryTree() {
			DeleteTree();
		}
		//cur是current的缩写
		bool Insertlchild(BinTreeNode *cur, ElemType e);
		bool InsertRchild(BinTreeNode *cur, ElemType e);
		void LevelOrder(BinTreeNode *cur);
		void PreOrder(BinTreeNode *cur);
		void InOrder(BinTreeNode *cur);
		void PostOrder(BinTreeNode *cur);
		void PreOrder_Stack(BinTreeNode *cur);
		void InOrder_Stack(BinTreeNode *cur);
		void PostOrder_Stack(BinTreeNode *cur);
		void   InOrder_Count(BinTreeNode *cur);
		BinTreeNode *&visRoot();
		BinTreeNode *Root();
		int Count(BinTreeNode *cur);
		int Height(BinTreeNode *cur);
		BinTreeNode *copyTree(BinTreeNode *t);
		BinTreeNode *Find (BinTreeNode *cur, ElemType e);
		void Destory(BinTreeNode *cur);//删除指点子树
		void DeleteTree() {
			Destory(root);
			root = NULL;
		}
		bool IsEmpty() {
			return root == NULL;
		}
		BinTreeNode *CreateTree();//以先序序列输入
	private:
		BinTreeNode *root;
};

bool BinaryTree::Insertlchild(BinTreeNode *cur, ElemType e) {
	if (cur == NULL)
		return false;
	BinTreeNode *p;
	p = new BinTreeNode();
	p->data = e;
	cur->lchild = p;
	return true;
}

bool BinaryTree::InsertRchild(BinTreeNode *cur, ElemType e) {
	if (cur == NULL)
		return false;
	BinTreeNode *p;
	p = new BinTreeNode();
	p->data = e;
	cur->rchild = p;
	return true;
}

void BinaryTree::Destory(BinTreeNode *cur) {
	if (cur != NULL) {
		Destory(cur->lchild);
		Destory(cur->rchild);
		delete cur;
	}
}

BinTreeNode *BinaryTree::Find(BinTreeNode *cur, ElemType e) {
	if (cur == NULL)
		return NULL;
	if (cur->data == e)
		return cur;
	BinTreeNode *p = Find(cur->lchild, e);
	if (p != NULL)
		return p;
	else
		return Find(cur->rchild, e);
}

void BinaryTree::PreOrder(BinTreeNode *cur) {
	if (cur != NULL) {
		cout << cur->data << " ";
		PreOrder(cur->lchild);
		PreOrder(cur->rchild);
	}
}

void BinaryTree::InOrder(BinTreeNode *cur) {
	if (cur != NULL) {
		InOrder(cur->lchild);
		cout << cur->data << " ";
		InOrder(cur->rchild);
	}
}

void BinaryTree::PostOrder(BinTreeNode *cur) {
	if (cur != NULL) {
		PostOrder(cur->lchild);
		PostOrder(cur->rchild);
		cout << cur->data << " ";
	}
}

void BinaryTree::PreOrder_Stack(BinTreeNode *cur) {
	stack<BinTreeNode *>s;
	while (cur || !s.empty())
		if (cur) {
			cout << cur->data << " ";
			s.push(cur);
			cur = cur->lchild;
		} else {
			cur = s.top();
			s.pop();
			cur = cur->rchild;
		}
}

void BinaryTree::InOrder_Stack(BinTreeNode *cur) {
	stack<BinTreeNode *>s;
	while (cur || !s.empty())
		if (cur) {
			s.push(cur);
			cur = cur->lchild;
		} else {
			cur = s.top();
			s.pop();
			cout << cur->data << " ";
			cur = cur->rchild;
		}
}

void BinaryTree::PostOrder_Stack(BinTreeNode *cur) {
	stack<BinTreeNode *>s1;
	stack<bool>s2;
	bool flag;
	while (cur || !s1.empty())
		if (cur) {
			flag = false;
			s1.push(cur);
			s2.push(flag);
			cur = cur->lchild;
		} else {
			cur = s1.top();
			flag = s2.top();
			s1.pop();
			s2.pop();
			if (flag == false) {
				flag = true;
				s1.push(cur);
				s2.push(flag);
				cur = cur->rchild;
			} else {
				cout << cur->data << " ";
				cur = NULL;
			}
		}
}

void   BinaryTree::InOrder_Count(BinTreeNode *cur) {
	if (cur != NULL) {
		InOrder_Count(cur->lchild);
		InOrder_count++;//InOrder_count为全局变量，使用前要赋值为0
		InOrder_Count(cur->rchild);
	}
}

int BinaryTree::Count(BinTreeNode *cur) {
	int lcnt, rcnt;
	if (cur == NULL)
		return 0;
	lcnt = Count(cur->lchild);
	rcnt = Count(cur->rchild);
	return lcnt + rcnt + 1;
}


int BinaryTree::Height(BinTreeNode *cur) {
	if (cur == NULL)
		return 0;
	else
		return max(Height(cur->lchild), Height(cur->rchild)) + 1;
}

BinTreeNode *BinaryTree::copyTree(BinTreeNode *t) {
	if (t == NULL)
		return NULL;
	BinTreeNode *p;
	p = new BinTreeNode();
	p->data = t->data;
	p->lchild = copyTree(t->lchild);
	p->rchild = copyTree(t->rchild);
	return p;
}

BinTreeNode *BinaryTree::CreateTree() {
	ElemType ch;
	BinTreeNode *t;
	cin >> ch;
	if (ch == '0')
		t = NULL;
	else {
		t = new BinTreeNode();
		t->data = ch;
		t->lchild = CreateTree();
		t->rchild = CreateTree();
	}
	return t;
}

BinTreeNode *BinaryTree::Root() {
	return root;
}

BinTreeNode *&BinaryTree::visRoot() {
	return root;
}

void BinaryTree::LevelOrder(BinTreeNode *cur) {
	if (cur == NULL)
		return ;
	queue<BinTreeNode *>q;
	q.push(cur);
	while (q.size()) {
		BinTreeNode *t = q.front();
		q.pop();
		if (t == NULL)
			continue;
		cout << t->data << " ";
		q.push(t->lchild);
		q.push(t->rchild);
	}
}


int main() {
	BinaryTree T;
	T.visRoot() = T.CreateTree();
	T.PreOrder(T.visRoot());
	cout << endl;
	T.InOrder(T.visRoot());
	cout << endl;
	T.PostOrder(T.visRoot());
	cout << endl;
	cout << "-----------------------------------" << endl;
	T.PreOrder_Stack(T.visRoot());
	cout << endl;
	T.InOrder_Stack(T.visRoot());
	cout << endl;
	T.PostOrder_Stack(T.visRoot());
	cout << endl;
	T.LevelOrder(T.visRoot());
	cout << endl;
	char c1;
	cin >> c1;
	char c2;
	cin >> c2;
	T.Insertlchild(T.Find(T.visRoot(), c1), c2);
	T.PreOrder(T.visRoot());
	cout << endl;
	cout << T.Height(T.visRoot()) << endl;
	T.InOrder_Count(T.visRoot());
	cout << InOrder_count << endl;//全局变量，使用前要赋值为0
	cout << T.Count(T.visRoot()) << endl;
	return 0;
}


