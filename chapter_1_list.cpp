//���Ա�LIST
/*

		|˳���	
		|		|������
		|������	|ѭ������
		|		|˫����
���Ա�	|		|��̬����
		|ջ
		|		|˫�˶���
		|���С���	|ѭ������
		|		|
*/
ADT List
	{
		InitList(&L);				//�������Ա�
		DestroyList(&L);			//�������Ա�
		ClearList(&L);				//��ձ�
		ListEmpty(L);				//�Ƿ�Ϊ��
		ListLength(L);				//���ر���
		GetElem(L,i,&e);			//���ص�i���ڵ�
		LocateElem(L,e,compare());	//�ҵ���һ����e����compare()��ϵ�Ľڵ�
		PriorElem(L,cur_e,&pre_e);	//cur_e��ǰһ���ڵ�
		NextElem(L,cur_e,&next_e);	//cur_e�ĺ�һ���ڵ�
		ListInsert(&L,i,e);			//�ڵ�i��λ�ô�����ڵ�
		ListDelete(&L,i,&e);		//ɾ����i���ڵ�
		ListTraverse(L,visit());	//����ÿһ���ڵ㣬��ÿһ���ڵ����visit()����
	}ADT list��
//˳���
typedef struct 
{
	ElemType *elem;	//�洢�ռ��ַ
	int length;		//��ǰ����
	int listsize;	//�洢����
}SqList;
//����
typedef struct LNode
{
	ElemType data;	
	struct LNode*next;
}LNode,*LinkList;
//��̬����
typedef struct 
{
	ElemType data;
	int cur;	//��һ���ڵ����ڵ�λ��
}component,SLinkList[MAXSIZE];
//˫������
typedef struct DuLNode
{
	ElemType data;	
	struct LNode *next;
	struct LNode *prior;
}DuLNode,*DuLinkList;

//ջstack
ADT Stack
	{
		InitStack(&S);
		DestroyStack(&S);
		ClearStack(S);
		StackEmpty(S);
		StackLength(S);
		GetTop(S,&e);
		Push(&S,e);
		pop(&S,&e);
		StackTraverse(S,visit());
	}ADT Stack;
//˳��ջ
typedef struct 
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}sqStack;
//����queue
ADT Queue
{
	InitQueue(&Q);
	DestroyQueue(&Q);
	ClearQueue(&Q);
	QueueEmpty(Q);
	QueueLength(Q);
	GetLength(Q);
	GetHead(Q,&e);
	EnQueue(&Q,e);	//����
	DeQueue(&Q,&e);	//ɾ��
	QueueTraverse(Q,visit());
}ADT Queue;
//������
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct 
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
//˳�����
typedef struct 
{
	QElemType *base;
	int front;
	int rear;
}SqQueue;