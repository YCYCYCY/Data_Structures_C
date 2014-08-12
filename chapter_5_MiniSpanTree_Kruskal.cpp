typedef struct    //边集数组Edge结构的定义
{
  int begin;
  int end;
  int weight;
}Edge;
MAXEDGE 15  //边数量的极大值
MAXVEX 9    //顶点个数最大值
void MiniSpanTree_Kruskal(MGraph G)
{
  int i,n,m;
  Edge edges[MAXEDGE];  //定义边集数组
  int parent[MAXVEX];   //定义一数组用来判断边与边是否形成环路
  //此处省略將邻接矩阵G转化未边集数组edges并按权由大到小排序的代码
  for(i=0;i<G.numVertexes;i++)
    parent[i]=0;        //初始化数组值为0
  for(i=0;i<G.numVertexes;i++)  //循环每一条边
  {
    n=Find(parent,edges[i].begin);  //寻找边起点所在子树的根节点
    m=Find(parent,edges[i].end);    //寻找边终点所在子树的根节点
    if(n!=m)    //假如n与m不等，说明这条边的起点和终点不在同一子树中
    {
      parent[n]=m;
      print("(%d,%d) %d",edges[i].begin,edges[i].end,edges[i].weight);
    }
  }
}
int Find(int *parent,int f)   //寻找根节点
{
  while(parent[f]>0)
    f=parent[f];
  return f;
}
