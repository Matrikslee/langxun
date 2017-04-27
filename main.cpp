#include <stdio.h>
#include <utility>
#include <iostream>
#include "langxun.h"
#define INF 1e9
#define Depth 3///�������
using namespace std;
int Color;///1�����,2�����
int max_value=-INF;///��ʼ������ľ����ֵ
int Map[21][21],Copy_Map[Depth+1][21][21];///����
int Map_value[21][21];///��ֵ��
int Step_x[500],Step_y[500];///��ʷ�ŷ�
int dirx[10]={-1,1,0,0,-1,1,-1,1};///�˸���������,���ϣ����£��������ң����ϣ����£����ϣ�����
int diry[10]={0,0,-1,1,-1,-1,1,1};

struct node{
    int x,y;
    int MoveDir[10];
    int DirNum;
}Ans,Move[Depth+1][500];///���մ𰸺��ŷ�ջ
int MoveDepth[Depth+1]={0};///ָ���ŷ�ջ�����

bool check(int x,int y){
    if (x<1||x>19) return false;
    if (y<1||y>19) return false;
    return !((x>=9&&x<=11)&&(y>=9&&y<=11));
}

bool Is_Right(int handle,int x,int y,int depth,int color)///���1����������Щ�����пɷ�ת����,���2�����жϸõ��Ƿ��ǿ��н⣬1������壬2�������
{
    int anti_color=color^3;///�з���ɫ
    bool flag=false;
    bool flag2=false;///����handle==1
    if(handle==1)
        Move[depth][MoveDepth[depth]].DirNum=0;

    for(int i=x-1;check(i,y);i--)///���Ϸ�
    {
        if(Map[i][y]==anti_color)///�����з����ӣ��򿪱��λ
            flag=true;
        else if(Map[i][y]==color&&flag)///���ն������ҷ����ӣ����м��ез�����
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

    for(int i=x+1;check(i,y);i++)///���·�
    {
        if(Map[i][y]==anti_color)///�����з����ӣ��򿪱��λ
            flag=true;
        else if(Map[i][y]==color&&flag)///���ն������ҷ����ӣ����м��ез�����
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

    for(int j=y-1;check(x,j);j--)///����
    {
        if(Map[x][j]==anti_color)///�����з����ӣ��򿪱��λ
            flag=true;
        else if(Map[x][j]==color&&flag)///���ն������ҷ����ӣ����м��ез�����
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

    for(int j=y+1;check(x,j);j++)///���ҷ�
    {
        if(Map[x][j]==anti_color)///�����з����ӣ��򿪱��λ
            flag=true;
        else if(Map[x][j]==color&&flag)///���ն������ҷ����ӣ����м��ез�����
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

    for(int i=x-1,j=y-1;check(i,j);i--,j--)///���Ϸ�
    {
        if(Map[i][j]==anti_color)///�����з����ӣ��򿪱��λ
            flag=true;
        else if(Map[i][j]==color&&flag)///���ն������ҷ����ӣ����м��ез�����
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

    for(int i=x+1,j=y-1;check(i,j);i++,j--)///���·�
    {
        if(Map[i][j]==anti_color)///�����з����ӣ��򿪱��λ
            flag=true;
        else if(Map[i][j]==color&&flag)///���ն������ҷ����ӣ����м��ез�����
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

    for(int i=x-1,j=y+1;check(i,j);i--,j++)///���Ϸ�
    {
        if(Map[i][j]==anti_color)///�����з����ӣ��򿪱��λ
            flag=true;
        else if(Map[i][j]==color&&flag)///���ն������ҷ����ӣ����м��ез�����
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

    for(int i=x+1,j=y+1;check(i,j);i++,j++)///���·�
    {
        if(Map[i][j]==anti_color)///�����з����ӣ��򿪱��λ
            flag=true;
        else if(Map[i][j]==color&&flag)///���ն������ҷ����ӣ����м��ез�����
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

    return handle==1?flag2:false;///handle=1ʱ������flag2��handle=2ʱ���޿��н�
}

int CanMove(int handle,int depth,int color){
  int eva=0, cnt=0;
  if(handle==1)MoveDepth[depth]=0;
  for(int i=1;i<=19;i++) {
    for(int j=1;j<=19;j++) {
      if(Map[i][j]==0&&check(i,j)&&Is_Right(1,i,j,depth,color)){
        if(handle==1) {
          Move[depth][MoveDepth[depth]].x=i;///������ŷ�����ջ
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
    int anti_color=color^3;///�з���ɫ
    ///��ֵ��ָ���
    for(int i=1;i<=19;i++)
        for(int j=1;j<=19;j++)
            Copy_Map[depth][i][j]=Map[i][j];

    int x=Move[depth][MoveDepth[depth]-1].x;
    int y=Move[depth][MoveDepth[depth]-1].y;
    int dirnum=Move[depth][MoveDepth[depth]-1].DirNum;

    ///������ֱ任
    Map[x][y]=color;
    for(int k=0;k<dirnum;k++)///��ͬ������з�ת
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

void UnMakeMove(int depth){///ȡ������
  for(int i=1;i<=19;i++)
    for(int j=1;j<=19;j++)
      Map[i][j]=Copy_Map[depth][i][j];
}

int Evaluation(int color){
  int opp_color=color^3;///�з���ɫ

  int obj_val = 0, opp_val = 0;

  obj_val = CanMove(2,Depth,color);
  opp_val = CanMove(2,Depth,color^3);

  return opp_val-obj_val;
}

int Alpha_Beta(int depth, int alpha, int beta, int color)///color������Ҫ�ж����Ƿ�
{
  if(depth==0) {//�ִ��������
    return Evaluation(color);
  }
  ///CanMove�ŷ���������˳���������ŷ��ķ�ת�����¼��
  if(!CanMove(1,depth,color)) {///ĳ������޷�����
    return Evaluation(color);
  }
  int maxval = -INF;
  ///����CanMove����ѡ�����color���п����µĵ㣬ͨ��ջ����
  while(MoveDepth[depth]){
    MakeMove(depth,color);///ģ������
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

void Init(){///��ʼ��
  readBoard(Map);///�����ͼ
  ///�����ֵ��
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
    Init();///��ʼ��
    if(!CanMove(1,Depth,Color)) {
      outputAnswer(0,0);///�޿����ŷ����и�
      return 0;
    }

    ///����CanMove����ѡ�����color���п����µĵ㣬ͨ��ջ����
    while(MoveDepth[Depth])
    {
        MakeMove(Depth,Color);///ģ������
        int tmp_value=Alpha_Beta(Depth-1,-INF,INF,Color^3);
        if(tmp_value>max_value)
        {
            Ans.x=Move[Depth][MoveDepth[Depth]-1].x;
            Ans.y=Move[Depth][MoveDepth[Depth]-1].y;
            max_value=tmp_value;
        }
        UnMakeMove(Depth);///ȡ������
        MoveDepth[Depth]--;
    }
    FILE*p = fopen("debug", "w");
    fprintf(p, "%d %d", Ans.x, Ans.y);
    fclose(p);
    outputAnswer(Ans.x,Ans.y);
    return 0;
}
