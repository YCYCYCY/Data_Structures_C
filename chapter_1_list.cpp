//线性表LIST
/*

		|顺序表	
		|		|单链表
		|链表——	|循环链表
		|		|双链表
线性表	|		|静态链表
		|栈
		|		|双端队列
		|队列——	|循环队列
		|		|
*/
ADT List
	{
		InitList(&L);				//构造线性表
		DestroyList(&L);			//销毁线性表
		ClearList(&L);				//清空表
		ListEmpty(L);				//是否为空
		ListLength(L);				//返回表长度
		GetElem(L,i,&e);			//返回第i个节点
		LocateElem(L,e,compare());	//找到第一个与e满足compare()关系的节点
		PriorElem(L,cur_e,&pre_e);	//cur_e的前一个节点
		NextElem(L,cur_e,&next_e);	//cur_e的后一个节点
		ListInsert(&L,i,e);			//在第i个位置处插入节点
		ListDelete(&L,i,&e);		//删除第i个节点
		ListTraverse(L,visit());	//遍历每一个节点，对每一个节点调用visit()函数
	}ADT list；
//顺序表
typedef struct 
{
	ElemType *elem;	//存储空间基址
	int length;		//当前长度
	int listsize;	//存储容量
}SqList;
//链表
typedef struct LNode
{
	ElemType data;	
	struct LNode*next;
}LNode,*LinkList;
//静态链表
typedef struct 
{
	ElemType data;
	int cur;	//下一个节点所在的位置
}component,SLinkList[MAXSIZE];
//双向链表
typedef struct DuLNode
{
	ElemType data;	
	struct LNode *next;
	struct LNode *prior;
}DuLNode,*DuLinkList;

//栈stack
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
//顺序栈
typedef struct 
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}sqStack;
//队列queue
ADT Queue
{
	InitQueue(&Q);
	DestroyQueue(&Q);
	ClearQueue(&Q);
	QueueEmpty(Q);
	QueueLength(Q);
	GetLength(Q);
	GetHead(Q,&e);
	EnQueue(&Q,e);	//插入
	DeQueue(&Q,&e);	//删除
	QueueTraverse(Q,visit());
}ADT Queue;
//链队列
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
//顺序队列
typedef struct 
{
	QElemType *base;
	int front;
	int rear;
}SqQueue;