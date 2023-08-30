#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef struct{
    KeyType key;
    char others[20];
} VertexType;
typedef struct ArcNode{
    int adjvex;
    struct ArcNode *nextarc;
	}ArcNode;
typedef struct VNode{
    VertexType data;
    ArcNode *firstarc;
    }VNode,AdjList[MAX_VERTEX_NUM];
typedef struct{
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;
typedef struct{
    struct{
        char name[30];
        ALGraph G;
    }elem[10];
    int length;
}LISTS;
void Visit(VertexType v);
void Traverse(ALGraph G);
int locate(int key,VertexType V[]);
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G,KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,KeyType u);
int NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
status DFSTraverse(ALGraph &G);
status BFSTraverse(ALGraph &G);
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,int i);
int LocateList(LISTS Lists,char ListName[]);
int sum;						//�ⲿ���������ڼ�¼����ʱ�ѱ�������ĸ���
int t;							//�ⲿ���������ڼ�¼��ǰ�����Ķ���
int visited[20];				//�ⲿ���������ڼ�¼�����Ƿ��ѱ�����

int main(){
    ALGraph G;
    G.vexnum=0;
    VertexType V[30],value;
    KeyType VR[100][2];
    int flag,op,i,j,u,v,w,n,x;
    LISTS Lists;
    Lists.length=0;
    char FileName[30],name[30],Name[30];
    printf("     Menu for Linear Table On Sequence Structure \n");
    printf("-----------------------------------------------------\n");
    printf("    	  1. CreateCraph(��)  9. InsertArc\n");
    printf("    	  2. DestroyGraph(��)10. DeleteArc\n");
    printf("    	  3. LocateVex       11. DFSTraverse\n");
    printf("    	  4. PutVex          12. BFSTraverse\n");
    printf("    	  5. FirstAdjVex     13. SaveGraph\n");
    printf("    	  6. NextAdjVex      14. LoadGraph(��)\n");
    printf("    	  7. InsertVex       15. AddList(��)\n");
    printf("    	  8. DeleteVex       16. RemoveList(��)\n");
    printf("    	  0. exit            17. LocateList(��)\n");
    printf("-----------------------------------------------------\n");
    printf("          \n����ͼ��������0�����ͼ��������1:");
    scanf("%d",&flag);
    while(1){
        printf("      \n\n��ѡ����Ĳ���[0~19]: ");
        scanf("%d",&op);
        if(!flag&&op>13){
            printf("��ѡ���ͼ����\n");
            continue;
        }
        if(flag&&op>0&&op<3){
            printf("��ѡ��ͼ����\n");
            continue;
        }
        if(flag&&op<14&&op>0){
            printf("\n���������ͼ������: ");
            scanf("%s",Name);
            x=LocateList(Lists,Name)-1;
            if(x>=0) G=Lists.elem[x].G;
            else{
                printf("INFEASIBLE");
                continue;
            }
        }
        switch(op){
            case 1:										//����
                if(G.vexnum) printf("INFEASIBLE");
                else{
                    printf("�����붥�����ݣ���������-1 null��");
                    i=0;
                    do{
                        scanf("%d%s",&V[i].key,V[i].others);
                    } while(V[i++].key!=-1);			//���붥������
                    for(i=0;V[i+1].key!=-1;i++){
                        for(j=i+1;V[j].key!=-1;j++){
                            if(V[i].key==V[j].key){
                                j=0;
                                break;
                            }
                        }
                        if(!j) break;
                    }
                    if(!j){ 							//�ؼ��ʲ�Ψһ
                        printf("ERROR");
                        break;
                    }
                    else{
                        printf("�����뻡����������-1 -1��");
                        i=0;
                        do{
                            scanf("%d%d",&VR[i][0],&VR[i][1]);
                        }while(VR[i++][0]!=-1);	//���뻡����
                        if(CreateCraph(G,V,VR))
                            printf("OK");
                        else printf("ERROR");
                    }
                }
                break;
            case 2:										//����
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    if(flag) j=DestroyGraph(Lists.elem[x].G);
                    else j=DestroyGraph(G);
                    if(j) printf("OK");
                    else printf("ERROR");
                }
                break;
            case 3:										//���
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("����������ҵĶ���ؼ��֣�");
                    scanf("%d",&u);
                    j=LocateVex(G,u);
                    if(j!=-1) Visit(G.vertices[j].data);
                    else printf("ERROR");
                }
                break;
            case 4:										//��ֵ
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("�������븳ֵ�Ķ���ؼ��֣�");
                    scanf("%d",&u);
                    printf("�����붥����ֵ��");
                    scanf("%d%s",&value.key,value.others);
                    if(flag)
                        if(PutVex(Lists.elem[x].G,u,value))
                            for(i=0;i<Lists.elem[x].G.vexnum;i++)
                                Visit(Lists.elem[x].G.vertices[i].data);
                        else printf("ERROR");
                    else
                        if(PutVex(G,u,value))
                            for(i=0;i<G.vexnum;i++)
                                Visit(G.vertices[i].data);
                        else printf("ERROR");
                }
                break;
            case 5:									//��õ�һ�ڽӶ���
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("����������ҵĶ���ؼ��֣�");
                    scanf("%d",&u);
                    j=FirstAdjVex(G,u);
                    if(j!=-1) Visit(G.vertices[j].data);
                    else printf("ERROR");
                }
                break;
            case 6:									//�����һ�ڽӶ���
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("����������ҵĶ�����ڽӶ���ؼ��֣�");
                    scanf("%d%d",&v,&w);
                    j=NextAdjVex(G,v,w);
                    if(j!=-1) Visit(G.vertices[j].data);
                    else printf("ERROR");
                }
                break;
            case 7:									//���붥��
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("�����������Ķ�������ݣ�");
                    scanf("%d%s",&value.key,value.others);
                    if(flag)
                        if(InsertVex(Lists.elem[x].G,value))
                            Traverse(Lists.elem[x].G);
                        else printf("ERROR");
                    else if(InsertVex(G,value))
                        for(i=0;i<G.vexnum;i++)
                            Visit(G.vertices[i].data);
                    else printf("ERROR");
                }
                break;
            case 8:									//ɾ������
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("��������ɾ���Ķ���Ĺؼ�ֵ��");
                    scanf("%d",&v);
                    if(flag)
                        if(DeleteVex(Lists.elem[x].G,v))
                            Traverse(Lists.elem[x].G);
                        else printf("ERROR");
                    else if(DeleteVex(G,v))
                        Traverse(G);
                    else printf("ERROR");
                }
                break;
            case 9:									//���뻡
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("�����������Ļ���");
                    scanf("%d%d",&v,&w);
                    if(flag)
                        if(InsertArc(Lists.elem[x].G,v,w))
                            Traverse(Lists.elem[x].G);
                        else printf("ERROR");
                    else if(InsertArc(G,v,w))
                        Traverse(G);
                    else printf("ERROR");
                }
                break;
            case 10:								//ɾ����
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("��������ɾ���Ļ���");
                    scanf("%d%d",&v,&w);
                    if(flag)
                        if(DeleteArc(Lists.elem[x].G,v,w))
                            Traverse(Lists.elem[x].G);
                        else printf("ERROR");
                    else if(DeleteArc(G,v,w))
                        Traverse(G);
                    else printf("ERROR");
                }
                break;
            case 11:								//����
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    t=sum=0;				//���������͵�ǰ����λ��Ϊ0
                    for(i=0;i<20;i++)
                        visited[i]=0;				//���ж���δ����
                    DFSTraverse(G);
                }
                break;
            case 12:								//����
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    t=sum=0;				//���������͵�ǰ����λ��Ϊ0
                    for(i=0;i<20;i++)
                        visited[i]=0;				//���ж���δ����
                    BFSTraverse(G);
                }
                break;
            case 13:								//д���ļ�
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("�����ļ���:");
                    scanf("%s",FileName);
                    if(SaveGraph(G,FileName));
                    printf("OK");
                }
                break;
            case 14:
                printf("�����ļ�����");
                scanf("%s",FileName);
                while(1){
                    printf("����ͼ��:");
                    scanf("%s",name);
                    if(LocateList(Lists,name))
                        printf("����\n");		    //����,��������
                    else break;
                }
                AddList(Lists,name);
                if(LoadGraph(Lists.elem[Lists.length-1].G,FileName))
                    Traverse(Lists.elem[Lists.length-1].G);
                else printf("ERROR\n");
                break;
            case 15:								//����ͼ
                printf("����Ҫ���ӵ�ͼ�ĸ���:");
                scanf("%d",&n);
                if(Lists.length+n>10){
                    printf("OVERFLOW\n");
                    break;
                }
                while(n--){
                    printf("����ͼ��:");
                    scanf("%s",name);
                    if(LocateList(Lists,name)){   //�ж��Ƿ�������
                        printf("����\n");
                        n++;
                        continue;
                    }
                    else{
                        if(AddList(Lists,name)){
                            printf("�����붥�����ݣ���������-1 null��");
                            i=0;
                            do{
                                scanf("%d%s",&V[i].key,V[i].others);
                            }while(V[i++].key!=-1);
                            printf("�����뻡����������-1 -1��");
                            i=0;
                            do{
                                scanf("%d%d",&VR[i][0],&VR[i][1]);
                            }while(VR[i++][0]!=-1);
                            if(CreateCraph(Lists.elem[Lists.length-1].G,V,VR))
                                printf("OK\n");
                        }
                        else printf("ERROR\n");
                    }
                    for(i=0;i<30;i++)				//��ʼ������
                        V[i].key=-1;
                    for(i=0;i<100;i++)
                        VR[i][0]=VR[i][1]=-1;
                }
                break;
            case 16:								//ɾ��ͼ
                printf("����Ҫɾ����ͼ������:");
                scanf("%s",name);
                if(LocateList(Lists,name)){			//����ͼ
                    if(RemoveList(Lists,LocateList(Lists,name)-1)){
                        for(n=0;n<Lists.length;n++){
                            printf("%s\n",Lists.elem[n].name);
                            if(!Lists.elem[n].G.vexnum) printf("��ͼ\n");
                            else Traverse(Lists.elem[n].G);
                        }
                    }
                }
                else printf("ɾ��ʧ��");
                break;
            case 17:								//����ͼ
                printf("����Ҫ���ҵ�ͼ������:");
                scanf("%s",name);
                if(n=LocateList(Lists,name)){
                    if(!Lists.elem[n-1].G.vexnum) printf("INFEASIBLE");
                    else{
                        printf("%s\n",Lists.elem[n-1].name);
                        if(!Lists.elem[n-1].G.vexnum)
                            printf("��ͼ\n");
                        else Traverse(Lists.elem[n-1].G);
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

void Visit(VertexType v){								//�������
    printf("%d %s ",v.key,v.others);
}

void Traverse(ALGraph G){								//����ͼ
    for(int i=0;i<G.vexnum;i++){
        ArcNode *p=G.vertices[i].firstarc;
        printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
        while(p){
            printf(" %d",p->adjvex);
            p=p->nextarc;
        }
        printf("\n");
    }
}

int locate(int key,VertexType V[]){
    int i;
    for(i=0;V[i].key!=-1;i++)
        if(key==V[i].key)
            return i;
}

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]){	//����
    int i,j,k,flag;		//flag���ڱ�ǻ��е������Ƿ��붥��ؼ���ƥ��
    ArcNode *p;
    for(k=0;k<2;k++){
        for(j=0;VR[j][k]!=-1;j++){
            for(flag=i=0;V[i].key!=-1;i++)
                if(V[i].key==VR[j][k])
                    flag=1;
            if(!flag) return ERROR;
        }							//�жϻ��е������Ƿ��붥��ؼ���ƥ��
    }
    G.vexnum=G.arcnum=0;
    for(i=0;V[i].key!=-1;i++){
        G.vexnum++;
        G.vertices[i].data.key=V[i].key;			//���㸳ֵ
        strcpy(G.vertices[i].data.others,V[i].others);
        G.vertices[i].firstarc=NULL;
        for(j=0;VR[j][0]!=-1;j++){
            p=G.vertices[i].firstarc;
            if(VR[j][0]==V[i].key){
                G.vertices[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
                G.vertices[i].firstarc->adjvex=locate(VR[j][1],V);
                G.vertices[i].firstarc->nextarc=p;
                G.arcnum++;
            }
            else if(VR[j][1]==V[i].key){
                G.vertices[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
                G.vertices[i].firstarc->adjvex=locate(VR[j][0],V);
                G.vertices[i].firstarc->nextarc=p;
                G.arcnum++;
            }					//�ֱ𽫻���һ�����ݼӵ���Ӧ�Ķ���������
        }
    }
    G.arcnum/=2;										//����������Ҫ����2
    return OK;
}

status DestroyGraph(ALGraph &G){					//����
    int i;
    ArcNode *p,*q;
    for(i=0;i<G.vexnum;i++){
        while(G.vertices[i].firstarc){
            p=G.vertices[i].firstarc;
            q=p->nextarc;
            free(p);
            G.vertices[i].firstarc=q;
        }
        G.vertices[i].firstarc=NULL;
    }
    G.vexnum=G.arcnum=0;
    return OK;
}

int LocateVex(ALGraph G,KeyType u){				//����
    int i;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==u)
            return i;
    }
    return -1;
}

status PutVex(ALGraph &G,KeyType u,VertexType value){	//��ֵ
    int i=LocateVex(G,u);
    if(i==-1) return ERROR;							//�ж϶����Ƿ����
    if(u!=value.key&&LocateVex(G,value.key)!=-1)	//�жϹؼ����Ƿ�Ψһ
        return ERROR;
    G.vertices[i].data.key=value.key;
    strcpy(G.vertices[i].data.others,value.others);
    return OK;
}

int FirstAdjVex(ALGraph G,KeyType u){				//��õ�һ�ڽӶ���
    int i=LocateVex(G,u);
    if(i==-1) return -1;								//�ж϶����Ƿ����
    else return G.vertices[i].firstarc->adjvex;
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w){	//�����һ�ڽӶ���
    int i=LocateVex(G,v),j=LocateVex(G,w);
    if(i==-1||j==-1) return -1;						//�жϻ��Ƿ����
    ArcNode *p=G.vertices[i].firstarc;
    while(p->nextarc){
        if(p->adjvex==j)
            return p->nextarc->adjvex;
        p=p->nextarc;
    }
    return -1;
}

status InsertVex(ALGraph &G,VertexType v){		//���붥��
    int i=LocateVex(G,v.key);
    if(i!=-1||G.vexnum>19) return ERROR;			//�жϹؼ����Ƿ�Ψһ
    G.vertices[G.vexnum].data.key=v.key;			//���㸳ֵ
    strcpy(G.vertices[G.vexnum].data.others,v.others);
    G.vertices[G.vexnum++].firstarc=NULL;
    return OK;
}

status DeleteVex(ALGraph &G,KeyType v){			//ɾ������
    int i,w=LocateVex(G,v);
    if(w==-1||G.vexnum==1) return ERROR;			//�ж϶����Ƿ����
    ArcNode *p=NULL,*q=NULL;
    while(p=G.vertices[w].firstarc){				//�ͷ������ڴ�
        q=p->nextarc;
        free(p);
        G.vertices[w].firstarc=q;
    }
    G.vexnum--;
    for(i=w;i<G.vexnum;i++)						//��һ���㸲��ǰһ����
        G.vertices[i]=G.vertices[i+1];
    for(i=0;i<G.vexnum;i++){						//ɾ���ö���Ļ�
        if(!G.vertices[i].firstarc) continue;
        if(G.vertices[i].firstarc->adjvex==w){	//Ϊͷ�����һ���
            G.arcnum--;
            p=G.vertices[i].firstarc;
            q=p->nextarc;
            free(p);
            G.vertices[i].firstarc=q;
        }
        else{											//��ͷ�����һ���
            p=G.vertices[i].firstarc->nextarc;
            q=G.vertices[i].firstarc;
            while(p){
                if(p->adjvex==w){
                    G.arcnum--;
                    free(p);
                    q->nextarc=p->nextarc;
                    p=q->nextarc;
                }
                else{
                    p=p->nextarc;
                    q=q->nextarc;
                }
            }
        }
    }
    for(i=0;i<G.vexnum;i++){						//�µĶ���λ�����
        p=G.vertices[i].firstarc;
        while(p){
            if(p->adjvex>w)
                p->adjvex--;
            p=p->nextarc;
        }
    }
    return OK;
}

status InsertArc(ALGraph &G,KeyType v,KeyType w){	//���뻡
    int i=LocateVex(G,v),j=LocateVex(G,w);
    if(i==-1||j==-1) return ERROR;					//�жϻ��Ƿ�Ϸ�
    ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode)),*q=G.vertices[i].firstarc,*r=(ArcNode*)malloc(sizeof(ArcNode));						//�½������ڴ�
    while(q){
        if(q->adjvex==j) return ERROR;              //�жϻ��Ƿ��Ѵ���
        q=q->nextarc;
    }
    p->adjvex=j;									//�½�㸳ֵ
    r->adjvex=i;
    q=G.vertices[i].firstarc;
    G.vertices[i].firstarc=p;
    p->nextarc=q;
    q=G.vertices[j].firstarc;
    G.vertices[j].firstarc=r;
    r->nextarc=q;
    G.arcnum++;
    return OK;
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w){	//ɾ����
    int i=LocateVex(G,v),j=LocateVex(G,w),flag=0;
    if(i==-1||j==-1) return ERROR;					//�жϻ��Ƿ����
    ArcNode *p,*q;
    if(G.vertices[i].firstarc->adjvex==j){		//Ϊͷ�����һ���
        flag=1;
        p=G.vertices[i].firstarc;
        q=p->nextarc;
        free(p);
        G.vertices[i].firstarc=q;
    }
    else{												//Ϊ��ͷ�����һ���
        p=G.vertices[i].firstarc->nextarc;
        q=G.vertices[i].firstarc;
        while(p){
            if(p->adjvex==j){
                flag=1;
                q->nextarc=p->nextarc;				//ɾ�����
                free(p);								//�ͷ��ڴ�
                p=q->nextarc;						//ָ����һ���
            }
            else{
                p=p->nextarc;
                q=q->nextarc;
            }
        }
    }
    if(!flag) return ERROR;					   //flag���ڱ���Ƿ���ɾ��
    if(G.vertices[j].firstarc->adjvex==i){  //�ظ�һ�Σ�ɾ����һ�����
        p=G.vertices[j].firstarc;
        q=p->nextarc;
        free(p);
        G.vertices[j].firstarc=q;
    }
    else{
        p=G.vertices[j].firstarc->nextarc;
        q=G.vertices[j].firstarc;
        while(p){
            if(p->adjvex==i){
                q->nextarc=p->nextarc;
                free(p);
                p=q->nextarc;
            }
            else{
                p=p->nextarc;
                q=q->nextarc;
            }
        }
    }
    G.arcnum--;
    return OK;
}

status DFSTraverse(ALGraph &G){						//����
    ArcNode *p=NULL;
    int w,i;
    Visit(G.vertices[t].data);
    visited[t]=1;										//���Ϊ�ѷ���
    sum++;												//��������1
    p=G.vertices[t].firstarc;
    while(p){
        w=p->adjvex;
        if(!visited[w]){
            t=w;
            DFSTraverse(G);				  //������һδ���ʹ����ڽӶ���
        }
        p=p->nextarc;
    }
    if(sum!=G.vexnum){								//����ͨͼ
        for(i=0;i<G.vexnum;i++){
            if(!visited[i]){						//Ѱ����һδ���ʶ���
                t=i;
                break;
            }
        }
        DFSTraverse(G);
    }
}

status BFSTraverse(ALGraph &G){						//����
    ArcNode *p;
    int w,i;
    int q[G.vexnum],front=0,rear=0;//�������ڼ�¼��ͨ��֧�Ƿ��ѷ�����
    Visit(G.vertices[t].data);
    visited[t]=1;
    sum++;
    rear=(rear+1)%G.vexnum;							//��βָ���1
    q[rear]=t;
    while(front!=rear){
        front=(front+1)%G.vexnum;					//����ָ���1
        w=q[front];
        p=G.vertices[w].firstarc;
        while(p){
            if(!visited[p->adjvex]){		//������һδ���ʹ��Ķ���
                Visit(G.vertices[p->adjvex].data);
                sum++;
                visited[p->adjvex]=1;
                rear=(rear+1)%G.vexnum;   //��βָ���1
                q[rear]=p->adjvex;			//�������
            }
            p=p->nextarc;
        }
    }
    if(sum!=G.vexnum){						//����ͨͼ
        for(i=0;i<G.vexnum;i++){
            if(!visited[i]){				//Ѱ����һδ���ʹ��Ķ���
                t=i;
                break;
            }
        }
        BFSTraverse(G);
    }
}
status SaveGraph(ALGraph G, char FileName[]){	//д���ļ�
    int i;
    ArcNode *p;
    FILE *fp;
    if(fp=fopen(FileName,"wb")){
        fprintf(fp,"%d %d",G.vexnum,G.arcnum);	//д�붥�����ͻ���
        fputc('\n', fp);						//д�����
        for(i=0;i<G.vexnum;i++){
fprintf(fp,"%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
            for(p=G.vertices[i].firstarc;p;p=p->nextarc)
                fprintf(fp," %d",p->adjvex);
            fputc('\n',fp);						//д��һ�������
        }
        fclose(fp);
        return OK;
    }else return ERROR;
}

status LoadGraph(ALGraph &G, char FileName[]){	//��ȡ�ļ�
    ArcNode *p;
    FILE *fp;
    if(fp=fopen(FileName,"r")){
        fscanf(fp,"%d %d",&G.vexnum,&G.arcnum);	//��ȡ�������ͻ���
        fgetc(fp);								//��ȡ���з�
        int a=0,i;
        for(i=0;i<G.vexnum;i++){
fscanf(fp,"%d %s",&G.vertices[i].data.key,G.vertices[i].data.others);
            G.vertices[i].firstarc=NULL;
            if(fgetc(fp)!='\n'){
                fscanf(fp,"%d",&a);
                G.vertices[i].firstarc=(ArcNode *)malloc(sizeof(ArcNode));							//����ͷ���
                G.vertices[i].firstarc->adjvex=a;
                G.vertices[i].firstarc->nextarc=NULL;
                p=G.vertices[i].firstarc;
                while(fgetc(fp)!='\n'){	   //���з�ǰΪͬһ��������
                    fscanf(fp,"%d",&a);
                    p->nextarc=(ArcNode *)malloc(sizeof(ArcNode));
                    p->nextarc->adjvex=a;
                    p->nextarc->nextarc=NULL;   //�����ڽӽ��
                    p=p->nextarc;
                }
            }
        }
        fclose(fp);
        return OK;
    }else return ERROR;
}

status AddList(LISTS &Lists,char ListName[]){
    strcpy(Lists.elem[Lists.length++].name,ListName);
    return OK;
}

status RemoveList(LISTS &Lists,int i){
    for(int j=i;j<Lists.length-1;j++)
        Lists.elem[j]=Lists.elem[j+1];
    Lists.length--;
    return OK;
}

int LocateList(LISTS Lists,char ListName[]){
    for(int i=0;i<Lists.length;i++)
        if(!strcmp(ListName,Lists.elem[i].name))
            return i+1;
    return 0;
}

