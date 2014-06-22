ADT String {
	StrAssign(&T,chars);
	StrCopy(&T,S);
	StrEmpty(S);
	StrCompare(S,T);
	StrLength(S);
	ClearString(&S);
	Concat(&T,S1,S2);//��S1��S2���ӳ�һ���´�T
	SubString(&Sub,S,pos,len);//���ش�S�е�pos���ַ�֮�󳤶�Ϊlen���Ӵ�
	Index(S,T,pos);//�����е�pos���ַ�֮���һ�γ��ֵ�λ��
	Replace(&S,T,V);//��V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ�
	StrInsert(&S,pos,T);//�ڴ�S�ĵ�pos���ַ�֮ǰ���봮T
	StrDelete(&S,pos,len);
	DestroyString(&S);
}ADT String
//����˳��洢
#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN+1];

//�ѷ���洢��ʾ
typedef struct 
{
	char *ch;
	int lenght;
}HString;

//���Ŀ����洢��ʾ
#define CHUNKSIZE 80	//�����û�����Ŀ��С
typedef struct Chunk
{
	char ch[CHUNKSIZE];
	struct Chunk *next; 
}Chunk;
typedef struct 
{
	Chunk *head,*tail;  //����ͷ��βָ��
	int curlen;			//���ĳ���
}LString;

int Index (String S,String T,int pos)
{
	//���ش�S��posλ��֮���һ����T��ȵ��Ӵ�λ��
	if(pos>0)
	{
		n=StrLength(S);
		m=StrLength(T);
		i=pos;
		while(i<=n-m+1)
		{
			SubString(sub,S,i,m);
			if(StrCompara(sub,T)!=0)
				++i;
			else
				return i;
		}
	}
	return 0;
}


int  Index(string s,string t,int pos)
{
	i=pos;
	j=1;
	while(i<=s[0]&&j<=t[0])
		if(s[i]==t[j])
	{
		++i;
		++j;
	}
	else
	{
		i=i-j+2;
		j=1;
	}
	if(j>T[0])
		return i-T[0];
	else
		return 0;
}


int strCompare(String s,String t)
{
	//s>t,����һ������0����
	//s=t,����0
	//s<t,����С��0����
	for(i=0;i<s.length&&i<t.length;++i)
		if(s.ch[i]!=t.ch[i])
		return s.ch[i]-t.ch[i];
	return s.length-t.length;
}
