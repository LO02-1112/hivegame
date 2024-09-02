#include <iostream>
#include "utils.h"
#include "chess.h"
#include <windows.h>
using namespace std;
void setConsoleWindowBufferSize(short width, short height)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {width, height};
    SetConsoleScreenBufferSize(hConsole, bufferSize);
}

int main()
{
    system("chcp 65001");
    setConsoleWindowBufferSize(80, 10);
    test();
    system("pause");
    return 0;
}