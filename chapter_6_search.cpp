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

//B+树
/*
B+树是应文件系统所需而出的一种B-树的变型树。一颗m阶的B+树和m阶的B-树的差异在于：
1 有n棵子树的结点中含有n个关键字。
2 所有的叶子结点中包含了全部关键字的信息，及指向含这些关键字记录的指针，且叶子结点本身依关键字的大小自小而大顺序链接。
3 所有的非终端节点可以看成是索引部分，节点中仅含有其子树中的最大（或最小）关键字。
*/



//哈希表
//记录的存储位置和她的关键字之间建立一个确定的对应关系，使每个关键字和结构中一个唯一的存储位置相对应。
/*
1 哈希函数是一个映像
2 对不同的关键字可能得到同一哈希地址，这种现象称作冲突。
在创建哈希表时不仅要设定一个好的哈希函数，而且要设定一种处理冲突的方法。
*/



//哈希函数的构造方法
/*
好的哈希函数：若对于关键字集合中的任意关键字，经哈希函数映像到地址集合中任何一个地址的概率是相等的，则称此类哈希函数为均匀的哈希函数。
常用的构造哈希函数的方法：
1、直接定址法
取关键字或关键字的某个线性函数值为哈希地址。
2、数字分析法
分析关键字的特征选取合适的几位数作为哈希地址
3、平方取中法
去关键字平方后的中间几位为哈希地址。这是一种常见的构造哈希函数的方法。
4、折叠法
讲关键字分割成位数相同的几部分（最后一部分的位数可以不同），然后取这几部分的叠加和（舍去进位）作为哈希地址。
5、除留余数法
取关键字被某个不大于哈希表表长m的树p除后所得余数为哈希地址
6、随机数法
选择一个随机函数，取关键字的随机函数值为它的哈希地址。
*/



//处理冲突的方法
/*
1 开放定址法
H(i)=(H(key)+d(i))MOD m	i=1,2,...,k(k<=m-1)
其中:H(key)为哈希函数，m为哈希表表长，d(i)增量序列，可有下列3中取法：
（1）d(i)=1,2,3,...,m-1，称线性探测再散列。缺点：会产生二次聚集
（2）d(i)=1,-1,4,-4,9,-9....，称二次探测再散列。缺点：只有在哈希表长m为形如4j+3的素数时才有效
（3）d(i)=伪随机数序列
2 再哈希法
H(i)=RH(key) i=1,2,...,k
3 链地址法
将所有关键字为同义词的记录存储在同一线性链表中。
4 建立一个公共溢出区
另设立向量OverTable[0..v]为溢出表，当产生冲突时，将其加入溢出表中。
*/


//哈希表的查找及其分析
/*
给定K值，根据造表使设定的哈希函数求得哈希地址，若表中此位置上没有记录，则查找不成功。
否则比较关键字，若和给定值相等，则查找成功。否则根据造表时设定的处理冲突的方法找下一地址，
直至哈希表中某一个位置为空或者表中所填记录的关键字等于给定值为止。
*/
//开放定址的存储结构
int hashsize[]={997,...};	
typedef struct 
{
	ElemType *elem;	//数据元素存储基址，一个合适的素数序列
	int count;		//当前数据元素个数
	int sizeindex;	//hashsize[sizeindex]为当前容量
}hashTable;
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1
Status SearchHash(HashTable H,KeyType K,int &p,int &c)
{
	//查找成功，p指示待查数据K在表中的位置，并返回SUCCESS
	//否则，p指示插入位置，UNSUCCESS。
	//c用以计算冲突次数，其初值置零。
	p=Hash(K);
	while(H.elem[p].key!=NULLKEY&&!EQ(K,H.elem[p].key))
		collision(p,++c);
	if(EQ(K,H.elem[p].key))
		return SUCCUSS;
	else
		return UNSUCCESS;
}
//insertHash
Status InsertHash(HashTable &H,Elemtype e)
{
	c=0;
	if(SearchHash(H,e.key,p,c))
		return DUPLICATE;
	else if(c<Hahsize[H.sizeindex]/2)
	{
		H.elem[p]=e;
		++H.count;
		return OK;
	}
	else
	{
		ReceateHashTable(H);
		return UNSUCCESS;
	}
}
                                                                                              