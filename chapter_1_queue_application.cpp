//�¼�����
typedef struct{
	int OccurTime;	//�¼�����ʱ��
	int NType;		//�¼����ͣ�0��ʾ�����¼���1��4��ʾ�ĸ����ڵ��뿪�¼�
}Event,ElemType;	//�¼�����������Ԫ������

typedef LinkList EventList	//�¼�����

typedef struct
{
	int ArrivalTime;	//����ʱ��
	int Duarion;		//������������ʱ��
}QElemType;				//���е�����Ԫ������

EventList ev;	//�¼���
Event en;		//�¼�
LinkQueue q[5];	//4���ͻ����У���Ӧ4������
QElemType customer;	//�ͻ���¼
int TotalTime,CustomerNum;
int cmp(Event a,Event b);	//�Ƚ��¼�a��b����ʱ�̣��ֱ𷵻�-1,0,1
void OpenForDay()	//��ʼ��
{
	TotalTime=0;	//��ʼ���ۼ�ʱ��Ϊ0
	CustomerNum=0;	//�ͻ���Ϊ0
	InitList(ev);	//��ʼ���¼�����Ϊ�ձ�
	en.OccurTime=0;	//�趨��һ���ͻ������¼�������ʱ��Ϊ0
	en.NType=0;		//�¼�����Ϊ����
	OrderInsert(ev,en,cmp);	//�����¼���
	for(int i=1;i<4;++i)
		InitQueue(q[i]);	//��ʼ����������
}
void customerArrived(){
	//����ͻ������¼�,en.NType=0
	++CustomerNum;
	Random(durtime,insertime);	//���������������һ���ǿͻ��������������¼�����һ������һ���ͻ������ʱ����
	t=en.OccurTime+interime;	//��һ���ͻ�����ʱ��
	if(t<CloseTime)				//����û���ţ������¼���
		OrderInsert(ev,(t,0),cmp);
	i=Minimum(q);	//�ҳ���̶���
	EnQueue(q[i],(en.OccurTime,durtime));	//����һ���ͻ�
	if(QueueLength(q[i])==1)
		OrderInsert(ev,(en.OccurTime+durtime,i),cmp);	///����һ���뿪�¼�
}
void CustomerDeparture(){
	//����ͻ��뿪�¼���en.NType>0
	i=en.NType;
	DelQueue(q[i],customer);	//ɾ����i�����е���ͷ����
	TotalTime+=en.OccurTime-customer.ArrivalTime;
	if(!QueueEmpty(q[i])){	//���в���
		GetHead(q[i],customer);
		OrderInsert(ev,(en.OccurTime+customer.Duration,i),(*cmp)());
	}
}

//����һ���пͻ������ж�����ƾ��ʱ��
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