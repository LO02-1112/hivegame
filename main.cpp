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

class chess_for_deploy
{
public:
    int beequeen=1, spider=2, grasshopper=3,beetle=2,ant=3,player;char id = 'a';
    shared_ptr<Chess> get_chess()
    {
        int x;        
        cout<<"PLAYER "<<player<<"'s TURN"<<endl << "Choose:";
        cout << "1.beequeen:" << beequeen << "  2.spider:" << spider << "  3.grasshopper:" << grasshopper << "  4.beetle:" << beetle << "  5.ant:" << ant << endl;
        cout << "enter: ";
        cin >> x;
        switch (x)
        {
        case 1:
            if (beequeen==0)
                return nullptr;
            beequeen--;
            return move(make_shared<Beequeen>(player, id));
        case 2:
            if (spider == 0)
                return nullptr;
            spider--;
            return move(make_shared<Spider>(player, id));
        case 3:
            if (grasshopper == 0)
                return nullptr;
            grasshopper--;
            return move(make_shared<Grasshopper>(player, id));
        case 4:
            if (beetle == 0)
                return nullptr;
            beequeen--;
            return move(make_shared<Beetle>(player, id));
        case 5:
            if (ant == 0)
                return nullptr;
            beequeen--;
            return move(make_shared<Ant>(player, id));
        default:
            return nullptr;
        }
    }
};

void switch_player(int &p)
{
    if (p==1)
        p = 2;
    else
        p = 1;
}

void mian()
{   
    Chessboard x;
    unordered_map<char,Point> cmap;
    int playcfg,current_player=1;
    chess_for_deploy c[2];
    c[0].player = 1;
    c[1].player = 2;
    //cout << "PLAY WITH 1.HUMAN 2.AI" << endl;
    //cin >> playcfg;
    cout << "FIRST ROUND" << endl;
    auto p = c[0].get_chess();
    while (p==nullptr)
    {
        p = c[0].get_chess();
    }
    x.add({0, 0, 0}, move(p));
    auto x2 = x;
    auto s = enum_nearby({0, 0, 0});
    char a='a';
    for (auto it = s.begin(); it != s.end(); it++)
    {        
        x2.add(*it, make_shared<Chess>(-1,a));
        cmap.insert({a, *it});
        a++;
    }
    x2.print();
    cout << "SECOND ROUND.PLAYER 2 "<<"ENTER POSITION: ";
    char enter;
    cin >> enter;    
    while (enter<'a' || enter>=a)
    {
        cout << "重新输入" << endl;
        cin >> enter;
    } 
    p = c[1].get_chess();
    while (p == nullptr)
    {
        p = c[1].get_chess();
    }   
    x.add(cmap[enter],p);
    x.print();
    //前2回合于此结束
    x.add({-1, 1, 0}, move(make_shared<Chess>(1, 'c')));
    cout << x.isConnected({-1,0,0});
}

int main()
{
    system("chcp 65001");
    system("cls");
    mian();
    system("pause");
    return 0;
}