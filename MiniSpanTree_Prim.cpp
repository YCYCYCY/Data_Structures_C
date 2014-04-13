/*
Prim算法生成最小生成树
创建一个数组lowcost[n]，用来存储已加入最小生成树的节点到各个未加入节点的最短距离，
然后从未加入节点中找出最短距离的那个节点，添加进最小生成树。
若节点i加入生成树，lowcost[i]=0
创建一个数组adjvex[n],用来存储最小生成树的连接关系。
adjvex[j]=k表示节点j通过k链接进最小生成树。
 */
void MiniSpanTree_Prim(MGraph G)
{
  int min,i,j,k;
  int adjvex[MAXVEX];
  int lowcost[MAXVEX];
  lowcost[0]=0; //加入第一个节点
  adjvex[0]=0;  //根节点的值设为0
  for(i=1;i<G.numVertexes;i++)
  {
    lowcost[i]=G.arc[0][i];//初始化lowcost数组，只有根节点加入最小生成树
    adjvex[j]=0;          //初始化adjvex数组
  }
  for(i=1;i<G.numVertexes;i++)
  {
    min=INFINITY;
    j=1;k=0;
    while(j<G.numVertexes)  //找出距离最短的那个节点
    {
      if(lowcost[j]!=0 && lowcost[j]<min)
      {
        min=lowcost[j];
        k=j;
      }
      j++;
    }
  }
  printf("(%d,%d)",adjvex[k],k);
  lowcost[k]=0; //节点k加入生成树
  for(j=1;j<G.numVertexes;++j)    //加入了新节点，更新lowcost数组和adjvex数组
  {
    if(lowcost[j]!=0 && G.arc[k][j]<lowcost[j])
    {
      lowcost[j]=G.arc[k][j];
      adjvex[j]=k;
    }

  }

}
