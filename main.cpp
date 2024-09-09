#include <iostream>
#include <windows.h>
#include <memory>
#include <algorithm>
#include "utils.h"
#include "chess.h"
#include "chessboard.h"
#include "startgame.h"

using namespace std;


int main()
{
    system("chcp 65001");
    system("cls");
    while(startgame());
    system("pause");
    return 0;
}