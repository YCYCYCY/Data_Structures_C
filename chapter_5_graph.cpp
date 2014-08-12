//�ڽӾ����ʾ��
typedef char VertexType;
typedef int EdgeType;
#define MAXVEX 100
#define INFINITY 65535
typedef struct MGraph
{
  VertexType vexs[MAXVEX];      //�����
  EdgeType arc[MAXVEX][MAXVEX]; //�ڽӾ���
  int numVertexes,numEdges;     //�������ͱ���
}��
void CreateMGraph(MGraph *G)
{
  int i,j,k,w;
  printf("input numbers of vexs and arc:\n");
  scanf("%d,%d",&G->numVertexes,&G->numEdges);
  for(i=0;i<G->numVertexes;++i)
    scanf(&G->vexs[i]);
  for(i=0;i<G->numVertexes;i++) //�ڽӾ����ʼ��
    for(j=0;j<G->numVertexes;j++)
    {
      if(j==i)
        G->arc[i][j]=0;
      else
        G->arc[i][j]=INFINITY;
    }
  for(k=0;k<G->numVertexes;k++) //����Ȩֵ
  {
    printf("�����(vi,vj)�ϵ��±�i���±�j��Ȩw:\n");
    scanf("%d,%d,%d",&i,&j,&w);
    G->arc[i][j]=w;
    G->arc[j][i]=G->arc[i][j];  //����ͼ
  }

}



//�ڽӱ��ʾ��
typedef char VertexType;
typedef int EdgeType;
typedef struct EdgeNode //�߱�ڵ�
{
  int adjvex; //�±�
  EdgeType weight;
  struct EdgeNode *next;  //��һ���ڽӵ�
}EdgeNode;
typedef struct VertexNode //�����ڵ�
{
  VertexType data;        //������
  EdgeNode *firstedge;    //�߱�ͷָ��
}VertexNode,AdjList[MAXVEX];
typedef struct
{
  AdjList adjList;
  int numVertexes,numEdges; //�������ͱ���
}GraphAdjList;
void CreateALGraph(GraphAdjList *G)
{
  int i,j,k;
  EdgeNode *e;
  printf("���붥�����ͱ�����\n");
  scanf("%d,%d",&G->numVertexes,&G->numEdges);
  for(i=0;i<G->numVertexes;i++)
  {
    scanf(&G->adjList[i].data);
    G->adjList[i].firstedge=NULL;
  }
  for(k=0;k<G->numVertexes;++k)
  {
    printf("�����(vi,vj)�ϵĶ������:\n");
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