#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <queue>
#include <iostream>
using namespace std;

#define FILE_PATH "maze.data"

int maze[1004][1004];
int m, n;
int count;//我们总共搜索的步数


struct Node
{
    int x;
    int y;
};//迷宫矩阵每个节点的坐标；
bool haveExit() {
	queue<Node> Q;  //定义我们的队列
    Node Vs,Vn, Vw,Vd;
    int i,j;
    int visit[m][n];//用来标记我们的节点是否被访问过，以防止算法重复搜索已经搜索过的节点
    char path[m][n];//用来显示我们的算法过程
    for(i=0;i<m;i++)
    {
    	for(j=0;j<n;j++)
    		visit[i][j]=0;
    }
         

       for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
            path[i][j]='*';
    }
    Vs.x=0;
    Vs.y=0;//Vs是我们的起点
    Vd.x=m-1;//Vd使我们的终点
    Vd.y=n-1;
    Q.push(Vs);//首先将我们的起点加入队列
    visit[Vs.x][Vs.y] = 1;
     path[Vs.x][Vs.y] = '@';

    int dir[][2] = {
    	{0,1},{1,0},{0,-1},{-1,0}
    };//用来表示四个方向的运动
    while(!Q.empty())//我们的停止的条件是找到终点，或者访问完所有的路径
    {
    	Vn = Q.front();//取我们的队列头
    	Q.pop();


    	for(i=0;i<4;i++)
    	{
    		Vw.x = Vn.x+dir[i][0];
    		Vw.y = Vn.y+dir[i][1];
    		if(Vw.x>=0 && Vw.y>=0)//此处是防止我们在矩阵的边缘，方向不是四个方向都可以的
    		{
    		if(Vw.x==Vd.x && Vw.y==Vd.y)//找到终点
    		{
				  count +=1;
                  path[Vw.x][Vw.y] = '@';
                 for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
            printf("%c \t",path[i][j]);
        printf("\n");

    }
    			return true;
    		}
    	//如果不是终点，且未被访问过，就加入我们的队列
    	if(maze[Vw.x][Vw.y]==0 && visit[Vw.x][Vw.y]==0){
    		Q.push(Vw);
    		visit[Vw.x][Vw.y] = 1; 
            path[Vw.x][Vw.y] = '@';
			count +=1;
    	}
    } 
    else 
    	continue;
}


}

 
return false;
}
  
//我们的读数据操作
void read() {
    FILE *fp;
    memset(maze, -1, sizeof(maze));
    if ((fp = fopen(FILE_PATH, "r")) == NULL) {
        perror(FILE_PATH);
        exit(1);
    }
    fscanf(fp, "%d %d", &m, &n);
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < n; ++ j) {
            fscanf(fp, "%d", &maze[i][j]);
        }
    }
    fclose(fp);
}

int main() {
    read();
    if (haveExit()) {

        printf("成功走出我们的迷宫！\n");
	printf("总共花的步数为：%d\n",count);
    } else {
        printf("NO\n");
    }
    return 0;
}
