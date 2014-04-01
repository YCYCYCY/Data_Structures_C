/*************************************************************************
 > File Name: Linkstack.cpp
 > Author:  何源川
 > Mail: 249288984@qq.com 
 > Created Time: Tue 01 Apr 2014 12:22:33 PM CST
**************************************************************************/

#include<iostream>
using namespace std;
typedef struct StackNode
{
  SElemType data;
  struct StaticNode *next;
}StackNode;
typedef struct Linkstack
{
  StackNode* top;
  int count;
}LinkStack;
Status Push(LinkStack *stack,SElemType e)
{
  StackNode* newNode=new StackNode();
  newNode->data=e;
  newNode->next=stack->top;
  stack->top=newNode;
  stack->count ++;
  return OK;
}
Static Pop(LinkStack *stack,SElemType *e)
{
  stackNode*node;
  if(StackEmpty(*stack))
    return ERROR;
  *e=stack->top->data;
  node=stack->top;
  stack->top=stack->top->next;
  free(node);
  stack->count--;
  return OK;
}
