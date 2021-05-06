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
