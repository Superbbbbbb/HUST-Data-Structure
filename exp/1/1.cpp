#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int status;
typedef int ElemType;
typedef struct{
    ElemType * elem;
    int length;
    int listsize;
}SqList;
typedef struct{
     struct { char name[30];
              SqList L;
      } elem[10];
      int length;
 }LISTS;
status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList& L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType &e);
int LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType e,ElemType &pre);
status NextElem(SqList L,ElemType e,ElemType &next);
status ListInsert(SqList &L,int i,ElemType e);
status ListDelete(SqList &L,int i,ElemType &e);
status ListTraverse(SqList L);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,int i);
int LocateList(LISTS Lists,char ListName[]);
status Input(SqList &L);
status SaveList(SqList L,char FileName[]);
status LoadList(LISTS &Lists,char FileName[]);

int main(){
    SqList L;
    L.elem=NULL;
    LISTS Lists;
    int n,i,j,e,pre,next,op,x,flag;
    char FileName[30],name[30],Name[30];
    Lists.length=0;
    printf("      Menu for Linear Table On Sequence Structure \n");
    printf("-----------------------------------------------------\n");
    printf("    	  1. InitList(单)   9.  NextElem\n");
    printf("    	  2. DestroyList(单)10. ListInsert\n");
    printf("    	  3. ClearList      11. ListDelete\n");
    printf("    	  4. ListEmpty      12. ListTrabverse\n");
    printf("    	  5. ListLength     13. SaveList\n");
    printf("    	  6. GetElem        14. LoadList(多)\n");
    printf("    	  7. LocateElem     15. AddList(多)\n");
    printf("    	  8. PriorElem      16. RemoveList(多)\n");
    printf("    	  0. Exit           17. LocateList(多)\n");
    printf("-----------------------------------------------------\n");
    printf("          \n单线性表操作输入0，多线性表操作输入1:");
    scanf("%d",&flag);							//flag标记单或多操作
    while(1){
        printf("      \n请选择你的操作[0~17]: ");
        scanf("%d",&op);                            //选择的功能编号
        if(!flag&&op>13){
            printf("请选择多线性表操作\n");
            continue;
        }
        if(flag&&op>0&&op<3){
            printf("请选择单线性表操作\n");
            continue;
        }
        if(flag&&op<14&&op>0){		//若对多线性表中的某个表进行操作
            printf("\n输入操作的线性表的名字: ");
            scanf("%s",Name);
            x=LocateList(Lists,Name)-1;
            if(x>=0) L=Lists.elem[x].L;		   //调用LocateList查找
            else{
                printf("INFEASIBLE\n");
                continue;
            }
        }
        switch(op){
            case 1:										//初始化
                if(L.elem) printf("INFEASIBLE\n");
                else
                    if(InitList(L)){					//创建线性表成功
                        Input(L);						//输入线性表元素
                        printf("OK\n");
                    }
                    else printf("ERROR\n");
                break;
            case 2:
                if(!L.elem) printf("INFEASIBLE\n");
                else{
                    if(flag) j=DestroyList(Lists.elem[x].L);
                    else j=DestroyList(L);
                    if(j) printf("OK\n");
                    else printf("ERROR\n");
                }
                break;
            case 3:										//清空
                if(!L.elem) printf("INFEASIBLE\n");
                else{
                    if(flag) j=ClearList(Lists.elem[x].L);
                    else j=ClearList(L);
                    if(j) printf("OK\n");
                    else printf("ERROR\n");
                }
                break;
            case 4:										//判空
                if(!L.elem) printf("INFEASIBLE\n");
                else
                    if (ListEmpty(L)) printf("TRUE\n");
                    else printf("FALSE\n");
                break;
            case 5:										//求表长
                if(!L.elem) printf("INFEASIBLE\n");
                else printf("%d\n",ListLength(L));
                break;
            case 6:										//获取
                if(!L.elem) printf("INFEASIBLE\n");
                else if(!L.length) printf("空线性表\n");
                else{
                    printf("输入要获取的元素的位置:");
                    scanf("%d",&i);
                    if(GetElem(L,i,e)) printf("%d\n",e);
                    else printf("ERROR\n");
                }
                break;
            case 7:										//查找
                if(!L.elem) printf("INFEASIBLE\n");
                else if(!L.length) printf("空线性表\n");
                else{
                    printf("输入要查找位置的元素:");
                    scanf("%d",&e);
                    if(LocateElem(L,e)) printf("%d\n",j);
                    else printf("ERROR\n");
                }
                break;
            case 8:										//前驱
                if(!L.elem) printf("INFEASIBLE\n");
                else if(!L.length) printf("空线性表\n");
                else{
                    printf("输入要查找的元素:");
                    scanf("%d",&e);
                    if(PriorElem(L,e,pre)) printf("%d\n",pre);
                    else printf("ERROR\n");
                }
                break;
            case 9:										//后继
                if(!L.elem) printf("INFEASIBLE\n");
                else if(!L.length) printf("空线性表\n");
                else{
                    printf("输入要查找的元素:");
                    scanf("%d",&e);
                    if(NextElem(L,e,next)) printf("%d\n",next);
                    else printf("ERROR\n");
                }
                break;
            case 10:									//插入
                if(!L.elem) printf("INFEASIBLE\n");
                else{
                    printf("输入要插入的位置和元素:");
                    scanf("%d%d",&i,&e);
                    j=ListInsert(L,i,e);
                    if(flag) Lists.elem[x].L.length++;
                    else L.length++;
                    if(j) ListTraverse(L);
                    else printf("ERROR\n");
                }
                break;
            case 11:									//删除
                if(!L.elem) printf("INFEASIBLE\n");
                else if(!L.length) printf("空线性表\n");
                else{
                    printf("输入要删除元素的位置:");
                    scanf("%d",&i);
                    j=ListDelete(L,i,e);
                    if(j){
                        if(flag) Lists.elem[x].L.length--;
                        else L.length--;
                        ListTraverse(L);
                    }else printf("ERROR\n");
                }
                break;
            case 12:									//遍历
                if(!L.elem) printf("INFEASIBLE\n");
                else if(!L.length) printf("空线性表\n");
                else ListTraverse(L);
                break;
            case 13:									//写入文件
                if(!L.elem) printf("INFEASIBLE\n");
                else{
                    i=0;
                    printf("输入文件名:");
                    scanf("%s",FileName);
                    if(SaveList(L,FileName))
                        printf("OK\n");
                    else printf("ERROR\n");
                }
                break;
            case 14:									//读取文件
                printf("输入文件名:");
                scanf("%s",FileName);
                while(1){
                    printf("输入线性表名:");
                    scanf("%s",name);
                    if(LocateList(Lists,name))
                    printf("重名\n");			        //重名,重新输入
                    else break;
                }
                AddList(Lists,name);
                if(LoadList(Lists,FileName))
                    ListTraverse(Lists.elem[Lists.length-1].L);
                else printf("ERROR\n");
                break;
            case 15:									//添加新表
                printf("输入要增加的线性表的个数:");
                scanf("%d",&n);
                if(Lists.length+n>10){				//表总数溢出
                    printf("OVERFLOW\n");
                    break;
                }
                while(n--){
                    printf("输入线性表名字:");
                    scanf("%s",name);
                    if(LocateList(Lists,name)){   //判断是否有重名
                        printf("重名\n");
                        n++;
                        continue;
                    }
                    else{
                        if(AddList(Lists,name)){
                            Input(Lists.elem[Lists.length-1].L);
                            printf("OK\n");
                        }else printf("ERROR\n");
                    }
                }
                break;
            case 16:									//删除表
                printf("输入要删除的线性表的名字:");
                scanf("%s",name);
                if(LocateList(Lists,name)){		//查找表
                    if(RemoveList(Lists,LocateList(Lists,name)-1))
                        for(n=0;n<Lists.length;n++){
                            printf("%s ",Lists.elem[n].name);
                            ListTraverse(Lists.elem[n].L);
                        }
                }else printf("删除失败\n");
                break;
            case 17:									//查找表
                printf("输入要查找的线性表的名字:");
                scanf("%s",name);
                if (n=LocateList(Lists,name)){
                    printf("%s ",Lists.elem[n-1].name);
                    ListTraverse(Lists.elem[n-1].L);
                }else printf("查找失败\n");
                break;
            case 0:
                goto down;
        }
    }
	down:
    printf("\n欢迎下次再使用本系统！\n");
    return 0;
}

status Input(SqList &L){
    int i;
    printf("输入元素,结束输入0:\n");
    scanf("%d",&i);
    while(i){
        L.elem[L.length++]=i;
        scanf("%d",&i);
    }
}

status InitList(SqList& L){							//初始化
    L.length=0;
    L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
                                                    //分配内存
    L.listsize=LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList& L){						//销毁
    free(L.elem);										//释放内存
    L.length=0;
    L.elem=NULL;
    return OK;
}

status ClearList(SqList& L){						//清空
    L.length=0;
    return OK;
}

status ListEmpty(SqList L){							//判空
    if(L.length) return FALSE;
    else return TRUE;
}

status ListLength(SqList L){						//求表长
    return L.length;
}

status GetElem(SqList L,int i,ElemType &e){			//获取
    if(i<1||i>L.length) return ERROR;				//位置不合法
    else{
        e=L.elem[i-1];
        return OK;
    }
}

int LocateElem(SqList L,ElemType e){				//查找
    int i;
    for(i=0;i<L.length;i++)
        if(L.elem[i]==e) return i+1;
    return 0;
}

status PriorElem(SqList L,ElemType e,ElemType &pre){
    int i=LocateElem(L,e);							//调用LocateElem
    if(i>1){										//判断i是否合法
        pre=L.elem[i-2];
        return OK;
    }
    else return ERROR;
}

status NextElem(SqList L,ElemType e,ElemType &next){
    int i=LocateElem(L,e); 							//调用LocateElem
    if(0<i<L.length){								//判断i是否合法
        next=L.elem[i];
        return OK;
    }
    else return ERROR;
}

status ListInsert(SqList &L,int i,ElemType e){		//插入
    int j;
    if(i>L.length+1||i<1) return ERROR;				//位置不合法
        else if(!L.length){
            L.elem[0]=e;
            return OK;
        }
    else{
        if(L.length+1>LIST_INIT_SIZE){	//如果插入后溢出，重新分配
            ElemType *newelem=(ElemType*)realloc(L.elem,sizeof(ElemType)*LIST_INIT_SIZE+LISTINCREMENT);
            L.elem=newelem;
        }
        for(j=L.length-1;j>=i-1;j--)
            L.elem[j+1]=L.elem[j];
        L.elem[i-1]=e;
        return OK;
    }
}

status ListDelete(SqList &L,int i,ElemType &e){		//删除
    int j;
    if(i<1||i>L.length) return ERROR;				//位置不合法
    else{
        e=L.elem[i-1];
        for(j=i-1;j<L.length-1;j++)
            L.elem[j]=L.elem[j+1];
        return OK;
    }
}

status ListTraverse(SqList L){						//遍历
    int i;
    for(i=0;i<L.length;i++){
        printf("%d",L.elem[i]);
        if(i!=L.length-1) printf(" ");
        else printf("\n");
    }
    return OK;
}

status SaveList(SqList L,char FileName[]){			//写入文件
    FILE *fp;
    int i=0;
    if(!(fp=fopen(FileName,"wb")))	return ERROR;   //打开文件失败
    else{
        while(i<L.length){
            fprintf(fp,"%d ",L.elem[i]);			//线性表写入文件
            i++;
        }
        fclose(fp);
        return OK;
    }
}

status LoadList(LISTS &Lists,char FileName[]){		//读出文件
    FILE *fp;
    int i=0;
    if(!(fp=fopen(FileName,"rb")))	return ERROR;   //打开文件失败
    else{
        while((fscanf(fp,"%d ",&Lists.elem[Lists.length-1].L.elem[i]))!=EOF)										//读入线性表中
            if(!feof(fp)) i++;
        Lists.elem[Lists.length-1].L.length=i+1;		//表总数加一
        fclose(fp);
		 return OK;
    }
}

status AddList(LISTS &Lists,char ListName[]){		//增加新表
    strcpy(Lists.elem[Lists.length].name,ListName);
   Lists.elem[Lists.length].L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    Lists.elem[Lists.length].L.length=0;			//长度为0
    Lists.length++;
    return OK;										//表总数加一
}

status RemoveList(LISTS &Lists,int i){				//删除表
    free(Lists.elem[i].L.elem);						//释放内存
    for(int j=i;j<Lists.length-1;j++)
        Lists.elem[j]=Lists.elem[j+1];				//前一个覆盖
    Lists.length--;
    return OK;
}

int LocateList(LISTS Lists,char ListName[]){		//查找表
    for(int i=0;i<Lists.length;i++)
        if(!strcmp(ListName,Lists.elem[i].name))	//名字相同
            return i+1;
    return 0;
}
