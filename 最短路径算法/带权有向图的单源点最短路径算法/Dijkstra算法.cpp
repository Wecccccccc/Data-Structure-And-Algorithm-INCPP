#include <iostream>
using namespace std;

const int MAXW = 30000;
const int MaxVertexNum = 30;
typedef int VertexType;
class MGraph
{
public:
	void CreateGraph();
	void ShortestPath_Dij(int v0);
	void Print_Path_Dij(int v0);

private:
	int vertexnum;
	VertexType vertexs[MaxVertexNum];
	int edgenum;
	int P[MaxVertexNum];
	int D[MaxVertexNum];
	int arcs[MaxVertexNum][MaxVertexNum];
};

void MGraph::CreateGraph()
{
	cout << "请输入节点数和边条数" << endl;
	cin >> vertexnum >> edgenum;
	for (int i = 0; i < vertexnum; i++)
		for (int j = 0; j < vertexnum; j++)
			arcs[i][j] = MAXW;
	cout << "请依次输入按序号0到n顶点的中存储的信息" << endl;
	for (int i = 0; i < vertexnum; i++)
	{
		cin >> vertexs[i];
	}
	cout << "下面输入边的信息" << endl;
	for (int i = 0; i < edgenum; i++)
	{
		int v1, v2, w;
		cout << "输入边<i,j>对应的顶点序号i,j,然后再输入该边的权值" << endl;
		cin >> v1 >> v2 >> w;
		arcs[v1][v2] = w;
	}
}

void MGraph::ShortestPath_Dij(int v0)
{
	bool f[MaxVertexNum];
	for (int v = 0; v <vertexnum; v++)
	{
		f[v] = false;
		D[v] = arcs[v0][v];
		P[v] = -1;
		if (D[v] < MAXW) P[v] = v0;
	}
	D[v0] = 0;
	f[v0] = true;
	for (int i = 0; i < vertexnum; i++)
	{
		int v = -1;
		int min = MAXW;
		for (int w = 0; w < vertexnum; w++)
			if (!f[w] && D[w] < min)
			{
				v = w;
				min = D[w];
			}
		if (v == -1) break;
		f[v] = true;
		for (int w = 0; w < vertexnum; w++)
		{
			if (!f[w] && (min + arcs[v][w] < D[w]))
			{
				D[w] = min+arcs[v][w];
				P[w] = v;
			}
		}
	}
}


void MGraph::Print_Path_Dij(int v0)
{
	cout << "The shortest path from Vertex:" << v0 << " to the other Vertex:" << endl;
	for (int v = 0; v < vertexnum; v++)
	{
		if (P[v] == -1)continue;
		cout << D[v] << " ";
		cout << v << "<=";
		int i = v;
		while (P[i] != -1)
		{
			cout << P[i] << "<=";
			i = P[i];
		}
		cout << endl;
	}
}


int main()
{
	MGraph g;
	g.CreateGraph();
	int v0;
	cin >> v0;
	g.ShortestPath_Dij(v0);
	g.Print_Path_Dij(v0);
	return 0;
}
