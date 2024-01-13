#ifndef SFML_FIVE_AI_H
#define SFML_FIVE_AI_H

#include <check.h>
class AI {
public:
    pos go(vector<vector<int>>*chessmap,pos ans,Sprite *a);
    void init();
    void setValuMap(pos ans,vector<vector<int>>*chessmap);
    void process(pos ans,int x,int y,vector<vector<int>>*chessmap);
private:
    int gradeSize=13;
    int marginX=44;
    int marginY=43;
    float chessSize=67.3;
    int valumap[13][13];
};


#endif //SFML_FIVE_AI_H
