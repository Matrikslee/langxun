#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <iostream>
#include <time.h>
#include "langxun.h"
#define INF 1e9
#define Depth 4///搜索深度
using namespace std;
int Color;///1代表黑,2代表白
#define _DEBUG_
#undef _DEBUG_
int Map[21][21],Copy_Map[Depth+1][21][21];///局面
int Step_x[500],Step_y[500];///历史着法
///八个方向,正上，正下，正左，正右，左上，左下，右上，右下
#define MAX_DIRNUM (8)
int dirx[MAX_DIRNUM]={-1,1,0,0,-1,1,-1,1};
int diry[MAX_DIRNUM]={0,0,-1,1,-1,-1,1,1};

struct node{
    int x,y;
    int MoveDir[8];
    int DirNum;
}Ans,Move[Depth+1][500];///最终答案和着法栈
int MoveDepth[Depth+1]={0};///指出着法栈的深度

bool check(int x,int y){
    if (x<1||x>19) return false;
    if (y<1||y>19) return false;
    return !((x>=9&&x<=11)&&(y>=9&&y<=11));
}

bool Is_Right(int x,int y,int depth,int color){
  int dirnum = 0;
  Move[depth][MoveDepth[depth]].DirNum=0;

  for(int d=0; d<MAX_DIRNUM; ++d) {
    bool flag = false;
    for (int i=x+dirx[d],j=y+diry[d]; check(i,j); i+=dirx[d], j+=diry[d]){
      if(!Map[i][j]) { break; }  // 有空子,不能下
      if(Map[i][j]==(color^3)) { // 碰到对方的子,可行
        flag =true;
        continue;
      }
      //碰到己方的子，结束
      if(flag) {
        Move[depth][MoveDepth[depth]].MoveDir[dirnum++] = d;
      }
      break;
    }
  }
  Move[depth][MoveDepth[depth]].DirNum = dirnum;
  return dirnum!=0;
}

///句柄1代表寻找可行着法并入栈，句柄2代表估值计算sum(估值表*每个落子点)
int CanMove(int depth,int color){
  MoveDepth[depth]=0;
  for(int i=1;i<=19;i++) {
    for(int j=1;j<=19;j++) {
      if(Map[i][j]==0&&check(i,j)&&Is_Right(i,j,depth,color)){
        ///找到一个起点
        Move[depth][MoveDepth[depth]].x=i;///允许的着法，入栈
        Move[depth][MoveDepth[depth]].y=j;
        MoveDepth[depth]++;
      }
    }
  }
  return MoveDepth[depth];
}

int MakeMove(int depth,int color){
  ///模拟落子
  ///赋值棋局副本
  for(int i=1;i<=19;i++)
    for(int j=1;j<=19;j++)
      Copy_Map[depth][i][j]=Map[i][j];

  //  int casenum = MoveDepth[depth]-1;
  //随机选择一个落子方案,以获得较大的速度和期望
  int casenum = rand()%MoveDepth[depth];

  int x = Move[depth][casenum].x;
  int y = Move[depth][casenum].y;
  int dirnum = Move[depth][casenum].DirNum;

  ///进行棋局变换
  for(int k=0;k<dirnum;k++){///不同方向进行翻转
    int d = Move[depth][casenum].MoveDir[k];
    while(Map[x][y]!=color) {
      Map[x][y]=color;
      x += dirx[d];
      y += diry[d];
    }
  }
  return casenum;
}

void UnMakeMove(int depth){///取消落子
  for(int i=1;i<=19;i++)
    for(int j=1;j<=19;j++)
      Map[i][j]=Copy_Map[depth][i][j];
}

int Evaluation(int color){
  const char sign[2] = {-1, 1};
  int value = 0;

  for ( int i = 1; i <= 19; ++ i ) {
    for ( int j = 1; j <= 19; ++j ) {
      if(!Map[i][j]) continue;
      value += sign[Map[i][j]==color];//*Map_value[i-1][j-1];
    }
  }

  return value;
}

int Alpha_Beta(int depth, int alpha, int beta, int color){
  ///color代表即将要行动的那方
  if(depth==0||!CanMove(depth,color))///抵达搜索深度
    return Evaluation(color^3);

  int maxval = -INF;
  ///否则，CanMove函数选择出该color所有可以下的点，通过栈返回
  while(MoveDepth[depth]) {
    int casenum = MakeMove(depth,color);///模拟落子
    int val=-Alpha_Beta(depth-1,-beta,-alpha,color^3);
    UnMakeMove(depth);
    Move[depth][casenum] = Move[depth][--MoveDepth[depth]];
    if(val>maxval) {
      maxval = val;
    }
    if(maxval > alpha) {
      alpha=maxval;
    }
    if(maxval >= beta) {
      break;
    }
  }
  return maxval;
}

void init(){///初始化
  srand(time(NULL));
  readBoard(Map);///载入地图
  int Step=readStep(Step_x,Step_y);
  Color = 1+(Step&1);
}

int main(){
#ifdef _DEBUG_
  clock_t t1, t2;
  t1 = clock();
#endif
  init();///初始化
  if(!CanMove(Depth,Color)) {
    outputAnswer(0,0);
    return 0;
  }
  int max_value=-INF;///初始化最初的局面估值
  ///否则，CanMove函数选择出该color所有可以下的点，通过栈返回
  while(MoveDepth[Depth]) {
    int casenum = MakeMove(Depth,Color);///模拟落子
    int tmp_value=Alpha_Beta(Depth-1,-INF,INF,Color^3);
    if(tmp_value>max_value) {
      Ans.x=Move[Depth][MoveDepth[Depth]-1].x;
      Ans.y=Move[Depth][MoveDepth[Depth]-1].y;
      max_value=tmp_value;
    }
    UnMakeMove(Depth);///取消落子
    Move[Depth][casenum] = Move[Depth][--MoveDepth[Depth]];
  }
  outputAnswer(Ans.x,Ans.y);
#ifdef _DEBUG_
  t2 = clock();
  FILE* fp = fopen("debug", "a");
  fprintf(fp,"spent %.3lf ms by main\n",((float)(t2 - t1) / 1000000.0F ) * 1000);
  fclose(fp);
#endif
  return 0;
}
