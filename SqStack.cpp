/*************************************************************************
 > File Name: SqStack.cpp
 > Author:  何源川
 > Mail: 249288984@qq.com 
 > Created Time: Tue 01 Apr 2014 12:13:05 PM CST
**************************************************************************/

#include<iostream>
using namespace std;

typedef int SElemType;
typedef struct
{
  SElemType data[MAXSIZE];
  int top;
}SqStack;
Static Push (SqStack *s,SElemType e)
{
  if(S->top ==MAXSIZE-1)
  {
    return ERROR;
  }
  S->top++;
  S->data[S->top]=e;
  return OK;
}
Status Pop (SqStack *S,SElemType *e)
{
  if(S->top==-1)
    return ERROR;
  *e=S->data[S->top];
  S->top--;
  return OK;
}
