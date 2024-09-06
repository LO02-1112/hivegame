#include <iostream>
#include <windows.h>
#include <memory>
#include <algorithm>
#include "utils.h"
#include "chess.h"
#include "chessboard.h"
using namespace std;

void input(int &x, int lb, int ub)
{
    do
    {
        cout << "请输入" << lb << "到" << ub << "之间的值：";
        cin >> x;
    } while (x < lb || x > ub);
}
void input(char &x, char lb, char ub)
{
    do
    {
        cout << "请输入" << lb << "到" << ub << "之间的值：";
        cin >> x;
    } while (x < lb || x > ub);
}

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
    auto temp_chessboard = x;
    auto s = enum_nearby({-1, 1,0}); 
    temp_chessboard.move_chess({2, 'b'}, {-1, 1, 0});
    for (auto it = s.begin(); it!=s.end();it++)
    {
        temp_chessboard.add(*it, make_shared<Chess>(-1, 's'));
        // cout << it->x << it->z << endl;
    }
    temp_chessboard.print();
}

class chess_for_deploy
{
public:
    int beequeen=1, spider=2, grasshopper=3,beetle=2,ant=3,player;char id = 'a'-1;
    shared_ptr<Chess> deploy_chess()
    {
        int x;
        SetInfoColor(player);
        cout << "Player "<<player<<"'s Turn"<<endl;
        cout << "1.beequeen:" << beequeen;
        cout << "  2.spider:"<< spider;
        cout << "  3.grasshopper:" << grasshopper;
        cout << "  4.beetle:" << beetle;
        cout << "  5.ant:" << ant << endl;
        cout << "请选择棋子: ";
        SetInfoColor();
        cin>>x;
        switch (x)
        {
        case 1:
            if (beequeen==0)
                return nullptr;
            beequeen--;
            id++;
            return move(make_shared<Beequeen>(player, id));
        case 2:
            if (spider == 0)
                return nullptr;
            spider--;
            id++;
            return move(make_shared<Spider>(player, id));
        case 3:
            if (grasshopper == 0)
                return nullptr;
            grasshopper--;
            id++;
            return move(make_shared<Grasshopper>(player, id));
        case 4:
            if (beetle == 0)
                return nullptr;
            beetle--;
            id++;
            return move(make_shared<Beetle>(player, id));
        case 5:
            if (ant == 0)
                return nullptr;
            ant--;
            id++;
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


int mian()
{   
    Chessboard main_chessboard;
    unordered_map<char,Point> map4newchess;
    int playcfg,round=2,current_player=1;
    chess_for_deploy c[3];
    c[1].player = 1;
    c[2].player = 2;
    //cout << "PLAY WITH 1.HUMAN 2.AI" << endl;
    //cin >> playcfg;
    SetInfoColor(1);
    cout << "第一轮" << endl;
    auto p = c[1].deploy_chess();
    while (p==nullptr)
    {
        p = c[1].deploy_chess();
    }
    SetInfoColor();
    main_chessboard.add({0, 0, 0}, move(p));
    auto temp_chessboard=new Chessboard ;
    *temp_chessboard=main_chessboard;
    auto s = enum_nearby({0, 0, 0});
    char char_id='a';
    for (auto it = s.begin(); it != s.end(); it++)
    {
        temp_chessboard->add(*it, make_shared<Chess>(-1, char_id));
        map4newchess.insert({char_id, *it});
        char_id++;
    }
    temp_chessboard->print();
    SetInfoColor(2);
    cout << "第二轮 玩家2 请选择摆放棋子的位置: ";
    delete temp_chessboard;
    char enter_char;
    input(enter_char, 'a', char_id);
    p = c[2].deploy_chess();
    while (p == nullptr)
    {
        p = c[2].deploy_chess();
    }
    SetInfoColor();
    main_chessboard.add(map4newchess[enter_char], p);
    map4newchess.clear();
    main_chessboard.print();
    //前2回合于此结束
    /*
    //测试bfs
    x.add({0, 1, 0}, move(make_shared<Chess>(1, 'c')));
    cout << x.isConnected({-1,1,0})<<endl;
    x.print();*/
    int otherplayer;
    set<Point> s1, s2, s3;
    while(1)//2回合之后开始的循环逻辑
    {
        //FLAG://用户取消操作
        map4newchess.clear();
        system("cls");
        main_chessboard.print();
        SetInfoColor(current_player);
        cout << "现在是玩家" << current_player << "的回合" << endl;
        cout << "选项：0=弃权，1=摆放，2=移动" << endl;
        input(enter_char, '0', '2');
        SetInfoColor();
        switch (enter_char)
        {
        case '1':
            s3.clear();
            s1 = main_chessboard.get_chess(current_player);
            s1 = enum_nearby(s1);
            if(current_player==1)
            {
                otherplayer = 2;
            } 
            else{
                otherplayer = 1;
            }
            s2 = main_chessboard.get_chess(otherplayer);
            s1 = s1 - s2;
            s2 = enum_nearby(s2);
            s3 = s1 - s2;
            temp_chessboard = new Chessboard;
            *temp_chessboard = main_chessboard;
            char_id = 'a';
            for (auto it = s3.begin(); it != s3.end();++it)
            {
                temp_chessboard->add(*it, move(make_shared<Chess>(-1, char_id)));
                map4newchess.insert({char_id, *it});
                char_id++;                
            }
            s3.clear();
            system("cls");
            temp_chessboard->print();
            delete temp_chessboard;
            SetInfoColor(current_player);
            input(enter_char,'a',char_id);
            SetInfoColor();
            if (enter_char==char_id)
            {
                cout << "无效的操作，返回上一步..." << endl;
                system("pause");
                continue;
            }
            p = c[current_player].deploy_chess();
            if (p == nullptr)
            {
                cout << "无效的操作，返回上一步..." << endl;
                system("pause");
                continue;
            }
            main_chessboard.add(map4newchess[enter_char],move(p));
            break;
        
        default:
            break;
        }
        switch_player(current_player);
        round++;
    }
    return 1;
}

int main()
{
    system("chcp 65001");
    system("cls");
    while(mian());
    system("pause");
    return 0;
}