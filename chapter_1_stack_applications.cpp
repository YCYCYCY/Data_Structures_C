//数制转化
void conversion()	//把十进制转化成八进制
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
//括号匹配
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
//递归算法
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

//行编辑器
//退格符：#
//退行符：@
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
		//将从栈底到栈顶的栈内字符传送至调用过程的数据区
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
//迷宫求解
/*
设定当前位置的初值为入口位置
do{
	若当前位置可通，
	则{
		将当前位置插入栈顶；
		若该位置是出口位置，则结束；
		否则切换当前位置的东邻方块为当前位置；
		}
	否则
	{
		若栈不空且且栈顶位置尚有其它方向未经探索
		则设定新的当前位置为沿顺时针方向旋转找到的栈顶位置的下一相邻块；
		若栈不空但栈顶位置的四周均不通，
		则{
			删除栈顶元素，
			若栈不空，则重新测试新的栈顶位置，
			直至找到一个可通的相邻块或出栈至栈空。
		}
	}
}
*/
typedef struct 
{
	int ord;		//通道块在路径上的“序号”
	PosType seat;	//通道块在迷宫中的“坐标位置”
	int di;			//从此通道块走向下一通道块的“方向”
}SElemType;			//栈的元素类型
Status MazePath(MazeType maze,PosType start,PosType end){
	InitStack(S);
	curpos=start;//当前位置为入口位置
	curstep=1;
	do{
		if(Pass(curpos)){	//当前位置可以通过，即是未曾走到过的通道块
			FootPrint(curpos);	//留下足迹
			e=(curstep,curpos,1);//SElemType类型
			Push(S,e);	//加入路径
			if(curpos==end)		//到达路径
				return TRUE;
			curpos=NextPos(curpos,1);	//下一位置是当前位置的东邻
			curstep++;	//探索下一步
		}
		else{	//当前位置不能通过
			if(!StackEmpty(S)){
				Pop(S,e);
				while(e.di==4 && !StackEmpty(S)){
					MarkPrint(e.seat);
					Pop(S,e);	//留下不能通过的标记，并退回一步
				}
				if(e.di<4){	//换下一个方向探索
					e.di++;
					Push(S,e);
					curpos=NextPos(e.seat,e.di);
				}
			}
		}
	}while(!StackEmpty(S));
	return FALSE;
}






//表达式求解
//为实现算符优先算法，可以使用两个工作栈。一个称为OPTR，用以寄存运算符；另一个称作OPND，用以寄存操作数或运算结果。
//（1）首先置操作数栈为空，表达式起始符'#'为运算符栈的栈底元素
//（2）依次读入表达式中每个字符，若是操作数则进OPND栈，若是运算符则和OPTR栈的栈顶运算符比较优先权后作相应操作，直至整个表达式求值完毕
OprandType EvaluateExpression(){
	//设OPTR和OPND分别为运算符栈和运算数栈
	//OP为运算符集合
	InitStack(OPTR);
	InitStack(OPND);
	Push(OPTR,'#');
	c=getchar();
	while(c!='#'||GetTop(OPTR)!='#'){
		if(!In(c,op))	//c不是运算符，则进运算数栈
			Push(OPND,c);
		else
			switch(Precede(GetTop(OPTR),c))
			{
			case '<':	//操作符栈栈顶元素优先权低于c
				Push(OPTR,c);
				break;
			case '=':	//等号时为括号匹配。
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