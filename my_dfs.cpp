#include<iostream>
#include<windows.h>

#define Maxsize 100
using namespace std;

void generate_maze(int maze[][8],int n)
{
    //初始化迷宫,暂时使用硬编码,暂时不处理

}

void printMaze(int maze[][8],int n)
{
      for(int i=0;i<n;i++)
      {
        for(int j=0;j<8;j++)
        {
            cout<<maze[i][j];
        }
        cout<<endl;
      }

}


//深度搜索，寻找路径
bool dfs(int x,int y,int maze[][8])
{
   int row = 8;
   int column = 8;
   if(x<0||x>=row||y<0||y>=column)//防止越界
   {
      return false;
   }
   if(maze[x][y]==1)
   {
    return false;
   }


}

int main()
{
    int maze[8][8]=
    {
        0,0,1,1,1,1,1,1,
        1,0,0,0,0,0,1,1,
        1,1,0,1,1,0,0,1,
        1,1,0,1,0,0,1,1,
        1,1,0,1,0,1,1,1,
        1,1,1,1,0,0,0,1,
        1,1,1,1,0,1,0,1,
        1,1,1,1,0,1,0,1
    };
    generate_maze(maze,8);
    printMaze(maze,8);
}