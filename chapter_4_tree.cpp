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
int depth(BiTNode* T)
{
	if(T == null)
		return 0;
	int ld = depth(phead->lchild);
	int rd = depth(phead->rchild);
	return (ld>rd)?ld:rd + 1;
}
//先序遍历递归实现
Status PreOrderTraverse(BiTree T,Status (*Visit)(TElemType e))	
{
	if(T!=NULL)
	{
		Visit(T->data);
		PreOrderTraverse(T->lchild,visit);
		PreOrderTraverse(T->rchild,visit);
	}
}
void PreOrderTraverse_(BiTree T, Status (*Visit)(TElemType e))
{
	stack<BiTNode> s;
	BiTree p=T;
	while(p!=NULL ||!s.empty())
	{
		while(p!=NULL)
		{
			Visit(p->data);
			s.push(p);
			p=p->lchild;
		}
		while(!s.empty())
		{
			p=s.top();
			s.pop();
			p=p->rchild; 
		}
	}
}
//中序遍历
Status InOrderTraverse(BiTree T,Status (*Visit)(TElemType e))
{
	if(T!=NULL)
	{
		InOrderTraverse(T->lchild,Visit);
		Visit(T->data);
		InOrderTraverse(T->rchild,Visit);
	}
}
Status InOrderTraverse_(BiTree T,Status (*Visit)(TElemType e))
{
	stack<BiTNode> s;
	BiTree p=T;
	while(p!=NULL||!s.empty())
	{
		while(p!=NULL)
		{
			s.push(p);
			p=p->lchild;
		}
		while(!s.empty())
		{
			p=s.top();
			s.pop();
			Visit(p->data);
			p=p->rchild;
		}
	}
}
//后序遍历
Status PostOrderTraverse(BiTree T,Status (*Visit)(TElemType e))
{
	if(T!=NULL)
	{
		PostOrderTraverse(T->lchild,Visit);
		PostOrderTraverse(T->rchild,Visit);
		Visit(T->data);
	}
}
Status PostOrderTraverse_(BiTree T,Status (*Visit)(TElemType e))
{
	stack<BiTNode>s;
	BiTree *cur;
	biTree *pre=NULL;
	s.push(T);
	while(!s.empty())
	{
		cur=s.top();
		if((cur->lchild==NULL&&cur->rchild==NULL)||
			(pre!=NULL&&(pre==cur->lchild||pre==cur->rchild)))
		{
			Visit(cur->data);
			s.pop();
			pre=cur;
		}
		else
		{
			if(cur->rchild!=NULL)
				s.push(cur->rchild);
			if(cur->lchild!=NULL)
				s.push(cur->lchild);
		}
	}
}
//层序遍历
Status LevelOrderTraverse(BiTree T,Status (*Visit)(TElemType e))
{
	
	BiNode node[MAXSIZE];
	node[0]=T;
	int cur=0;
	int pos=cur;
	while(node[cur])
	{
		Visit(node[cur]->data);
		if(node[cur]->lchild)
			node[++pos]=node[cur]->lchild;
		if(node[cur]->rchild)
			node[++pos]=node[cur]->lchild;
		++cur;
	}
}

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


//线索二叉树
typedef enum PointerTag {Link,Thread};//Link==0，指针；Thread==1，线索。
typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode *lchild,*rchild;
	PointerTag LTag,Rtag;
}BiThrNode,*BiThrTree;
//添加一个头结点，其lchild域的指针指向二叉树的根节点，其rchild域的指针指向中序遍历时访问的最后一个节点
//这好比为二叉树建立了一个双向线索链表
Status InOrderTraverse_Thr(BiThrTree T,Status (*Visit)(TElemType e))
{
	//T指向头结点，头结点的左链lchild指向根结点
	p=T->lchild;
	while(p!=T)
	{
		while(p->LTag==Link)
			p=p->lchild;
		Visit(p->data);
		while(p->RTag==Thread && p->rchild!=T)
		{
			p=p->rchild;
			Visit(p->data);
		}
		p=p->rchild;
	}
	return OK;
}

//二叉树线索化
Status InOrderThreading(BiThrTree &Thrt,BiThrTree T)
{
	if(!(Thr=(BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
	Thr->LTag=Link;
	Thr->RTag=Thread;
	Thr->rchild=Thr;
	if(!T)
		Thr->lchild=Thr;
	else
	{
		Thr->lchild=T;
		pre=Thrt;
		InThreading(T);
		pre->rchild=Thrt;//最后一个结点线索化
		pre->RTag=Thread;
		Thrt->rchild=pre;
	}
	return OK;
}
void InThreading(BiThrTree p)
{
	if(p)
	{
		InThread(p->lchild);
		if(!p->lchild)
		{
			p->LTag=Thread;
			p->lchild=pre;
		}
		if(!pre->rchild)
		{
			pre->RTag=Thread;
			pre->rchild=p;
		}
		pre=p;
		InThreading(p->rchild);
	}
}

//树的存储结构
//双亲表示法
//一组连续空间存储树的结点
#define MAX_TREE_SIZE 100
typedef struct PTNode	//结点结构
{
	TElemType data;
	int parent;		//双亲位置域
}PTNode;
typedef struct		//树结构
{
	PTNode nodes[MAX_TREE_SIZE];
	int r,n;		//跟的位置和结点数
}PTree;
//孩子表示法
typedef struct CTNode	//child node
{
	int child;
	struct CTNode *next;
}*ChildPtr;
typedef struct
{
	TElemType data;
	ChildPtr firstchild;	//孩子链表头指针
}CTBox;
typedef struct 
{
	CTBox node[MAX_TREE_SIZE];
	int n,r;
}CTree;
//孩子兄弟表示法
typedef struct CSNode
{
	ElemType data;
	struct CSNode *firstchild,*nextsibing;
};


//森林与二叉树的转换
//孩子兄弟表示法
//森林的先序和中序遍历即为其对应二叉树的先序和中序遍历

//赫夫曼树(Huffman)的构造过程
/*
1 根据给定的n个权值构成n棵二叉树的集合F。
2 在F中选取两棵根节点的权值最小的数作为左右子树构造一颗新的二叉树，且新的二叉树的根节点的权值为其左右子树上根节点的权值之和。
3 在F中删除这两棵子树，将新得到的二叉树加入F中。
4 重复步骤2和3，知道F中所有二叉树都合并为止。
*/
typedef struct 
{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;	//动态分配数组存储赫夫曼树
typedef char ** HuffmanCode;	//动态分配数组存储赫夫曼编码表
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
//w存放n个字符的权值，构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
{
	if(n<=1) return;
	m=2*n-1;//合并n-1次，故共有2n-1个元素
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));//0号单元不用
	for(p=HT+1,i=1;i<=n;++i,++p,++w)	//从1号单元开始，初始化为各个字符的权值
		*p={*w,0,0,0};
	for(;i<=m;++i,++p)	*p={0,0,0,0};
	for(i=n+1;i<=m;++i)	//建赫夫曼树
	{
		//在HT[1...i-1]中选择parent=0且weight值最小的两个节点，期序号分别为s1和s2.
		Select(HT,i-1,s1,s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}

	//从叶子到根逆向求每个字符的赫夫曼编码
	HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
	cd=(char*)malloc(n*sizeof(char));
	cd[n-1]='\0';
	for(i=1;i<=n;++i)
	{
		start=n-1;
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)//从叶子节点到根逆向求编码
			if(HT[f].lchild==c)		cd[--start]='0';
			else cd[--start]='1';
		HC[i]=(char *)malloc((n-start)*sizeof(char));	//为第i个字符编码分配空间
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
}
//赫夫曼编码
