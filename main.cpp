#include <stdio.h>
#include <utility>
#include <iostream>
#include "langxun.h"
#define INF 1e9
#define Depth 3///搜索深度
using namespace std;
int Color;///1代表黑,2代表白
int max_value=-INF;///初始化最初的局面估值
int Map[21][21],Copy_Map[Depth+1][21][21];///局面
int Map_value[21][21];///估值表
int Step_x[500],Step_y[500];///历史着法
int dirx[10]={-1,1,0,0,-1,1,-1,1};///八个遍历方向,正上，正下，正左，正右，左上，左下，右上，右下
int diry[10]={0,0,-1,1,-1,-1,1,1};

struct node{
    int x,y;
    int MoveDir[10];
    int DirNum;
}Ans,Move[Depth+1][500];///最终答案和着法栈
int MoveDepth[Depth+1]={0};///指出着法栈的深度

bool check(int x,int y){
    if (x<1||x>19) return false;
    if (y<1||y>19) return false;
    return !((x>=9&&x<=11)&&(y>=9&&y<=11));
}

bool Is_Right(int handle,int x,int y,int depth,int color)///句柄1代表计算出哪些方向有可翻转棋子,句柄2代表判断该点是否是可行解，1代表黑棋，2代表白棋
{
    int anti_color=color^3;///敌方颜色
    bool flag=false;
    bool flag2=false;///处理handle==1
    if(handle==1)
        Move[depth][MoveDepth[depth]].DirNum=0;

    for(int i=x-1;check(i,y);i--)///正上方
    {
        if(Map[i][y]==anti_color)///遇到敌方棋子，打开标记位
            flag=true;
        else if(Map[i][y]==color&&flag)///在终端遇到我方棋子，且中间有敌方棋子
        {
            if(handle==1)
            {
                Move[depth][MoveDepth[depth]].MoveDir[Move[depth][MoveDepth[depth]].DirNum++]=0;
                flag=false;
                flag2=true;
                break;
            }
            else
                return true;
        }
        else
            break;
    }
    flag=false;

    for(int i=x+1;check(i,y);i++)///正下方
    {
        if(Map[i][y]==anti_color)///遇到敌方棋子，打开标记位
            flag=true;
        else if(Map[i][y]==color&&flag)///在终端遇到我方棋子，且中间有敌方棋子
        {
            if(handle==1)
            {
                Move[depth][MoveDepth[depth]].MoveDir[Move[depth][MoveDepth[depth]].DirNum++]=1;
                flag=false;
                flag2=true;
                break;
            }
            else
                return true;
        }
        else
            break;
    }
    flag=false;

    for(int j=y-1;check(x,j);j--)///正左方
    {
        if(Map[x][j]==anti_color)///遇到敌方棋子，打开标记位
            flag=true;
        else if(Map[x][j]==color&&flag)///在终端遇到我方棋子，且中间有敌方棋子
        {
            if(handle==1)
            {
                Move[depth][MoveDepth[depth]].MoveDir[Move[depth][MoveDepth[depth]].DirNum++]=2;
                flag=false;
                flag2=true;
                break;
            }
            else
                return true;
        }
        else
            break;
    }
    flag=false;

    for(int j=y+1;check(x,j);j++)///正右方
    {
        if(Map[x][j]==anti_color)///遇到敌方棋子，打开标记位
            flag=true;
        else if(Map[x][j]==color&&flag)///在终端遇到我方棋子，且中间有敌方棋子
        {
            if(handle==1)
            {
                Move[depth][MoveDepth[depth]].MoveDir[Move[depth][MoveDepth[depth]].DirNum++]=3;
                flag=false;
                flag2=true;
                break;
            }
            else
                return true;
        }
        else
            break;
    }
    flag=false;

    for(int i=x-1,j=y-1;check(i,j);i--,j--)///左上方
    {
        if(Map[i][j]==anti_color)///遇到敌方棋子，打开标记位
            flag=true;
        else if(Map[i][j]==color&&flag)///在终端遇到我方棋子，且中间有敌方棋子
        {
            if(handle==1)
            {
                Move[depth][MoveDepth[depth]].MoveDir[Move[depth][MoveDepth[depth]].DirNum++]=4;
                flag=false;
                flag2=true;
                break;
            }
            else
                return true;
        }
        else
            break;
    }
    flag=false;

    for(int i=x+1,j=y-1;check(i,j);i++,j--)///左下方
    {
        if(Map[i][j]==anti_color)///遇到敌方棋子，打开标记位
            flag=true;
        else if(Map[i][j]==color&&flag)///在终端遇到我方棋子，且中间有敌方棋子
        {
            if(handle==1)
            {
                Move[depth][MoveDepth[depth]].MoveDir[Move[depth][MoveDepth[depth]].DirNum++]=5;
                flag=false;
                flag2=true;
                break;
            }
            else
                return true;
        }
        else
            break;
    }
    flag=false;

    for(int i=x-1,j=y+1;check(i,j);i--,j++)///右上方
    {
        if(Map[i][j]==anti_color)///遇到敌方棋子，打开标记位
            flag=true;
        else if(Map[i][j]==color&&flag)///在终端遇到我方棋子，且中间有敌方棋子
        {
            if(handle==1)
            {
                Move[depth][MoveDepth[depth]].MoveDir[Move[depth][MoveDepth[depth]].DirNum++]=6;
                flag=false;
                flag2=true;
                break;
            }
            else
                return true;
        }
        else
            break;
    }
    flag=false;

    for(int i=x+1,j=y+1;check(i,j);i++,j++)///右下方
    {
        if(Map[i][j]==anti_color)///遇到敌方棋子，打开标记位
            flag=true;
        else if(Map[i][j]==color&&flag)///在终端遇到我方棋子，且中间有敌方棋子
        {
            if(handle==1)
            {
                Move[depth][MoveDepth[depth]].MoveDir[Move[depth][MoveDepth[depth]].DirNum++]=7;
                flag=false;
                flag2=true;
                break;
            }
            else
                return true;
        }
        else
            break;
    }
    flag=false;

    return handle==1?flag2:false;///handle=1时，返回flag2，handle=2时均无可行解
}

int CanMove(int handle,int depth,int color){
  int eva=0, cnt=0;
  if(handle==1)MoveDepth[depth]=0;
  for(int i=1;i<=19;i++) {
    for(int j=1;j<=19;j++) {
      if(Map[i][j]==0&&check(i,j)&&Is_Right(1,i,j,depth,color)){
        if(handle==1) {
          Move[depth][MoveDepth[depth]].x=i;///允许的着法，入栈
          Move[depth][MoveDepth[depth]].y=j;
          MoveDepth[depth]++;
        } else {
          ++eva;
        }
        cnt++;
      }
    }
  }
  return handle==1?cnt:eva;
}

void MakeMove(int depth,int color){
    int anti_color=color^3;///敌方颜色
    ///赋值棋局副本
    for(int i=1;i<=19;i++)
        for(int j=1;j<=19;j++)
            Copy_Map[depth][i][j]=Map[i][j];

    int x=Move[depth][MoveDepth[depth]-1].x;
    int y=Move[depth][MoveDepth[depth]-1].y;
    int dirnum=Move[depth][MoveDepth[depth]-1].DirNum;

    ///进行棋局变换
    Map[x][y]=color;
    for(int k=0;k<dirnum;k++)///不同方向进行翻转
    {
        int xx=dirx[Move[depth][MoveDepth[depth]-1].MoveDir[k]];
        int yy=diry[Move[depth][MoveDepth[depth]-1].MoveDir[k]];
        int step=1;
        while(Map[x+xx*step][y+yy*step]==anti_color)
        {
            Map[x+xx*step][y+yy*step]=color;
            step++;
        }
    }
}

void UnMakeMove(int depth){///取消落子
  for(int i=1;i<=19;i++)
    for(int j=1;j<=19;j++)
      Map[i][j]=Copy_Map[depth][i][j];
}

int Evaluation(int color){
  int opp_color=color^3;///敌方颜色

  int obj_val = 0, opp_val = 0;

  obj_val = CanMove(2,Depth,color);
  opp_val = CanMove(2,Depth,color^3);

  return opp_val-obj_val;
}

int Alpha_Beta(int depth, int alpha, int beta, int color)///color代表即将要行动的那方
{
  if(depth==0) {//抵达搜索深度
    return Evaluation(color);
  }
  ///CanMove着法生成器，顺带将所有着法的翻转方向记录下
  if(!CanMove(1,depth,color)) {///某个玩家无法下棋
    return Evaluation(color);
  }
  int maxval = -INF;
  ///否则，CanMove函数选择出该color所有可以下的点，通过栈返回
  while(MoveDepth[depth]){
    MakeMove(depth,color);///模拟落子
    int val=-Alpha_Beta(depth-1,-beta,-alpha,color^3);
    UnMakeMove(depth);
    if(val>alpha) {
      if(val>=beta)
        return beta;
      alpha=val;
    }
    if(val>maxval)
      maxval = val;
    MoveDepth[depth]--;
  }
  return alpha;
}

void Init(){///初始化
  readBoard(Map);///载入地图
  ///载入估值表
  /*FILE *fp = fopen("Map_value.txt","r");
    if(fp==NULL) {printf("Error!");return ;}
    for (int i=1;i<=19;i++)
    for (int j=1;j<=19;j++)
    fscanf(fp,"%d",&Map_value[i][j]);
    fclose(fp);*/
  int Step=readStep(Step_x,Step_y);
  Color = Step%2+1;
}

int main(){
    Init();///初始化
    if(!CanMove(1,Depth,Color)) {
      outputAnswer(0,0);///无可行着法，判负
      return 0;
    }

    ///否则，CanMove函数选择出该color所有可以下的点，通过栈返回
    while(MoveDepth[Depth])
    {
        MakeMove(Depth,Color);///模拟落子
        int tmp_value=Alpha_Beta(Depth-1,-INF,INF,Color^3);
        if(tmp_value>max_value)
        {
            Ans.x=Move[Depth][MoveDepth[Depth]-1].x;
            Ans.y=Move[Depth][MoveDepth[Depth]-1].y;
            max_value=tmp_value;
        }
        UnMakeMove(Depth);///取消落子
        MoveDepth[Depth]--;
    }
    FILE*p = fopen("debug", "w");
    fprintf(p, "%d %d", Ans.x, Ans.y);
    fclose(p);
    outputAnswer(Ans.x,Ans.y);
    return 0;
}
