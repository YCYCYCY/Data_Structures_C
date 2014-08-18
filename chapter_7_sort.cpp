//�ȶ��Ͳ��ȶ�����
//�ڲ�������ⲿ�����ڲ��������ڴ������򣬶��ⲿ������������ʡ�

//����������һ���¼����ڵ�ַ������һ��洢��Ԫ��Ԫ�ϡ�
#define MAXSIZE 20	//һ������ʾ����С˳������󳤶�
typedef int KeyType;	//����ؼ�������Ϊ��������
typedef struct 
{
	KeyType key;		//�ؼ�����
	InfoType otherinfo;	//����������
}RedType;				//��¼����
typedef struct 
{
	RedType r[MAXSIZE+1];	//r[0]���û��������ڱ���Ԫ
	int length;
}SqList;

//��������
//ֱ�Ӳ�������straight insertion sort��
void insertSort(SqList &L)
{
	for(i=2;i<L.length;++i)
	{
		if(L.r[i].key<L.r[i-1].key)
		{
			L.r[0]=L.r[i];				//�ڱ�
			for(j=i-1;L.r[0].key<L.r[j].key;--j)
				L.r[j+1]=L.r[j];		//���Ƽ�¼
			L.r[j+1]=L.r[0];			//�����¼

		}
	}
}
//�۰��������
void BInsertSort(AqList &L)
{
	for(i=2;i<=L.length;++i)
	{
		L.r[0]=L.r[i];
		low=1;
		high=i-1;
		while(low<=high)
		{
			m=(low+high)/2;
			if(L.r[0].key<L.r[m].key)
				high=m-1;
			else
				low=m+1;
		}
		for(j=i-1;j>=high;--j)
			L.r[j+1]=L.r[j];
		L.r[high]=L.r[0];
	}
}
//shell����
void shellSort(int *num,int size)
{
    int len=size;
    while(len>1)
    {
        len=(len+1)/2;
        for(int i=0;i<size-len;i++)
            if(num[i]>num[i+len])
                swp(num[i],num[i+len]);
    }
}

 //��������
 void quickSort(int *num,int begin,int end)
{
	int i=begin;
	int j=end+1;
	int compara=num[i];
	while(i<j)
	{
		for(i=i+1;i<end;i++)
		if{num[i]>compara}
		break;
    for (j=j-1;j>=begin;--j)
		if(num[j]>compara)
		break;
		if(j>i)
		swap(num[i],num[j]);
	}
	swap(num[begin],num[j]);
	quickSort(num,begin,j-1);
	quickSort(num,i;end);
}
