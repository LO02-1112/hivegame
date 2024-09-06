#include <windows.h>
#include <iostream>
#include "printer.h"
#include "utils.h"
#include "color.h"

void Printer::add(graph x) {
    single_line a;
    a = {x.color, x.line1};
    line1.push_back(a);
    a = {x.color, x.line2};
    line2.push_back(a);
    a = {x.color, x.line3};
    line3.push_back(a);
}

//修改玩家棋子的颜色
void Printer::set_color(int color) {
    if (color == -1) {
        SetConsoleColor(WHITE, BLACK);
    } else if (color == 1) {
        SetConsoleColor(RED, BRIGHT_YELLOW);
    } else if (color >= 2) {
        SetConsoleColor(WHITE, BRIGHT_RED);
    }
}

void Printer::print() {
    for (int x = 0; x <= line1.size() - 1; x++) {
        set_color(line1[x].color);
        cout << line1[x].str;
    }
    cout << endl;
    for (int x = 0; x <= line2.size() - 1; x++) {
        set_color(line2[x].color);
        cout << line2[x].str;
    }
    cout << endl;
    for (int x = 0; x <= line3.size() - 1; x++) {
        set_color(line3[x].color);
        cout << line3[x].str;
    }
    cout << endl;
    line1.clear();
    line2.clear();
    line3.clear();
    set_color(-1);
}
