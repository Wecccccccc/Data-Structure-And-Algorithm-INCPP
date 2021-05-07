/*基本思想是：
假设求从顶点vi到vj的最短路径。

如果从vi到vj有弧，则从vi到vj存在一条长度为arcs[i][j]的路径，该路径不一定是最短路径，尚需进行n次试探。

首先考虑路径（vi, v0, vj）是否存在（判别弧（vi, v0）和（v0, vj）是否存在）。

如果存在，则比较（vi, vj）和（vi, v0, vj）的路径长度，取长度较短者为从vi到vj的中间顶点的序号不大于0的最短路径。

假如在路径上再增加一个顶点v1，也就是说，如果（vi, …, v1）和（v1, …, vj）分别是当前找到的中间顶点的序号不大于0的最短路径，
那么（vi, …, v1, … , vj）就有可能是从vi到vj的中间顶点的序号不大于1的最短路径。

将它和已经得到的从vi到vj中间顶点序号不大于0的最短路径相比较，从中选出中间顶点的序号不大于1的最短路径之后，再增加一个顶点v2，继续进行试探，依此类推。
在一般情况下，若（vi, …, vk）和（vk, …, vj）分别是从vi到vk和从vk到vj的中间顶点的序号不大于k-1的最短路径，
则将（vi, …, vk, …, vj）和已经得到的从vi到vj且中间顶点序号不大于k-1的最短路径相比较，其长度较短者便是从vi到vj的中间顶点的序号不大于k的最短路径。

这样，在经过n次比较后，最后求得的必是从vi到vj的最短路径。

按此方法，可以同时求得各对顶点间的最短路径。*/


#include <iostream>
using namespace std;

const int MAXW = 30000;
const int MaxVertexNum = 30;
typedef char VertexType;
class MGraph
{
public:
	void CreateGraph();
	void ShortestPath_Floyd();
	void Print_Path_Floyd(int v,int w);

private:
	int vertexnum;
	VertexType vertexs[MaxVertexNum];
	int edgenum;
	bool P[MaxVertexNum][MaxVertexNum][MaxVertexNum];
	int D[MaxVertexNum][MaxVertexNum];
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

void MGraph::ShortestPath_Floyd()
{//用Floyd算法求有向图G中各对顶点v和w之间的最短路径P[v][w]及其带权长度D[v][w]

	//若P[v][w][u] = 1，则u是从v到w当前求得的最短路径上的顶点

	for (int v = 0;v<vertexnum;v++)
		for (int w = 0; w < vertexnum; w++)
		{
			D[v][w] = arcs[v][w];
				for (int u = 0; u < vertexnum; u++) P[v][w][u] = 0;
			if (D[v][w] < MAXW)//从v到w有直接路径
			{
				P[v][w][v] = 1;
				P[v][w][w] = 1;
			}
		}
	for (int u = 0;u< vertexnum;u++)
			for (int v = 0;v<vertexnum;v++)
				for (int w = 0; w < vertexnum; w++)
				{
					if (D[v][u] + D[u][w] < D[v][w])
					{
						D[v][w] = D[v][u] + D[u][w];
						P[v][w][u] = 1;
					}
				}
}

void MGraph::Print_Path_Floyd(int v, int w)
{
	int i;
	for (i = 0; i < vertexnum; i++)
	if (i != v && i != w && P[v][w][i] == true) break;

		if (i >= vertexnum) cout << v << "->" << w << endl;
		else
		{
			Print_Path_Floyd(v, i);
			Print_Path_Floyd(i, w);
		}
}


int main()
{
	MGraph g;
	g.CreateGraph();
	g.ShortestPath_Floyd();
	int v, w;
	cin >> v >> w;
	g.Print_Path_Floyd(v, w);
	return 0;
}
