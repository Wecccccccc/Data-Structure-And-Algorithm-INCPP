#include <iostream>
#include <queue>
using namespace std;
typedef int InfoType;
typedef int VertexType;
const int MaxVertexNum = 30;

class ArcNode
{
	friend class OLGraph;
	friend class VertexNode;
private:
	int tailvertex, headvertex;
	ArcNode *hlink, *tlink;
	InfoType info;
};

class VertexNode
{
	friend class OLGraph;
private:
	VertexType vertex;
	ArcNode *firstin, *firstout;
};

class OLGraph
{
public:
	OLGraph() {
		Init_vis();
	};
	void CreateOLgraph();
	int  GetOut_degree(VertexType v);
	int  GetIn_degree(VertexType v);
	void Init_vis()
	{
		for (int i = 0; i < MaxVertexNum; i++) vis[i] = false;//注意是MaxVertexNum，不是vertexNum
	};
	void DFS_Node(int i);
	void BFS_Node(int i);
	void DFStraverse();
	void BFStraverse();
	int LocateVertex(VertexType v);//通过结点信息查找其序号
	void Visit(int v)
	{
		cout << xlist[v].vertex << " ";
	};
private:
	void DFS(int  i);
	VertexNode xlist[MaxVertexNum];
	int vertexNum, edgeNum;
	bool vis[MaxVertexNum];
};


int OLGraph::LocateVertex(VertexType v)
{
	for (int i = 0; i < vertexNum; i++)
	{
		if (xlist[i].vertex == v) return i;
	}
}

void OLGraph::CreateOLgraph()
{
	ArcNode *p;
	cout << "请输入顶点数和边数" << endl;
	cin >> vertexNum >> edgeNum;
	for (int i = 0; i < vertexNum; i++)
	{
		cout << "请输入第" << i << "个顶点信息:" << endl;
		cin >> xlist[i].vertex;
		xlist[i].firstin = nullptr;
		xlist[i].firstout = nullptr;
	}
	cout << "下面输入边表信息" << endl;
	for (int i = 0; i < edgeNum; i++)
	{
		VertexType v1, v2;//v1--->v2
		cout << "输入边<i,j>对应的顶点信息i,j" << endl;
		cin >> v1 >> v2;
		int p_v1 = LocateVertex(v1);
		int p_v2 = LocateVertex(v2);
		p = new ArcNode;
		p->tailvertex = p_v1;
		p->headvertex = p_v2;
		p->tlink = xlist[p_v1].firstout;
		xlist[p_v1].firstout = p;
		p->hlink = xlist[p_v2].firstin;
		xlist[p_v2].firstin = p;
	}
}


int  OLGraph::GetOut_degree(VertexType v)
{
	int i = LocateVertex(v);
	ArcNode *p;
	int cnt = 0;
	for (p = xlist[i].firstout; p; p = p->tlink) cnt++;
	return cnt;
}

int OLGraph::GetIn_degree(VertexType v)
{
	int i = LocateVertex(v);
	ArcNode *p;
	int cnt = 0;
	for (p = xlist[i].firstin; p; p = p->hlink) cnt++;
	return cnt;
}

void OLGraph::DFS(int i)
{
	vis[i] = true;
	Visit(i);
	ArcNode *p;
	for (p = xlist[i].firstout; p; p = p->tlink)
	{
		if (!vis[p->headvertex])
		{
			vis[p->headvertex] = true;
			DFS(p->headvertex);
		}
	}
}

void OLGraph::DFS_Node(int i)
{
	DFS(i);
	cout << endl;
	Init_vis();
}

void OLGraph::BFS_Node(int i)
{
	queue<int>q;
	vis[i] = true;
	q.push(i);
	ArcNode *p;
	while (q.size())
	{
		int t = q.front();
		q.pop();
		Visit(t);
		for (p = xlist[t].firstout; p; p = p->tlink)
		{
			if (!vis[p->headvertex])
			{
				vis[p->headvertex] = true;
				q.push(p->headvertex);
			}
		}
	}
	cout << endl;
	Init_vis();
}

void OLGraph::DFStraverse()
{
	for (int i = 0; i < vertexNum; i++)
	{
		if (!vis[i])
		{
			vis[i] = true;
			DFS(i);
		}
	}
	cout << endl;
	Init_vis();
}

void OLGraph::BFStraverse()
{
	for (int i = 0; i < vertexNum; i++)
	{
		if (!vis[i])
		{
			queue<int>q;
			vis[i] = true;
			q.push(i);
			ArcNode *p;
			while (q.size())
			{
				int t = q.front();
				q.pop();
				Visit(t);
				for (p = xlist[t].firstout; p; p = p->tlink)
				{
					if (!vis[p->headvertex])
					{
						vis[p->headvertex] = true;
						q.push(p->headvertex);
					}
				}
			}
		}
	}
	cout << endl;
	Init_vis();
}

int main()
{
	OLGraph g;
	g.CreateOLgraph();
	cout << "bfs:" << endl;
	g.BFStraverse();
	cout << "dfs:" << endl;
	g.DFStraverse();
	VertexType  v;
	cin >> v;
	cout << "结点" << v << "的入度为:" << endl;
	cout<<g.GetIn_degree(v)<<endl;
	cout << "结点" << v << "的出度为:" << endl;
	cout << g.GetOut_degree(v) << endl;
	cin >> v;
	cout << "结点" << v << "的入度为:" << endl;
	cout << g.GetIn_degree(v) << endl;
	cout << "结点" << v << "的出度为:" << endl;
	cout << g.GetOut_degree(v) << endl;
	int p;
	cin >> p;
	g.BFS_Node(p);
	g.DFS_Node(p);
	return 0;
}
