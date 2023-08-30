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
    printf("    	  1. InitList(��)   9.  NextElem\n");
    printf("    	  2. DestroyList(��)10. ListInsert\n");
    printf("    	  3. ClearList      11. ListDelete\n");
    printf("    	  4. ListEmpty      12. ListTrabverse\n");
    printf("    	  5. ListLength     13. SaveList\n");
    printf("    	  6. GetElem        14. LoadList(��)\n");
    printf("    	  7. LocateElem     15. AddList(��)\n");
    printf("    	  8. PriorElem      16. RemoveList(��)\n");
    printf("    	  0. Exit           17. LocateList(��)\n");
    printf("-----------------------------------------------------\n");
    printf("          �����Ա��������0�������Ա��������1:");
    scanf("%d",&flag);
    while(1){
        printf("          \n��ѡ����Ĳ���[0~17]:");
        scanf("%d",&op);
        if(!flag&&op>13){
            printf("��ѡ������Ա����\n");
            continue;
        }
        if(flag&&op>0&&op<3){
            printf("��ѡ�����Ա����\n");
            continue;
        }
        if(flag&&op<14&&op>0){
            printf("\n������������Ա�����֣�");
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
                    if(InitList(L)){					//�����ɹ�
                        Input(L); 						//����Ԫ��
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
            case 3:										//���
                if(!L) printf("INFEASIBLE\n");
                else
                    if(ClearList(L)&&L&&!L->next) printf("OK\n");
                    else printf("ERROR\n");
                break;
            case 4:										//�п�
                if(!L) printf("INFEASIBLE\n");
                else
                    if(ListEmpty(L)) printf("TRUE\n");
                    else printf("FALSE\n");
                break;
            case 5:										//���
                if(!L) printf("INFEASIBLE\n");
                else printf("%d\n",ListLength(L));
                break;
            case 6:										//��ȡ
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("�����Ա�\n");
                else{
                    printf("����Ҫ��ȡ��Ԫ�ص�λ�ã�");
                    scanf("%d",&i);
                    if(GetElem(L,i,e)) printf("%d\n",e);
                    else printf("ERROR\n");
                }
                break;
            case 7:										//����
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("�����Ա�\n");
                else{
                    printf("����Ҫ��ȡλ�õ�Ԫ�أ�");
                    scanf("%d",&e);
                    if(LocateElem(L,e)) printf("%d\n",j);
                    else printf("ERROR");
                }
                break;
            case 8:										//ǰ��
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("�����Ա�\n");
                else{
                    printf("����Ҫ���ҵ�Ԫ�أ�");
                    scanf("%d",&e);
                    if(PriorElem(L,e,pre)) printf("%d\n",pre);
                    else printf("ERROR\n");
                }
                break;
            case 9:										//���
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("�����Ա�\n");
                else{
                    printf("����Ҫ���ҵ�Ԫ�أ�");
                    scanf("%d",&e);
                    if(NextElem(L,e,next)) printf("%d\n",next);
                    else printf("ERROR\n");
                }
                break;
            case 10:										//����
                if(!L) printf("INFEASIBLE\n");
                else{
                    printf("����Ҫ�����λ�ú�Ԫ�أ�");
                    scanf("%d%d",&i,&e);
                    if(ListInsert(L,i,e)) ListTraverse(L);
                    else printf("ERROR");

                }
                break;
            case 11:										//ɾ��
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("�����Ա�\n");
                else{
                    printf("����Ҫɾ����Ԫ�ص�λ�ã�");
                    scanf("%d",&i);
                    if(ListDelete(L,i,e)) ListTraverse(L);
                    else printf("ERROR\n");
                }
                break;
            case 12:										//����
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("�����Ա�\n");
                else ListTraverse(L);
                break;
            case 13:          							//д���ļ�
                if(!L) printf("INFEASIBLE\n");
                else if(!L->next) printf("�����Ա�\n");
                else{
                    printf("�����ļ�����");
                    scanf("%s",FileName);
                    if(SaveList(L,FileName))
                        printf("OK\n");
                    else printf("ERROR\n");
                }
                break;
            case 14:
                printf("�����ļ���:");
                scanf("%s",FileName);
                while(1){
                    printf("�������Ա���:");
                    scanf("%s",name);
                    if(LocateList(Lists,name))
                        printf("����\n");			//����,��������
                    else break;
                }
                AddList(Lists,name);
                if(LoadList(Lists,FileName))
                    ListTraverse(Lists.elem[Lists.length-1].L);
                else printf("ERROR\n");
                break;
            case 15:										//�����±�
                printf("����Ҫ���ӵ����Ա�ĸ���:");
                scanf("%d",&n);
                if(Lists.length+n>10){					//���
                    printf("OVERFLOW\n");
                    break;
                }
                while(n--){
                    printf("�������Ա�����:");
                    scanf("%s",name);
                    if(LocateList(Lists,name)){   //�ж��Ƿ�������
                        printf("����\n");
                        n++;
                        continue;
                    }
                    else
                        if(AddList(Lists,name))
                            Input(Lists.elem[Lists.length-1].L);
                        else printf("ERROR\n");
               }
               break;
            case 16:										//ɾ����
                printf("����Ҫɾ�������Ա������:");
                scanf("%s",name);
                if(LocateList(Lists,name))			//���ұ�
                    if(RemoveList(Lists,LocateList(Lists,name)-1))
                        for(n=0;n<Lists.length;n++){
                            printf("%s ",Lists.elem[n].name);
                            ListTraverse(Lists.elem[n].L);
                        }
                else printf("ɾ��ʧ��\n");
                break;
            case 17:										//���ұ�
                printf("����Ҫ���ҵ����Ա������:");
                scanf("%s",name);
                if (n=LocateList(Lists,name)){
                    printf("%s ",Lists.elem[n-1].name);
                    ListTraverse(Lists.elem[n-1].L);
                }
                else printf("����ʧ��\n");
                break;
            case 0:
                printf("\n��ӭ�´���ʹ�ñ�ϵͳ��\n");
                goto down;
        }
    }
	down:
    return 0;
}

status Input(LinkList &L){								//����
    int i;
    LNode *s,*r=L;
    printf("����Ԫ��,��������0��\n");
    scanf("%d",&i);
    while(i){
        s=(LNode*) malloc(sizeof(LNode));				//�½����
        s->data=i;										//��㸳ֵ
        r->next=s;
        r=s;
        scanf("%d",&i);
    }
    r->next=NULL;
}

status InitList(LinkList &L){							//����
    L=(struct LNode*)malloc(sizeof(ElemType));		//����ͷ���
    L->next=NULL;
    return OK;
}

status DestroyList(LinkList &L){						//����
    struct LNode *p=L->next;
    while(p){
        L->next=p->next;						//��������ͷ����Ľ��
        p=NULL;
        p=L->next;							//pָ��ͷ�����һ���
    }
    free(L);									//�ͷ��ڴ�
    L=NULL;									//���ٱ�ͷ
    return OK;
}

status ClearList(LinkList &L){							//���
    struct LNode *p=L->next;
    while(p){									//��������ͷ����Ľ��
        L->next=p->next;
        free(p);								//pָ��ͷ�����һ���
        p=L->next;							//�ͷ��ڴ�
    }
    return OK;
}

status ListEmpty(LinkList L){							//�п�
    if(!L->next) return TRUE;
    else return FALSE;
}

int ListLength(LinkList L){								//���
    int cnt=0;
    struct LNode *p=L;
    while(p->next){
        cnt++;											//��cnt��¼
        p=p->next;										//ָ����һ���
    }
    return cnt;
}

status GetElem(LinkList L,int i,ElemType &e){			//��ȡ
    if(i<1||i>ListLength(L)) return ERROR;			//λ�ò��Ϸ�
    struct LNode *p=L;
    while(i--) p=p->next;
    e=p->data;
    return OK;
}

status LocateElem(LinkList L,ElemType e){				//����
    int i=1;
    struct LNode *p=L->next;
    while(p){
        if(e==p->data) return i;						//�����Ƚ�
        p=p->next;										//ָ����һ���
        i++;
    }
    return ERROR;
}

status PriorElem(LinkList L,ElemType e,ElemType &pre){	//ǰ��
    struct LNode *p=L;
    int i=LocateElem(L,e)-1;							//����LocateElem
    if(!i||i==-1) return ERROR;							//i���Ϸ�
    while(i--) p=p->next; 								//���ҽ��
    pre=p->data; 											//��ֵ
    return OK;
}

status NextElem(LinkList L,ElemType e,ElemType &next){	//���
    struct LNode *p=L;
    int i=LocateElem(L,e);								//����LocateElem
if(!i||i==ListLength(L)) return ERROR;					//i���Ϸ�
    while(i--) p=p->next;								//���ҽ��
    next=p->next->data;									//��ֵ
    return OK;
}

status ListInsert(LinkList &L,int i,ElemType e){		//����
if(i<1||i>ListLength(L)+1) return ERROR;			//i���Ϸ�
    i--;
    struct LNode *n=(struct LNode*)malloc(sizeof(ElemType)), *p=L->next,*q=L;
    while(i--){                                     //���ҽ��
        p=p->next;
        q=q->next;
    }
    q->next=n;
    n->data=e; 											//��㸳ֵ
    n->next=p;
    return OK;
}

status ListDelete(LinkList &L,int i,ElemType &e){	//ɾ��
    if(i<1||i>ListLength(L)) return ERROR;			//i���Ϸ�
    i--;
    struct LNode *p=L->next,*q=L;
    while(i--){
        p=p->next;
        q=q->next;
    }
    e=p->data;											//��㸳ֵ
    q->next=p->next;										//ɾ�����
    free(p);
    return OK;
}

status ListTraverse(LinkList L){						//����
    struct LNode *p=L->next;
    while(p){
        printf("%d",p->data);
        if(p->next) printf(" ");
        else printf("\n");
        p=p->next;
    }
    return OK;
}

status SaveList(LinkList L,char FileName[]){			//д���ļ�
    struct LNode *p=L->next;
    FILE *fp;
    if(!(fp=fopen(FileName,"wb")))	return ERROR;		//���ļ�ʧ��
    else{
        while(p){
            fprintf(fp,"%d ",p->data);					//���Ա�д���ļ�
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
        Lists.elem[Lists.length-1].L->next=(LinkList)malloc(sizeof(LNode));			//�����½��
        p=Lists.elem[Lists.length-1].L->next;
        p->next=NULL;
        while((fscanf(fp,"%d ",&p->data))!=EOF)		//�������Ա�
            if(!feof(fp)){
                p->next=(LinkList)malloc(sizeof(LNode)); //�����½��
                p=p->next;
            }
        p->next=NULL;
        fclose(fp);
        return OK;
    }else return ERROR;
}

status AddList(LISTS &Lists,char ListName[]){				//�����±�
    strcpy(Lists.elem[Lists.length].name,ListName);
    Lists.elem[Lists.length].L=(LNode*)malloc(sizeof(LNode*));
    Lists.elem[Lists.length].L->next=NULL;
    Lists.length++;
    return OK;
}

status RemoveList(LISTS &Lists,int i){						//ɾ����
    DestroyList(Lists.elem[i].L);
    for(int j=i;j<Lists.length-1;j++)
        Lists.elem[j]=Lists.elem[j+1];						//����ǰһ��
    Lists.length--;
    return OK;
}

int LocateList(LISTS Lists,char ListName[]){				//���ұ�
    for(int i=0;i<Lists.length;i++)
        if(!strcmp(ListName,Lists.elem[i].name))
            return i+1;
    return 0;
}
