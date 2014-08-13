#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))
ADT StaticSearchTable{
	Create(&ST,n);
	Destroy(&ST);
	Search(ST,key);
	Traverse(ST,Visit());
}ADT StaticSearchTable
//˳�����
int Search_Seq(SSTable ST,KeyType key)
{
	ST.elem[0].key=key;
	for(i=ST.length;!EQ(ST.elem[i].key,key);--i);
	return i;
}
//�����Ķ��ֲ���
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
//�ݹ鷽ʽ
int Search_Bin(SStable ST,KeyType key,int low,int high)
{

	mid=(low+high)/2;
	if(EQ(key,ST.elem[mid].key))	return mid;
	else if(LT(key,ST.elem[mid].key))	Search_Bin(ST,key,low,mid-1);
	else Search_Bin(ST,key,mid+1,high);
}
//��������и���¼�Ĳ��Ҹ��ʲ����ʱ��Ӧʹ�þ�̬���Ų�������
//�����쾲̬���Ų��������ѵ�ʱ����۽ϸߣ������ô��Ų����������档
//���Ų�����
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


//����˳���
//�ֽ����ֿ���ң�����һ�����������а����������ݣ��ؼ�����ӱ��е����ؼ��֣���ָ���ָʾ���ӱ�ĵ�һ����¼�ڱ���λ�ã�
//�������ö��ֲ���������ȷ����¼���ڵĿ飬Ȼ���ڿ���˳����ҡ�




//��̬����
//�����д�����ؼ��ֵ���key�ļ�¼������ҳɹ����ء��������ؼ��ֵ���key�ļ�¼��

//�����������������������н���ֵ��С�����ĸ��ڵ��ֵ�������������н���ֵ�����ڸ��ڵ��ֵ
//����
Status SearchBST(BiTree T,KeyType key,BiTree f,BiTree &p)
//�ڶ���������T�в���key�������ҳɹ�����pָ�������Ԫ�ؽ�㣬������TRUE������pָ�����·���Ϸ��ʵ����һ����㲢����FALSE��fΪT�ڵ��˫�ס�
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
//ɾ���ڵ�
/*
�����ڶ����������ϱ�ɾ���ڵ�Ϊ*p����˫�׽ڵ�Ϊ*f���Ҳ���һ���ԣ�����*p��*f������
��1����*p�ڵ�ΪҶ�ӽڵ㣬��PL��PRΪ������ֻ���޸���˫�׽ڵ��ָ�뼴�ɡ�
��2����*p�ڵ�ֻ������������ֻ����������������������������ֱ�ӳ�Ϊ��˫�׽ڵ�*f�����������ɡ�
��3����*p�ڵ���������������գ����������ַ�������
һ����*p��������Ϊ*f������������*p��������Ϊ*s��������
������*p��ֱ��ǰ�����*p��Ȼ���ٴӶ�����������ɾ������ֱ��ǰ����
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
	if(!p->rchild)	//������Ϊ��
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




//B-�� ��������Ȳ�һ��
/*
һ��m�׵�B-��������һ��������
1 ����ÿ�����������m������
2 ������㲻��Ҷ�ӽڵ㣬��������2��������
3 ����֮������з��ն˽��������m/2��������
4 ���еķ��ն˽���а���������Ϣ����
	(n,A0,K1,A1,K2,A2,...Kn,An)
���У�KiΪ���ݣ���K1<K2<..<Kn;AiΪָ������������ָ�룬��Ai-1��ָ���������н��Ĺؼ���С��Ki,Ai��ָ���������нڵ�Ĺؼ��־�����Ki��nΪ���ݸ�����
5 ���е�Ҷ�ӽڵ㶼������ͬһ����ϣ����Ҳ�����Ϣ��
*/
#define m 3	//B-���Ľף���Ϊ3
typedef struct BTNode
{
	int  keynum;//�ڵ��йؼ��ֵĸ���
	struct BTNode *parent;
	KeyType key[m+1];	//�ؼ���������0�ŵ�Ԫδ��
	struct BTNode *ptr[m+1];	//����ָ������
	Record *recptr[m+1];		//��¼ָ��������0�ŵ�Ԫδ��
}BRNode,*BTree;
typedef struct 
{
	BTNode *p;	//ָ���ҵ��Ľڵ�
	int i;		//�ڽ���еĹؼ������
	int tag;	//���ҳɹ�Ϊ1������Ϊ0
}Result;
Result SearchBTree(BTree T,KeyTree K){
	//��m��B-��T�ϲ��ҹؼ���K�����ؽ����pt,i,tag���������ҳɹ���������ֵtag=1��ָ��pt��ָ����е�i���ؼ��ֵ���k��
	//��������ֵtag=0������k�Ĺؼ���Ӧ������ָ��pt��ָ����е�i�͵�i+1���ؼ���֮��
	p=T;q=NULL;
	found=FALSE;
	i=0;
	while(p&&!found){
		i=Search(p,k);	//��p->key[1...keynum]�в���i,ʹ�ã�p->key[i]<= K <=p->key[i+1]
		if(i>0&&p->key[i]==k)	found=TRUE;
		else {q=p;p=p->ptr[i];}
	}
	if(found)	return (p,i,1);
	else return (q,i,0);
}
//3�׵�B-�������з��ն˽��������������ؼ��֣�������һ���ؼ��֣�����������Ϊ2��3�����ֳ�2-3����

//B-���Ĳ����㷨
Status InsertBTree(BTree &T,KeyType K,BTree q,int i)
{
	//��m��B-��T�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���K
	//���������������˫�������б�Ҫ�Ľڵ���ѵ�����ʹT����m��B-��
	x=K;
	ap=NULL;
	finished=FALSE;
	while(q&&!finished)
	{
		Insert(q,i,x,ap);	//��x��ap�ֱ���뵽q->key[i+1]��q->ptr[i+1]
		if(q->keynum<m)finished=TRUE;
		else{
			s=m/2;
			split(q,s,ap);	//����*q����q->key[s+1..m],q->ptr[s..m]��q->recptr[s+1..m]�����½��*ap��
			x=q->key[s];
			q=q->parent;
			if(q)i=Search(q,x);	//��˫�׽��*q��Ѱ��x�Ĳ���λ��
		}
	}
	if(!finished)	//T�ǿ����������ѷ���Ϊ���*q��*ap
		NewRoot(T,q,x,ap);	//���ɺ���Ϣ(T,x,ap)���µĸ����*T��ԭT��apΪ����ָ��
	return TRUE;
}