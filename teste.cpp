 #include<string.h>
 #include<ctype.h>
 #include<malloc.h> /* malloc()等 */
 #include<limits.h> /* INT_MAX等 */
 #include<stdio.h> /* EOF(=^Z或F6),NULL */
 #include<stdlib.h> /* atoi() */
 #include<io.h> /* eof() */
 #include<math.h> /* floor(),ceil(),abs() */
 #include<process.h>

#define OK 1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define ERROR 0

typedef int ElemType;
typedef int Status;

typedef struct
{

ElemType *elem;
int length;
int listsize;

}SqList;

Status InitList_Sq(SqList &L);

Status ListInsert_Sq(SqList &L, int i, ElemType e);

Status PriorElem_Sq(SqList L,ElemType cur_e,ElemType &pre_e);

Status ListTraverse_Sq(SqList L);

Status NextElem_Sq(SqList L,ElemType cur_e,ElemType &next_e);

Status ListDelete_Sq(SqList &L, int i,ElemType &e);

Status GetElem(SqList L,int i,ElemType &e);

void MergeList_Sq(SqList La, SqList Lb, SqList &Lc);

Status DestroyList_Sq(SqList &L);



int main(void)
{
	int i;
	SqList LA,LB,LC;
	ElemType pre_e,next_e,del_e;
	
	InitList_Sq(LA);
	InitList_Sq(LB);
	
	ListInsert_Sq(LA,1,9);
	ListInsert_Sq(LA,1,6);
	ListInsert_Sq(LA,1,3);
	ListInsert_Sq(LA,1,5);

	ListTraverse_Sq(LA);

	ListInsert_Sq(LB,1,7);
	ListInsert_Sq(LB,1,2);
	ListInsert_Sq(LB,1,5);
	ListInsert_Sq(LB,1,8);
    ListInsert_Sq(LB,1,9);

	ListTraverse_Sq(LB);

	printf("\n");


	printf("%d\n",pre_e);

	printf("\n");

	NextElem_Sq(LB,8,pre_e);

	printf("%d\n",pre_e);

    PriorElem_Sq(LA,6,pre_e);

	ListDelete_Sq(LB,2,del_e);

	printf("%d\n",del_e);

	ListTraverse_Sq(LB);


	MergeList_Sq(LA,LB,LC);

	printf("Lc=");

	ListTraverse_Sq(LC);

	//getchar();

	DestroyList_Sq(LC);
	
	printf("Lc=");

	ListTraverse_Sq(LC);


    return 0;

}


Status InitList_Sq(SqList &L)
{
	

L.elem=(ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));

if(!L.elem)exit(OVERFLOW);

L.length = 0;

L.listsize = LIST_INIT_SIZE;

return OK;
}

Status ListInsert_Sq(SqList &L, int i,ElemType e)
{
	ElemType *newbase,*q,*p;
	if(i<1||i>L.listsize+1)
	return ERROR;
    if(L.length>=L.listsize)
	{
		newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)exit(OVERFLOW);
		L.elem=newbase;
		L.listsize+=LISTINCREMENT;	
	 } 

	 q = &(L.elem[i-1]);
	 for(p=&(L.elem[L.length-1]);p>=q;--p)*(p+1)=*p;
	 *q=e;
	 ++L.length;
	 return OK;
}

Status ListTraverse_Sq(SqList L)
{
    int i;
	
	for(i=0;i < L.length;i++)
	{
		printf("%d",L.elem[i]);
	}

	printf("\n");
	
	return OK;
   
}

Status PriorElem_Sq(SqList L,ElemType cur_e,ElemType &pre_e)
{
    int i;
	
	for(i=1;i < L.length;i++)
	{
		if(cur_e == L.elem[i])
		
		pre_e = L.elem[i-1];
	}
	
	return OK;
}

Status NextElem_Sq(SqList L,ElemType cur_e,ElemType &next_e)
{
	int i;
	
	for(i=1;i < L.length;i++)
	{
		if(cur_e == L.elem[i])
		
		next_e = L.elem[i+1];
	}
	
	return OK;
}

Status ListDelete_Sq(SqList &L, int i,ElemType &e)
{
	
	 ElemType *q,*p;
	 int c;

	 c=0;
	
	 p = &(L.elem[i-1]);

	 e = *p;

	 for(q = &(L.elem[i-1]); q < &(L.elem[L.length]); ++q)

	 *q=*(q+1);
	 
	 --L.length;
	 return OK;
}

Status GetElem(SqList L,int i,ElemType &e)
 { 
   if(i<1||i>L.length)
     exit(ERROR);

   e=*(L.elem+i-1);

   return OK;
 }

void MergeList_Sq(SqList La, SqList Lb, SqList &Lc)
 { 
   
   ElemType *pa,*pa_last,*pb,*pb_last,*pc;

   pa=La.elem;
   pb=Lb.elem;

   Lc.listsize=Lc.length=La.length+Lb.length;
   pc=Lc.elem=(ElemType *)malloc(Lc.listsize*sizeof(ElemType));

   if(!Lc.elem)
     exit(OVERFLOW);

   pa_last=La.elem+La.length-1;
   pb_last=Lb.elem+Lb.length-1;//

   while(pa<=pa_last&&pb<=pb_last) 
   { 
     if(*pa<=*pb)
       *pc++=*pa++;
     else
       *pc++=*pb++;
   }

   while(pa<=pa_last) 
     *pc++=*pa++; 
     
   while(pb<=pb_last)
     *pc++=*pb++; 

 }

 Status DestroyList_Sq(SqList &L)
{
	free(L.elem);
	L.elem = NULL;

	L.length = 0;
	L.listsize = 0;

	return OK;
}