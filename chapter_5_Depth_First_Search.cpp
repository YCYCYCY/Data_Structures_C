/*************************************************************************
 > File Name: Depth_First_Search.cpp
 > Author:  何源川
 > Mail: 249288984@qq.com 
 > Created Time: 2014年04月08日 星期二 11时00分29秒
**************************************************************************/
//邻接矩阵的深度遍历和广度遍历
typedef char VertexType;
typedef int EdgeType;
#define MAXVEX 100
#define INFINITY 65535
typedef struct MGraph
{
  VertexType vexs[MAXVEX];      //顶点表
  EdgeType arc[MAXVEX][MAXVEX]; //邻接矩阵
  int numVertexes,numEdges;     //顶点数和边数
}；
void CreateMGraph(MGraph *G)
{
  int i,j,k,w;
  printf("input numbers of vexs and arc:\n");
  scanf("%d,%d",&G->numVertexes,&G->numEdges);
  for(i=0;i<G->numVertexes;++i)
    scanf(&G->vexs[i]);
  for(i=0;i<G->numVertexes;i++) //邻接矩阵初始化
    for(j=0;j<G->numVertexes;j++)
    {
      if(j==i)
        G->arc[i][j]=0;
      else
        G->arc[i][j]=INFINITY;
    }
  for(k=0;k<G->numVertexes;k++) //读入权值
  {
    printf("输入边(vi,vj)上的下表i，下表j和权w:\n");
    scanf("%d,%d,%d",&i,&j,&w);
    G->arc[i][j]=w;
    G->arc[j][i]=G->arc[i][j];  //无向图
  }

}
/*从图中某个顶点v出发，访问此顶点，然后从v的未访问的邻接点出发深度优先遍历图，直至图中所有和v有路径相同的顶点都被访问。对于非连通图，若图中尚有顶点未被访问，则另选图中一个未曾被访问的顶点作起始点，重复上述过程，直至图中所有顶点都被访问到为止。*/
typedef int Boolean;  
Boolean visited[MAX]; //访问标志
void DFS(MGraph G,int i)
{
  int j;
  visited[i]=TRUE;
  printf("%c ",G.vexs[i]);  //输出顶点
  for(j=0;j<G.numVertexes;j++)  //对顶点v的邻接点进行访问
  {
    if(i!=j && G.arc[i][j]!=INFINITY && !visited[j])
      DFS(G,j);
  }
}
void DFSTraverse(MGraph G)  //邻接矩阵的深度遍历操作
{
  int i;
  for (i=0;i<G.numVertexes;i++)
    visited[i]=FALSE; //初始化所有顶点都是未访问
  for(i=0;i<G.numVertexes;i++)
    if(!visited[i])   //若是连通图，只会执行一次
      DFS(G,i);
}


//邻接表的深度遍历和广度遍历
typedef char VertexType;
typedef int EdgeType;
typedef struct EdgeNode //边表节点
{
  int adjvex; //下标
  EdgeType weight;
  struct EdgeNode *next;  //下一个邻接点
}EdgeNode;
typedef struct VertexNode //顶点表节点
{
  VertexType data;        //顶点域
  EdgeNode *firstedge;    //边表头指针
}VertexNode,AdjList[MAXVEX];
typedef struct
{
  AdjList adjList;
  int numVertexes,numEdges; //顶点数和边数
}GraphAdjList;
void CreateALGraph(GraphAdjList *G)
{
  int i,j,k;
  EdgeNode *e;
  printf("输入顶点数和边数：\n");
  scanf("%d,%d",&G->numVertexes,&G->numEdges);
  for(i=0;i<G->numVertexes;i++)
  {
    scanf(&G->adjList[i].data);
    G->adjList[i].firstedge=NULL;
  }
  for(k=0;k<G->numVertexes;++k)
  {
    printf("输入边(vi,vj)上的顶点序号:\n");
    scanf("%d,%d",&i,&j);
    e=(EdgeNode *)malloc(sizeof(EdgeNode));
    e->adjvex=j;
    e->next=G->adjList[i].firstedge;
    G->adjList[i].firstedge=e;
    e=(EdgeNode*)malloc(sizeof(EdgeNode));
    e->adjvex=i;
    e->next=G->adjList[j].firstedge;
    G->adjList[j].firstedge=e;
  }
}
void DFS(GraphAdjList GL,int i)
{
  EdgeNode*p;
  visited[i]=TRUE;
  print("%c ",GL->adjList[i].data);
  p=GL->adjList[i].firstedge;
  while(p)
  {
    if(!visited[p-adjvex])
      DFS(GL,p->adjvex);
    p=p->next;
  }
}
void DFSTraverse(GraphAdjList GL)
{
  int i;
  for(i=0;i<GL->numVertexes;i++)
    visited[i]=FALSE;
  for(i=0;i<GL->numVertexes;i++)
    if(!visited[i])
      DFS(GL,i);
}
