/*************************************************************************
 > File Name: reverse_polish.cpp
 > Author:  何源川
 > Mail: 249288984@qq.com 
 > Created Time: Tue 01 Apr 2014 12:43:38 PM CST
**************************************************************************/

//这是栈的一个应用
//计算机对表达式的处理方式
//(1):將中缀表达式转化成后缀表达式
//(2):將后缀表达式进行运算得出结果
//
//中缀表达式转后缀表达式的规则：从左到右遍历中缀表达式的每一个数字和符号。
//若是数字就输出；若是符号，则判断其与栈顶符号的优先级，是右括号或是优先级不高于栈顶符号则栈顶元素依次出栈并输出，否则將当前符号进栈，一直到最终输出后缀表达式为止。
//后缀表达式运算规则：
//从左到右遍历表达式的每个数字和符号，遇到数字就进栈
//遇到符号，就將栈顶两个数字出栈，进行运算，运算结果进栈，一直到获得结果
//
#include<iostream>
#include<string>
#include<stack>
#include<vector>
using namespace std;
void transform_suffix_expression(const string&,  string&);
double operation_suffix_expression(const string&);
bool not_prior_operator(char first,char second);
bool IsOperator(char);
bool IsNumber(char);
int main()
{
  string  expression,suffix_expression;
  cin>>expression;
  suffix_expression=expression;
  transform_suffix_expression(expression,suffix_expression);
  double result=operation_suffix_expression(suffix_expression);
  cout<<result;
  return 0;
}
void transform_suffix_expression(const string &exp, string &suff_exp)
{
  stack<char> sign_stack;
  int j=0;
  for(size_t i=0;i!=exp.length();++i)
  {
    if(IsOperator(exp[i])) 
    {
      if(exp[i]==')')
      {
        while(sign_stack.top()!='(')
        {
          suff_exp[j++]=sign_stack.top();
          sign_stack.pop();
        }
        sign_stack.pop();
      }
      else if(not_prior_operator(exp[i],sign_stack.top()))
      {
        suff_exp[j++]=exp[i];
        while(!sign_stack.empty())
        {
          suff_exp[j++]=(sign_stack.top());
          sign_stack.pop();
        }
      }
      else 
      {
        sign_stack.push(exp[i]);
      }
      
    }
    else if(IsNumber(exp[i]))
    {
      suff_exp.push_back(exp[i]);
    }
    else 
      return ;

  }
  
}
double operation_suffix_expression(const string &suff_exp)
{
  stack<char> elem_stack;
  for(size_t i=0;i!=suff_exp.length();++i)
  {
    if(IsOperator(suff_exp[i])&&IsNumber(elem_stack.top()))
    {
      int num1=elem_stack.top()-'0';
      elem_stack.pop();
      int num2=elem_stack.top()-'0';
      elem_stack.pop();
      if(suff_exp[i]=='+')
        elem_stack.push(num1+num2);
      else if(suff_exp[i]=='-')
        elem_stack.push(num2-num1);
      else if(suff_exp[i]=='*')
        elem_stack.push(num2*num1);
      else
        elem_stack.push(num2/num1);
    }
    else if(IsNumber(suff_exp[i]))
    {
      elem_stack.push(suff_exp[i]);
    }
    else
      return -1;
  }
  return (elem_stack.top()-'0');
}

bool not_prior_operator( char first,char second)
{
  if((first=='+'||first=='-') &&(second =='*'||second=='/'))
    return true;
  else
    return false;
}
bool IsOperator(char charater)
{
  if(charater =='+'||charater=='-'||charater=='*'||charater=='/')
    return true;
  else if(charater=='('||charater==')')
    return true;
  else
    return false;
}
bool IsNumber(char charater)
{
  if(charater>='0'&& charater<='9')
    return true;
  else 
    return false;
}
