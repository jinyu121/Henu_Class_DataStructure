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
#include <malloc.h>

#define Status      int
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1

using namespace std;

struct Node{
    int Data;
    Node* next;
};

struct LinkedList{
    Node* head;
    int length;
};

Status LinkedListInit(LinkedList &L){
    /* Create the header node */
    L.head=new Node;
    /* Set the header node's next with NULL */
    L.head->next=NULL;
    /* Default length is 0 */
    L.length=0;
    return OK;
}

Status LinkedListDestroy(LinkedList &L){
    /* Free all of the items one by one. */
    Node* pNow;
    Node* pNext;
    pNow=L.head;
    pNext=(pNow->next);
    while (pNext){
        delete pNow;
        pNow=pNext;
        pNext=pNow->next;
    }
    delete pNow;
    /* And set the head pointer NULL. */
    L.head=NULL;
    /* And edit the length */
    L.length=0;
    return OK;
}

Status LinkedListClear(LinkedList &L){
    /* Destroy the list first */
    LinkedListDestroy(L);
    /* Then, create a new one */
    LinkedListInit(L);
    return OK;
}

bool LinkedListIsEmpty(LinkedList L){
    return (L.length==0);
}

int LinkedListLength(LinkedList L){
    return L.length;
}

Status LinkedListGetElemByPosition(LinkedList L, int position, int &e){
    Node* p;

    /* Some error: the input is illegal */
    if (position<=0 || position>L.length)
        return INFEASIBLE;

    /* Get to the position through the chain */
    p=L.head;
    for (int i=1;i<=position;i++)
        p=p->next;
    /* OK, got it! */
    e=p->Data;

    return OK;
}

int LinkedListGetPositionByValue(LinkedList L, int value){
    int findPosition=-1;
    int stepCounter=0;
    Node* p=L.head->next;
    /* Get to the aimed element through the chain */
    while (p!=NULL){
        /* Increase the step counter (as well as the position) */
        stepCounter++;
        /* Got it! */
        if (p->Data==value){
            findPosition=stepCounter;
            break;
        }
        p=p->next;
    }

    return findPosition;
}

Status LinkedListPriorElem(LinkedList L, int position, int &e){
    /* Some error: out of range */
    if (position<=1 || position>L.length)
        return INFEASIBLE;
    Node* p=L.head;
    /* there should be "<" rather than "<=" */
    for (int i=1;i<position;i++)
        p=p->next;
    e=p->Data;

    return OK;
}

Status LinkedListNextElem(LinkedList L, int position, int &e){
    /* Some error: out of range */
    if (position<=0 || position>=L.length)
        return INFEASIBLE;
    /* There are some small differents whith the prior one! */
    Node* p=L.head->next;
    for (int i=1;i<=position;i++)
        p=p->next;
    e=p->Data;

    return OK;
}

Status LinkedListInsert(LinkedList &L, int position, int value){
    /* The position is illegal */
    if (position<1 || position>L.length+1)
        return INFEASIBLE;
    /*  */
    Node* p=L.head;
    for (int i=1;i<position;i++)
        p=p->next;
    /* Create a new node */
    Node* newNode=new Node;
    newNode->Data=value;
    /* insert it into the linked list */
    newNode->next=p->next;
    p->next=newNode;
    /* Edit the length */
    L.length++;
    return OK;
}

Status LinkedListDelete(LinkedList &L, int position, int value){
    /* The position is illegal */
    if (position<1 || position>L.length)
        return INFEASIBLE;
    /*  */
    Node* p=L.head;
    for (int i=1;i<position;i++)
        p=p->next;
    /* The elem which is ready to delete */
    Node* oldNode=p->next;
    /* Make it off the linked list */
    p->next=oldNode->next;
    /* Delete it */
    delete oldNode;
    /* Edit the length */
    L.length--;
    return OK;
}

void LinkedListShow(LinkedList L){
    cout<<"Length: "<<L.length<<endl;
    cout<<"Elements: "<<endl;
    Node* p=L.head->next;
    for(;p;p=p->next)
        cout<<p->Data<<" ";
        //cout<<p<<"\t"<<p->Data<<endl;
    cout<<endl<<endl;
}

void LinkedListMerge(LinkedList &L1, LinkedList &L2){
    Node* p1=L1.head->next;
    Node* p2=L2.head->next;
    Node* p=L1.head;

    /* Merge */
    for(;p1&&p2;){
        if (p1->Data<p2->Data){
            p->next=p1;
            p1=p1->next;
        }else{
            p->next=p2;
            p2=p2->next;
        }
        /* !! REMEMBER TO MOVING THE POINTER !! */
        p=p->next;
    }
    /* Merge the remains */
    p->next=p1?p1:p2;
    /* Edit the length */
    L1.length+=L2.length;

    /* Destroy the second linked list */
    L2.head->next=NULL;
    LinkedListClear(L2);
}

int main(){
    //freopen (".in", "r", stdin);
    //freopen (".out", "w", stdout);
    int e;

    LinkedList iList;
    LinkedListInit( iList );
    LinkedListShow(iList);
    /* Insert test */
    for (int i=1;i<=10;i++)
        LinkedListInsert(iList,i,i);
    LinkedListShow(iList);
    /* Delete test*/
    for (int i=1;i<=5;i++)
        LinkedListDelete(iList,i,e);
    LinkedListShow(iList);
    /* Test for Get Value By Position */
    LinkedListGetElemByPosition(iList,2,e);
    cout<<e<<endl;
    /* Test for Get Value By Value */
    cout<<LinkedListGetPositionByValue(iList,4)<<endl;
    /* Test for The Prior Elem */
    LinkedListPriorElem(iList,3,e);
    cout<<e<<endl;
    /* Test for The Next Elem */
    LinkedListNextElem(iList,3,e);
    cout<<e<<endl;

    /* MERGE */
    LinkedList iList2;
    LinkedListInit( iList2 );
    for (int i=1;i<=10;i++)
        LinkedListInsert(iList2,i,i);
    LinkedListDelete(iList2,2,e);
    LinkedListDelete(iList2,4,e);
    LinkedListDelete(iList2,6,e);
    LinkedListShow(iList2);

    LinkedListMerge(iList,iList2);
    LinkedListShow(iList);
    LinkedListShow(iList2);

    LinkedListClear(iList);
    LinkedListShow(iList);

    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
