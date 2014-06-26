/*
文本编辑器
为文本串建立相应的页表和行表
页表的每一项给出了页号和该页的起始行号
行表的每一项则指示出每一行的行号，起始地址和该行子串的长度
文本编辑器中设立页指针，行指针和字符指针，分别指示当前操作的页，行和字符。
如果在某行内插入或删除若干字符，则要修改行表中改行的长度。若该行超出了分配给它的存储空间，则要为该行重新分配存储空间，同时还要修改该行的起始位置。
如果要插入或删除一行，就要涉及行表的插入和删除。若插入或者删除的是第一行，则还要修改页表中相应页的起始行号。
*/


/*
词索引表
1 从书目文件中读入一个书目串
2 从书目串中中提取所有关键字插入词表
判断从书目串中提取的单词是否为关键词，需要一张常用词表（若 an a of the等词）。若提取出来的单词不在常用词表中则为关键词。
3 对词表中的每一个关键词，在索引表中进行查找并作相应的插入操作。
若索引表上已有此关键词的索引项，只要在该项中插入书号索引即可；若不在索引表中，插入此关键词的索引项，插入应按字典有序原则进行。
设定数据结构：
词表为线性表，存放一本书的书名中若干关键词，采用顺序存储结构，其中每个词是一个字符串
索引表为有序表，采用顺序存储结构，表中每个索引项包含两个内容：
其一是关键词，因索引表为常驻结构，则应考虑节省存储，采用堆分配存储表示的串类型；
其二是书号索引，由于书号索引是在索引表的生成过程中逐个插入，且不同的关键词的书号索引个数不等，故采用链表结构的线性表。
*/
#define MaxBookNum 1000	//假设只对1000本书建索引表
#define MaxKeyNum 2500	//索引表的最大容量
#define MaxLineLen 500	//书目串的最大长度
#define MaxWordNum 10	//词表的最大容量
typedef struct 
{
	char *item[];	//字符串的数组
	int last;		//词表的长度
}WordListType;		//词表类型（顺序表）
typedef int ElemType;	//定义链表的数据元素类型为整型（书号类型）
typedef struct 
{
	string key;			//关键词
	LinkList bnolist;	//存放书号索引的链表
}IdxTermType;			//索引项类型
typedef struct 
{
	IdxTermType item[MaxKeyNum+1];
	int last;
}IdxLstType;			//索引表类型（有序表）

//主要变量
char *buf;				//书目串缓冲区
WordListType wdlist;	//词表

//基本操作
void InitIdxList(IdxListType &idxlist);
//初始化操作，置索引表idxlist为空表，且在idxlist.item[0]设一空串

void GetLine(FILE f);
//从文件f读入一个书目信息到书目串缓冲区buf

void ExtractKeyWord(ElemType &bno);
//从buf中提取书名关键词到词典wdlist，书号存入bno

Status InsIdxList(IdxListType &idxlist,ElemType bno);
//将书号为bno的书名关键词按词典顺序插入索引表idxlist

void PutText(FILE g,IdxListType idxlist);
//将生成的索引表idxlist输出到文件g


void main()
{
	if(f=openf("BookInfo.txt","r"))
	{
		if(g=openf("BookIdx.txt","r"))
		{
			InitIdxList(idxlist);	//建立空的索引表
			while(!feof(f))
			{
				GetLine(f);			//从文件f读入一个书目信息到buf
				ExtractKeyWord(BookNo);	//从buf提取关键词到词表，书号存入BookNo
				InsIdList(idxlist,BookNo);	//将书号BookNo的关键词插入索引表
			}
			PutText(g,idxlist);
		}//end if
	}//end if
}//end main

//为实现在索引表上进行插入，要先实现下列操作：
void Getword(int i,string &wd);
//用wd返回词表wdlist中的第i个关键词

int Locate(IdxListType idxlist,string wd,Boolean &b);
//在索引表idxlist中查询是否存在与wd相等的关键词。若存在，则返回其在索引表中位置，b为true
//否则返回插入位置，且b为false。
status InsertBook(IdxListType &idxlist,int i,int bno);
//在索引表idxlist的第i项中插入书号为bno的索引