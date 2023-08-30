#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int status;
typedef int ElemType;
typedef struct LNode{
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct{
     struct { char name[30];
              LinkList L;
      }elem[10];
      int length;
}LISTS;
status InitList(LinkList& L);
status DestroyList(LinkList& L);
status ClearList(LinkList& L);
status ListEmpty(LinkList L);
status ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType &e);
int LocateElem(LinkList L,ElemType e);
status PriorElem(LinkList L,ElemType e,ElemType &pre);
status NextElem(LinkList L,ElemType e,ElemType &next);
status ListInsert(LinkList &L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType &e);
status ListTraverse(LinkList L);
status SaveList(LinkList L,char FileName[]);
status LoadList(LISTS &Lists,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,int i);
int LocateList(LISTS Lists,char ListName[]);
status Input(LinkList &L);

int main(){
    int op,i,j,e,pre,next,flag,x,n;
    LinkList L=NULL;
    LISTS Lists;
    Lists.length=0;
    char FileName[30],name[30],Name[30];
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
    printf("          单线性表操作输入0，多线性表操作输入1:");
    scanf("%d",&flag);
    while(1){
        printf("          \n请选择你的操作[0~17]:");
        scanf("%d",&op);
        if(!flag&&op>13){
            printf("请选择多线性表操作\n");
            continue;
        }
        if(flag&&op>0&&op<3){
            printf("请选择单线性表操作\n");
            continue;
        }
        if(flag&&op<14&&op>0){
            printf("\n输入操作的线性表的名字：");
            scanf("%s",Name);
            x=LocateList(Lists,Name)-1;
            if(x>=0) L=Lists.elem[x].L;
            else{
                printf("INFEASIBLE\n");
                continue;
            }
        }
        switch(op){
            case 1:
                if(L) printf("INFEASIBLE\n");
                else
                    if(InitList(L)){					//创建成功
                        Input(L); 						//输入元素
                        printf("OK\n");
                }else printf("ERROR\n");
                break;
            case 2:
                if(!L) printf("INFEASIBLE\n");
                else{
                    if(flag) j=DestroyList(Lists.elem[x].L);
                    else j=DestroyList(L);
                    if(j) printf("OK\n");
                    else printf("ERROR\n");
                }
                break;
            case 3:										//清空
                if(!L) printf("INFEASIBLE\n");
                else
                    if(ClearList(L)&&L&&!L->next) printf("OK\n");
                    else printf("ERROR\n");
                break;
            case 4:										//判空
                if(!L) printf("INFEASIBLE\n");
                else
                    if(ListEmpty(L)) printf("TRUE\n");
                    else printf("FALSE\n");
                break;
            case 5:										//求表长
                if(!L) printf("INFEASIBLE\n");
                else printf("%d\n",ListLength(L));
                break;
            case 6:										//获取
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("空线性表\n");
                else{
                    printf("输入要获取的元素的位置：");
                    scanf("%d",&i);
                    if(GetElem(L,i,e)) printf("%d\n",e);
                    else printf("ERROR\n");
                }
                break;
            case 7:										//查找
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("空线性表\n");
                else{
                    printf("输入要获取位置的元素：");
                    scanf("%d",&e);
                    if(LocateElem(L,e)) printf("%d\n",j);
                    else printf("ERROR");
                }
                break;
            case 8:										//前驱
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("空线性表\n");
                else{
                    printf("输入要查找的元素：");
                    scanf("%d",&e);
                    if(PriorElem(L,e,pre)) printf("%d\n",pre);
                    else printf("ERROR\n");
                }
                break;
            case 9:										//后继
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("空线性表\n");
                else{
                    printf("输入要查找的元素：");
                    scanf("%d",&e);
                    if(NextElem(L,e,next)) printf("%d\n",next);
                    else printf("ERROR\n");
                }
                break;
            case 10:										//插入
                if(!L) printf("INFEASIBLE\n");
                else{
                    printf("输入要插入的位置和元素：");
                    scanf("%d%d",&i,&e);
                    if(ListInsert(L,i,e)) ListTraverse(L);
                    else printf("ERROR");

                }
                break;
            case 11:										//删除
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("空线性表\n");
                else{
                    printf("输入要删除的元素的位置：");
                    scanf("%d",&i);
                    if(ListDelete(L,i,e)) ListTraverse(L);
                    else printf("ERROR\n");
                }
                break;
            case 12:										//遍历
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("空线性表\n");
                else ListTraverse(L);
                break;
            case 13:          							//写入文件
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("空线性表\n");
                else{
                    printf("输入文件名：");
                    scanf("%s",FileName);
                    if(SaveList(L,FileName))
                        printf("OK\n");
                    else printf("ERROR\n");
                }
                break;
            case 14:
                printf("输入文件名:");
                scanf("%s",FileName);
                while(1){
                    printf("输入线性表名:");
                    scanf("%s",name);
                    if(LocateList(Lists,name))
                        printf("重名\n");			//重名,重新输入
                    else break;
                }
                AddList(Lists,name);
                if(LoadList(Lists,FileName))
                    ListTraverse(Lists.elem[Lists.length-1].L);
                else printf("ERROR\n");
                break;
            case 15:										//增加新表
                printf("输入要增加的线性表的个数:");
                scanf("%d",&n);
                if(Lists.length+n>10){					//溢出
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
                    else
                        if(AddList(Lists,name))
                            Input(Lists.elem[Lists.length-1].L);
                        else printf("ERROR\n");
               }
               break;
            case 16:										//删除表
                printf("输入要删除的线性表的名字:");
                scanf("%s",name);
                if(LocateList(Lists,name))			//查找表
                    if(RemoveList(Lists,LocateList(Lists,name)-1))
                        for(n=0;n<Lists.length;n++){
                            printf("%s ",Lists.elem[n].name);
                            ListTraverse(Lists.elem[n].L);
                        }
                else printf("删除失败\n");
                break;
            case 17:										//查找表
                printf("输入要查找的线性表的名字:");
                scanf("%s",name);
                if (n=LocateList(Lists,name)){
                    printf("%s ",Lists.elem[n-1].name);
                    ListTraverse(Lists.elem[n-1].L);
                }
                else printf("查找失败\n");
                break;
            case 0:
                printf("\n欢迎下次再使用本系统！\n");
                goto down;
        }
    }
	down:
    return 0;
}

status Input(LinkList &L){								//输入
    int i;
    LNode *s,*r=L;
    printf("输入元素,结束输入0：\n");
    scanf("%d",&i);
    while(i){
        s=(LNode*) malloc(sizeof(LNode));				//新建结点
        s->data=i;										//结点赋值
        r->next=s;
        r=s;
        scanf("%d",&i);
    }
    r->next=NULL;
}

status InitList(LinkList &L){							//创建
    L=(struct LNode*)malloc(sizeof(ElemType));		//生成头结点
    L->next=NULL;
    return OK;
}

status DestroyList(LinkList &L){						//销毁
    struct LNode *p=L->next;
    while(p){
        L->next=p->next;						//依次销毁头结点后的结点
        p=NULL;
        p=L->next;							//p指向头结点下一结点
    }
    free(L);									//释放内存
    L=NULL;									//销毁表头
    return OK;
}

status ClearList(LinkList &L){							//清空
    struct LNode *p=L->next;
    while(p){									//依次销毁头结点后的结点
        L->next=p->next;
        free(p);								//p指向头结点下一结点
        p=L->next;							//释放内存
    }
    return OK;
}

status ListEmpty(LinkList L){							//判空
    if(!L->next) return TRUE;
    else return FALSE;
}

int ListLength(LinkList L){								//求表长
    int cnt=0;
    struct LNode *p=L;
    while(p->next){
        cnt++;											//用cnt记录
        p=p->next;										//指向下一结点
    }
    return cnt;
}

status GetElem(LinkList L,int i,ElemType &e){			//获取
    if(i<1||i>ListLength(L)) return ERROR;			//位置不合法
    struct LNode *p=L;
    while(i--) p=p->next;
    e=p->data;
    return OK;
}

status LocateElem(LinkList L,ElemType e){				//查找
    int i=1;
    struct LNode *p=L->next;
    while(p){
        if(e==p->data) return i;						//遍历比较
        p=p->next;										//指向下一结点
        i++;
    }
    return ERROR;
}

status PriorElem(LinkList L,ElemType e,ElemType &pre){	//前驱
    struct LNode *p=L;
    int i=LocateElem(L,e)-1;							//调用LocateElem
    if(!i||i==-1) return ERROR;							//i不合法
    while(i--) p=p->next; 								//查找结点
    pre=p->data; 											//赋值
    return OK;
}

status NextElem(LinkList L,ElemType e,ElemType &next){	//后继
    struct LNode *p=L;
    int i=LocateElem(L,e);								//调用LocateElem
if(!i||i==ListLength(L)) return ERROR;					//i不合法
    while(i--) p=p->next;								//查找结点
    next=p->next->data;									//赋值
    return OK;
}

status ListInsert(LinkList &L,int i,ElemType e){		//插入
if(i<1||i>ListLength(L)+1) return ERROR;			//i不合法
    i--;
    struct LNode *n=(struct LNode*)malloc(sizeof(ElemType)), *p=L->next,*q=L;
    while(i--){                                     //查找结点
        p=p->next;
        q=q->next;
    }
    q->next=n;
    n->data=e; 											//结点赋值
    n->next=p;
    return OK;
}

status ListDelete(LinkList &L,int i,ElemType &e){	//删除
    if(i<1||i>ListLength(L)) return ERROR;			//i不合法
    i--;
    struct LNode *p=L->next,*q=L;
    while(i--){
        p=p->next;
        q=q->next;
    }
    e=p->data;											//结点赋值
    q->next=p->next;										//删除结点
    free(p);
    return OK;
}

status ListTraverse(LinkList L){						//遍历
    struct LNode *p=L->next;
    while(p){
        printf("%d",p->data);
        if(p->next) printf(" ");
        else printf("\n");
        p=p->next;
    }
    return OK;
}

status SaveList(LinkList L,char FileName[]){			//写入文件
    struct LNode *p=L->next;
    FILE *fp;
    if(!(fp=fopen(FileName,"wb")))	return ERROR;		//打开文件失败
    else{
        while(p){
            fprintf(fp,"%d ",p->data);					//线性表写入文件
            p=p->next;
        }
        fclose(fp);
        return OK;
    }
}

status LoadList(LISTS &Lists,char FileName[]){
    FILE *fp;
    struct LNode *p=Lists.elem[Lists.length-1].L;
    if((fp=fopen(FileName,"rb"))){
        Lists.elem[Lists.length-1].L->next=(LinkList)malloc(sizeof(LNode));			//生产新结点
        p=Lists.elem[Lists.length-1].L->next;
        p->next=NULL;
        while((fscanf(fp,"%d ",&p->data))!=EOF)		//读入线性表
            if(!feof(fp)){
                p->next=(LinkList)malloc(sizeof(LNode)); //生成新结点
                p=p->next;
            }
        p->next=NULL;
        fclose(fp);
        return OK;
    }else return ERROR;
}

status AddList(LISTS &Lists,char ListName[]){				//创建新表
    strcpy(Lists.elem[Lists.length].name,ListName);
    Lists.elem[Lists.length].L=(LNode*)malloc(sizeof(LNode*));
    Lists.elem[Lists.length].L->next=NULL;
    Lists.length++;
    return OK;
}

status RemoveList(LISTS &Lists,int i){						//删除表
    DestroyList(Lists.elem[i].L);
    for(int j=i;j<Lists.length-1;j++)
        Lists.elem[j]=Lists.elem[j+1];						//覆盖前一个
    Lists.length--;
    return OK;
}

int LocateList(LISTS Lists,char ListName[]){				//查找表
    for(int i=0;i<Lists.length;i++)
        if(!strcmp(ListName,Lists.elem[i].name))
            return i+1;
    return 0;
}
