#ifndef SFML_FIVE_CHECK_H
#define SFML_FIVE_CHECK_H
#include "player.h"

typedef struct pos{
    int x;
    int y;
}pos;
class check {
public:
    pos translocation(location loc,vector<vector<int>>*chessmap);
    bool checkWin(vector<vector<int>>*chessmap,pos ans);
    void setPosition(Sprite *a,pos ans);
private:
    int gradeSize=13;
    int marginX=44;
    int marginY=43;
    float chessSize=67.3;
};


#endif //SFML_FIVE_CHECK_H
