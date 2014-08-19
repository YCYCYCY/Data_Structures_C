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

int partition(SqList &L,int low,int high)
{
	L.r[0]=L.r[low];
	pivotkey=L.r[low].key;
	while(low<high)
	{
		while(low<high && L.r[high]>=pivotkey)
			--high;
		L.r[low]=L.r[high];
		while(low<high && L.r[low].key<=pivotkey)
			++low;
		L.r[high]=L.r[low];
	}
	L.r[low]=L.r[0];
	return low;
}
void QSort(SqList &L,int low,int high)
{
	if(low<high)
	{
		pivotloc=Parition(L,low,high);
		QSort(L,low,pivotloc-1);
		QSort(L,pivotloc+1,high);
	}
}
void HeapAdjust(HeapType &H,int s,int m)
{
	rc=H.r[s];
	for(j=2*s;j<=m;j*=2)
	{
		if(j<m && H.r[j].key<H[j+1].key)
			j++;

		if(rc.key>=H.r[j].key)
			break;
		H.r[s]=H.r[j];
		s=j;
	}
	H.r[s]=rc;
}
void HeapSort(HeapType &H)
{
	for(i=H.length/2;i>0;--i)
		HeapAdjust(H,I,H.length);
	for(i=H.length;i>1;--i)
	{
		H.r[1]=H.r[i];
		HeapAdjust(H,1,i-1);
	}
}
//merging sort
void MergeArray(int *,int,int,int,int *);
void MergeSort(int *data,int first,int last,int *temp)
{
  if(first<last)
  {
    int mid=(first+last)/2;
    MergeSort(data,first,mid,temp);
    MergeSort(data,mid+1,last,temp);
    MergeArray(data,first,mid,last,temp);
  }
}
void MergeArray(int *data,int first,int mid,int last,int *temp)
{
  int i=first,j=mid+1,k=first;
  while(i<=mid && j<=last)
  {
    if(data[i]<data[j])
      temp[k++]=data[i++];
    else
      temp[k++]=data[j++];
  }
  while(i<=mid)
    temp[k++]=data[i++];
  while(j<=last)
    temp[k++]=data[j++];
}
						