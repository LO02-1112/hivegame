#include <iostream>
#include <windows.h>
#include <memory>
#include "utils.h"
#include "chess.h"
#include "chessboard.h"
using namespace std;

void test()
{
    shared_ptr<Chess> a = make_shared<Beequeen>(1, 'a');
    shared_ptr<Chess> b = make_shared<Spider>(2, 'b');
    shared_ptr<Chess> c = make_shared<Chess>(1, 'c');
    // shared_ptr<Chess> d = make_shared<Grasshopper>(2, 'd');
    // shared_ptr<Chess> e = make_shared<Beetle>(1, 'e');
    // shared_ptr<Chess> f = make_shared<Ant>(2, 'f');
    // shared_ptr<Chess> g = make_shared<Chess>(1, 'g');
    Chessboard x;
    x.add({0, -1, 0},move(a));
    x.add({-1, 0, 0}, move(b));
    // x.add({-1, 1, 0}, move(c));
    // x.add({0, 1}, move(d));
    // x.add({1, 0}, move(e));
    // x.add({1, -1},move(f));
    // x.add({0, 0}, move(g));
    x.print();
    auto x2 = x;
    auto s = enum_nearby({-1, 1,0}); 
    x2.move_chess({2, 'b'}, {-1, 1, 0});
    for (auto it = s.begin(); it!=s.end();it++)
    {
        x2.add(*it, make_shared<Chess>(-1, 's'));
        // cout << it->x << it->z << endl;
    }
    x2.print();
}

int main()
{
    system("chcp 65001");
    system("cls");
    test();
    system("pause");
    return 0;
}