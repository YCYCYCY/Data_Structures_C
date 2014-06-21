//事件链表
typedef struct{
	int OccurTime;	//事件发生时刻
	int NType;		//事件类型，0表示到达事件，1至4表示四个窗口的离开事件
}Event,ElemType;	//事件类型有序表的元素类型

typedef LinkList EventList	//事件链表

typedef struct
{
	int ArrivalTime;	//到达时刻
	int Duarion;		//办理事务所需时间
}QElemType;				//队列的数据元素类型

EventList ev;	//事件表
Event en;		//事件
LinkQueue q[5];	//4个客户队列，对应4个窗口
QElemType customer;	//客户记录
int TotalTime,CustomerNum;
int cmp(Event a,Event b);	//比较事件a与b发生时刻，分别返回-1,0,1
void OpenForDay()	//初始化
{
	TotalTime=0;	//初始化累计时间为0
	CustomerNum=0;	//客户数为0
	InitList(ev);	//初始化事件链表为空表
	en.OccurTime=0;	//设定第一个客户到达事件，发生时刻为0
	en.NType=0;		//事件类型为到达
	OrderInsert(ev,en,cmp);	//插入事件表
	for(int i=1;i<4;++i)
		InitQueue(q[i]);	//初始化各个队列
}
void customerArrived(){
	//处理客户到达事件,en.NType=0
	++CustomerNum;
	Random(durtime,insertime);	//随机生成两个数，一个是客户办理事务所需事件，另一个是下一个客户到达的时间间隔
	t=en.OccurTime+interime;	//下一个客户到达时刻
	if(t<CloseTime)				//银行没关门，插入事件表
		OrderInsert(ev,(t,0),cmp);
	i=Minimum(q);	//找出最短队列
	EnQueue(q[i],(en.OccurTime,durtime));	//插入一个客户
	if(QueueLength(q[i])==1)
		OrderInsert(ev,(en.OccurTime+durtime,i),cmp);	///插入一个离开事件
}
void CustomerDeparture(){
	//处理客户离开事件，en.NType>0
	i=en.NType;
	DelQueue(q[i],customer);	//删除第i个队列的排头队列
	TotalTime+=en.OccurTime-customer.ArrivalTime;
	if(!QueueEmpty(q[i])){	//队列不空
		GetHead(q[i],customer);
		OrderInsert(ev,(en.OccurTime+customer.Duration,i),(*cmp)());
	}
}

//计算一天中客户在银行逗留的凭据时间
void Bank_Simulation(int CloeTime)
{
	openForDay();
	while(!ListEmpty(ev)){
		DelFirst(GetHead(ev),p);
		en=GetCurElem(p);
		if(en.NType==0)
			CustomerArrived();
		else
			CustomerDeparture();
		}//End switch
	}//End while
}