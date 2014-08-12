/*************************************************************************
 > File Name: Breadth_First_Search.cpp
 > Author:  何源川
 > Mail: 249288984@qq.com 
 > Created Time: 2014年04月08日 星期二 20时44分37秒
**************************************************************************/

void BFSTraverse(MGraph G)
{
  int i,j;
  Queue Q;
  for(i=0;i<G.numVertexes;i++)
    visited[i]=FALSE;
  InitQueue(&Q);
  for(i=0;i<G.numVertexes;++i)
  {
    if(!visited[i])
    {
      visited[i]=TRUE;
      printf("%c ",G.vexs[i]);
      EnQueue(&Q,i);
      while(!QueueEmpty(Q))
      {
        DeQueue(&Q,&i);
        for(j=0;j<G.numVertexes;j++)
        {
          if(G.arc[i][j]==1 && !visited[j])
          {
            visited[j]=TRUE;
            printf("%c ",G.vexs[j]);
            EnQueue(&Q,j);
          }
        }
      }
    }
  }
}
void BFSTraverse(GraphAdjList GL)
{
  int i;
  EdgeNode *p;
  Queue Q;
  for(i=0;i<GL->numVertexes;i++)
    visited[i]=FLASE;
  InitQueue(&Q);
  for(i=0;i<GL->numVertexes;i++)
  {
    if(!visited[i])
    {
      visited[i]=TRUE;
      printf("%c ",GL->adjList[i].data);
      EnQueue(&Q,i);
      while(!QueueEmpty(Q))
      {
        DeQueue(&Q,&i);
        p=GL->adjList[i].firstedge; //找到当前顶点边表链表头指针
        while(p)
        {
          if(!visited[p->adjvex]) //若此顶点未被访问
          {
            visited[p->adjvex]=TRUE;
            printf("%c ",GL->adjList[p->adjvex].data);
            EnQueue(&Q,p->adjvex);
          }
          p=p->next;
        }
      }
    }
  }
}
