ADT String {
	StrAssign(&T,chars);
	StrCopy(&T,S);
	StrEmpty(S);
	StrCompare(S,T);
	StrLength(S);
	ClearString(&S);
	Concat(&T,S1,S2);//由S1和S2连接成一个新串T
	SubString(&Sub,S,pos,len);//返回串S中第pos个字符之后长度为len的子串
	Index(S,T,pos);//主串中第pos个字符之后第一次出现的位置
	Replace(&S,T,V);//用V替换主串S中出现的所有与T相等的不重叠的子串
	StrInsert(&S,pos,T);//在串S的第pos个字符之前插入串T
	StrDelete(&S,pos,len);
	DestroyString(&S);
}ADT String
//定长顺序存储
#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN+1];

//堆分配存储表示
typedef struct 
{
	char *ch;
	int lenght;
}HString;

//串的块链存储表示
#define CHUNKSIZE 80	//可由用户定义的块大小
typedef struct Chunk
{
	char ch[CHUNKSIZE];
	struct Chunk *next; 
}Chunk;
typedef struct 
{
	Chunk *head,*tail;  //串的头和尾指针
	int curlen;			//串的长度
}LString;

int Index (String S,String T,int pos)
{
	//返回串S中pos位置之后第一个与T相等的子串位置
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
	//s>t,返回一个大于0的数
	//s=t,返回0
	//s<t,返回小于0的数
	for(i=0;i<s.length&&i<t.length;++i)
		if(s.ch[i]!=t.ch[i])
		return s.ch[i]-t.ch[i];
	return s.length-t.length;
}
