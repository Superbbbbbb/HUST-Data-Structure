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
BiTNode* q=NULL;						//�ⲿ��������ĳЩ������������ֵ
int flag0;								//�ⲿ��������ĳЩ���������жϱ�ʶ

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
    printf("    	 1. CreateBiTree(��) 10. DeleteNode\n");
    printf("    	 2. DestroyBiTree(��)11. PreOrderTraverse\n");
    printf("    	 3. ClearBiTree      12. InOrderTraverse\n");
    printf("    	 4. BiTreeEmpty      13. PostOrderTraverse\n");
    printf("    	 5. BiTreeDepth      14. LevelOrderTraverse\n");
    printf("    	 6. LocateNode       15. SaveBiTree\n");
    printf("    	 7. Assign           16. LoadBiTree(��)\n");
    printf("    	 8. GetSibling       17. AddList(��)\n");
    printf("    	 9. InsertNode       18. RemoveList(��)\n");
    printf("    	 0. exit             19. LocateList(��)\n");
    printf("-----------------------------------------------------\n");
    printf("         \n����������������0�����������������1:");
    scanf("%d",&flag);
    while(1){
        printf("     \n\n��ѡ����Ĳ���[0~19]: ");
        scanf("%d",&op);
        if(!flag&&op>15){
            printf("��ѡ������������\n");
            continue;
        }
        if(flag&&op>0&&op<3){
            printf("��ѡ�񵥶���������\n");
            continue;
        }
        if(flag&&op<16&&op>0){
            printf("\n��������Ķ�����������: ");
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
                    printf("�����������Ԫ��,��������0 0 null��");
                    do{
                        scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);										//����λ��ͽ������
                    }while(definition[i++].pos);
                    for(i=0;definition[i+1].pos;i++){
                        for(j=i+1;definition[j].pos;j++)
                            if(definition[i].data.key==definition[j].data.key){
                                j=0;
                                break;
                            }
                        if(!j) break;
                    }								//�жϹؼ����Ƿ�Ψһ
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
                    else j=DestroyBiTree(T);				//������root
                    if(j) printf("OK");
                    else printf("ERROR");
                }
                break;
            case 3:											//���
                if(!T) printf("INFEASIBLE");
                else{
                    if(flag) p=Lists.elem[x].T->lchild;	//����root
                    else p=T->lchild;
                    if(ClearBiTree(p)){
                        printf("OK");
                        T->lchild=NULL;
                    }
                    else printf("ERROR");
                }
                break;
            case 4:											//�п�
                if(!T) printf("INFEASIBLE");
                else{
                    if(BiTreeEmpty(T)) printf("TRUE");
                    else printf("FALSE");
                }
                break;
            case 5:											//�����
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("0");			//�ն�����
                else printf("%d",BiTreeDepth(T->lchild));
                break;
            case 6:											//����
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("�ն�����");
                else{
                    printf("������Ҫ���ҵĽڵ�Ĺؼ�ֵ��");
                    scanf("%d",&e);
                    q=NULL;
                    if(p=LocateNode(T->lchild,e))
                        visit(p);
                    else printf("ERROR");
                }
                break;
            case 7:											//��ֵ
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("�ն�����");
                else{
                    if(flag) p=Lists.elem[x].T;
                    else p=T;
                    printf("������Ҫ���ҵĽڵ�Ĺؼ�ֵ��");
                    scanf("%d",&e);
                    printf("������Ҫ�滻�Ľ��ֵ��");
                    scanf("%d%s",&c.key,c.others);
                    if(Assign(p->lchild,e,c))
                        Traverse(T->lchild);
                    else printf("ERROR");
                }
                break;
            case 8:											//����ֵ�
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("�ն�����");
                else{
                    printf("������Ҫ���ҵĽڵ�Ĺؼ�ֵ��");
                    scanf("%d",&e);
                    q=NULL;
                    if(p=GetSibling(T->lchild,e))
                        visit(p);
                    else printf("ERROR");
                }
                break;
            case 9:											//����
                if(!T) printf("INFEASIBLE");
                else{
                    if(flag) p=Lists.elem[x].T;
                    else p=T;
                    if(p->lchild){							//�ǿն�����
                        printf("������Ҫ����Ľڵ�Ĺؼ�ֵ��");
                        scanf("%d",&e);
                        printf("L:0,R:1,���ڵ�:-1 :");
                        scanf("%d",&LR);
                        printf("������Ҫ����Ľ��ֵ��");
                        scanf("%d%s",&c.key,c.others);
                        q=NULL;
                        if(LocateNode(p->lchild,c.key))
                            printf("ERROR");
                        else if(InsertNode(p,e,LR,c))
                            Traverse(T->lchild);
                        else printf("ERROR");
                    }else{									//�ն�����
                        printf("������Ҫ����Ľ��ֵ��");
                        scanf("%d%s",&c.key,c.others);
                        BiTree newnode=(BiTree)malloc(sizeof(BiTNode));				//�����½��
                        newnode->data.key=c.key;		//�����ڵ㸳ֵ
                        strcpy(newnode->data.others,c.others);
                        newnode->lchild=NULL;
                        newnode->rchild=NULL;
                        p->lchild=newnode;
                        Traverse(T->lchild);
                    }
                }
                break;
            case 10:											//ɾ��
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("�ն�����");
                else{
                    if(flag) p=Lists.elem[x].T;
                    else p=T;
                    printf("������Ҫɾ���Ľڵ�Ĺؼ�ֵ��");
                    scanf("%d",&e);
                    q=NULL;
                    flag0=0;
                    if(!LocateNode(T,e)) printf("ERROR");
                    else if(DeleteNode(p->lchild,e))
                        Traverse(T->lchild);
                }
                break;
            case 11:											//�������
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("�ն�����");
                else PreOrderTraverse(T->lchild);
                break;
            case 12:											//�������
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("�ն�����");
                else InOrderTraverse(T->lchild);
                break;
            case 13:											//�������
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("�ն�����");
                else PostOrderTraverse(T->lchild);
                break;
            case 14:											//�������
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("�ն�����");
                else LevelOrderTraverse(T->lchild);
                break;
            case 15:											//д���ļ�
                if(!T) printf("INFEASIBLE");
                else if(!T->lchild) printf("�ն�����");
                else{
                    printf("�����ļ���:");
                    scanf("%s",FileName);
                    SaveBiTree(T->lchild,FileName);
                    printf("OK");
                }
                break;
            case 16:
                printf("�����ļ�����");
                scanf("%s",FileName);
                while(1){
                    printf("�����������:");
                    scanf("%s",name);
                    if(LocateList(Lists,name))
                        printf("����\n");			//����,��������
                    else break;
                }
                AddList(Lists,name);
                p=Lists.elem[Lists.length-1].T;
                if(LoadBiTree(p,FileName))
                     Traverse(Lists.elem[Lists.length-1].T->lchild);
                else printf("ERROR\n");
                break;
            case 17:										//������
                printf("����Ҫ���ӵĶ������ĸ���:");
                scanf("%d",&n);
                if(Lists.length+n>10){
                    printf("OVERFLOW\n");
                    break;
                }
                definition=(DEF*)malloc(100*sizeof(DEF));
                while(n--){
                    printf("�������������:");
                    scanf("%s",name);
                    if(LocateList(Lists,name)){   //�ж��Ƿ�������
                        printf("����\n");
                        n++;
                        continue;
                    }
                    else
                        if(AddList(Lists,name)){
                            i=0;
                            printf("�����������Ԫ��,��������0 0 null��");
                            do{
                                scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);										//����λ��ͽ������
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
            case 18:										//ɾ����
                printf("����Ҫɾ���Ķ�����������:");
                scanf("%s",name);
                if(LocateList(Lists,name)){
                    if(RemoveList(Lists,LocateList(Lists,name)-1))
                        for(n=0;n<Lists.length;n++){
                            printf("%s\n",Lists.elem[n].name);
                            if(!Lists.elem[n].T->lchild) printf("�ն�������\n");
                            else{
                                Traverse(Lists.elem[n].T->lchild);
                                printf("\n");
                            }
                        }
                }
                else printf("ɾ��ʧ��");
                break;
            case 19:										//������
                printf("����Ҫ���ҵĶ�����������:");
                scanf("%s",name);
                if(n=LocateList(Lists,name)){
                    if(!Lists.elem[n-1].T) printf("INFEASIBLE");
                    else{
                        printf("%s\n",Lists.elem[n-1].name);
                        if(!Lists.elem[n-1].T->lchild)
                            printf("�����Ա�\n");
                        else Traverse(Lists.elem[n-1].T->lchild);
                    }
                }
                else printf("����ʧ��");
                break;
            case 0: goto down;
        }
    }
	down:
    printf("\n��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}

void Traverse(BiTree T){
    PreOrderTraverse(T);
    printf("\n");
    InOrderTraverse(T);
}

status CreateBiTree(BiTree &T,DEF definition[]){		//����
    int i=0,j;
    BiTNode *p[100];									//��λ�򴢴���
    while(j=definition[i].pos){
        p[j]=(BiTree)malloc(sizeof(BiTNode));
        p[j]->data=definition[i].data;
        p[j]->lchild=NULL;
        p[j]->rchild=NULL;
        if(j!=1){
            if(j%2) p[j/2]->rchild=p[j];			 //��λ�����ָ����
            else p[j/2]->lchild=p[j];
        }
        i++;
    }
    T=p[1];
    return OK;
}

status DestroyBiTree(BiTree &T){						//����
    if(T){
		DestroyBiTree(T->lchild);						//��������
		DestroyBiTree(T->rchild);						//�����Һ���
		free(T);
		T=NULL;
	}
	return OK;
}

status ClearBiTree(BiTree &T){							//���
    if(T){
		ClearBiTree(T->lchild);
		ClearBiTree(T->rchild);
		free(T);
		T=NULL;
	}
	return OK;
}

status BiTreeEmpty(BiTree T){							//�п�
    if(T->lchild) return FALSE;
    else return TRUE;
}

int BiTreeDepth(BiTree T){								//�����
    if(!T) return 0;
    int a=BiTreeDepth(T->lchild);
    int b=BiTreeDepth(T->rchild);
    return (a>b)?(a+1):(b+1);					//�������������и����
}

BiTNode* LocateNode(BiTree T,KeyType e){				//����
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

status Assign(BiTree &T,KeyType e,TElemType value){	//��ֵ
    if(value.key!=e){
        q=NULL;
        if(LocateNode(T,value.key))				//�ؼ��ֲ�Ψһ
            return ERROR;
    }
    q=NULL;
    BiTree p=LocateNode(T,e);					   //����LocateNode
    if(p){
        p->data.key=value.key;							//��㸳ֵ
        strcpy(p->data.others,value.others);
        return OK;
    }
    else return ERROR;
}

BiTNode* GetSibling(BiTree T,KeyType e){				//����ֵ�
    if(T->lchild&&T->rchild){
        if(q) return q;
        if(T->lchild->data.key==e){					//��������
            q=T->rchild;
            return q;									//�����Һ���
        }else if(T->rchild->data.key==e){				//�����Һ���
            q=T->lchild;
            return q;									//��������
        }else{
            GetSibling(T->lchild,e);
            GetSibling(T->rchild,e);
        }
        return q;
    }
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c){	//����
    BiTree newnode=(BiTree)malloc(sizeof(BiTNode));		//�����½��
    newnode->data.key=c.key;								//��㸳ֵ
    strcpy(newnode->data.others,c.others);
    newnode->lchild=NULL;
    newnode->rchild=NULL;
    if(LR==-1){												//��������
        newnode->rchild=T->lchild;
        T->lchild=newnode;
        return OK;
    }
    else{
        BiTree p=LocateNode(T->lchild,e);
        if(p){
            if(!LR){											//�������
                newnode->rchild=p->lchild;
                p->lchild=newnode;
            }
            else if(LR==1){									//�ҽ�����
                newnode->rchild=p->rchild;
                p->rchild=newnode;
            }
            return OK;
        }
    }
    return ERROR;
}

status DeleteNode(BiTree &T,KeyType e){					//ɾ��
    if(T){
        if(flag0) return 1;
		 if(e==T->data.key){
            if(!T->lchild&&!T->rchild){					//û�к���
                free(T);										//�ͷ��ڴ�
                T=NULL;
            }else if(T->lchild&&T->rchild){				//��������
                BiTree p=T->rchild,q=T;
                T=T->lchild;
                free(q);
                q=NULL;
                q=T;
                while(T->rchild) T=T->rchild;
                T->rchild=p;						//�Һ��ӽ�������
                T=q;
            }else if(T->lchild){							//������
                BiTree q=T;
                T=T->lchild;
                free(q);
                q=NULL;
            }else if(T->rchild){							//���Һ���
                BiTree q=T;
                T=T->rchild;
                free(q);
                q=NULL;
            }
            flag0=1;							//flag0���ڱ���Ƿ����ɾ��
            return OK;
        }else{
            DeleteNode(T->lchild,e);						//��������
            DeleteNode(T->rchild,e);
        }
    }
}

void visit(BiTree T){
    printf("%d,%s ",T->data.key,T->data.others);
}

void PreOrderTraverse(BiTree T){							//����
    if(T){
        visit(T);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

void InOrderTraverse(BiTree T){								//����
    if(T){
        InOrderTraverse(T->lchild);
        visit(T);
        InOrderTraverse(T->rchild);
    }
}

void PostOrderTraverse(BiTree T){							//����
    if(T){
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        visit(T);
    }
}

void LevelOrderTraverse(BiTree T){						//����
    BiTree p[100]={0};								//�������ڴ���λ��
    p[0]=T;
    int i=0,j=1;
    do{
        visit(p[i]);
        if(p[i]->lchild)									//��������
            p[j++]=p[i]->lchild;
        if(p[i]->rchild)									//�����Һ���
            p[j++]=p[i]->rchild;
        i++;
    }while(i<j);
}

status SaveBiTree(BiTree T,char FileName[]){			//д���ļ�
    int i=1;
    FILE *fp;
    BiTree p[101]={0,};
    p[1]=T;
    if((fp=fopen(FileName,"wb"))){
        while(i<101){
            if(p[i]){
                fprintf(fp,"%d %d %s ",i,p[i]->data.key,p[i]->data.others);		//λ��ͽ������д���ļ�
                if(p[i]->lchild)				//���Ӵ�������
                    p[2*i]=p[i]->lchild;
                if(p[i]->rchild)				//�Һ��Ӵ�������
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
        p[j].pos=0;										//��ʼ������
    FILE *fp;
    if(fp=fopen(FileName,"rb")){
        while(fscanf(fp,"%d %d %s ",&p[i].pos,&p[i].data.key,p[i].data.others)!=EOF) //�ļ�����д������
            i++;
        CreateBiTree(T->lchild,p);					  //�����¶�����
        fclose(fp);
        return OK;
    }
    else return ERROR;

}

status AddList(LISTS &Lists,char ListName[]){			//����������
    strcpy(Lists.elem[Lists.length].name,ListName);
    Lists.elem[Lists.length++].T=(BiTNode*)malloc(sizeof(BiTNode));
    return OK;
}

status RemoveList(LISTS &Lists,int i){					//�Ƴ�������
    free(Lists.elem[i].T);
    for(int j=i;j<Lists.length-1;j++)
        Lists.elem[j]=Lists.elem[j+1];					//����ǰһ��
    Lists.length--;
    return OK;
}

int LocateList(LISTS Lists,char ListName[]){			//���Ҷ�����
    for(int i=0;i<Lists.length;i++)
        if(!strcmp(ListName,Lists.elem[i].name))
            return i+1;
    return 0;
}
