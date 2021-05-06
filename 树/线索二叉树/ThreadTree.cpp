#include <iostream>
using namespace std;
typedef char ElemType;

class ThreadNode {
	friend class ThreadTree;
public:
	ThreadNode() : ltag(0), rtag(0), lch(NULL), rch(NULL) {
	};
private:
	int ltag, rtag;
	ElemType data;
	ThreadNode *lch;
	ThreadNode *rch;
};

class ThreadTree {
public:
	ThreadTree() : root(NULL) {
	};
	~ThreadTree()
	{
		DeleteTree(root);
		root = NULL;
	}
	void InOrder_Thread();
	void InOrder(ThreadNode *root);
	ThreadNode *InPreNode(ThreadNode *cur);
	ThreadNode *InPostNode(ThreadNode *cur);
	ThreadNode *CreateTree();//以先序遍历方式读入
	ThreadNode *&visRoot();
	ThreadNode *Root();
	void DeleteTree(ThreadNode *root);
	ThreadNode *Search(ThreadNode *root, ElemType e);
	void InsertThrRight(ThreadNode *s, ThreadNode *p);//在中序线索二叉树中插入结点p，使其成为结点s的右孩子
	ElemType visElem(ThreadNode *cur);
private:
	ThreadNode *root;
	void InThread(ThreadNode *root, ThreadNode *&pre);
};

void ThreadTree::InOrder_Thread() {
	ThreadNode *pre = nullptr;
	InThread(root, pre);
}

void ThreadTree::InThread(ThreadNode *root, ThreadNode *&pre) {
	if (root != NULL) {
		InThread(root->lch, pre);
		if (root->lch == NULL) {
			root->ltag = 1;
			root->lch = pre;
		}
		if ((pre) && pre->rch == NULL) {
			pre->rtag = 1;
			pre->rch = root;
		}
		pre = root;
		InThread(root->rch, pre);
	}
}

void ThreadTree::InOrder(ThreadNode *root) {
	ThreadNode *p;
	if (root == NULL)
		return;
	p = root;
	while (p->ltag == 0)
		p = p->lch;
	while (p) {
		cout << p->data << " ";
		p = InPostNode(p);
	}
}

ThreadNode *ThreadTree::InPreNode(ThreadNode *cur) {
	ThreadNode *pre;
	if (cur == nullptr) return nullptr;
	pre = cur->lch;
	if (cur->ltag != 1)
		while (pre!=nullptr && pre->rtag == 0)
			pre = pre->rch;
	return pre;
}

ThreadNode *ThreadTree::InPostNode(ThreadNode *cur) {
	ThreadNode *post;
	if (cur == nullptr) return nullptr;
	post = cur->rch;
	if (cur->rtag != 1)
		while (post != nullptr &&post->ltag == 0)
			post = post->lch;
	return post;
}

ThreadNode *ThreadTree::CreateTree() {
	ThreadNode *t;
	ElemType ch;
	cin >> ch;
	if (ch == '0')
		t = nullptr;
	else {
		t = new ThreadNode();
		t->data = ch;
		t->lch = CreateTree();
		t->rch = CreateTree();
	}
	return t;
}

void ThreadTree::DeleteTree(ThreadNode *root)
{
	ThreadNode *p;
	if (root == NULL) return;
	p = root;
	while (p->ltag == 0) p = p->lch;
	while (p)
	{
		ThreadNode *q;
		q = p;
		/*delete q;*/ //delete q不能写这个位置，要先让p指针指向别处，再销毁这块内存，否则会报错
		p = InPostNode(p);
		delete q;
	}
}

ThreadNode *ThreadTree::Search(ThreadNode *root, ElemType e)
{
	ThreadNode *p;
	if (root == NULL) return NULL;
	p = root;
	while (p->ltag == 0) p = p->lch;
	while (p && p->data != e) p = InPostNode(p);
	if (p == NULL)
	{
		cout << "Not Found the data!!!" << endl;
		return NULL;
	}
	else return p;
}


//在中序线索二叉树中插入结点p，使其成为结点s的右孩子
void ThreadTree::InsertThrRight(ThreadNode *s, ThreadNode *p)
{
	ThreadNode *w;
	p->rch = s->rch;
	p->rtag = s->rtag;
	p->lch = s;
	p->ltag = 1;
	s->rch = p;
	s->rtag = 0;
	if (p->rtag == 0)
	{
		w = InPostNode(p);
		w->lch = p;
	}
}

ElemType ThreadTree::visElem(ThreadNode *cur)
{
	return cur->data;
}

ThreadNode *&ThreadTree::visRoot() {
	return root;
}

ThreadNode *ThreadTree::Root() {
	return root;
}

int main() {
	ThreadTree t;
	t.visRoot() = t.CreateTree();
	t.InOrder_Thread();
	t.InOrder(t.Root());
	cout << endl;
	char ch = 'E';
	cout << t.visElem(t.Search(t.Root(), ch)) << endl;
	return 0;

}
