#include "AI.h"

pos AI::go(vector<vector<int>> *chessmap,pos ans,Sprite *a) {
    valumap[ans.x][ans.y]=-1;
    setValuMap(ans,chessmap);
    pos max;
    max.x=0;
    max.y=0;
    for (int i = 0; i < gradeSize; ++i) {
        for (int j = 0; j < gradeSize; ++j) {
            if(valumap[i][j]>valumap[max.x][max.y]){
                max.x=i;
                max.y=j;
            }
        }
    }
    chessmap->at(max.x).at(max.y)=-1;
    valumap[max.x][max.y]=-1;
    setValuMap(max,chessmap);
    location loc;
    loc.x=max.x*chessSize+marginX;
    loc.y=max.y*chessSize+marginY;
    a->setPosition(loc.x,loc.y);
    printf("White:%d %d\n",max.x,max.y);
    return max;
}

void AI::init() {
    memset(valumap,0,sizeof(valumap));
}

void AI::setValuMap(pos ans,vector<vector<int>> *chessmap) {
    int x=ans.x;
    int y=ans.y;
    x--;
    y--;
    if(x>=0) {
        if (y >= 0) {
            process(ans, -1, -1, chessmap);
        } else if (ans.y + 1 <= 13 and ans.x+1<=13)process(ans, 1, 1, chessmap);
    }else if(ans.x+1<=13 and ans.y+1<=13)process(ans,1,1,chessmap);
    y++;
    if(y<=13){
        if(x>=0)process(ans,-1,0,chessmap);
        else if(ans.x+1<=13)process(ans,1,0,chessmap);
    }
    y++;
    if(y<=13){
        if(x>=0)process(ans,-1,1,chessmap);
        else if(ans.x+1<=13 and ans.y-1 >=0)process(ans,1,-1,chessmap);
    }else if(ans.x+1<=13 and ans.y-1>=0)process(ans,1,-1,chessmap);
    x++;
    if(x<=13){
        if(y<13)process(ans,0,1,chessmap);
        else if(ans.y-1>=0)process(ans,0,-1,chessmap);
    }
    return;

}

void AI::process(pos ans, int x, int y,vector<vector<int>> *chessmap) {
    bool startflag= true,endflag= true;
    pos start,end;
    int x1=ans.x;
    int y1=ans.y;
    int count=0;
    int i=chessmap->at(x1).at(y1);
    while(chessmap->at(x1).at(y1)==i){
        count++;
        x1+=x;
        y1+=y;
        if(x1<0 or y1<0 or x1>=13 or y1>=13)break;
    }
    if(x1>=0 and x1<13 and y1>=0 and y1<13 and chessmap->at(x1).at(y1)==0){
        start.x=x1;
        start.y=y1;
    }else startflag= false;
    x1=ans.x-x;
    y1=ans.y-y;
    if(x1>=0 and y1>=0 and x1<13 and y1<13){
        while(chessmap->at(x1).at(y1)==i){
            count++;
            x1-=x;
            y1-=y;
            if(x1<0 or y1<0 or x1>=13 or y1>=13)break;
        }
        if (x1>=0 and x1<13 and y1>=0 and y1<13 and chessmap->at(x1).at(y1)==0){
            end.x=x1;
            end.y=y1;
        }else endflag= false;
    }else endflag= false;
    if(startflag== false and endflag== false)return;
    else if(startflag== true and endflag== false){
        switch (count) {
            case 1:
                valumap[start.x][start.y]+=5;
                break;
            case 2:
                valumap[start.x][start.y]+=50;
                break;
            case 3:
                valumap[start.x][start.y]+=500;
                break;
            case 4:
                valumap[start.x][start.y]=10000;
                break;
            default:
                break;
        }
    }
    else if(startflag== false and endflag== true) {
        switch (count) {
            case 1:
                valumap[end.x][end.y] += 5;
                break;
            case 2:
                valumap[end.x][end.y] += 50;
                break;
            case 3:
                valumap[end.x][end.y] += 500;
                break;
            case 4:
                valumap[end.x][end.y] = 10000;
                break;
            default:
                break;
        }
    }
    else{
        switch (count) {
            case 1:
                valumap[start.x][start.y] += 10;
                valumap[end.x][end.y] += 10;
                break;
            case 2:
                valumap[start.x][start.y] += 100;
                valumap[end.x][end.y] += 100;
                break;
            case 3:
                valumap[start.x][start.y] += 1000;
                valumap[end.x][end.y] += 1000;
                break;
            case 4:
                valumap[start.x][start.y] = 10000;
                valumap[end.x][end.y] = 10000;
                break;
            default:
                break;
        }
    }
    return;
}
