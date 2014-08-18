//稳定和不稳定排序
//内部排序和外部排序：内部排序都在内存中排序，而外部排序需对外存访问。

//假设待排序的一组记录存放在地址连续的一组存储单元单元上。
#define MAXSIZE 20	//一个用作示例的小顺序表的最大长度
typedef int KeyType;	//定义关键字类型为整数类型
typedef struct 
{
	KeyType key;		//关键字项
	InfoType otherinfo;	//其他数据项
}RedType;				//记录类型
typedef struct 
{
	RedType r[MAXSIZE+1];	//r[0]闲置或者用作哨兵单元
	int length;
}SqList;

//插入排序
//直接插入排序（straight insertion sort）
void insertSort(SqList &L)
{
	for(i=2;i<L.length;++i)
	{
		if(L.r[i].key<L.r[i-1].key)
		{
			L.r[0]=L.r[i];				//哨兵
			for(j=i-1;L.r[0].key<L.r[j].key;--j)
				L.r[j+1]=L.r[j];		//后移记录
			L.r[j+1]=L.r[0];			//插入记录

		}
	}
}
//折半插入排序
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
//shell排序
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

 //快速排序
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
