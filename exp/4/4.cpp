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
int sum;						//外部变量，用于记录遍历时已遍历顶点的个数
int t;							//外部变量，用于记录当前遍历的顶点
int visited[20];				//外部变量，用于记录顶点是否已遍历过

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
    printf("    	  1. CreateCraph(单)  9. InsertArc\n");
    printf("    	  2. DestroyGraph(单)10. DeleteArc\n");
    printf("    	  3. LocateVex       11. DFSTraverse\n");
    printf("    	  4. PutVex          12. BFSTraverse\n");
    printf("    	  5. FirstAdjVex     13. SaveGraph\n");
    printf("    	  6. NextAdjVex      14. LoadGraph(多)\n");
    printf("    	  7. InsertVex       15. AddList(多)\n");
    printf("    	  8. DeleteVex       16. RemoveList(多)\n");
    printf("    	  0. exit            17. LocateList(多)\n");
    printf("-----------------------------------------------------\n");
    printf("          \n单个图操作输入0，多个图操作输入1:");
    scanf("%d",&flag);
    while(1){
        printf("      \n\n请选择你的操作[0~19]: ");
        scanf("%d",&op);
        if(!flag&&op>13){
            printf("请选择多图操作\n");
            continue;
        }
        if(flag&&op>0&&op<3){
            printf("请选择单图操作\n");
            continue;
        }
        if(flag&&op<14&&op>0){
            printf("\n输入操作的图的名字: ");
            scanf("%s",Name);
            x=LocateList(Lists,Name)-1;
            if(x>=0) G=Lists.elem[x].G;
            else{
                printf("INFEASIBLE");
                continue;
            }
        }
        switch(op){
            case 1:										//创建
                if(G.vexnum) printf("INFEASIBLE");
                else{
                    printf("请输入顶点数据，结束输入-1 null：");
                    i=0;
                    do{
                        scanf("%d%s",&V[i].key,V[i].others);
                    } while(V[i++].key!=-1);			//输入顶点数据
                    for(i=0;V[i+1].key!=-1;i++){
                        for(j=i+1;V[j].key!=-1;j++){
                            if(V[i].key==V[j].key){
                                j=0;
                                break;
                            }
                        }
                        if(!j) break;
                    }
                    if(!j){ 							//关键词不唯一
                        printf("ERROR");
                        break;
                    }
                    else{
                        printf("请输入弧，结束输入-1 -1：");
                        i=0;
                        do{
                            scanf("%d%d",&VR[i][0],&VR[i][1]);
                        }while(VR[i++][0]!=-1);	//输入弧数据
                        if(CreateCraph(G,V,VR))
                            printf("OK");
                        else printf("ERROR");
                    }
                }
                break;
            case 2:										//销毁
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    if(flag) j=DestroyGraph(Lists.elem[x].G);
                    else j=DestroyGraph(G);
                    if(j) printf("OK");
                    else printf("ERROR");
                }
                break;
            case 3:										//清空
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("请输入想查找的顶点关键字：");
                    scanf("%d",&u);
                    j=LocateVex(G,u);
                    if(j!=-1) Visit(G.vertices[j].data);
                    else printf("ERROR");
                }
                break;
            case 4:										//赋值
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("请输入想赋值的顶点关键字：");
                    scanf("%d",&u);
                    printf("请输入顶点数值：");
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
            case 5:									//获得第一邻接顶点
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("请输入想查找的顶点关键字：");
                    scanf("%d",&u);
                    j=FirstAdjVex(G,u);
                    if(j!=-1) Visit(G.vertices[j].data);
                    else printf("ERROR");
                }
                break;
            case 6:									//获得下一邻接顶点
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("请输入想查找的顶点和邻接顶点关键字：");
                    scanf("%d%d",&v,&w);
                    j=NextAdjVex(G,v,w);
                    if(j!=-1) Visit(G.vertices[j].data);
                    else printf("ERROR");
                }
                break;
            case 7:									//插入顶点
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("请输入想插入的顶点的数据：");
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
            case 8:									//删除顶点
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("请输入想删除的顶点的关键值：");
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
            case 9:									//插入弧
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("请输入想插入的弧：");
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
            case 10:								//删除弧
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("请输入想删除的弧：");
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
            case 11:								//深搜
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    t=sum=0;				//搜索总数和当前搜索位置为0
                    for(i=0;i<20;i++)
                        visited[i]=0;				//所有顶点未搜索
                    DFSTraverse(G);
                }
                break;
            case 12:								//广搜
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    t=sum=0;				//搜索总数和当前搜索位置为0
                    for(i=0;i<20;i++)
                        visited[i]=0;				//所有顶点未搜索
                    BFSTraverse(G);
                }
                break;
            case 13:								//写入文件
                if(!G.vexnum) printf("INFEASIBLE");
                else{
                    printf("输入文件名:");
                    scanf("%s",FileName);
                    if(SaveGraph(G,FileName));
                    printf("OK");
                }
                break;
            case 14:
                printf("输入文件名：");
                scanf("%s",FileName);
                while(1){
                    printf("输入图名:");
                    scanf("%s",name);
                    if(LocateList(Lists,name))
                        printf("重名\n");		    //重名,重新输入
                    else break;
                }
                AddList(Lists,name);
                if(LoadGraph(Lists.elem[Lists.length-1].G,FileName))
                    Traverse(Lists.elem[Lists.length-1].G);
                else printf("ERROR\n");
                break;
            case 15:								//新增图
                printf("输入要增加的图的个数:");
                scanf("%d",&n);
                if(Lists.length+n>10){
                    printf("OVERFLOW\n");
                    break;
                }
                while(n--){
                    printf("输入图名:");
                    scanf("%s",name);
                    if(LocateList(Lists,name)){   //判断是否有重名
                        printf("重名\n");
                        n++;
                        continue;
                    }
                    else{
                        if(AddList(Lists,name)){
                            printf("请输入顶点数据，结束输入-1 null：");
                            i=0;
                            do{
                                scanf("%d%s",&V[i].key,V[i].others);
                            }while(V[i++].key!=-1);
                            printf("请输入弧，结束输入-1 -1：");
                            i=0;
                            do{
                                scanf("%d%d",&VR[i][0],&VR[i][1]);
                            }while(VR[i++][0]!=-1);
                            if(CreateCraph(Lists.elem[Lists.length-1].G,V,VR))
                                printf("OK\n");
                        }
                        else printf("ERROR\n");
                    }
                    for(i=0;i<30;i++)				//初始化数组
                        V[i].key=-1;
                    for(i=0;i<100;i++)
                        VR[i][0]=VR[i][1]=-1;
                }
                break;
            case 16:								//删除图
                printf("输入要删除的图的名字:");
                scanf("%s",name);
                if(LocateList(Lists,name)){			//查找图
                    if(RemoveList(Lists,LocateList(Lists,name)-1)){
                        for(n=0;n<Lists.length;n++){
                            printf("%s\n",Lists.elem[n].name);
                            if(!Lists.elem[n].G.vexnum) printf("空图\n");
                            else Traverse(Lists.elem[n].G);
                        }
                    }
                }
                else printf("删除失败");
                break;
            case 17:								//查找图
                printf("输入要查找的图的名字:");
                scanf("%s",name);
                if(n=LocateList(Lists,name)){
                    if(!Lists.elem[n-1].G.vexnum) printf("INFEASIBLE");
                    else{
                        printf("%s\n",Lists.elem[n-1].name);
                        if(!Lists.elem[n-1].G.vexnum)
                            printf("空图\n");
                        else Traverse(Lists.elem[n-1].G);
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

void Visit(VertexType v){								//输出顶点
    printf("%d %s ",v.key,v.others);
}

void Traverse(ALGraph G){								//遍历图
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

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]){	//创建
    int i,j,k,flag;		//flag用于标记弧中的数据是否与顶点关键字匹配
    ArcNode *p;
    for(k=0;k<2;k++){
        for(j=0;VR[j][k]!=-1;j++){
            for(flag=i=0;V[i].key!=-1;i++)
                if(V[i].key==VR[j][k])
                    flag=1;
            if(!flag) return ERROR;
        }							//判断弧中的数据是否与顶点关键字匹配
    }
    G.vexnum=G.arcnum=0;
    for(i=0;V[i].key!=-1;i++){
        G.vexnum++;
        G.vertices[i].data.key=V[i].key;			//顶点赋值
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
            }					//分别将弧的一组数据加到相应的顶点链表中
        }
    }
    G.arcnum/=2;										//弧的总数需要除以2
    return OK;
}

status DestroyGraph(ALGraph &G){					//销毁
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

int LocateVex(ALGraph G,KeyType u){				//查找
    int i;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==u)
            return i;
    }
    return -1;
}

status PutVex(ALGraph &G,KeyType u,VertexType value){	//赋值
    int i=LocateVex(G,u);
    if(i==-1) return ERROR;							//判断顶点是否存在
    if(u!=value.key&&LocateVex(G,value.key)!=-1)	//判断关键字是否唯一
        return ERROR;
    G.vertices[i].data.key=value.key;
    strcpy(G.vertices[i].data.others,value.others);
    return OK;
}

int FirstAdjVex(ALGraph G,KeyType u){				//获得第一邻接顶点
    int i=LocateVex(G,u);
    if(i==-1) return -1;								//判断顶点是否存在
    else return G.vertices[i].firstarc->adjvex;
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w){	//获得下一邻接顶点
    int i=LocateVex(G,v),j=LocateVex(G,w);
    if(i==-1||j==-1) return -1;						//判断弧是否存在
    ArcNode *p=G.vertices[i].firstarc;
    while(p->nextarc){
        if(p->adjvex==j)
            return p->nextarc->adjvex;
        p=p->nextarc;
    }
    return -1;
}

status InsertVex(ALGraph &G,VertexType v){		//插入顶点
    int i=LocateVex(G,v.key);
    if(i!=-1||G.vexnum>19) return ERROR;			//判断关键字是否唯一
    G.vertices[G.vexnum].data.key=v.key;			//顶点赋值
    strcpy(G.vertices[G.vexnum].data.others,v.others);
    G.vertices[G.vexnum++].firstarc=NULL;
    return OK;
}

status DeleteVex(ALGraph &G,KeyType v){			//删除顶点
    int i,w=LocateVex(G,v);
    if(w==-1||G.vexnum==1) return ERROR;			//判断顶点是否存在
    ArcNode *p=NULL,*q=NULL;
    while(p=G.vertices[w].firstarc){				//释放链表内存
        q=p->nextarc;
        free(p);
        G.vertices[w].firstarc=q;
    }
    G.vexnum--;
    for(i=w;i<G.vexnum;i++)						//后一顶点覆盖前一顶点
        G.vertices[i]=G.vertices[i+1];
    for(i=0;i<G.vexnum;i++){						//删除该顶点的弧
        if(!G.vertices[i].firstarc) continue;
        if(G.vertices[i].firstarc->adjvex==w){	//为头结点下一结点
            G.arcnum--;
            p=G.vertices[i].firstarc;
            q=p->nextarc;
            free(p);
            G.vertices[i].firstarc=q;
        }
        else{											//非头结点下一结点
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
    for(i=0;i<G.vexnum;i++){						//新的顶点位序调整
        p=G.vertices[i].firstarc;
        while(p){
            if(p->adjvex>w)
                p->adjvex--;
            p=p->nextarc;
        }
    }
    return OK;
}

status InsertArc(ALGraph &G,KeyType v,KeyType w){	//插入弧
    int i=LocateVex(G,v),j=LocateVex(G,w);
    if(i==-1||j==-1) return ERROR;					//判断弧是否合法
    ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode)),*q=G.vertices[i].firstarc,*r=(ArcNode*)malloc(sizeof(ArcNode));						//新结点分配内存
    while(q){
        if(q->adjvex==j) return ERROR;              //判断弧是否已存在
        q=q->nextarc;
    }
    p->adjvex=j;									//新结点赋值
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

status DeleteArc(ALGraph &G,KeyType v,KeyType w){	//删除弧
    int i=LocateVex(G,v),j=LocateVex(G,w),flag=0;
    if(i==-1||j==-1) return ERROR;					//判断弧是否存在
    ArcNode *p,*q;
    if(G.vertices[i].firstarc->adjvex==j){		//为头结点下一结点
        flag=1;
        p=G.vertices[i].firstarc;
        q=p->nextarc;
        free(p);
        G.vertices[i].firstarc=q;
    }
    else{												//为非头结点下一结点
        p=G.vertices[i].firstarc->nextarc;
        q=G.vertices[i].firstarc;
        while(p){
            if(p->adjvex==j){
                flag=1;
                q->nextarc=p->nextarc;				//删除结点
                free(p);								//释放内存
                p=q->nextarc;						//指向下一结点
            }
            else{
                p=p->nextarc;
                q=q->nextarc;
            }
        }
    }
    if(!flag) return ERROR;					   //flag用于标记是否已删除
    if(G.vertices[j].firstarc->adjvex==i){  //重复一次，删除另一个结点
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

status DFSTraverse(ALGraph &G){						//深搜
    ArcNode *p=NULL;
    int w,i;
    Visit(G.vertices[t].data);
    visited[t]=1;										//标记为已访问
    sum++;												//访问数加1
    p=G.vertices[t].firstarc;
    while(p){
        w=p->adjvex;
        if(!visited[w]){
            t=w;
            DFSTraverse(G);				  //访问下一未访问过的邻接顶点
        }
        p=p->nextarc;
    }
    if(sum!=G.vexnum){								//不连通图
        for(i=0;i<G.vexnum;i++){
            if(!visited[i]){						//寻找下一未访问顶点
                t=i;
                break;
            }
        }
        DFSTraverse(G);
    }
}

status BFSTraverse(ALGraph &G){						//广搜
    ArcNode *p;
    int w,i;
    int q[G.vexnum],front=0,rear=0;//队列用于记录联通分支是否已访问完
    Visit(G.vertices[t].data);
    visited[t]=1;
    sum++;
    rear=(rear+1)%G.vexnum;							//队尾指针加1
    q[rear]=t;
    while(front!=rear){
        front=(front+1)%G.vexnum;					//队首指针加1
        w=q[front];
        p=G.vertices[w].firstarc;
        while(p){
            if(!visited[p->adjvex]){		//访问下一未访问过的顶点
                Visit(G.vertices[p->adjvex].data);
                sum++;
                visited[p->adjvex]=1;
                rear=(rear+1)%G.vexnum;   //队尾指针加1
                q[rear]=p->adjvex;			//加入队列
            }
            p=p->nextarc;
        }
    }
    if(sum!=G.vexnum){						//非连通图
        for(i=0;i<G.vexnum;i++){
            if(!visited[i]){				//寻找下一未访问过的顶点
                t=i;
                break;
            }
        }
        BFSTraverse(G);
    }
}
status SaveGraph(ALGraph G, char FileName[]){	//写入文件
    int i;
    ArcNode *p;
    FILE *fp;
    if(fp=fopen(FileName,"wb")){
        fprintf(fp,"%d %d",G.vexnum,G.arcnum);	//写入顶点数和弧数
        fputc('\n', fp);						//写完后换行
        for(i=0;i<G.vexnum;i++){
fprintf(fp,"%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
            for(p=G.vertices[i].firstarc;p;p=p->nextarc)
                fprintf(fp," %d",p->adjvex);
            fputc('\n',fp);						//写完一顶点后换行
        }
        fclose(fp);
        return OK;
    }else return ERROR;
}

status LoadGraph(ALGraph &G, char FileName[]){	//读取文件
    ArcNode *p;
    FILE *fp;
    if(fp=fopen(FileName,"r")){
        fscanf(fp,"%d %d",&G.vexnum,&G.arcnum);	//读取顶点数和弧数
        fgetc(fp);								//读取换行符
        int a=0,i;
        for(i=0;i<G.vexnum;i++){
fscanf(fp,"%d %s",&G.vertices[i].data.key,G.vertices[i].data.others);
            G.vertices[i].firstarc=NULL;
            if(fgetc(fp)!='\n'){
                fscanf(fp,"%d",&a);
                G.vertices[i].firstarc=(ArcNode *)malloc(sizeof(ArcNode));							//生成头结点
                G.vertices[i].firstarc->adjvex=a;
                G.vertices[i].firstarc->nextarc=NULL;
                p=G.vertices[i].firstarc;
                while(fgetc(fp)!='\n'){	   //换行符前为同一顶点数据
                    fscanf(fp,"%d",&a);
                    p->nextarc=(ArcNode *)malloc(sizeof(ArcNode));
                    p->nextarc->adjvex=a;
                    p->nextarc->nextarc=NULL;   //生产邻接结点
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

