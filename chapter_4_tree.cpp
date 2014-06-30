//二叉树
/*
性质1 在二叉树的第i层上至多有2^(i-1)个节点
性质2 深度为k的二叉树至多有2^k-1个节点
性质3 对任何一颗二叉树T，如果其终端节点数为n0,度为2的节点数为n2，则n0=n2+1。
性质4 具有n个结点的完全二叉树的深度位lgn+1
*/
//顺序存储结构
#define MAX_TREE_SIZE 100	//最多结点数
typedef TElemType SqBiTree[MAX_TREE_SIZE];
SqBiTree bt;
//链式存储结构
//二叉树的。链表中结点至少包含3个域:数据域和左、右指针域。
typedef struct BiTNode
{
  int data;
  struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
//先序遍历
Status PreOrderTraverse(BiTree T,Status (*Visit)(TElemType e))	
{
	if(T==NULL)
	{
		return true;
		
	}
	else
	{
		Visit(T->data);
		PreOrderTraverse(T->lchild,visit);
		PreOrderTraverse(T->rchild,visit);
	}
}
//中序遍历
Status InOrderTraverse(BiTree T,Status (*visit)(TElemType e));	
//后序遍历
Status PostOrderTraverse(BiTree T,Status (*Visit)(TElemType e));	
//层序遍历
Status LevelOrderTraverse(BiTree T,Status (*Visit)(TElemType e));	

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
bool Delete(BiTree *p)
{
  BiTree q,s;
  if((*p)->rchild==NULL)
  {
    q=*p;
    *p=(*p)->lchild;
    free(q);

  }
  else if((*p)->lchild==NULL)
  {
      q=*p;
      *p=(*p)->rchild;
      free(q);
  }
  else
  {
      q=*p;
      s=(*p)->lchild;
      while(s->rchild)
      {
        q=s;
        s=s->rchild;
      }
      (*p)->data=s->data;
      if(q!=*p)
        q->rchild=s->lchild;
      else
        q->lchild=s->lchild;
      free(s);
  }
  return true;
}
bool delete_bitree(BiTree *T,int key)
{
	if(key==(*T)->data)
		Delete(T);
	else if(key<(*T)->data)
		delete_bitree(&(*T)->lchild,key);
	else 
		delete_bitree(&(*T)->rchild,key);
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
  BiTree  t ;
  create_bitree(data,length,&t);
  int key=88;
  BiTNode *p=SearchBST(*t,key);
  printf("%d,%d,%d",p->data,p->lchild->data,p->rchild->data);
  return 0;
}