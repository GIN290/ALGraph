#include <stdio.h>
#include <stdlib.h>

#define N 20 //N表示图的顶点个数
typedef enum {
    DG, DN __attribute__((unused)), UDG __attribute__((unused)), UDN __attribute__((unused))
} GraphKind;//{有向图，有向网，无向图，无向网}
typedef struct ArcNode {
    int adjvex;//该弧指向顶点位置
    struct ArcNode *nextarc;//指向下一条弧的指针
} ArcNode;
typedef struct VNode {
    int data;//注意图的顶点信息是整型
    ArcNode *firstarc;//指向第一条邻接该顶点（以该顶点为弧尾）的弧的指针
} VNode, Adjlist[N];//最多N个顶点
typedef struct {
    Adjlist vertices;
    int vexnum, arcnum;//分别存图的顶点数和弧数
    GraphKind kind;//图的种类标志
} ALGraph;//邻接表
void CreateDG(ALGraph *G) {//创建一个有向图
    int i, j, k;
    ArcNode *s;
    G->kind = DG;//有向图
    printf("分别输入顶点数和弧数:>");
    scanf("%d%d", &G->vexnum, &G->arcnum);
    printf("输入顶点信息，从0开始，编号连续:>\n");
    for (i = 0; i < G->vexnum; i++) {
        scanf("%d", &G->vertices[i].data);
        G->vertices[i].firstarc = NULL;
    }
    printf("输入%d条弧，弧的信息格式:顶点信息,顶点信息\n", G->arcnum);
    for (k = 0; k < G->arcnum; k++) {
        //输入每个边信息，注意录入边的形式，例如顶点0，1之间有边，录入正确形式是:0,1
        scanf("%d,%d", &i, &j);
        s = (ArcNode *) malloc(sizeof(ArcNode));
        s->adjvex = j;
        s->nextarc = G->vertices[i].firstarc;
        G->vertices[i].firstarc = s;
    }
}

int visited[N] = {0}; //全局变量，初值是0，避免重复遍历
void DFS(ALGraph G, int v) {
    //从顶点v出发进行深度优先遍历，注意参数G的类型
    ArcNode *w;
    visited[v] = 1;
    printf("%3d", G.vertices[v].data);//输出顶点信息，在屏幕占3个宽度
    //找顶点v的邻接点，如果未被访问，则从相应的邻接点出发深度遍历
    for (w = G.vertices[v].firstarc; w; w = w->nextarc)
        if (!visited[w->adjvex])
            DFS(G, w->adjvex);//递归
}

void DFSGraph(ALGraph G) {
    //尝试从各点出发DFS
    int i;
    for (i = 0; i < G.vexnum; i++)
        if (!visited[i]) {
            printf("\n从顶点 %d 出发，深度遍历的结果:", i);
            DFS(G, i);//从i点出发深度遍历
            putchar('\n');//换行
        }
}

int OutputDegree(ALGraph G, int i) {
    //返回编号为i的结点出度
    int counts = 0;
    ArcNode *p = G.vertices[i].firstarc;
    while (p) {
        counts++;
        p = p->nextarc;
    }
    return counts;
}

int InDegree(ALGraph G, int i) {
    //求顶点编号为i的入度
    int j;//循环变量
    int counts = 0;
    ArcNode *p;
    for (j = 0; j < G.vexnum; j++) {//遍历每个顶点，查找边表中是否有编号i，有就加1
        p = G.vertices[j].firstarc;
        while (p) {
            if (p->adjvex == i) {
                counts++;
                break;
            }
            p = p->nextarc;
        }
    }
    return counts;
}

int DelEdge(ALGraph *G, int i, int j) {
    if (!G->arcnum) return 0;//没有弧的时候不用删除，没有这个点也无法删除
    if (i < 0 || i >= G->arcnum) return 0;
    ArcNode *p, *q;
    q = G->vertices[i].firstarc;
    while (q && q->adjvex != j) {
        p = q;
        q = q->nextarc;
    }
    if (!q) return 0;//没找到这条边
    if (!p) G->vertices[i].firstarc = q->nextarc;
    else p->nextarc = q->nextarc;
    free(q);
    return 1;
}

int delete(ALGraph G, int i, int j) {
    int flag = 0;
    ArcNode *p;
    if (i < 0 || i >= G.vexnum) return 0;//顶点有问题，过大或者过小
    if (G.arcnum == 0) return 0;//没边就不删了
//    if(!(i>=0&&i<G.vexnum&&j>=0&&j<G.vexnum))
//        printf("您输入的点不存在！");
//    return 0;                      //用户输入的顶点范围不对，则删除失败

    //判断用户输入的边是否存在，flag作为一个标志
    p = G.vertices[i].firstarc;
    while (p != NULL) {
        if (p->adjvex == j) {
            flag = 1;
        }
        p = p->nextarc;
    }
    if (flag == 0) {
        printf("您输入的边不存在！");
        return 0;
    }


    if (G.vertices[i].firstarc->adjvex == j)
        G.vertices[i].firstarc = G.vertices[i].firstarc->nextarc;
    else {
        p = G.vertices[i].firstarc;
        while (p->nextarc->adjvex != j) p = p->nextarc;
        p->nextarc = p->nextarc->nextarc;
    }
    return 1;
}