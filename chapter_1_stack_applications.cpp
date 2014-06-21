//����ת��
void conversion()	//��ʮ����ת���ɰ˽���
{
	InitStack(S);
	scanf("%d",N);
	while(N)
	{
		Push(S,N%8);
		N=N/8;
	}
	while(!StackEmpty(S))
	{
		Pop(S,e);
		printf("%d",e);
	}
}
//����ƥ��
//[([][])]
bool isMatched(const char *str)
{
	InitStack(S);
	while(*str)
	{
		if(*str=='['||*str=='('||*str=='{')
		{
			Push(S,*str)
		}
		else if (*str==']'||*str==')'||*str=='}')
		{
			GetTop(S,e);
			if((*str==']'&&e=='[')||(*str==')'&&e=='(')||(*str=='}'&&e=='{'))
			{
				pop(S,e);
			}
			else 
				return false;
		}
	}
	if(StackEmpty(S))
		return true;
	else
		return false;
}
//�ݹ��㷨
const char *next_token(const char *s){
   while(*s!='\0'&&*s!='['&&*s!=']'&&*s!='('&&*s!=')'&&*s!='{'&&*s!='}')s++;
   return s;
}
const char *IsRecurMatch(const char *string){
    char cur_char = -1;    
    const char *next;
    string = next_token(string);
    switch(*string){
    case '(':
    case '[':
    case '{':
        cur_char = *string;
        next = IsRecurMatch(string+1); 
        if(next == NULL)return NULL;
        if(*next!=cur_char)return NULL;
        next++;
        next = next_token(next);
        break;
    case ')':
    case ']':
    case '{':
        return string;
    }
    return NULL;
}

//�б༭��
//�˸����#
//���з���@
void LineEdit(char *str)
{
	InitStack(S);
	ch=getchar();
	while(ch!=EOF)
	{
		while(ch!=EOF &&ch!='\n'){
			switch(ch){
				case '#':Pop(S,c);	break;
				case '@':ClearStack(S);	break;
				default:Push(S,ch);	break;
			}
			ch=getchar();
		}
		//����ջ�׵�ջ����ջ���ַ����������ù��̵�������
		int length =StackLength(S);
		for(int i=0;i<length;++i)
		{
			Pop(S,e);
			str[i]=e;
		}
		ClearStack(S);
		if(ch!=EOF)ch=getchar();
	}
	DestroyStack(S);
}
//�Թ����
/*
�趨��ǰλ�õĳ�ֵΪ���λ��
do{
	����ǰλ�ÿ�ͨ��
	��{
		����ǰλ�ò���ջ����
		����λ���ǳ���λ�ã��������
		�����л���ǰλ�õĶ��ڷ���Ϊ��ǰλ�ã�
		}
	����
	{
		��ջ��������ջ��λ��������������δ��̽��
		���趨�µĵ�ǰλ��Ϊ��˳ʱ�뷽����ת�ҵ���ջ��λ�õ���һ���ڿ飻
		��ջ���յ�ջ��λ�õ����ܾ���ͨ��
		��{
			ɾ��ջ��Ԫ�أ�
			��ջ���գ������²����µ�ջ��λ�ã�
			ֱ���ҵ�һ����ͨ�����ڿ���ջ��ջ�ա�
		}
	}
}
*/
typedef struct 
{
	int ord;		//ͨ������·���ϵġ���š�
	PosType seat;	//ͨ�������Թ��еġ�����λ�á�
	int di;			//�Ӵ�ͨ����������һͨ����ġ�����
}SElemType;			//ջ��Ԫ������
Status MazePath(MazeType maze,PosType start,PosType end){
	InitStack(S);
	curpos=start;//��ǰλ��Ϊ���λ��
	curstep=1;
	do{
		if(Pass(curpos)){	//��ǰλ�ÿ���ͨ��������δ���ߵ�����ͨ����
			FootPrint(curpos);	//�����㼣
			e=(curstep,curpos,1);//SElemType����
			Push(S,e);	//����·��
			if(curpos==end)		//����·��
				return TRUE;
			curpos=NextPos(curpos,1);	//��һλ���ǵ�ǰλ�õĶ���
			curstep++;	//̽����һ��
		}
		else{	//��ǰλ�ò���ͨ��
			if(!StackEmpty(S)){
				Pop(S,e);
				while(e.di==4 && !StackEmpty(S)){
					MarkPrint(e.seat);
					Pop(S,e);	//���²���ͨ���ı�ǣ����˻�һ��
				}
				if(e.di<4){	//����һ������̽��
					e.di++;
					Push(S,e);
					curpos=NextPos(e.seat,e.di);
				}
			}
		}
	}while(!StackEmpty(S));
	return FALSE;
}






//���ʽ���
//Ϊʵ����������㷨������ʹ����������ջ��һ����ΪOPTR�����ԼĴ����������һ������OPND�����ԼĴ����������������
//��1�������ò�����ջΪ�գ����ʽ��ʼ��'#'Ϊ�����ջ��ջ��Ԫ��
//��2�����ζ�����ʽ��ÿ���ַ������ǲ��������OPNDջ��������������OPTRջ��ջ��������Ƚ�����Ȩ������Ӧ������ֱ���������ʽ��ֵ���
OprandType EvaluateExpression(){
	//��OPTR��OPND�ֱ�Ϊ�����ջ��������ջ
	//OPΪ���������
	InitStack(OPTR);
	InitStack(OPND);
	Push(OPTR,'#');
	c=getchar();
	while(c!='#'||GetTop(OPTR)!='#'){
		if(!In(c,op))	//c��������������������ջ
			Push(OPND,c);
		else
			switch(Precede(GetTop(OPTR),c))
			{
			case '<':	//������ջջ��Ԫ������Ȩ����c
				Push(OPTR,c);
				break;
			case '=':	//�Ⱥ�ʱΪ����ƥ�䡣
				pop(OPTR,x);
				break;
			case '>':
				Pop(OPTR,theta);
				Pop(OPND,b);
				Pop(OPND,a);
				Push(OPND,Operate(a,theta,b));
				break;
			}//END SWITCH
	}//END WHILE
	return GetTop(OPND);
}//END EVALUATEEXPRESSION