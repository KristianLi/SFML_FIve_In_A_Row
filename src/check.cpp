//
// Created by KenLee on 2024/1/13.
//

#include "check.h"

pos check::translocation(location loc, vector<vector<int>> *chessmap) {
    int x,y;
    pos ans;
    x=(loc.x-marginX)/chessSize;
    y=(loc.y-marginY)/chessSize;
    int leftTopx=marginX+x*chessSize;
    int leftTopy=marginY+y*chessSize;
    int rightBottomx=marginX+(x+1)*chessSize;
    int rightBottomy=marginY+(y+1)*chessSize;
    int left,right,up,down;
    left=loc.x-leftTopx;
    right=rightBottomx-loc.x;
    up=loc.y-leftTopy;
    down=rightBottomy-loc.y;
    if(left<right){
        ans.x=x;
        if(up<down){
            ans.y=y;
        } else ans.y=y+1;
    } else{
        ans.x=x+1;
        if(up<down){
            ans.y=y;
        } else ans.y=y+1;
    }
    if(chessmap->at(ans.x).at(ans.y)!=0){
        ans.x=-1;
        ans.y=-1;
        return ans;
    }
    chessmap->at(ans.x).at(ans.y)=1;
    return ans;
}

void check::setPosition(Sprite *a, pos ans) {
    float x,y;
    x=ans.x*chessSize+marginX;
    y=ans.y*chessSize+marginY;
    a->setPosition(x,y);
    return;
}

bool check::checkWin(vector<vector<int>> *chessmap,pos ans) {
    int x=ans.x;
    int y=ans.y;
    int i=chessmap->at(x).at(y);
    int count=0;
    while(chessmap->at(x).at(y)==i){
        count++;
        y++;
        if(y>=13)break;
    }
    y=ans.y-1;
    while(chessmap->at(x).at(y)==i){
        count++;
        y--;
        if(y<0)break;
    }
    if(count>=5)return true;
    count=0;
    y=ans.y;
    while(chessmap->at(x).at(y)==i){
        count++;
        x++;
        if(x>=13)break;
    }
    x=ans.x-1;
    while(chessmap->at(x).at(y)==i){
        count++;
        x--;
        if(x<0)break;
    }
    if(count>=5)return true;
    count=0;
    x=ans.x;
    while(chessmap->at(x).at(y)==i){
        count++;
        x++;
        y++;
        if(x>=13 or y>=13)break;
    }
    x=ans.x-1;
    y=ans.y-1;
    while(chessmap->at(x).at(y)==i){
        count++;
        x--;
        y--;
        if(x<0 or y<0)break;
    }
    if(count>=5)return true;
    count=0;
    x=ans.x;
    y=ans.y;
    while(chessmap->at(x).at(y)==i){
        count++;
        x++;
        y--;
        if(x>=13 or y<0)break;
    }
    x=ans.x-1;
    y=ans.y+1;
    while(chessmap->at(x).at(y)==i){
        count++;
        x--;
        y++;
        if(x<0 or y>=13)break;

    }
    if(count>=5)return true;
    return false;

}
