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
    printf("          \n�����Ա��������0�������Ա��������1:");
    scanf("%d",&flag);							//flag��ǵ�������
    while(1){
        printf("      \n��ѡ����Ĳ���[0~17]: ");
        scanf("%d",&op);                            //ѡ��Ĺ��ܱ��
        if(!flag&&op>13){
            printf("��ѡ������Ա����\n");
            continue;
        }
        if(flag&&op>0&&op<3){
            printf("��ѡ�����Ա����\n");
            continue;
        }
        if(flag&&op<14&&op>0){		//���Զ����Ա��е�ĳ������в���
            printf("\n������������Ա������: ");
            scanf("%s",Name);
            x=LocateList(Lists,Name)-1;
            if(x>=0) L=Lists.elem[x].L;		   //����LocateList����
            else{
                printf("INFEASIBLE\n");
                continue;
            }
        }
        switch(op){
            case 1:										//��ʼ��
                if(L.elem) printf("INFEASIBLE\n");
                else
                    if(InitList(L)){					//�������Ա�ɹ�
                        Input(L);						//�������Ա�Ԫ��
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
            case 3:										//���
                if(!L.elem) printf("INFEASIBLE\n");
                else{
                    if(flag) j=ClearList(Lists.elem[x].L);
                    else j=ClearList(L);
                    if(j) printf("OK\n");
                    else printf("ERROR\n");
                }
                break;
            case 4:										//�п�
                if(!L.elem) printf("INFEASIBLE\n");
                else
                    if (ListEmpty(L)) printf("TRUE\n");
                    else printf("FALSE\n");
                break;
            case 5:										//���
                if(!L.elem) printf("INFEASIBLE\n");
                else printf("%d\n",ListLength(L));
                break;
            case 6:										//��ȡ
                if(!L.elem) printf("INFEASIBLE\n");
                else if(!L.length) printf("�����Ա�\n");
                else{
                    printf("����Ҫ��ȡ��Ԫ�ص�λ��:");
                    scanf("%d",&i);
                    if(GetElem(L,i,e)) printf("%d\n",e);
                    else printf("ERROR\n");
                }
                break;
            case 7:										//����
                if(!L.elem) printf("INFEASIBLE\n");
                else if(!L.length) printf("�����Ա�\n");
                else{
                    printf("����Ҫ����λ�õ�Ԫ��:");
                    scanf("%d",&e);
                    if(LocateElem(L,e)) printf("%d\n",j);
                    else printf("ERROR\n");
                }
                break;
            case 8:										//ǰ��
                if(!L.elem) printf("INFEASIBLE\n");
                else if(!L.length) printf("�����Ա�\n");
                else{
                    printf("����Ҫ���ҵ�Ԫ��:");
                    scanf("%d",&e);
                    if(PriorElem(L,e,pre)) printf("%d\n",pre);
                    else printf("ERROR\n");
                }
                break;
            case 9:										//���
                if(!L.elem) printf("INFEASIBLE\n");
                else if(!L.length) printf("�����Ա�\n");
                else{
                    printf("����Ҫ���ҵ�Ԫ��:");
                    scanf("%d",&e);
                    if(NextElem(L,e,next)) printf("%d\n",next);
                    else printf("ERROR\n");
                }
                break;
            case 10:									//����
                if(!L.elem) printf("INFEASIBLE\n");
                else{
                    printf("����Ҫ�����λ�ú�Ԫ��:");
                    scanf("%d%d",&i,&e);
                    j=ListInsert(L,i,e);
                    if(flag) Lists.elem[x].L.length++;
                    else L.length++;
                    if(j) ListTraverse(L);
                    else printf("ERROR\n");
                }
                break;
            case 11:									//ɾ��
                if(!L.elem) printf("INFEASIBLE\n");
                else if(!L.length) printf("�����Ա�\n");
                else{
                    printf("����Ҫɾ��Ԫ�ص�λ��:");
                    scanf("%d",&i);
                    j=ListDelete(L,i,e);
                    if(j){
                        if(flag) Lists.elem[x].L.length--;
                        else L.length--;
                        ListTraverse(L);
                    }else printf("ERROR\n");
                }
                break;
            case 12:									//����
                if(!L.elem) printf("INFEASIBLE\n");
                else if(!L.length) printf("�����Ա�\n");
                else ListTraverse(L);
                break;
            case 13:									//д���ļ�
                if(!L.elem) printf("INFEASIBLE\n");
                else{
                    i=0;
                    printf("�����ļ���:");
                    scanf("%s",FileName);
                    if(SaveList(L,FileName))
                        printf("OK\n");
                    else printf("ERROR\n");
                }
                break;
            case 14:									//��ȡ�ļ�
                printf("�����ļ���:");
                scanf("%s",FileName);
                while(1){
                    printf("�������Ա���:");
                    scanf("%s",name);
                    if(LocateList(Lists,name))
                    printf("����\n");			        //����,��������
                    else break;
                }
                AddList(Lists,name);
                if(LoadList(Lists,FileName))
                    ListTraverse(Lists.elem[Lists.length-1].L);
                else printf("ERROR\n");
                break;
            case 15:									//����±�
                printf("����Ҫ���ӵ����Ա�ĸ���:");
                scanf("%d",&n);
                if(Lists.length+n>10){				//���������
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
                    else{
                        if(AddList(Lists,name)){
                            Input(Lists.elem[Lists.length-1].L);
                            printf("OK\n");
                        }else printf("ERROR\n");
                    }
                }
                break;
            case 16:									//ɾ����
                printf("����Ҫɾ�������Ա������:");
                scanf("%s",name);
                if(LocateList(Lists,name)){		//���ұ�
                    if(RemoveList(Lists,LocateList(Lists,name)-1))
                        for(n=0;n<Lists.length;n++){
                            printf("%s ",Lists.elem[n].name);
                            ListTraverse(Lists.elem[n].L);
                        }
                }else printf("ɾ��ʧ��\n");
                break;
            case 17:									//���ұ�
                printf("����Ҫ���ҵ����Ա������:");
                scanf("%s",name);
                if (n=LocateList(Lists,name)){
                    printf("%s ",Lists.elem[n-1].name);
                    ListTraverse(Lists.elem[n-1].L);
                }else printf("����ʧ��\n");
                break;
            case 0:
                goto down;
        }
    }
	down:
    printf("\n��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}

status Input(SqList &L){
    int i;
    printf("����Ԫ��,��������0:\n");
    scanf("%d",&i);
    while(i){
        L.elem[L.length++]=i;
        scanf("%d",&i);
    }
}

status InitList(SqList& L){							//��ʼ��
    L.length=0;
    L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
                                                    //�����ڴ�
    L.listsize=LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList& L){						//����
    free(L.elem);										//�ͷ��ڴ�
    L.length=0;
    L.elem=NULL;
    return OK;
}

status ClearList(SqList& L){						//���
    L.length=0;
    return OK;
}

status ListEmpty(SqList L){							//�п�
    if(L.length) return FALSE;
    else return TRUE;
}

status ListLength(SqList L){						//���
    return L.length;
}

status GetElem(SqList L,int i,ElemType &e){			//��ȡ
    if(i<1||i>L.length) return ERROR;				//λ�ò��Ϸ�
    else{
        e=L.elem[i-1];
        return OK;
    }
}

int LocateElem(SqList L,ElemType e){				//����
    int i;
    for(i=0;i<L.length;i++)
        if(L.elem[i]==e) return i+1;
    return 0;
}

status PriorElem(SqList L,ElemType e,ElemType &pre){
    int i=LocateElem(L,e);							//����LocateElem
    if(i>1){										//�ж�i�Ƿ�Ϸ�
        pre=L.elem[i-2];
        return OK;
    }
    else return ERROR;
}

status NextElem(SqList L,ElemType e,ElemType &next){
    int i=LocateElem(L,e); 							//����LocateElem
    if(0<i<L.length){								//�ж�i�Ƿ�Ϸ�
        next=L.elem[i];
        return OK;
    }
    else return ERROR;
}

status ListInsert(SqList &L,int i,ElemType e){		//����
    int j;
    if(i>L.length+1||i<1) return ERROR;				//λ�ò��Ϸ�
        else if(!L.length){
            L.elem[0]=e;
            return OK;
        }
    else{
        if(L.length+1>LIST_INIT_SIZE){	//����������������·���
            ElemType *newelem=(ElemType*)realloc(L.elem,sizeof(ElemType)*LIST_INIT_SIZE+LISTINCREMENT);
            L.elem=newelem;
        }
        for(j=L.length-1;j>=i-1;j--)
            L.elem[j+1]=L.elem[j];
        L.elem[i-1]=e;
        return OK;
    }
}

status ListDelete(SqList &L,int i,ElemType &e){		//ɾ��
    int j;
    if(i<1||i>L.length) return ERROR;				//λ�ò��Ϸ�
    else{
        e=L.elem[i-1];
        for(j=i-1;j<L.length-1;j++)
            L.elem[j]=L.elem[j+1];
        return OK;
    }
}

status ListTraverse(SqList L){						//����
    int i;
    for(i=0;i<L.length;i++){
        printf("%d",L.elem[i]);
        if(i!=L.length-1) printf(" ");
        else printf("\n");
    }
    return OK;
}

status SaveList(SqList L,char FileName[]){			//д���ļ�
    FILE *fp;
    int i=0;
    if(!(fp=fopen(FileName,"wb")))	return ERROR;   //���ļ�ʧ��
    else{
        while(i<L.length){
            fprintf(fp,"%d ",L.elem[i]);			//���Ա�д���ļ�
            i++;
        }
        fclose(fp);
        return OK;
    }
}

status LoadList(LISTS &Lists,char FileName[]){		//�����ļ�
    FILE *fp;
    int i=0;
    if(!(fp=fopen(FileName,"rb")))	return ERROR;   //���ļ�ʧ��
    else{
        while((fscanf(fp,"%d ",&Lists.elem[Lists.length-1].L.elem[i]))!=EOF)										//�������Ա���
            if(!feof(fp)) i++;
        Lists.elem[Lists.length-1].L.length=i+1;		//��������һ
        fclose(fp);
		 return OK;
    }
}

status AddList(LISTS &Lists,char ListName[]){		//�����±�
    strcpy(Lists.elem[Lists.length].name,ListName);
   Lists.elem[Lists.length].L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    Lists.elem[Lists.length].L.length=0;			//����Ϊ0
    Lists.length++;
    return OK;										//��������һ
}

status RemoveList(LISTS &Lists,int i){				//ɾ����
    free(Lists.elem[i].L.elem);						//�ͷ��ڴ�
    for(int j=i;j<Lists.length-1;j++)
        Lists.elem[j]=Lists.elem[j+1];				//ǰһ������
    Lists.length--;
    return OK;
}

int LocateList(LISTS Lists,char ListName[]){		//���ұ�
    for(int i=0;i<Lists.length;i++)
        if(!strcmp(ListName,Lists.elem[i].name))	//������ͬ
            return i+1;
    return 0;
}
