#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int status;
typedef int KeyType;
typedef struct {
    KeyType  key;
    char others[20];
} TElemType;
typedef struct BiTNode{
    TElemType  data;
    struct BiTNode *lchild,*rchild;
}BiTNode, *BiTree;
typedef struct {
    int pos;
    TElemType data;
}DEF;
typedef struct{
    struct {
        char name[30];
        BiTree T;
    }elem[10];
int length;
}LISTS;
void visit(BiTree T);
void Traverse(BiTree T);
status CreateBiTree(BiTree &T,DEF definition[]);
status DestroyBiTree(BiTree &T);
status ClearBiTree(BiTree &T);
status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T,KeyType e);
status Assign(BiTree &T,KeyType e,TElemType value);
BiTNode* GetSibling(BiTree T,KeyType e);
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);
status DeleteNode(BiTree &T,KeyType e);
void PreOrderTraverse(BiTree T);
void InOrderTraverse(BiTree T);
void PostOrderTraverse(BiTree T);
void LevelOrderTraverse(BiTree T);
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T, char FileName[]);
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T, char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,int i);
int LocateList(LISTS Lists,char ListName[]);
BiTNode* q=NULL;						//外部变量，在某些函数中作返回值
int flag0;								//外部变量，在某些函数中作判断标识

int main(){
    BiTree T=NULL,p;
    LISTS Lists;
    TElemType c;
    BiTree s[100];
    DEF *definition;
    int op,flag,e,i=0,j,LR,x,n;
    Lists.length=0;
    char FileName[30],name[30],Name[30];
    printf("     Menu for Linear Table On Sequence Structure \n");
    printf("-----------------------------------------------------\n");
    printf("    	 1. CreateBiTree(单) 10. DeleteNode\n");
    printf("    	 2. DestroyBiTree(单)11. PreOrderTraverse\n");
    printf("    	 3. ClearBiTree      12. InOrderTraverse\n");
    printf("    	 4. BiTreeEmpty      13. PostOrderTraverse\n");
    printf("    	 5. BiTreeDepth      14. LevelOrderTraverse\n");
    printf("    	 6. LocateNode       15. SaveBiTree\n");
    printf("    	 7. Assign           16. LoadBiTree(多)\n");
    printf("    	 8. GetSibling       17. AddList(多)\n");
    printf("    	 9. InsertNode       18. RemoveList(多)\n");
    printf("    	 0. exit             19. LocateList(多)\n");
    printf("-----------------------------------------------------\n");
    printf("         \n单二叉树操作输入0，多二叉树操作输入1:");
    scanf("%d",&flag);
    while(1){
        printf("     \n\n请选择你的操作[0~19]: ");
        scanf("%d",&op);
        if(!flag&&op>15){
            printf("请选择多二叉树操作\n");
            continue;
        }
        if(flag&&op>0&&op<3){
            printf("请选择单二叉树操作\n");
            continue;
        }
        if(flag&&op<16&&op>0){
            printf("\n输入操作的二叉树的名字: ");
            scanf("%s",Name);
            x=LocateList(Lists,Name)-1;
            if(x>=0) T=Lists.elem[x].T;
            else{
                printf("INFEASIBLE");
                continue;
            }
        }
        switch(op){
            case 1:
                if(T) printf("INFEASIBLE");
                else{
                    definition=(DEF*)malloc(100*sizeof(DEF));
                    printf("请输入二叉树元素,结束输入0 0 null：");
                    do{
                        scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);										//输入位序和结点数据
                    }while(definition[i++].pos);
                    for(i=0;definition[i+1].pos;i++){
                        for(j=i+1;definition[j].pos;j++)
                            if(definition[i].data.key==definition[j].data.key){
                                j=0;
                                break;
                            }
                        if(!j) break;
                    }								//判断关键字是否唯一
                    if(!j) printf("ERROR");
                    else{
                        T=(BiTree)malloc(sizeof(BiTNode));
                        T->rchild=NULL;
                        p=T;
                        if(CreateBiTree(p->lchild,definition))
                            printf("OK");
                        else printf("ERROR");
                        free(definition);
                    }
                }
                break;
            case 2:
                if(!T) printf("INFEASIBLE");
                else{
                    if(flag) j=DestroyBiTree(Lists.elem[x].T);
                    else j=DestroyBiTree(T);				//不保留root
                    if(j) printf("OK");
                    else printf("ERROR");
                }
                break;
            case 3:											//清空
                if(!T) printf("INFEASIBLE");
                else{
                    if(flag) p=Lists.elem[x].T->lchild;	//保留root
                    else p=T->lchild;
                    if(ClearBiTree(p)){
                        printf("OK");
                        T->lchild=NULL;
                    }
                    else printf("ERROR");
                }
                break;
            case 4:											//判空
                if(!T) printf("INFEASIBLE");
                else{
                    if(BiTreeEmpty(T)) printf("TRUE");
                    else printf("FALSE");
                }
                break;
            case 5:											//求深度
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("0");			//空二叉树
                else printf("%d",BiTreeDepth(T->lchild));
                break;
            case 6:											//查找
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("空二叉树");
                else{
                    printf("输入想要查找的节点的关键值：");
                    scanf("%d",&e);
                    q=NULL;
                    if(p=LocateNode(T->lchild,e))
                        visit(p);
                    else printf("ERROR");
                }
                break;
            case 7:											//赋值
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("空二叉树");
                else{
                    if(flag) p=Lists.elem[x].T;
                    else p=T;
                    printf("输入想要查找的节点的关键值：");
                    scanf("%d",&e);
                    printf("输入想要替换的结点值：");
                    scanf("%d%s",&c.key,c.others);
                    if(Assign(p->lchild,e,c))
                        Traverse(T->lchild);
                    else printf("ERROR");
                }
                break;
            case 8:											//获得兄弟
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("空二叉树");
                else{
                    printf("输入想要查找的节点的关键值：");
                    scanf("%d",&e);
                    q=NULL;
                    if(p=GetSibling(T->lchild,e))
                        visit(p);
                    else printf("ERROR");
                }
                break;
            case 9:											//插入
                if(!T) printf("INFEASIBLE");
                else{
                    if(flag) p=Lists.elem[x].T;
                    else p=T;
                    if(p->lchild){							//非空二叉树
                        printf("输入想要插入的节点的关键值：");
                        scanf("%d",&e);
                        printf("L:0,R:1,根节点:-1 :");
                        scanf("%d",&LR);
                        printf("输入想要插入的结点值：");
                        scanf("%d%s",&c.key,c.others);
                        q=NULL;
                        if(LocateNode(p->lchild,c.key))
                            printf("ERROR");
                        else if(InsertNode(p,e,LR,c))
                            Traverse(T->lchild);
                        else printf("ERROR");
                    }else{									//空二叉树
                        printf("输入想要插入的结点值：");
                        scanf("%d%s",&c.key,c.others);
                        BiTree newnode=(BiTree)malloc(sizeof(BiTNode));				//生成新结点
                        newnode->data.key=c.key;		//将根节点赋值
                        strcpy(newnode->data.others,c.others);
                        newnode->lchild=NULL;
                        newnode->rchild=NULL;
                        p->lchild=newnode;
                        Traverse(T->lchild);
                    }
                }
                break;
            case 10:											//删除
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("空二叉树");
                else{
                    if(flag) p=Lists.elem[x].T;
                    else p=T;
                    printf("输入想要删除的节点的关键值：");
                    scanf("%d",&e);
                    q=NULL;
                    flag0=0;
                    if(!LocateNode(T,e)) printf("ERROR");
                    else if(DeleteNode(p->lchild,e))
                        Traverse(T->lchild);
                }
                break;
            case 11:											//先序遍历
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("空二叉树");
                else PreOrderTraverse(T->lchild);
                break;
            case 12:											//中序遍历
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("空二叉树");
                else InOrderTraverse(T->lchild);
                break;
            case 13:											//后序遍历
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("空二叉树");
                else PostOrderTraverse(T->lchild);
                break;
            case 14:											//按层遍历
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("空二叉树");
                else LevelOrderTraverse(T->lchild);
                break;
            case 15:											//写入文件
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("空二叉树");
                else{
                    printf("输入文件名:");
                    scanf("%s",FileName);
                    SaveBiTree(T->lchild,FileName);
                    printf("OK");
                }
                break;
            case 16:
                printf("输入文件名：");
                scanf("%s",FileName);
                while(1){
                    printf("输入二叉树名:");
                    scanf("%s",name);
                    if(LocateList(Lists,name))
                        printf("重名\n");			//重名,重新输入
                    else break;
                }
                AddList(Lists,name);
                p=Lists.elem[Lists.length-1].T;
                if(LoadBiTree(p,FileName))
                     Traverse(Lists.elem[Lists.length-1].T->lchild);
                else printf("ERROR\n");
                break;
            case 17:										//增加树
                printf("输入要增加的二叉树的个数:");
                scanf("%d",&n);
                if(Lists.length+n>10){
                    printf("OVERFLOW\n");
                    break;
                }
                definition=(DEF*)malloc(100*sizeof(DEF));
                while(n--){
                    printf("输入二叉树名字:");
                    scanf("%s",name);
                    if(LocateList(Lists,name)){   //判断是否有重名
                        printf("重名\n");
                        n++;
                        continue;
                    }
                    else
                        if(AddList(Lists,name)){
                            i=0;
                            printf("请输入二叉树元素,结束输入0 0 null：");
                            do{
                                scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);										//输入位序和结点数据
                            }while(definition[i++].pos);
                            i=0;
                            while(j=definition[i].pos){
                                s[j]=(BiTNode *)malloc(sizeof(BiTNode));
                                s[j]->data=definition[i].data;
                                s[j]->lchild=NULL;
                                s[j]->rchild=NULL;
                                if(j!=1){
                                    if(j%2) s[j/2]->rchild=s[j];
                                    else s[j/2]->lchild=s[j];
                                }
                                i++;
                            }
                            Lists.elem[Lists.length-1].T->lchild=s[1];
                            printf("OK\n");
                            for(i=0;i<100;i++)
                                definition[i].pos=0;
                            for(i=0;i<100;i++)
                                s[i]=NULL;
                        }else printf("ERROR\n");
                }
                break;
            case 18:										//删除树
                printf("输入要删除的二叉树的名字:");
                scanf("%s",name);
                if(LocateList(Lists,name)){
                    if(RemoveList(Lists,LocateList(Lists,name)-1))
                        for(n=0;n<Lists.length;n++){
                            printf("%s\n",Lists.elem[n].name);
                            if(!Lists.elem[n].T->lchild) printf("空二叉树表\n");
                            else{
                                Traverse(Lists.elem[n].T->lchild);
                                printf("\n");
                            }
                        }
                }
                else printf("删除失败");
                break;
            case 19:										//查找树
                printf("输入要查找的二叉树的名字:");
                scanf("%s",name);
                if(n=LocateList(Lists,name)){
                    if(!Lists.elem[n-1].T) printf("INFEASIBLE");
                    else{
                        printf("%s\n",Lists.elem[n-1].name);
                        if(!Lists.elem[n-1].T->lchild)
                            printf("空线性表\n");
                        else Traverse(Lists.elem[n-1].T->lchild);
                    }
                }
                else printf("查找失败");
                break;
            case 0: goto down;
        }
    }
	down:
    printf("\n欢迎下次再使用本系统！\n");
    return 0;
}

void Traverse(BiTree T){
    PreOrderTraverse(T);
    printf("\n");
    InOrderTraverse(T);
}

status CreateBiTree(BiTree &T,DEF definition[]){		//创建
    int i=0,j;
    BiTNode *p[100];									//按位序储存结点
    while(j=definition[i].pos){
        p[j]=(BiTree)malloc(sizeof(BiTNode));
        p[j]->data=definition[i].data;
        p[j]->lchild=NULL;
        p[j]->rchild=NULL;
        if(j!=1){
            if(j%2) p[j/2]->rchild=p[j];			 //按位序分配指针域
            else p[j/2]->lchild=p[j];
        }
        i++;
    }
    T=p[1];
    return OK;
}

status DestroyBiTree(BiTree &T){						//销毁
    if(T){
		DestroyBiTree(T->lchild);						//销毁左孩子
		DestroyBiTree(T->rchild);						//销毁右孩子
		free(T);
		T=NULL;
	}
	return OK;
}

status ClearBiTree(BiTree &T){							//清空
    if(T){
		ClearBiTree(T->lchild);
		ClearBiTree(T->rchild);
		free(T);
		T=NULL;
	}
	return OK;
}

status BiTreeEmpty(BiTree T){							//判空
    if(T->lchild) return FALSE;
    else return TRUE;
}

int BiTreeDepth(BiTree T){								//求深度
    if(!T) return 0;
    int a=BiTreeDepth(T->lchild);
    int b=BiTreeDepth(T->rchild);
    return (a>b)?(a+1):(b+1);					//返回左右子树中更深的
}

BiTNode* LocateNode(BiTree T,KeyType e){				//查找
    if(T){
       if(q) return q;
		if(e==T->data.key){
			q=T;
			return q;
		}else{
            LocateNode(T->lchild,e);
            LocateNode(T->rchild,e);
       }
       return q;
    }
}

status Assign(BiTree &T,KeyType e,TElemType value){	//赋值
    if(value.key!=e){
        q=NULL;
        if(LocateNode(T,value.key))				//关键字不唯一
            return ERROR;
    }
    q=NULL;
    BiTree p=LocateNode(T,e);					   //调用LocateNode
    if(p){
        p->data.key=value.key;							//结点赋值
        strcpy(p->data.others,value.others);
        return OK;
    }
    else return ERROR;
}

BiTNode* GetSibling(BiTree T,KeyType e){				//获得兄弟
    if(T->lchild&&T->rchild){
        if(q) return q;
        if(T->lchild->data.key==e){					//等于左孩子
            q=T->rchild;
            return q;									//返回右孩子
        }else if(T->rchild->data.key==e){				//等于右孩子
            q=T->lchild;
            return q;									//返回左孩子
        }else{
            GetSibling(T->lchild,e);
            GetSibling(T->rchild,e);
        }
        return q;
    }
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c){	//插入
    BiTree newnode=(BiTree)malloc(sizeof(BiTNode));		//生成新结点
    newnode->data.key=c.key;								//结点赋值
    strcpy(newnode->data.others,c.others);
    newnode->lchild=NULL;
    newnode->rchild=NULL;
    if(LR==-1){												//根结点插入
        newnode->rchild=T->lchild;
        T->lchild=newnode;
        return OK;
    }
    else{
        BiTree p=LocateNode(T->lchild,e);
        if(p){
            if(!LR){											//左结点插入
                newnode->rchild=p->lchild;
                p->lchild=newnode;
            }
            else if(LR==1){									//右结点插入
                newnode->rchild=p->rchild;
                p->rchild=newnode;
            }
            return OK;
        }
    }
    return ERROR;
}

status DeleteNode(BiTree &T,KeyType e){					//删除
    if(T){
        if(flag0) return 1;
		 if(e==T->data.key){
            if(!T->lchild&&!T->rchild){					//没有孩子
                free(T);										//释放内存
                T=NULL;
            }else if(T->lchild&&T->rchild){				//两个孩子
                BiTree p=T->rchild,q=T;
                T=T->lchild;
                free(q);
                q=NULL;
                q=T;
                while(T->rchild) T=T->rchild;
                T->rchild=p;						//右孩子接入左孩子
                T=q;
            }else if(T->lchild){							//有左孩子
                BiTree q=T;
                T=T->lchild;
                free(q);
                q=NULL;
            }else if(T->rchild){							//有右孩子
                BiTree q=T;
                T=T->rchild;
                free(q);
                q=NULL;
            }
            flag0=1;							//flag0用于标记是否完成删除
            return OK;
        }else{
            DeleteNode(T->lchild,e);						//继续查找
            DeleteNode(T->rchild,e);
        }
    }
}

void visit(BiTree T){
    printf("%d,%s ",T->data.key,T->data.others);
}

void PreOrderTraverse(BiTree T){							//先序
    if(T){
        visit(T);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

void InOrderTraverse(BiTree T){								//中序
    if(T){
        InOrderTraverse(T->lchild);
        visit(T);
        InOrderTraverse(T->rchild);
    }
}

void PostOrderTraverse(BiTree T){							//后序
    if(T){
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        visit(T);
    }
}

void LevelOrderTraverse(BiTree T){						//按层
    BiTree p[100]={0};								//数组用于储存位序
    p[0]=T;
    int i=0,j=1;
    do{
        visit(p[i]);
        if(p[i]->lchild)									//储存左孩子
            p[j++]=p[i]->lchild;
        if(p[i]->rchild)									//储存右孩子
            p[j++]=p[i]->rchild;
        i++;
    }while(i<j);
}

status SaveBiTree(BiTree T,char FileName[]){			//写入文件
    int i=1;
    FILE *fp;
    BiTree p[101]={0,};
    p[1]=T;
    if((fp=fopen(FileName,"wb"))){
        while(i<101){
            if(p[i]){
                fprintf(fp,"%d %d %s ",i,p[i]->data.key,p[i]->data.others);		//位序和结点数据写入文件
                if(p[i]->lchild)				//左孩子存入数组
                    p[2*i]=p[i]->lchild;
                if(p[i]->rchild)				//右孩子存入数组
                    p[2*i+1]=p[i]->rchild;
            }
            i++;
        }
        fclose(fp);
        return OK;
    }else return ERROR;
}

status LoadBiTree(BiTree &T,char FileName[]){
    int i=0,j;
    DEF p[100];
    for(j=0;j<100;j++)
        p[j].pos=0;										//初始化数组
    FILE *fp;
    if(fp=fopen(FileName,"rb")){
        while(fscanf(fp,"%d %d %s ",&p[i].pos,&p[i].data.key,p[i].data.others)!=EOF) //文件数据写入数组
            i++;
        CreateBiTree(T->lchild,p);					  //创建新二叉树
        fclose(fp);
        return OK;
    }
    else return ERROR;

}

status AddList(LISTS &Lists,char ListName[]){			//新增二叉树
    strcpy(Lists.elem[Lists.length].name,ListName);
    Lists.elem[Lists.length++].T=(BiTNode*)malloc(sizeof(BiTNode));
    return OK;
}

status RemoveList(LISTS &Lists,int i){					//移除二叉树
    free(Lists.elem[i].T);
    for(int j=i;j<Lists.length-1;j++)
        Lists.elem[j]=Lists.elem[j+1];					//覆盖前一个
    Lists.length--;
    return OK;
}

int LocateList(LISTS Lists,char ListName[]){			//查找二叉树
    for(int i=0;i<Lists.length;i++)
        if(!strcmp(ListName,Lists.elem[i].name))
            return i+1;
    return 0;
}
