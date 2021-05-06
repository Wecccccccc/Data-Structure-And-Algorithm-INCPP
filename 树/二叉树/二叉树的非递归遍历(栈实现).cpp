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
