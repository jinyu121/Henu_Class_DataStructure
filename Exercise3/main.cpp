/*
ID: jinyu121
PROG:
LANG: C++
EDIT: 1.0
*/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cmath>
#include <stack>
#include <queue>

#define Status      int
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1

#define STACK_INIT_SIZE      10      // Default memory
#define STACK_INCRESAEMENT   10      // Increasing memory

using namespace std;

struct Stack{
    int nowSize;
    /* I assume that the top pointer points the top element rather than the top+1 element which is always empty */
    int top;
    int* element;
};

Status StackInit(Stack &S){
    int* p=new int[STACK_INIT_SIZE];
    if (!p)
        return ERROR;
    S.element=p;
    S.nowSize=STACK_INIT_SIZE;
    S.top=0;
    return OK;
}

Status StackDestroy(Stack &S){
    /* It has been destroyed or has not been constructed */
    if (!S.element)
        return ERROR;
    /* Delete the elements */
    delete S.element;
    /* Reset something */
    S.top=0;
    S.nowSize=0;
    return OK;
}

Status StackClear(Stack &S){
    /* Clear = Destroy + Construct */
    StackDestroy(S);
    StackInit(S);
    return OK;
}

bool StackEmpty(Stack S){
    /* I suppose that the stack has been constructed */
    return (S.top==0);
}

int StackLength(Stack S){
    /* The same as the former one */
    return S.top;
}

Status StackGetTop(Stack S, int &e){
    /* The stack is empty */
    if (0==S.top)
        return ERROR;
    e=S.element[S.top];
    return OK;
}

Status StackPush(Stack &S, int e){
    /* See if it is full */
    if (S.top+1>=S.nowSize){
        int* newBase=new int[S.nowSize+STACK_INCRESAEMENT];
        if (!newBase)
            return ERROR;
        memcpy(newBase,S.element,(S.top+1)*sizeof(S.element));
        S.element=newBase;
        S.nowSize+=STACK_INCRESAEMENT;
    }
    /* Add to the stack */
    S.top++;
    S.element[S.top]=e;
    return OK;
}

Status StackPop(Stack &S, int &e){
    /* See if it is empty */
    if (0==S.top)
        return ERROR;
    e=S.element[S.top];
    S.top--;
    return OK;
}

void StackShow(Stack S){
    cout<<"The length of the stack: "<<StackLength(S)<<endl;
    cout<<"The size of the stack: "<<S.nowSize<<endl;
    cout<<"The element(s) of the stcak:"<<endl;
    for (int i=1;i<=S.top;i++)
        cout<<S.element[i]<<" ";
    cout<<endl<<endl;
}

void BracketsMate(string str){
    /* Oh, i used something provided by the C++ library... */
    stack< pair<char,int> > iStack;
    queue< pair<int, int> > trace;
    pair<char,int> sTemp;
    pair<int,int> qTemp;

    int errorOccurredPosition=str.length()-1;

    bool yes=true;

    /* Mate the string */
    for (int i=0;i<str.length()&&yes;i++){
        if (str[i]=='(' || str[i]=='[' || str[i]=='{'){
            sTemp.first=str[i];
            sTemp.second=i;
            iStack.push(sTemp);
            continue;
        }
        if (str[i]==')' || str[i]==']' || str[i]=='}'){
            if (!iStack.empty()){
                sTemp=iStack.top();
                if (((sTemp.first=='(') && (str[i]==')'))||
                    ((sTemp.first=='[') && (str[i]==']'))||
                    ((sTemp.first=='{') && (str[i]=='}'))){
                    iStack.pop();
                    qTemp.first=sTemp.second;
                    qTemp.second=i;
                    trace.push(qTemp);
                }else{
                    errorOccurredPosition=i;
                    yes=false;
                }
            }else{
                errorOccurredPosition=i;
                yes=false;
            }
        }
    }
    /* Handle the remaining */
    if(!iStack.empty())
        yes=false;
    /* Ok, now output the result */
    if (yes){
        cout<<"RIGHT!"<<endl;
    }
    else{
        cout<<"WRONG!"<<endl;
        cout<<"Error occurred at "<<errorOccurredPosition<<endl;
        cout<<"I will just output the mated bracket(s) before where it not paired."<<endl;
    }
    cout<<"The following bracket(s) are mated:"<<endl;
    for(;!trace.empty();){
        pair<int,int> p=trace.front();
        cout<<p.first<<" and "<<p.second<<endl;
        trace.pop();
    }
    cout<<endl;
}

int main(){
    //freopen (".in", "r", stdin);
    //freopen (".out", "w", stdout);

    int e=0;

    Stack iStack;
    StackInit(iStack);

    for (int i=1;i<=10;i++)
        StackPush(iStack,i);
    StackShow(iStack);

    for (int i=1;i<=5;i++){
        StackPop(iStack,e);
        cout<<"Poped "<<e<<endl;
    }
    StackShow(iStack);

    BracketsMate("()()}{}[][]{{}}[");
    BracketsMate("3+2*(2+2)-1");
    BracketsMate("()(){}{}[][]{{}}");
    BracketsMate("()(){}{}[][]{{}}[");


    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
