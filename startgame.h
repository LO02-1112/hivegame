#ifndef STARTGAME_H
#define STARTGAME_H
#include <iostream>
#include <memory>
#include "chessboard.h"
#include "chess.h"
#include "utils.h"

using namespace std;


class Chess_for_deploy
{
private:
    int beequeen, spider, grasshopper, beetle, ant, mosquito, ladybug;
    char id, queenid;
    int player;
    bool is_ai;   
public:
    Chess_for_deploy();
    void SetAttr(int p, bool ai) { player = p; is_ai=ai;}
    bool queendeployed() const;
    bool not_lose(const Chessboard &chessboard) const;
    char getid() const;
    std::shared_ptr<Chess> deploy_chess(int step);
}; 

class StartGame
{
private:
    int use_ai;
    int current_player = 1;
    Chessboard main_chessboard;
    Chess_for_deploy c[3];
    void switch_player(int &p);
private:
    static StartGame *self;
    StartGame()=default;
    ~StartGame() = default;
    StartGame &operator=(const StartGame& other) = delete;
    StartGame(const StartGame &other) = delete;
public:
    static StartGame &GetInstance();
    static void Free(){delete self;}
    int startgame();
};
#endif