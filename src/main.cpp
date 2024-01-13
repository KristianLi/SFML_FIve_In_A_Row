#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;
#include "player.h"
#include "AI.h"
#include "check.h"
#include "SFML/System/Sleep.hpp"

int gradeSize=13;
int marginX=44;
int marginY=43;
float chessSize=67.3;
sf::Texture textureBlack;
sf::Texture textureWhite;
vector<Sprite>Black;
vector<Sprite>White;
vector<vector<int>> chessMap;
bool iswin= false;
bool start= false;
int main() {
    player Player;
    AI ai;
    check Check;
    VideoMode vm(897,895);
    RenderWindow window (vm,"My_Five_In_A_Row");
    Texture texture;
    if (!texture.loadFromFile("../res/棋盘2.jpg")) {
        return -1;
    }
    Sprite spriteBlack;
    Sprite spriteWhite;
    // 加载黑色棋子的图像
    if (!textureBlack.loadFromFile("../res/black.png")) {
        return -1;
    }
    // 设置黑色棋子的纹理和大小
    spriteBlack.setTexture(textureBlack);
    spriteBlack.setScale(float(chessSize) / textureBlack.getSize().x, float(chessSize) / textureBlack.getSize().y);
    FloatRect bounds = spriteBlack.getLocalBounds();
    spriteBlack.setOrigin(bounds.width / 2, bounds.height / 2);

    // 加载白色棋子的图像
    if (!textureWhite.loadFromFile("../res/white.png")) {
        return -1;
    }
    // 设置白色棋子的纹理和大小
    spriteWhite.setTexture(textureWhite);
    spriteWhite.setScale(float(chessSize) / textureWhite.getSize().x, float(chessSize) / textureWhite.getSize().y);
    FloatRect bounds2 = spriteWhite.getLocalBounds();
    spriteWhite.setOrigin(bounds2.width / 2, bounds2.height / 2);
    // 加载并播放背景音乐
    sf::Music music;
    if (!music.openFromFile("../res/start.WAV")) {
        // 处理错误
    }
    music.play();
    for (int i = 0; i < gradeSize; ++i) {
        vector<int> temp;
        for (int j = 0; j < gradeSize; ++j) {
            temp.push_back(0);
        }
        chessMap.push_back(temp);
    }
    while(window.isOpen()){
        ai.init();

        // 清除窗口
        window.clear();

        // 绘制精灵（棋盘）
        window.draw(Sprite(texture));
        // 处理事件
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // 更新窗口内容
        window.display();
        while (1) {
            window.clear();
            location loc;
            loc=Player.go(window, &chessMap, event, &spriteBlack);
            if(loc.x==-1 and loc.y==-1){
                return 0;
            }
            pos ans;
            ans=Check.translocation(loc,&chessMap);
            if(ans.x==-1 and ans.y==-1){
                Player.Flag=true;
                continue;
            }
            Check.setPosition(&spriteBlack,ans);
            printf("%d %d\n",ans.x,ans.y);
            chessMap.at(ans.x).at(ans.y)=1;
            Black.push_back(spriteBlack);
            window.clear();
            window.draw(Sprite(texture));
            for (const auto &i: Black) {
                window.draw(i);
            }
            window.display();
            iswin=Check.checkWin(&chessMap,ans);
            if(iswin){
                Texture textureWin;
                if (!textureWin.loadFromFile("../res/胜利.jpg")) {
                    return -1;
                }
                if(music.openFromFile("../res/胜利.mp3")){
                    music.play();
                }
                Sprite spriteWin;
                spriteWin.setTexture(textureWin);
                spriteWin.setScale(float(897) / textureWin.getSize().x, float(895) / textureWin.getSize().y);
                window.clear();
                window.draw(spriteWin);
                window.display();
                while (1){
                    printf("win\n");
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed){
                            window.close();
                            return 0;
                        }
                        if(event.type==Event::MouseButtonPressed){
                            if(event.mouseButton.button==Mouse::Left){
                                start= true;
                                break;
                            }
                        }
                    }
                    if(start){
                        chessMap.clear();
                        for (int i = 0; i < gradeSize; ++i) {
                            vector<int> temp;
                            for (int j = 0; j < gradeSize; ++j) {
                                temp.push_back(0);
                            }
                            chessMap.push_back(temp);
                        }
                        Black.clear();
                        White.clear();
                        window.clear();
                        window.draw(Sprite(texture));
                        window.display();
                        Player.Flag= true;
                        break;
                    }
                }
                if(start){
                    start= false;
                    ai.init();
                    continue;
                }
            }
            ans=ai.go(&chessMap,ans,&spriteWhite);
            White.push_back(spriteWhite);
            window.clear();
            window.draw(Sprite(texture));
            for (const auto &i: Black) {
                window.draw(i);
            }
            for (auto &i: White) {
                window.draw(i);
            }
            window.display();
            iswin=Check.checkWin(&chessMap,ans);
            if(iswin){
                Texture textureWin;
                if (!textureWin.loadFromFile("../res/失败.jpg")) {
                    return -1;
                }
                if(music.openFromFile("../res/失败.mp3")){
                    music.play();
                }
                Sprite spriteWin;
                spriteWin.setTexture(textureWin);
                spriteWin.setScale(float(897) / textureWin.getSize().x, float(895) / textureWin.getSize().y);
                window.clear();
                window.draw(spriteWin);
                window.display();
                while (1){
                    printf("win\n");
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed){
                            window.close();
                            return 0;
                        }
                        if(event.type==Event::MouseButtonPressed){
                            if(event.mouseButton.button==Mouse::Left){
                                start= true;
                                break;
                            }
                        }
                    }
                    if(start){
                        chessMap.clear();
                        for (int i = 0; i < gradeSize; ++i) {
                            vector<int> temp;
                            for (int j = 0; j < gradeSize; ++j) {
                                temp.push_back(0);
                            }
                            chessMap.push_back(temp);
                        }
                        Black.clear();
                        White.clear();
                        window.clear();
                        window.draw(Sprite(texture));
                        window.display();
                        Player.Flag= true;
                        break;
                    }
                }
                if(start){
                    start= false;
                    ai.init();
                    continue;
                }
            }
            Player.Flag=true;
        }
    }
    return 0;
}
