#include <iostream>
using namespace std;
typedef int KeyType;

class BinSTreeNode
{
	friend class BinSTree;
private:
	KeyType key;
	BinSTreeNode *lchild;
	BinSTreeNode *rchild;
	BinSTreeNode() :lchild(nullptr), rchild(nullptr) {};
};

class BinSTree
{
public:

	BinSTree() :root(nullptr) {};
	~BinSTree()
	{
		DeleteTree();
	};
	void CreateTree();
	BinSTreeNode *BSTreeSearch_1(BinSTreeNode *bt, KeyType k, BinSTreeNode *&p);//非递归写法
	BinSTreeNode *BSTreeSearch_2(BinSTreeNode *bt, KeyType k, BinSTreeNode *&p);//递归写法
	void BSTreeInsert(BinSTreeNode *&bt, KeyType k);
	void Destroy(BinSTreeNode *current);
	void InorderTree();
	bool BSTreeDelete(BinSTreeNode *&bt, KeyType k);
	BinSTreeNode *&Get_Root()
	{
		return root;
	}
	void DeleteTree()
	{
		Destroy(root);
		root = nullptr;
	};
private:
	BinSTreeNode *root;
	void Inorder(BinSTreeNode *cur);
};


//BSTreeSearch_1,BSTreeSearch_2
//在根指针为bt的二叉排序树中查找元素为k的结点，
//若查找成功，则返回指向该结点的指针，参数p指向查找到的结点;
//否则返回空指针，参数p指向k应插入的父结点，p为指针的引用

BinSTreeNode *BinSTree::BSTreeSearch_1(BinSTreeNode *bt, KeyType k, BinSTreeNode *&p)
{
	BinSTreeNode *q;
	q = bt;
	while (bt)
	{
		q = bt;
		if (bt->key == k)
		{
			p = bt;
			return bt;
		}
		if (bt->key > k) bt = bt->lchild;
		else bt = bt->rchild;
	}
	p = q;
	return bt;
}

BinSTreeNode *BinSTree::BSTreeSearch_2(BinSTreeNode *bt, KeyType k, BinSTreeNode *&p)
{
	if (bt == nullptr) return bt;
	if (bt->key == k)
	{
		p = bt;
		return bt;
	}
		p = bt;
		if (bt->key > k) BSTreeSearch_2(bt->lchild, k, p);
		else BSTreeSearch_2(bt->rchild, k, p);
}


void BinSTree::BSTreeInsert(BinSTreeNode *&bt, KeyType k)
{
	BinSTreeNode *p = nullptr, *q, *r;
	q = bt;
	if (BSTreeSearch_1(q, k, p) == nullptr)
	{
		r = new BinSTreeNode;
		r->key = k;
		r->lchild = r->rchild = nullptr;
		if (p == nullptr) bt = r;//p == nullptr为该BST树一个节点都没有的情况
		else if (k < p->key) p->lchild = r;
		else p->rchild = r;
	}
}

/*在二叉排序树中删除一个结点时，需保证删除后的二叉树仍然是二叉排序树。
为讨论方便，假定被删除结点为p，其双亲结点为f。删除的过程可按下述的两种情况分别处理。
(1)如果被删除的结点没有左子树，则只需把结点f指向p的指针改为指向p的右子树。
(2)如果被删除的结点p有左子树，则删除结点p时，
从结点p的左子树中选择结点值最大的结点s（其实就是p的左子树中最右下角的结点，
该结点s可能有左子树，但右子树一定为空），用结点s替换结点p（把s的数据复制到p中），
再将指向结点s的指针改为指向结点s的左子树即可。
*/

bool BinSTree::BSTreeDelete(BinSTreeNode *&bt, KeyType k)
{
	BinSTreeNode *f, *p, *q, *s;
	p = bt;
	f = nullptr;
	while (p && p->key != k)
	{
		f = p;
		if (p->key > k) p = p->lchild;
		else p = p->rchild;
	}
	if (p==nullptr) return false;
	if (p->lchild == nullptr)
	{
		if (f == nullptr) bt = p->rchild;
		else if (f->lchild == p) f->lchild = p->rchild;
		else f->rchild = p->rchild;
		delete p;
		return true;
	}
	else
	{
		q = p;
		s = p->lchild;
		while (s->rchild)
		{
			q = s;
			s = s->rchild;
		}
		if (q == p) q->lchild = s->lchild;
		else q->rchild = s->lchild;
		p->key = s->key;
		delete s;
		return true;
	}
}



void BinSTree::Inorder(BinSTreeNode *cur)
{
	if (cur)
	{
		Inorder(cur->lchild);
		cout << cur->key << " ";
		Inorder(cur->rchild);
	}
}

void BinSTree::InorderTree()
{
	Inorder(root);
	cout << endl;
}

void BinSTree::Destroy(BinSTreeNode *cur)
{
	if (cur)
	{
		Destroy(cur->lchild);
		Destroy(cur->rchild);
		delete cur;
		cur = nullptr;
	}
}

void BinSTree::CreateTree()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		BSTreeInsert(root, x);
	}
}

int main()
{
	BinSTree t;
	t.CreateTree();
	t.InorderTree();
	int k;
	cin >> k;
	t.BSTreeDelete(t.Get_Root(),k);
	t.InorderTree();
	return 0;
}
