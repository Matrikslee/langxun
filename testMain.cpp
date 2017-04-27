#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>
#include "langxun.h"
using namespace std;
int MAP[21][21];
char name[3][100] = {"","teamA","teamB"};

bool checkSecure(int x,int y){
    if (x<1 || x>19) return false;
    if (y<1 || y>19) return false;
    return !((x>=9 && x<=11) && (y>=9 && y<=11));
}
set<pair<int,int> > func(int x,int y,int color){
    int i,j;
    set<pair<int,int> > result;
    for (i=x-1;checkSecure(i,y);i--){
        if (MAP[i][y] == color) break;
        if (MAP[i][y] == 0) break;
    }
    if (MAP[i][y] == color) {
        for (i = x-1;checkSecure(i,y);i--){
            if (MAP[i][y] == color) break;
            result.insert(make_pair(i,y));
        }
    }

    for (i = x+1;checkSecure(i,y);i++){
        if (MAP[i][y] == color) break;
        if (MAP[i][y] == 0) break;
    }
    if (MAP[i][y] == color) {
        for (i = x+1;checkSecure(i,y);i++){
            if (MAP[i][y] == color) break;
            result.insert(make_pair(i,y));
        }
    }

    for (i = y-1;checkSecure(x,i);i--){
        if (MAP[x][i] == color) break;
        if (MAP[x][i] == 0) break;
    }
    if (MAP[x][i] == color) {
        for (i = y-1;checkSecure(x,i);i--){
            if (MAP[x][i] == color) break;
            result.insert(make_pair(x,i));
        }
    }

    for (i = y+1;checkSecure(x,i);i++){
        if (MAP[x][i] == color) break;
        if (MAP[x][i] == 0) break;
    }
    if (MAP[x][i] == color) {
        for (i = y+1;checkSecure(x,i);i++){
            if (MAP[x][i] == color) break;
            result.insert(make_pair(x,i));
        }
    }

    for (i = x-1, j = y-1;checkSecure(i,j);i--,j--)
        if (MAP[i][j] == color || MAP[i][j] == 0) break;
    if (MAP[i][j] == color) {
        for (i = x-1, j = y-1;checkSecure(i,j);i--,j--){
            if (MAP[i][j] == color) break;
            result.insert(make_pair(i,j));
        }
    }

    for (i = x+1, j = y+1;checkSecure(i,j);i++,j++)
        if (MAP[i][j] == color || MAP[i][j] == 0) break;
    if (MAP[i][j] == color) {
        for (i = x+1, j = y+1;checkSecure(i,j);i++,j++){
            if (MAP[i][j] == color) break;
            result.insert(make_pair(i,j));
        }
    }

    for (i = x-1, j = y+1;checkSecure(i,j);i--,j++)
        if (MAP[i][j] == color || MAP[i][j] == 0) break;
    if (MAP[i][j] == color) {
        for (i = x-1, j = y+1;checkSecure(i,j);i--,j++){
            if (MAP[i][j] == color) break;
            result.insert(make_pair(i,j));
        }
    }

    for (i = x+1, j = y-1;checkSecure(i,j);i++,j--)
        if (MAP[i][j] == color || MAP[i][j] == 0) break;
    if (MAP[i][j] == color){
        for (i = x+1, j = y-1;checkSecure(i,j);i++,j--){
            if (MAP[i][j] == color) break;
            result.insert(make_pair(i,j));
        }
    }

    return result;
}
bool ifStop(int color){
    for (int i=1;i<=19;i++)
        for (int j=1;j<=19;j++){
            if (MAP[i][j]) continue;
            if (!checkSecure(i,j)) continue;
            if (func(i,j,color).size()) {
                return false;
            }
        }
    return true;
}
void writeStep(int x,int y){
    FILE *fp = fopen("steps.txt","a");
    fprintf(fp,"%d %d\n",x,y);
    fclose(fp);
}
void memsetFile(){
    FILE *fp = fopen("steps.txt","w");
    fclose(fp);
    fp = fopen("board.txt","w");
    fclose(fp);
}
void writeBoard(){
    FILE *fp = fopen("board.txt","w");
    for (int i=1;i<=19;i++){
        for (int j=1;j<=19;j++)
            fprintf(fp,"%d ",MAP[i][j]);
        fprintf(fp,"\n");
    }
    fclose(fp);
}
int main(int argc, char* argv[]){
    memsetFile();
    MAP[5][5] = MAP[6][6] = 1;
    MAP[5][6] = MAP[6][5] = 2;
    MAP[5][14] = MAP[6][15] = 1;
    MAP[5][15] = MAP[6][14] = 2;
    MAP[14][5] = MAP[15][6] = 1;
    MAP[14][6] = MAP[15][5] = 2;
    MAP[14][14] = MAP[15][15] = 1;
    MAP[14][15] = MAP[15][14] = 2;

    int nowColor = 1;
    if(argc==3) {
      strcpy(name[1], argv[1]);
      strcpy(name[2], argv[2]);
    }

    writeBoard();
    while (1){
        if (ifStop(nowColor)) break;
        int x=0,y=0;
        char command[100];
        //cºÍcpp
        sprintf(command,"./%s >ans.txt", name[nowColor]);
        //Java
        //sprintf(command,"java %s >ans.txt",name1);

        system(command);

        FILE *fp = fopen("ans.txt","r");
        fscanf(fp,"%d%d",&x,&y);
        fclose(fp);
        writeStep(x,y);

        if (MAP[x][y]) {
            printf("(%d,%d) ..%s output error 1.\n",x,y,name[nowColor]);
            break;
        }

        if (!checkSecure(x,y)) {
            printf("(%d,%d) ..%s output error 2.\n",x,y,name[nowColor]);
            break;
        }
        set<pair<int,int> > result = func(x,y,nowColor);
        if (result.size() == 0) {
            printf("(%d,%d) ..%s output error 3.\n",x,y,name[nowColor]);
            break;
        }
        else {
            for (set<pair<int,int> >::iterator iter = result.begin();iter!=result.end();iter++){
                MAP[iter->first][iter->second] = nowColor;
            }
            MAP[x][y] = nowColor;
        }

        writeBoard();

        if (nowColor == 1) nowColor =2;
        else nowColor = 1;
    }

    int color1 = 0,color2 = 0;
    for (int i=1;i<=19;i++)
        for (int j=1;j<=19;j++)
            color1+=MAP[i][j] == 1, color2+= MAP[i][j] ==2;

    printf("%s's score = %d\n",name[1],color1);
    printf("%s's score = %d\n",name[2],color2);
    if (color1>color2) printf("%s wins\n",name[1]);
    else if (color1<color2) printf("%s wins\n",name[2]);
    else printf("tie\n");
    return 0;
}
