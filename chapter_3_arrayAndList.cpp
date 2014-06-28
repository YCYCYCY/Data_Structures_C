/*
�����ѹ���洢��Ϊ���ֵ��ͬ��Ԫֻ����һ���洢�ռ䣬����Ԫ������ռ䡣

*/

//ϡ�����
ADT AparseMatrix{
	CreatSMatrix(&M);
	DestroySMatrix(&M);
	PrintSMatrix(M);
	CopySMatrix(M,&T);
	AddSMatrix(M,N,&Q);
	SubSMatrix(M,N,&Q);
	MultSMatrix(M,N,&Q);
	TransposeSMatrix(M,&T);	//ת��
}ADT SparseMatrix;
//һ����Ԫ��(i,j,aij)Ψһȷ���˾���A��һ������Ԫ���ټ���(m,n)��ʾ��������
#define MAXSIZE 12500	//����Ԫ���������ֵ
typedef struct 
{
	int i,j;		//����Ԫ�����±�����±�
	ElemType e;		//����Ԫ��ֵ
}Triple;
typedef struct 
{
	Triple data[MAXSIZE+1];		//����Ԫ��Ԫ���data[0]δ��
	int mu,nu,tu;				//����������������ͷ���Ԫ����
}TSMatrix;

//ת������
Status TransposeMatrix(TSMatrix M,TSMatrix &T)
{
	T.mu=M.nu;	//��
	T.nu=T.mu;	//��
	T.tu=M.tu;	//����
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

//����ת��
//�������飺num�洢ÿ���еķ���Ԫ�ĸ�����cpot�洢ÿ�е�һ������Ԫ��ת�þ����λ��
Status FastTransposeMatrix(TSMatrix M,TSMatrix &T){
	T.mu=M.nu;
	T.nu=M.mu;
	T.tu=M.tu;
	if(T.tu)
	{
		for(col=1;col<=M.nu;++col)	//������,��ʼ��num���顣
			num[col]=0;
		for(t=1;t<=M.nu;++t)
			++num[M.data[t].j];		//��M��ÿ�з���Ԫ�ĸ���
		cpot[1]=1;//��һ�еĵ�һ������Ԫ��ת�þ����е�һ��Ԫ��
		for(col=2;col<=M.nu;++col)	//��ֵcpot����
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

//���߼����ӵ�˳���
typedef struct 
{
	Triple data[MAXSIZE+1];
	int rpos[MAXRC+1];		//���е�һ������Ԫ��λ�ñ�
	int mu,nu,tu;
}RLSMatrix;
//�������
//Q��ʼ��

Status MultSMatrix(RLSMatrix M1,RLSMatrix M2,RLSMatrix &Result)
{
	//����������M1,M2�ĳ˻�
	if(M1.nu!=M2.mu)	return ERROR;	//��M1������������M2���������������������
	Result.mu=M1.mu;
	Result.nu=M2.nu;
	Result.tu=0;	//����Ԫ������ʼֵΪ0
	if(M1.tu*M2.tu!=0)	//ȷ��M1��M2������0����
	{
		for(arow=1;arow<=M1.mu;++arow)	//����M1��ÿһ�У���Ӧ����Result��ÿһ��
		{
			ctemp[]=0;//��ǰ�и�Ԫ�ض���ʼ��Ϊ0
			Result.rpos[arow]=Result.tu+1;	//����Result��ǰ�еĵ�һ������Ԫ��ǰһ�����һ������Ԫ����һλ��
			//�������M1�е�ǰ�е����һ������Ԫ�ص�λ��
			if(arow<M1.mu)
				plast=M1.rpos[arow+1];
			else
				plast=M1.tu+1;
			for(p=M1.rpos[arow];p<plast;++p)	//����M1��ǰ�е�ÿһ������Ԫ����Q��ǰ�еķ���Ԫ
			{
				brow=M1.data[p].j;	//browΪp��ָ���Ǹ�����Ԫ���к�
				//�������M2��brow�е��յ㣬��һ�е����з���Ԫ��Ҫ��M1.data[p]���
				if(brow<M2.mu)
					t=M2.rpos[brow+1];
				else
					t=M2.tu+1;
				for(q=M2.rpos[brow];q<t;++q)
				{
					ccol=M2.data[q].j;	//����M2�е�ǰԪ��q���кţ�Ҳ�����Ԫ���ھ���Result��ǰԪ�ص��к�
					ctemp[ccol]+=M1.data[p].e*M2.data[q].e;	//�ӽ�����Result��ǰ�и�Ԫ����
				}//end for q
			}//end for p ���Result����ǰ�е�����Ԫ�أ�������Ҳ�п�������Ԫ
			
			//���Result����ǰ�е���Ԫ
			for(ccol=1;ccol<=Q.nu;++ccol)
			{
				if(ctemp[ccol])	//ֵ��Ϊ��
				{
					if(Result.tu++>MAXSIZE)	return ERROR;	//������Χ��
					Result.data[Result.tu]=struct Triple(arow,ccol,ctemp[ccol]);	//�½�һ������Ԫ�أ�����Q�С�
				}//end if
			}//end for ѹ��ctemp�е�Ԫ�أ��ѷ���Ԫ���뵽��֤Result��
		}//end for(arow=1;arow<=M1.mu;++arow) ����ÿһ��
	}//end if(M1.tu*M2.tu!=0)
}



//ʮ������
//ÿһ������Ԫ����һ����5����Ľڵ��ʾ������i��j��e��3����ֱ��ʾ�÷���Ԫ���ڵ��� ���кͷ���Ԫ��ֵ��
//������right��������ͬһ������һ������Ԫ��������down��������ͬһ������һ������Ԫ��
//ͬһ�еķ���Ԫͨ��right��������һ����������ͬһ�еķ���Ԫͨ��down�����ӳ�һ����������
//�������ֱ�洢�������ͷָ����������ͷָ���һά����
typedef struct OLNode
{
	int i,j;			//����Ԫ���к����±�
	ElemType e;
	struct OLNode *right,*down;	//�������������
}OLNode,*OLink;
typedef struct 
{
	OLink *rhead,*chead;	//�������������ͷָ��������ַ��CreateSMatrix����
	int mu,nu,tu;			//����������������Ԫ����
}CrossList;
Status CreateSMatrix_OL(CrossList &M)
{
	if(M)	free(M);
	scanf(&m,$n,&t);//��������������������Ԫ����
	M.mu=m;
	M.nu=n;
	M.tu=t;
	if(!(M.rhead=(OLink*)malloc((m+1)*sizeof(OLink))))	exit(OVERFLOW);
	if(!(M.chead=(OLink*)malloc((n+1)*sizeof(OLink))))	exit(OVERFLOW);
	M.rhead[]=M.chead[]=NULL;//��ʼ������ͷָ������
	for(scanf(&i,&j,&e);i!=0;scanf(&i,&j,&e))//����������������Ԫ	
	{
		if(!(p=(OLNode*)malloc(sizeof(OLNode))))	exit(OVERFLOW);
		p->i=i;
		p->j=j;
		p->e=e;
		if(M.rhead[i]==NULL || M.rhead[i]->j>j)	//���뵽��ǰ��
		{
			p->right=M.rhead[i];
			M.rhead[i]=p;
		}
		else
		{
			//�ҵ������λ��
			for(q=M.rhead[i];q->right && q->right->j<j;q=q->right){	pre=q;}
			p->right=q;
			pre->right=p;
		}//end if:���뵽rhead�б���
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
		}//end if:���뵽chead�б���
	}
	return OK;
}//end createSMatrix_OL