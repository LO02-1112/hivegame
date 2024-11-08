#include <iostream>
#include <windows.h>
#include <memory>
#include <algorithm>
#include "utils.h"
#include "chess.h"
#include "chessboard.h"
#include "startgame.h"
#include <ctime>

using namespace std;

int main()
{
    srand(static_cast<unsigned>(time(0)));
    system("chcp 65001");
    system("cls");
    StartGame& game = StartGame::GetInstance();
    while(game.startgame());
    StartGame::Free();
    system("pause");
    return 0;
}