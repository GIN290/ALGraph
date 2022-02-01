#include "graph.h"
//int main() {
//    ALGraph G;
//    int i,j;
//    CreateDG(&G);//创建一个有向图
//    //DFSGraph(G);//对图G深度优先遍历
////    printf("请输入想要查询出度的顶点编号:>");
////    scanf("%d",&i);
////    printf("%d的出度:>%d",i,OutputDegree(G,i));
////    printf("请输入想要查询入度的顶点编号:>");
////    scanf("%d",&i);
////    printf("%d的入度:>%d",i,InDegree(G,i));
//    printf("请输入想要删除的边:顶点信息,顶点信息");
//    scanf("%d,%d",&i,&j);
//    if(DelEdge(&G,i,j)==1) printf("OK\n");
//    DFSGraph(G);
//    return 0;
//}
int main(){
    int i,j,n;
    ALGraph G;
    CreateDG(&G);


//    printf("\n请输入你想求哪个顶点的出度：");
//    scanf("%d",&i);
//    n=OutputDegree(G,i);
//    printf("顶点%d的出度是：%d",i,n);

//    printf("\n请输入你想求哪个顶点的入度：");
//    scanf("%d",&i);
//    n=InDegree(G,i);
//    printf("顶点%d的入度是：%d",i,n);

    printf("\n请输入你要删除的有向边:");
    scanf("%d,%d",&i,&j);
    n=delete(G,i,j);
    if(n==1) printf("删除成功！");
    else     printf("删除失败！");

    DFSGraph(G);
    return 0;
}
