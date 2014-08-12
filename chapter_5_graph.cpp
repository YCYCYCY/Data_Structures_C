//邻接矩阵表示法
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



//邻接表表示法
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