#ifndef STARTGAME_H
#define STARTGAME_H
#include <iostream>
#include <memory>
#include "chessboard.h"
#include "chess.h"
#include "utils.h"

using namespace std;

void switch_player(int &p);

int aiInput(int lower, int upper);
char aiInput(char lower, char upper);
int startgame();
int startAIgame();
class Chess_for_deploy
{
public:
    int player;

    Chess_for_deploy();

    bool queendeployed() const;
    bool not_lose(const Chessboard &chessboard) const;
    char getid() const;
    std::shared_ptr<Chess> deploy_chess(int step);
    std::shared_ptr<Chess> AI_deploy_chess(int step);

private:
    int beequeen, spider, grasshopper, beetle, ant, mosquito, ladybug;
    char id, queenid;
};
#endif