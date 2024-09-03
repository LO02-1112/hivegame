#include <iostream>
#include <windows.h>
#include <memory>
#include "utils.h"
#include "chess.h"
#include "chessboard.h"
using namespace std;

void test()
{
    unique_ptr<Chess> a = make_unique<Beequeen>(1, 'a');
    unique_ptr<Chess> b = make_unique<Spider>(2, 'b');
    // unique_ptr<Chess> c = make_unique<Chess>(1, 'c');
    // unique_ptr<Chess> d = make_unique<Grasshopper>(2, 'd');
    // unique_ptr<Chess> e = make_unique<Beetle>(1, 'e');
    // unique_ptr<Chess> f = make_unique<Ant>(2, 'f');
    // unique_ptr<Chess> g = make_unique<Chess>(1, 'g');
    Chessboard x;
    x.add({0, -1},move(a));
    x.add({-1, 0}, move(b));
    x.move_chess({2, 'b'}, {-1, 1});
    // x.add({-1, 1}, move(c));
    // x.add({0, 1}, move(d));
    // x.add({1, 0}, move(e));
    // x.add({1, -1},move(f));
    // x.add({0, 0}, move(g));
    x.print();
}

int main()
{
    system("chcp 65001");
    test();
    system("pause");
    return 0;
}