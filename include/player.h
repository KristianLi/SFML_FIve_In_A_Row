#ifndef SFML_FIVE_PLAYER_H
#define SFML_FIVE_PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
using namespace sf;
using namespace std;
typedef struct location {
    float x;
    float y;
}location;
class player {
public:
    bool Flag=true;
    location go(RenderWindow &window, vector<vector<int>>*chessmap, Event event,Sprite *Black);
private:
    int gradeSize=13;
    int marginX=44;
    int marginY=43;
    float chessSize=67.3;
};


#endif //SFML_FIVE_PLAYER_H
