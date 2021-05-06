#include <iostream>
#include <queue>

using namespace std;
const int MaxVertexNum = 30;
typedef int InfoType;
typedef int VertexType;

class Node
{
	friend class VNode;
	friend class ALGraph;
private:
	int adjvertex;
	InfoType info;
	Node *next;
};

class VNode
{
	friend class ALGraph;
private:
	VertexType vertex;
	Node *firstedge;
};

class ALGraph
{
public:
	void CreateALGraph();
	void DFStraverse();
	void BFStraverse();
	void DFS(int v);
	void BFS(int v);
	void Visit(int v)
	{
		cout << adjlist[v].vertex;
	}
private:
	VNode adjlist[MaxVertexNum];
	void Init_vis()
	{
		for (int i = 0; i < vertexnum; i++) vis[i] = false;
	}
	int vertexnum;
	int edgenum;
	int vis[MaxVertexNum];
};


void ALGraph::CreateALGraph()
{
	Node *p;
	cout << "请输入顶点数和边数" << endl;
	cin >> vertexnum >> edgenum;
	for (int i = 0; i < vertexnum; i++)
	{
		cout << "请输入第" << i << "个顶点信息:" << endl;
		cin >> adjlist[i].vertex;
		adjlist[i].firstedge = nullptr;
	}
	cout << "下面输入边表信息" << endl;
	for (int k = 0; k < edgenum; k++)
	{
		int i, j;
		cout << "输入边<i,j>对应的顶点编号i，j" << endl;
		cin >> i >> j;
		p = new Node;
		p->adjvertex = j;
		p->next = adjlist[i].firstedge;
		adjlist[i].firstedge = p;
	}
}

void ALGraph::DFStraverse()
{
	Init_vis();
	for (int i = 0; i < vertexnum; i++)
		if (!vis[i]) DFS(i);
	cout << endl;
}



void ALGraph::DFS(int v)
{
	Node *p;
	Visit(v);
	vis[v] = true;
	for (p = adjlist[v].firstedge; p; p = p->next)
	{
		int w = p->adjvertex;
		if (!vis[w]) DFS(w);
	}
}

void ALGraph::BFS(int v)
{
	Node *p;
	Init_vis();
	queue<int>q;
	q.push(v);
	vis[v] = true;
	while (q.size())
	{
		int t = q.front();
		q.pop();
		Visit(t);
		for (p = adjlist[t].firstedge; p; p = p->next)
		{
			int w = p->adjvertex;
			if (!vis[w])
			{
				vis[w] = true;
				q.push(w);
			}
		}
	}
}

void ALGraph::BFStraverse()
{
	queue<int>q;
	Node *p;
	Init_vis();
	for (int i = 0; i < vertexnum; i++)
	{
		if (!vis[i])
		{
			vis[i] = true;
			q.push(i);
			while (q.size())
			{
				int t = q.front();
				Visit(t);
				q.pop();
				for (p = adjlist[t].firstedge; p; p = p->next)
				{
					int w = p->adjvertex;
					if (!vis[w])
					{
						vis[w] = true;
						q.push(w);
					}
				}
			}
		}
	}
	cout << endl;
}

int main()
{
	ALGraph g;
	g.CreateALGraph();
	g.BFStraverse();
	g.DFStraverse();
	int n;
	cin >> n;
	g.DFS(n);
	cout << endl;
	g.BFS(n);
	cout << endl;
	cin >> n;
	g.DFS(n);
	cout << endl;
	g.BFS(n);
	cout << endl;
	return 0;
}
