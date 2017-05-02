#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <string>
#include <cstring>
#include <cstdio>
#include <malloc.h>

#define Status      int
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1
#define OVERFLOW    -2


#define LIST_INIT_SIZE      10      // Default memory
#define LIST_INCRESAEMENT   10      // Increasing memory

using namespace std;

struct List{
    int length;
    int nowSize;
    int* element;
};

/* Create a list */
Status ListInit(List &L){
    L.length=0;                         // Default length
    L.nowSize=LIST_INIT_SIZE;           // Default size
    L.element=new int[LIST_INIT_SIZE];  // New
    if (L.element==NULL)                  // ERROR
        return OVERFLOW;
    memset(L.element,0,sizeof(L.element));
    return OK;
}

/* Destroy a list */
Status ListDestroy(List &L){
    L.length=0;
    L.nowSize=0;
    delete[] L.element;
    L.element=NULL;
    return OK;
}

/* Clear a list */
Status ListClear(List &L){
    memset(L.element,0,sizeof(L.element));  //Clear all items (Another way: free all items)
    L.length=0;                             // Default length
    return OK;
}

/* Judge if the list is empty */
bool ListEmpty(List L){
    return (L.length==0);
}

/* The length of a list */
int ListLength(List L){
    return L.length;
}

/* One elem of the list at position i */
Status ListGetElemByPosition(List L, int i, int &e){
    if ((i>L.length)||(i<=0))
        return INFEASIBLE;
    e=L.element[i];
    return OK;
}

/* Find a elem's position by its value */
int ListFindElemByValue(List L, int e){
    int findPosition=-1;
    for (int i=1;i<=L.length;i++)
        if (L.element[i]==e){
            findPosition=i;
            break;
        }
    return findPosition;
}

/* The precious element of element i */
Status ListPriorElem(List L, int cur_e, int &pre_e){
    int findPosition=-1;
    for (int i=1;i<=L.length;i++){
        if (cur_e==L.element[i]){
            findPosition=i;
            break;
        }
    }
    if ((findPosition==-1)||(findPosition==1))
        return INFEASIBLE;
    pre_e=L.element[findPosition];
    return OK;
}

/* The next element of element i */
Status ListNextElem(List L, int cur_e, int &pre_e){
    int findPosition=-1;
    for (int i=1;i<=L.length;i++){
        if (cur_e==L.element[i]){
            findPosition=i;
            break;
        }
    }
    if ((findPosition==-1)||(findPosition==L.length))
        return INFEASIBLE;
    pre_e=L.element[findPosition+1];
    return OK;
}

/* insert a element into the list at the position i */
Status ListInsertElem(List &L, int position, int e){
    // Chick if the pisition is right
    if ((position>L.length+1)||(position<=0))
        return INFEASIBLE;
    // If the memory is too small
    if (position>=L.nowSize){
        int* newElemBase=new int[L.nowSize+LIST_INCRESAEMENT];
        if (newElemBase==NULL)
            return OVERFLOW;
        memcpy(newElemBase, L.element, (L.length+1)*sizeof(L.element));
        delete[] L.element;
        L.element=newElemBase;
        L.nowSize+=LIST_INCRESAEMENT;
    }
    // Move the element
    for (int i=L.length;i>=position;i--)
        L.element[i+1]=L.element[i];
    // Insert it
    L.element[position]=e;
    L.length+=1;
    return OK;
}

/* Delete a element in list */
Status ListDeleteElem(List &L, int position, int &e){
    if ((position<=0)||(position>L.length))
        return INFEASIBLE;
    e=L.element[position];
    for (int i=position;i<=L.length;i++)
        L.element[i]=L.element[i+1];
    L.length-=1;
    return OK;
}

/* Show the detail of a list */
void ListShow(List L){
    cout<<"The length of the list: "<<ListLength(L)<<endl;
    cout<<"The size of the list: "<<L.nowSize<<endl;
    cout<<"The element(s) of the list: \n"<<endl;
    for (int i=1;i<=L.length;i++)
        cout<<L.element[i]<<" ";
    cout<<endl<<endl;
}

/* Set intersection (using lists)*/
void SetIntersection(List L1, List L2, List &Answer){
    ListInit(Answer);
    for (int i=1;i<=L1.length;i++){
        if (ListFindElemByValue(L2,L1.element[i])!=(-1))
            ListInsertElem(Answer,1,L1.element[i]);
    }
}

/* Set Union (using lists)*/
void SetUnion(List L1, List L2, List &Answer){
    ListInit(Answer);
    // insert all items distinctly into the aim set
    for (int i=1;i<=L1.length;i++){
        if (ListFindElemByValue(Answer,L1.element[i])==(-1))
            ListInsertElem(Answer,1,L1.element[i]);
    }
    // insert another set's items
    for (int i=1;i<=L2.length;i++){
        if (ListFindElemByValue(Answer,L2.element[i])==(-1))
            ListInsertElem(Answer,1,L2.element[i]);
    }
}

/* Set complement (using lists)(L1-l2)*/
Status SetComplement(List L1, List L2, List &Answer){
    ListInit(Answer);
    List temp;
    ListInit(temp);
    for (int i=1;i<=L1.length;i++){
        if (ListFindElemByValue(Answer,L1.element[i])==(-1))
            ListInsertElem(Answer,1,L1.element[i]);
    }
    for (int i=1;i<=L2.length;i++){
        if (ListFindElemByValue(temp,L2.element[i])==(-1))
            ListInsertElem(temp,1,L2.element[i]);
    }
    int findPosition=0;
    for (int i=1;i<=temp.length;i++){
        findPosition=ListFindElemByValue(Answer,temp.element[i]);
        if (findPosition==(-1)){
            ListClear(Answer);
            return INFEASIBLE;
        }
        else{
            int e;
            ListDeleteElem(Answer,temp.element[i],e);
        }
    }
    return OK;
}

int main()
{
    List iList;

    /* Some test... */

    cout<<"status: "<<  ListInit(iList) <<endl;

    ListShow(iList);

    for(int i=1;i<=25;i++){
        cout<<"status: "<<  ListInsertElem(iList,i,i)   <<endl;
        //ListShow(iList);
    }

    int e;
    for(int i=1;i<=10;i++){
        cout<<"status: "<<  ListDeleteElem(iList,i,e)   <<endl;
        //ListShow(iList);
    }

    List iList2, ans;
    ListInit(iList2);
    ListInit(ans);
    ListInsertElem(iList2,1,100);
    ListInsertElem(iList2,1,10);

    ListShow(iList);
    ListShow(iList2);

    SetIntersection(iList,iList2,ans);
    ListShow(ans);

    SetUnion(iList,iList2,ans);
    ListShow(ans);

    ListDeleteElem(iList2,2,e);

    if (SetComplement(iList,iList2,ans)==1){
        ListShow(ans);
    }else{
        cout<<"WRONG"<<endl;
    }

    return 0;
}
