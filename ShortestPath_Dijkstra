#define MAXVEX 9
#define INFINITY 65535
typedef int Patharc[MAXVEX]         //用于存储最短路径下标的数组
typedef int ShortPathTable[MAXVEX]  //用于存储到各点最短路径的权值和
//求有向网G中顶点v0到其余顶点v最短路径P[v]和带权长度D[v]
//P[v]的值为前驱顶点下标，D[v]表示v0到v的最短路径长度和
void ShortestPath_Dijkstra(MGraph G,int v0,Patharc *p,ShortPathTable *D)
{
  int v,w,k,min;
  int final[MAXVEX];  //final[w]=1表示求得顶点v0至vw的最短路径
  for (v=0;v<G.numVertexes;v++) //初始化数据
  {
    final[v]=0;
    (*D)[v]=G.arc[v0][v];
    (*p)[v]=0;
  }
  (*D)[v0]=0;   //v0至v0路径为0
  final[v0]=1;  //v0至v0的最短路径已求得
  //求v0到顶点v的最短路径
  for(v=1;v<G.numVertexes;++v)
  {
    min=INFINITY;
    for(w=0;w<G.numVertexes;++w)    //寻找离v0最近的顶点
    {
      if(!final[w] && (*D)[w]<min)  
      {
        k=w;
        min=(*D)[w];  
      }
    }
    final[k]=1;   //將找到的最近的顶点加入已找到列表中
    for(w=0;w<G.numVertexes;++w)
    {
      if(!final[w] && (min+G.arc[k][w]<(*D)[w]))
      {
        (*D)[w]=min+G.arc[k][w];
        (*P)[w]=k;
      }
    }
  }
}
//求顶点v0到任意顶点v的最短路径
int Search_ShortestPath_between(MGraph G,int v0,int v,int *ShortPath)
{

  ShortestPath_Dijkstra(G,v0,P,D);
  stack<int> s;
  s.push(v);
  int k=v;
  while(P[k]!=0)
  {
    s.push(P[k]);
  }
  s.push(v0);
  int i=0;
  while(!s.empty())
  {
    ShortPath[i]=s.top();
    s.pop();
  }
  return D[v];  //v0到v的最短路径和
}
