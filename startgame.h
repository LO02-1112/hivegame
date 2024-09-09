#ifndef STARTGAME_H
#define STARTGAME_H
#include <iostream>
#include <memory>
#include "chessboard.h"
#include "chess.h"
#include "utils.h"

using namespace std;

void switch_player(int &p);


int startgame();

class Chess_for_deploy
{
public:
    int player;

    Chess_for_deploy();

    bool queendeployed();
    bool not_lose(Chessboard& chessboard);
    char getid() const;
    std::shared_ptr<Chess> deploy_chess(int step);

private:
    int beequeen, spider, grasshopper, beetle, ant;
    char id, queenid;

};
#endif