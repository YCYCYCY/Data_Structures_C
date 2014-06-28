/*
矩阵的压缩存储：为多个值相同的元只分配一个存储空间，对零元不分配空间。

*/

//稀疏矩阵
ADT AparseMatrix{
	CreatSMatrix(&M);
	DestroySMatrix(&M);
	PrintSMatrix(M);
	CopySMatrix(M,&T);
	AddSMatrix(M,N,&Q);
	SubSMatrix(M,N,&Q);
	MultSMatrix(M,N,&Q);
	TransposeSMatrix(M,&T);	//转置
}ADT SparseMatrix;
//一个三元组(i,j,aij)唯一确定了矩阵A的一个非零元。再加上(m,n)表示行列数。
#define MAXSIZE 12500	//非零元个数的最大值
typedef struct 
{
	int i,j;		//非零元的行下表和列下表
	ElemType e;		//非零元的值
}Triple;
typedef struct 
{
	Triple data[MAXSIZE+1];		//非零元三元组表，data[0]未用
	int mu,nu,tu;				//矩阵的行数，列数和非零元个数
}TSMatrix;

//转置运算
Status TransposeMatrix(TSMatrix M,TSMatrix &T)
{
	T.mu=M.nu;	//行
	T.nu=T.mu;	//列
	T.tu=M.tu;	//个数
	if(T.tu){
		q=1;
		for(col=1;col<=M.mu;++col)
			for(p=1;p<=M.tu;++p)
				if(M.data[p].j==col){
					T.data[q].i=M.data[p].j;
					T.data[q].j=M.data[p].i;
					T.data[q].e=M.data[p].e;
					++q;
				}
	}
	return OK;
}

//快速转置
//两个数组：num存储每列中的非零元的个数，cpot存储每列的一个非零元在转置矩阵的位置
Status FastTransposeMatrix(TSMatrix M,TSMatrix &T){
	T.mu=M.nu;
	T.nu=M.mu;
	T.tu=M.tu;
	if(T.tu)
	{
		for(col=1;col<=M.nu;++col)	//遍历列,初始化num数组。
			num[col]=0;
		for(t=1;t<=M.nu;++t)
			++num[M.data[t].j];		//求M中每列非零元的个数
		cpot[1]=1;//第一列的第一个非零元在转置矩阵中第一个元素
		for(col=2;col<=M.nu;++col)	//赋值cpot数组
			cpot[col]=cpot[col-1]+num[col-1];
		for(p=1;p<M.tu;++p)
		{
			col=M.data[p].j;
			q=cpot[col];
			T.data[q].i=M.data[p].j;
			T.data[q].j=M.data[p].i;
			T.data[q].e=M.data[p].e;
			++cpot[col];
		}//end for
	}//end if
}//end FastTransposeMatrix

//行逻辑链接的顺序表
typedef struct 
{
	Triple data[MAXSIZE+1];
	int rpos[MAXRC+1];		//各行第一个非零元的位置表
	int mu,nu,tu;
}RLSMatrix;
//矩阵相乘
//Q初始化

Status MultSMatrix(RLSMatrix M1,RLSMatrix M2,RLSMatrix &Result)
{
	//求两个矩阵M1,M2的乘积
	if(M1.nu!=M2.mu)	return ERROR;	//若M1的列数不等于M2的行数，两个矩阵不能相乘
	Result.mu=M1.mu;
	Result.nu=M2.nu;
	Result.tu=0;	//非零元个数初始值为0
	if(M1.tu*M2.tu!=0)	//确保M1与M2都不是0矩阵
	{
		for(arow=1;arow<=M1.mu;++arow)	//遍历M1的每一行，对应产生Result的每一行
		{
			ctemp[]=0;//当前行个元素都初始化为0
			Result.rpos[arow]=Result.tu+1;	//矩阵Result当前行的第一个非零元是前一行最后一个非零元的下一位数
			//求出矩阵M1中当前行的最后一个非零元素的位置
			if(arow<M1.mu)
				plast=M1.rpos[arow+1];
			else
				plast=M1.tu+1;
			for(p=M1.rpos[arow];p<plast;++p)	//遍历M1当前行的每一个非零元，求Q当前行的非零元
			{
				brow=M1.data[p].j;	//brow为p所指的那个非零元的列号
				//求出矩阵M2第brow行的终点，这一行的所有非零元都要与M1.data[p]相乘
				if(brow<M2.mu)
					t=M2.rpos[brow+1];
				else
					t=M2.tu+1;
				for(q=M2.rpos[brow];q<t;++q)
				{
					ccol=M2.data[q].j;	//矩阵M2中当前元素q的列号，也是这个元素在矩阵Result当前元素的列号
					ctemp[ccol]+=M1.data[p].e*M2.data[q].e;	//加进矩阵Result当前行各元素中
				}//end for q
			}//end for p 求得Result矩阵当前行的所有元素，但其中也有可能有零元
			
			//清除Result矩阵当前中的零元
			for(ccol=1;ccol<=Q.nu;++ccol)
			{
				if(ctemp[ccol])	//值不为零
				{
					if(Result.tu++>MAXSIZE)	return ERROR;	//超出范围了
					Result.data[Result.tu]=struct Triple(arow,ccol,ctemp[ccol]);	//新建一个矩阵元素，加入Q中。
				}//end if
			}//end for 压缩ctemp中的元素，把非零元加入到举证Result中
		}//end for(arow=1;arow<=M1.mu;++arow) 遍历每一行
	}//end if(M1.tu*M2.tu!=0)
}



//十字链表
//每一个非零元可用一个含5个域的节点表示，其中i、j和e这3个域分别表示该非零元所在的行 、列和非零元的值，
//向右域right用以链表同一行中下一个非零元，向下域down用以链接同一列中下一个非零元。
//同一行的非零元通过right域链表结成一个线性链表，同一列的非零元通过down域链接成一个线性链表
//用两个分别存储行链表的头指针和列链表的头指针的一维数组
typedef struct OLNode
{
	int i,j;			//非零元的行和列下标
	ElemType e;
	struct OLNode *right,*down;	//向右域和向下域
}OLNode,*OLink;
typedef struct 
{
	OLink *rhead,*chead;	//行链表和列链表头指针向量基址有CreateSMatrix分配
	int mu,nu,tu;			//行数、列数、非零元个数
}CrossList;
Status CreateSMatrix_OL(CrossList &M)
{
	if(M)	free(M);
	scanf(&m,$n,&t);//输入行数、列数、非零元个数
	M.mu=m;
	M.nu=n;
	M.tu=t;
	if(!(M.rhead=(OLink*)malloc((m+1)*sizeof(OLink))))	exit(OVERFLOW);
	if(!(M.chead=(OLink*)malloc((n+1)*sizeof(OLink))))	exit(OVERFLOW);
	M.rhead[]=M.chead[]=NULL;//初始化行列头指针向量
	for(scanf(&i,&j,&e);i!=0;scanf(&i,&j,&e))//按任意次序输入非零元	
	{
		if(!(p=(OLNode*)malloc(sizeof(OLNode))))	exit(OVERFLOW);
		p->i=i;
		p->j=j;
		p->e=e;
		if(M.rhead[i]==NULL || M.rhead[i]->j>j)	//插入到最前方
		{
			p->right=M.rhead[i];
			M.rhead[i]=p;
		}
		else
		{
			//找到插入的位置
			for(q=M.rhead[i];q->right && q->right->j<j;q=q->right){	pre=q;}
			p->right=q;
			pre->right=p;
		}//end if:插入到rhead列表中
		if(M.chead[j]==NULL ||M.chead[j]->i>i)
		{
			p->down=M.chead[j];
			M.chead[j]=p;
		}
		else
		{
			for(q=M.chead[j];q->down && q->down->i<i;q=q->down) {pre=q;}
			p->down=q;
			pre->down=p;
		}//end if:插入到chead列表中
	}
	return OK;
}//end createSMatrix_OL