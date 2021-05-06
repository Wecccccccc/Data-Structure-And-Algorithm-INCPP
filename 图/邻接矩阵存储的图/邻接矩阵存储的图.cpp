#include <iostream>
#include <queue>
using namespace std;
typedef int VertexType;
typedef int EdgeType;
const int MaxVertexNum = 30;

class MGraph
{
public:
	MGraph()
	{
		CreatGraph();
	};
	void CreatGraph();
	void Visit(int v);
	void BFS(int v);
	void BFStraverse();
	void DFStraverse();
	bool Ispath_BFS(int i, int j);//判断结点i和结点j之间是否有路径
	bool Ispath_DFS(int i, int j);//判断结点i和结点j之间是否有路径
	void Init_vis();
private:
	void DFS(int i, int j, bool &flag);
	void dfs_graph(int i);
	VertexType vertexs[MaxVertexNum];
	EdgeType arcs[MaxVertexNum][MaxVertexNum];
	int vertexnum;
	int edgenum;
	bool vis[MaxVertexNum];
};


void MGraph::CreatGraph()
{
	Init_vis();
	int a1, a2;
	cout << "请输入图的顶点个数和边的条数" << endl;
	cin >> vertexnum >> edgenum;
	cout << "请依次输入按序号0到n顶点的中存储的信息" << endl;
	for (int i = 0; i < vertexnum; i++) cin >> vertexs[i];
	for (int i = 0; i < vertexnum; i++)
		for (int j = 0; j < vertexnum; j++)
			arcs[i][j] = 0;
	cout << "请输入边的信息(该图以有向图的邻接矩阵存储方式存储)" << endl;
	for (int i = 0; i < edgenum; i++)
	{
		cin >> a1 >> a2;
		arcs[a1][a2] = 1;
		//若加入arcs[a2][a1] = 1，则为无向图
	}
}

void MGraph::Init_vis()
{
	for (int i = 0; i < MaxVertexNum; i++) vis[i] = false;
}

void MGraph::Visit(int v)
{
	cout << vertexs[v] << " ";
}

void MGraph::BFS(int v)
{
	queue<int >q;
	q.push(v);
	vis[v] = true;
	while (q.size())
	{
		int t = q.front();
		Visit(t);
		q.pop();
		for (int i = 0; i < vertexnum; i++)
		{
			if (arcs[t][i] == 1 && vis[i] == false)
			{
				vis[i] = true;
				q.push(i);
			}
		}
	}
	cout << endl;
	Init_vis();
}

void MGraph::BFStraverse()
{
	queue<int >q;
	for (int i = 0; i < vertexnum; i++)
	{
		if (vis[i] == false)
		{
			vis[i] = true;
			q.push(i);
			while (q.size())
			{
				int t = q.front();
				Visit(t);
				q.pop();
				for (int j = 0; j < vertexnum; j++)
					if (arcs[t][j] == 1 && vis[j] == false)
					{
						vis[j] = true;
						q.push(j);
					}
			}
		}
	}
	cout << endl;
	Init_vis();
}


void MGraph::dfs_graph(int i)
{
		Visit(i);
		for (int j = 0; j < vertexnum; j++)
		{
			if (arcs[i][j] == 1 && vis[j] == false)
			{
				vis[j] = true;
				dfs_graph(j);
			}
		}
}

void MGraph::DFStraverse()
{
	for (int i = 0; i < vertexnum; i++)
	{
		if (vis[i] == false)
		{
			vis[i] = true;
			dfs_graph(i);
		}
	}
	cout << endl;
	Init_vis();
}




bool MGraph::Ispath_BFS(int i, int j)
{
	queue<int >q;
	vis[i] = true;
	q.push(i);
	while (q.size())
	{
		int t = q.front();
		q.pop();
		if (t == j)
		{
			Init_vis();
			return true;
		}
		for (int k = 0; k < vertexnum; k++)
		{
			if (arcs[t][k] == 1 && vis[k] == false)
			{
				vis[k] = true;
				q.push(k);
			}
		}
	}
	Init_vis();
	return false;
}



void MGraph::DFS(int i, int j, bool &flag)
{
	if (i == j)
	{
		flag = true;
		return;
	}
	for (int k = 0; k < vertexnum; k++)
	{
		if (arcs[i][k] == 1 && vis[k] == false)
		{
			vis[k] = true;
			DFS(k, j, flag);
			vis[k] = false;
		}
	}
}

bool MGraph::Ispath_DFS(int i, int j)
{
	bool flag = false;
	vis[i] = true;
	DFS(i, j, flag);
	Init_vis();
	if (flag) return true;
	else return false;
}


int main()
{
	MGraph g;
	int v;
	cin >> v;
	g.BFS(v);
	g.BFStraverse();
	g.DFStraverse();
		int a,b, c;
		while (cin >> a >> b >> c, a)
		{
			if (a == 1)
				if (g.Ispath_BFS(b, c)) cout << "bfs:" << b << " and " << c << "yes" << endl;
				else cout << "bfs:" << b << " and  " << c << "no" << endl;
			else if (a == 2)
				if (g.Ispath_DFS(b, c)) cout << "dfs:" << b << " and " << c << "yes" << endl;
				else cout << "dfs:" << b << " and " << c << "no" << endl;
		}
	return 0;
}

