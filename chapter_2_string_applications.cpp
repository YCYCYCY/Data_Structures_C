/*
�ı��༭��
Ϊ�ı���������Ӧ��ҳ����б�
ҳ���ÿһ�������ҳ�ź͸�ҳ����ʼ�к�
�б��ÿһ����ָʾ��ÿһ�е��кţ���ʼ��ַ�͸����Ӵ��ĳ���
�ı��༭��������ҳָ�룬��ָ����ַ�ָ�룬�ֱ�ָʾ��ǰ������ҳ���к��ַ���
�����ĳ���ڲ����ɾ�������ַ�����Ҫ�޸��б��и��еĳ��ȡ������г����˷�������Ĵ洢�ռ䣬��ҪΪ�������·���洢�ռ䣬ͬʱ��Ҫ�޸ĸ��е���ʼλ�á�
���Ҫ�����ɾ��һ�У���Ҫ�漰�б�Ĳ����ɾ�������������ɾ�����ǵ�һ�У���Ҫ�޸�ҳ������Ӧҳ����ʼ�кš�
*/


/*
��������
1 ����Ŀ�ļ��ж���һ����Ŀ��
2 ����Ŀ��������ȡ���йؼ��ֲ���ʱ�
�жϴ���Ŀ������ȡ�ĵ����Ƿ�Ϊ�ؼ��ʣ���Ҫһ�ų��ôʱ��� an a of the�ȴʣ�������ȡ�����ĵ��ʲ��ڳ��ôʱ�����Ϊ�ؼ��ʡ�
3 �Դʱ��е�ÿһ���ؼ��ʣ����������н��в��Ҳ�����Ӧ�Ĳ��������
�������������д˹ؼ��ʵ������ֻҪ�ڸ����в�������������ɣ��������������У�����˹ؼ��ʵ����������Ӧ���ֵ�����ԭ����С�
�趨���ݽṹ��
�ʱ�Ϊ���Ա����һ��������������ɹؼ��ʣ�����˳��洢�ṹ������ÿ������һ���ַ���
������Ϊ���������˳��洢�ṹ������ÿ������������������ݣ�
��һ�ǹؼ��ʣ���������Ϊ��פ�ṹ����Ӧ���ǽ�ʡ�洢�����öѷ���洢��ʾ�Ĵ����ͣ�
���������������������������������������ɹ�����������룬�Ҳ�ͬ�Ĺؼ��ʵ���������������ȣ��ʲ�������ṹ�����Ա�
*/
#define MaxBookNum 1000	//����ֻ��1000���齨������
#define MaxKeyNum 2500	//��������������
#define MaxLineLen 500	//��Ŀ������󳤶�
#define MaxWordNum 10	//�ʱ���������
typedef struct 
{
	char *item[];	//�ַ���������
	int last;		//�ʱ�ĳ���
}WordListType;		//�ʱ����ͣ�˳���
typedef int ElemType;	//�������������Ԫ������Ϊ���ͣ�������ͣ�
typedef struct 
{
	string key;			//�ؼ���
	LinkList bnolist;	//����������������
}IdxTermType;			//����������
typedef struct 
{
	IdxTermType item[MaxKeyNum+1];
	int last;
}IdxLstType;			//���������ͣ������

//��Ҫ����
char *buf;				//��Ŀ��������
WordListType wdlist;	//�ʱ�

//��������
void InitIdxList(IdxListType &idxlist);
//��ʼ����������������idxlistΪ�ձ�����idxlist.item[0]��һ�մ�

void GetLine(FILE f);
//���ļ�f����һ����Ŀ��Ϣ����Ŀ��������buf

void ExtractKeyWord(ElemType &bno);
//��buf����ȡ�����ؼ��ʵ��ʵ�wdlist����Ŵ���bno

Status InsIdxList(IdxListType &idxlist,ElemType bno);
//�����Ϊbno�������ؼ��ʰ��ʵ�˳�����������idxlist

void PutText(FILE g,IdxListType idxlist);
//�����ɵ�������idxlist������ļ�g


void main()
{
	if(f=openf("BookInfo.txt","r"))
	{
		if(g=openf("BookIdx.txt","r"))
		{
			InitIdxList(idxlist);	//�����յ�������
			while(!feof(f))
			{
				GetLine(f);			//���ļ�f����һ����Ŀ��Ϣ��buf
				ExtractKeyWord(BookNo);	//��buf��ȡ�ؼ��ʵ��ʱ���Ŵ���BookNo
				InsIdList(idxlist,BookNo);	//�����BookNo�Ĺؼ��ʲ���������
			}
			PutText(g,idxlist);
		}//end if
	}//end if
}//end main

//Ϊʵ�����������Ͻ��в��룬Ҫ��ʵ�����в�����
void Getword(int i,string &wd);
//��wd���شʱ�wdlist�еĵ�i���ؼ���

int Locate(IdxListType idxlist,string wd,Boolean &b);
//��������idxlist�в�ѯ�Ƿ������wd��ȵĹؼ��ʡ������ڣ��򷵻�������������λ�ã�bΪtrue
//���򷵻ز���λ�ã���bΪfalse��
status InsertBook(IdxListType &idxlist,int i,int bno);
//��������idxlist�ĵ�i���в������Ϊbno������