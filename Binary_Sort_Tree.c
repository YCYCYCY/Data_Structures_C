#include<stdio.h>
#include<iostream>
typedef struct BiTNode
{
  int data;
  struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

//向二叉树中插入元素
void insert_bitree(BiTNode *p,BiTree *T)
{
  BiTNode *temp=*T;
  if(!T)
    *T=p;
  else if(temp->data>p->data)
  {
    if(temp->lchild)
      insert_bitree(p,&temp->lchild);
    else
      temp->lchild=p;
  }
  else if(temp->data<p->data)
  {
    if(temp->rchild)
      insert_bitree(p,&temp->rchild);
    else
      temp->rchild=p;
  }
}
//由数组构造二叉树
void create_bitree(int *data,int size,BiTree *T)
{
  BiTNode *pNode;
  for(int i=0;i<size;++i)
  {
    pNode=(BiTNode *)malloc(sizeof(BiTNode));
    pNode->data=data[i];
    pNode->lchild=NULL;
    pNode->rchild=NULL;
    insert_bitree(pNode,T);
    
  }
}
BiTNode* SearchBST(BiTree T,int key)
{
  if(!T)
    return NULL;
  else if(key==T->data)
  {
    return T;
  }
  else if(key>T->data)
    return SearchBST(T->rchild,key);
  else
    return SearchBST(T->lchild,key);
}
int main()
{
  int data[]={62,88,58,47,35,73,51,99,37,93};
  int length=sizeof(data)/sizeof(int);
  BiTree *t=NULL;
  create_bitree(data,length,t);
  int key=88;
  BiTNode *p=SearchBST(*t,key);
  printf("%d,%d,%d",p->data,p->lchild->data,p->rchild->data);
  return 0;
}
