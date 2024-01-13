#include "player.h"
location player::go(RenderWindow &window, vector<vector<int>> *chessmap, Event event, Sprite *spriteBlack) {
    while(Flag) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
                location loc;
                loc.x=-1;
                loc.y=-1;
                return loc;
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    location loc;
                    loc.x = event.mouseButton.x;
                    loc.y = event.mouseButton.y;
                    Flag= false;
                    return loc;
                }
            }
        }
    }
}

