/*实现Prim算法，需设置两个辅助一维数组lowcost和closevertex。

 1. 其中lowcost用来保存集合V-U中各顶点与集合U中各顶点构成的边中具有最小权值的边的权值；
 2. 数组closevertex用来保存依附于该边的在集合U中的顶点。


过程:
假设初始状态时，U={u0}（u0为出发的顶点），这时有lowcost[0]=0，它表示顶点u0已加入集合U中，数组lowcost的其他各分量的值是顶点u0到其余各顶点所构成的直接边的权值。
然后不断选取权值最小的边（ui,uk）（ui∈U,uk∈V-U），每选取一条边，就将lowcost（k）置为0，表示顶点uk已加入集合U中。
由于顶点uk从集合V-U进入集合U后，这两个集合的内容发生了变化，就需依据具体情况更新数组lowcost和closevertex中部分分量的内容。
最后closevertex中即为所建立的最小生成树。

*/




void MGraph::Min_Tree_Prim(int u)
{
	for (int i = 0; i < vertexnum; i++)
		if (i != u)
		{
			close_edge[i].adjvertex = u;
			close_edge[i].lowcost = arcs[u][i];
		}
	close_edge[u].lowcost = 0;
	int k;
	for (int i = 0; i < vertexnum - 1; i++)
	{
		int w = MAXW;
		for (int j = 0; j < vertexnum; j++)
		{
			if (close_edge[j].lowcost != 0 && close_edge[j].lowcost < w)
			{
				w = close_edge[j].lowcost;
				 k = j;
			}
		}
		close_edge[k].lowcost = 0;
		for (int j = 0;j<vertexnum;j++)
			if (arcs[k][j] < close_edge[j].lowcost)
			{
				close_edge[j].adjvertex = k;
				close_edge[j].lowcost = arcs[k][j];
			}
	}
	for (int i = 0; i < vertexnum; i++)
		if (i != u)
			cout << i << "->" << close_edge[i].adjvertex << "," << arcs[i][close_edge[i].adjvertex] << endl;
}
