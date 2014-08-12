typedef int Pathmatirx[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];
void ShortestPath_Floyd(MGraph G,Pathmatirx *P,ShortPathTable *D)
{
	int v,w,k;
	for(v=0;v<G.numVertexes;++v)
	{
		for(w=0;w<G.numVertexes;++w)
		{
			(*D)[v][w]=G.matirx[v][w];
			(*P)[v][w]=w;
		}
	}
	for(k=0;k<G.numVerexes;++k)
	{
		for(v=0;v<G.numVertexes;++v)
		{
			for(w=0;w<G.numVertexes;++w)
			{
				if((*D)[v][w]>(*D)[v][k]+(*D)[k][w])
				{
					(*D)[v][w]=(*D)[v][k]+(*D)[k][w];
					(*P)[v][w]=(*P)[v][k];
				}
			}
		}
	}
}
//	求最短路径
for(v=0;v<G.numVextexes;++v)
{
	for(w=v+1;w<G.numVertexes;++w)
	{
		//点v到点w的路径
		k=P[v][w];
		printf("%d ",v);
		while(k!=w)
		{
			printf("%d ",k);
			k=P[k][w];
		}
		printf("%d ",w);
	}
	printf("\n");
}