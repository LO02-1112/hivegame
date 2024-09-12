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

    bool queendeployed() const;
    bool not_lose(Chessboard &chessboard) const;
    char getid() const;
    std::shared_ptr<Chess> deploy_chess(int step);

private:
    int beequeen, spider, grasshopper, beetle, ant;
    char id, queenid;

};
#endif