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
class Chess_for_deploy
{
private:
    int player;
    bool is_ai;
public:
    Chess_for_deploy();
    void SetAttr(int p, bool ai) { player = p; is_ai=ai;}
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