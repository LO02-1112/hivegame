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
    int choice;
    cout << "请选择游戏模式: 1. 双人对战  2. 玩家 vs 电脑 (AI)" << endl;
    cin >> choice;
    if (choice == 1) {
        startgame();  // 双人对战模式
    } else if (choice == 2) {
        startAIgame();  // AI对战模式
    } else {
        cout << "无效选择，退出程序。" << endl;
    }
    while(startgame());
    system("pause");
    return 0;
}