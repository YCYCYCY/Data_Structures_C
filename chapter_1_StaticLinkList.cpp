#define MAXSIZE 1000
typedef struct
{
	ElemType data;
	int cur;
}Component,StaticLinkList[MAXSIZE];
Status InitList(StaticLinkList space)
{	
	for(i=0;i<MAXSIZE-1;i++)
		space[i].cur=i+1;
	space[MAXSIZE-1].cur=0;	
	//数组最后一个元素的cur用来存放第一个插入元素的下标，相当于头结点
	return OK;
}
int Malloc_SLL(StaticLinkList apace)
{
	int i =space[0].cur;
	if(space[0].cur)
		space[0].cur=space[i].cur;
	return i;
}
Status ListInsert(StaticLinkList L,int i,ElemType e)
{
	int  j,k,l;
	k=MAXSIZE-1;
	if(i<1 || i>ListLength(L)+1)
		return ERROR;
	j=Malloc_SSL(L);
	if(j)
	{
		L[j].data =e;
		for(l=1;l<=i-1;i++)	//找到第i个元素之前的位置
			k=L[k].cur;
		L[j].cur =L[k].cur;
		L[k].cur=j;
		return OK;
	}
	return ERROR;
}
Status ListDelete(StaticLinkList L,int i)
{
  int j,k;
  if(i<1 ||i>ListLength(L))
    return EROOR;
  k=MAXSIZE-1;
  for(j=1;j<=i-1;j++)
    k=L[k].cur;
  j=L[k].cur;
  L[k].cur=L[j].cur;
  Free_SSL(L,j);
  return OK;
}
void Free_SSL(StaticLinkList space,int k)
{
  space[k].cur=space[0].cur;
  space[0].cur=k;
}
int ListLength(StaticLinkList L)
{
  int j=0;
  int i=L[MAXSIZE-1].cur;
  while(i)
  {
    i=L[i].cur;
    j++;
  }
  return j;
}
