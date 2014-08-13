#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))
ADT StaticSearchTable{
	Create(&ST,n);
	Destroy(&ST);
	Search(ST,key);
	Traverse(ST,Visit());
}ADT StaticSearchTable
//顺序查找
int Search_Seq(SSTable ST,KeyType key)
{
	ST.elem[0].key=key;
	for(i=ST.length;!EQ(ST.elem[i].key,key);--i);
	return i;
}
//有序表的二分查找
int Search_Bin(SStable ST,KeyType key)
{
	low=1;
	high=ST.length;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(EQ(key,ST.elem[mid].key))	return mid;
		else if(LT(key,ST.elem[mid].key))	high=mid-1;
		else low=mid+1;
	}
	return 0;
}
//递归方式
int Search_Bin(SStable ST,KeyType key,int low,int high)
{

	mid=(low+high)/2;
	if(EQ(key,ST.elem[mid].key))	return mid;
	else if(LT(key,ST.elem[mid].key))	Search_Bin(ST,key,low,mid-1);
	else Search_Bin(ST,key,mid+1,high);
}
//当有序表中各记录的查找概率不相等时，应使用静态最优查找树。
//但构造静态最优查找树花费的时间代价较高，所以用次优查找树来代替。
//次优查找树
void SecondOptimal(BiTree &T,ElemType R[],float sw[],int low,int high)
{
	i=low;
	min=abs(sw[high]-sw[low]);
	dw=sw[high]+sw[low-1];
	for(j=low+1;j<=high;++j)
	{
		if(abs(dw-sw[j]-sw[j-1])<min)
		{
			i=j;
			min=abs(dw-sw[j]-sw[j-1]);
		}
	}
	T=(BiTree)malloc(sizeof(BiTNode));
	T->data=R[i];
	if(i==low)
		T->lchild=NULL;
	else
		SecondOptimal(T->lchild,R,sw,low,i-1);
	if(i==high)
		T->rchild=NULL;
	else
		SecondOptimal(T->rchild,R,sw,i+1,high);
}


//索引顺序表
//又叫做分块查找，建立一个索引表，其中包括两项内容：关键字项（子表中的最大关键字）和指针项（指示该子表的第一个记录在表中位置）
//可以先用二分查找索引表确定记录所在的块，然后在块中顺序查找。




//动态查找
//若表中存在其关键字等于key的记录，则查找成功返回。否则插入关键字等于key的记录。

//二叉排序树：左子树上所有结点的值均小于它的根节点的值，右子树上所有结点的值均大于根节点的值
//查找
Status SearchBST(BiTree T,KeyType key,BiTree f,BiTree &p)
//在二叉排序树T中查找key。若查找成功，则p指向该数据元素结点，并返回TRUE。否则，p指向查找路径上访问的最后一个结点并返回FALSE。f为T节点的双亲。
{
	if(!T)
	{
		p=f;
		return FALSE;
	}
	else if (EQ(key,T->data.key))
	{
		p=T;
		return T;
	}
	else if(LT(key,T->data.key))return SearchBST(T->lchild,key,T,p);
	else  return SearchBST(T->rchild,key,T,p);
}
Status InsertBST(BiTree &T,ElemType e)
{
	if(!SearchBST(T,e.key,NULL,p)){
		s=(BiTree)malloc (sizeof(BiTNode));
		s->data=e;
		s->lchild=s->rchild=NULL;
		if(!p)T=s;
		else if(LT(e.key,p->data.key))p->lchild=s;
		else p->rchild=s;
		return TRUE;
	}
	else 
		return FALSE;
}
//删除节点
/*
假设在二叉排序树上被删除节点为*p，其双亲节点为*f，且不是一般性，可设*p是*f的左孩子
（1）若*p节点为叶子节点，即PL和PR为空树，只需修改其双亲节点的指针即可。
（2）若*p节点只有左子树或者只有右子树，则令左子树或右子树直接成为其双亲节点*f的左子树即可。
（3）若*p节点的左右子树都不空，有以下两种方法处理：
一、令*p的左子树为*f的左子树，而*p的右子树为*s的右子树
二、令*p的直接前驱替代*p，然后再从二叉排序树中删除它的直接前驱。
*/
Status DeleteBST(BiTree &T,KeyType key)
{
	if(!T)	return FALSE;
	else
	{
		if(EQ(key,T->data.key))
			return Delete(T);
		else if(LT(key,T->data.key))
			return DeleteBST(T->lchild,key);
		else
			return DeleteBST(T->rchild,key);
	}
}
Status Delete(BiTree &p)
{
	if(!p->rchild)	//右子树为空
	{
		q=p->lchild;
		p->data=q->data;
		free(q);
	}
	else if(!p->lchild)
	{
		q=p->rchild;
		p->data=q->data;
		free(q);
	}
	else
	{
		q=p;
		s=p->lchild;
		while(s->rchild)
		{
			q=s;
			s=s->rchild;
		}
		p->data=s->data;
		if(q!=p)
			q->rchild=s->lchild;
		else
			q->lchild=s->lchild;
		delete s;
	}
	return true;
}




//B-树 阶数和深度不一样
/*
一棵m阶的B-树，满足一下条件：
1 树中每个结点至多有m棵子树
2 若根结点不是叶子节点，则至少有2棵子树。
3 除根之外的所有非终端结点至少有m/2棵子树。
4 所有的非终端结点中包含下列信息数据
	(n,A0,K1,A1,K2,A2,...Kn,An)
其中，Ki为数据，且K1<K2<..<Kn;Ai为指向子树根结点的指针，且Ai-1所指子树中所有结点的关键字小于Ki,Ai所指子树中所有节点的关键字均大于Ki，n为数据个数。
5 所有的叶子节点都出现在同一层次上，并且不带信息。
*/
#define m 3	//B-树的阶，设为3
typedef struct BTNode
{
	int  keynum;//节点中关键字的个数
	struct BTNode *parent;
	KeyType key[m+1];	//关键字向量，0号单元未用
	struct BTNode *ptr[m+1];	//子树指针向量
	Record *recptr[m+1];		//记录指针向量，0号单元未用
}BRNode,*BTree;
typedef struct 
{
	BTNode *p;	//指向找到的节点
	int i;		//在结点中的关键字序号
	int tag;	//查找成功为1，否则为0
}Result;
Result SearchBTree(BTree T,KeyTree K){
	//在m阶B-树T上查找关键字K，返回结果（pt,i,tag）。若查找成功，则特征值tag=1，指针pt所指结点中第i个关键字等于k；
	//否则特征值tag=0，等于k的关键字应插入在指针pt所指结点中第i和第i+1个关键字之间
	p=T;q=NULL;
	found=FALSE;
	i=0;
	while(p&&!found){
		i=Search(p,k);	//在p->key[1...keynum]中查找i,使得：p->key[i]<= K <=p->key[i+1]
		if(i>0&&p->key[i]==k)	found=TRUE;
		else {q=p;p=p->ptr[i];}
	}
	if(found)	return (p,i,1);
	else return (q,i,0);
}
//3阶的B-树上所有非终端结点至多可有两个关键字，至少有一个关键字，即子树个数为2或3，故又称2-3树。

//B-树的插入算法
Status InsertBTree(BTree &T,KeyType K,BTree q,int i)
{
	//在m阶B-树T上结点*q的key[i]与key[i+1]之间插入关键字K
	//若引入结点过大，则沿双亲链进行必要的节点分裂调整，使T仍是m阶B-树
	x=K;
	ap=NULL;
	finished=FALSE;
	while(q&&!finished)
	{
		Insert(q,i,x,ap);	//将x和ap分别插入到q->key[i+1]和q->ptr[i+1]
		if(q->keynum<m)finished=TRUE;
		else{
			s=m/2;
			split(q,s,ap);	//分裂*q，将q->key[s+1..m],q->ptr[s..m]和q->recptr[s+1..m]移入新结点*ap中
			x=q->key[s];
			q=q->parent;
			if(q)i=Search(q,x);	//在双亲结点*q中寻找x的插入位置
		}
	}
	if(!finished)	//T是空树或根结点已分裂为结点*q和*ap
		NewRoot(T,q,x,ap);	//生成含信息(T,x,ap)的新的根结点*T，原T和ap为子树指针
	return TRUE;
}