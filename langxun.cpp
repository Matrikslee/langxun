#include <stdio.h>
#include <stdlib.h>

//用于读取棋盘某个位置的棋子状态。
//如果返回0，说明当前是空白的，如果返回1，说明当前是先手的棋子，如果返回2，说明是后手的棋子。
//返回其他值说明函数执行出现了异常
//int readBoard(int MAP[][21]);
//用于读取第order步的落子位置，如果order大于总的步骤数，那么返回-10，否则返回一个坐标。
//结果用指针进行传输
//int readStep(int order,int *result_x,int *result_y);
//用于输出答案
//void outputAnswer(int x,int y);

/*
具体实现如下：
*/

int readBoard(int MAP[][21]){
    FILE *fp = fopen("board.txt","r");
    if (fp == NULL) return -1;
    for (int i=1;i<=19;i++)
        for (int j=1;j<=19;j++)
            fscanf(fp,"%1d",&MAP[i][j]);
    fclose(fp);
    return 0;
}

int readStep(int *x,int *y){
    int len = 0;
    FILE *fp = fopen("steps.txt","r");
    if (fp == NULL) return -1;

    while (fscanf(fp,"%d%d",x+len,y+len)==2) len++;
    fclose(fp);
    return len;
}

void outputAnswer(int x,int y){
    printf("%d %d\n",x,y);
}
