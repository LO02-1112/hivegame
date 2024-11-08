#include <iostream>
#include <stdexcept> 
#include <limits>
#include "startgame.h"
#include "utils.h"
#include "chessboard.h"

using namespace std;

Chess_for_deploy::Chess_for_deploy() 
    : beequeen(1), spider(2), grasshopper(3), beetle(2), ant(3), mosquito(1), ladybug(1), id('A' - 1), queenid(0), player(0),is_ai(false) {}

bool Chess_for_deploy::queendeployed() const
{
    return beequeen == 0;
}

char Chess_for_deploy::getid() const
{
    return id+1;//返回当前最大的字母+1，便于取消操作。
}

bool Chess_for_deploy::not_lose(const Chessboard &chessboard) const
{
    if (beequeen != 0)
    {
        return true;
    }
    Point p = chessboard.ID2Pnt({player, queenid});
    auto check = enum_nearby(p);
    auto allchess = chessboard.get_chess(0);
    for (auto it = check.begin(); it != check.end(); ++it)
    {
        if (allchess.count(*it) == 0)
        {
            return true;
        }
    }
    SetInfoColor();
    chessboard.print();
    cout << "PLAYER " << player << " 的蜂王被包围了，输掉了游戏。" << endl;
    system("pause");
    system("cls");
    return false;
}


std::shared_ptr<Chess> Chess_for_deploy::deploy_chess(int step)
{
    int x;
    SetInfoColor(player);
    cout << "Player " << player << "'s Turn" << endl;
    cout << "1.beequeen:" << beequeen;
    cout << "  2.spider:" << spider;
    cout << "  3.grasshopper:" << grasshopper;
    cout << "  4.beetle:" << beetle;
    cout << "  5.ant:" << ant;
    //扩展棋子在此加入
    cout << "  6.mosquito:" <<mosquito;
    cout << "  7.ladybug:" << ladybug;
    //
    cout << endl;
    cout << "请选择棋子: ";
    if(is_ai)
    {
        x = AIinput(1, 7);
    }
    else{
        x = input(1,7);
    }    
    SetInfoColor();
    
    if (step >= 7 && beequeen != 0)
    {
        SetInfoColor(player);
        if (!is_ai)
        {
            cout << "你现在必须放置蜂王..." << endl;
            system("pause");
        }        
        SetInfoColor();
        beequeen--;
        id++;
        queenid = id;
        return move(make_shared<Beequeen>(player, id));
    }

    switch (x)
    {
    case 1:
        if (beequeen == 0)
            return nullptr;
        beequeen--;
        id++;
        queenid = id;
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
    case 6:
        if (mosquito == 0)
            return nullptr;
        mosquito--;
        id++;
        return move(make_shared<Mosquito>(player, id));
    case 7:
        if (ladybug == 0)
            return nullptr;
        ladybug--;
        id++;
        return move(make_shared<Ladybug>(player, id));
    default:
        return nullptr;
    }
}

StartGame* StartGame::self = nullptr;

StartGame& StartGame::GetInstance()
{
    if(self==nullptr)
        self = new StartGame;
    return *self;
}


int StartGame::startgame()
{    
    cout << "请选择游戏模式: 1. 双人对战  2. 玩家 vs 电脑 (AI)" << endl;
    use_ai = input(1, 2);
    if (use_ai == 1)
    {
        use_ai=0; // 双人对战模式
    }
    else 
    {
        use_ai=1; // AI对战模式
    }    
    unordered_map<char,Point> map4newchess;    
    c[1].SetAttr(1,false);
    c[2].SetAttr(2, use_ai);
    SetInfoColor(1);
    cout << "第一轮" << endl;
    int step = 3;
    int current_player = 1;
    auto p = c[1].deploy_chess(step);
    while (p==nullptr)
    {
        p = c[1].deploy_chess(step);
    }
    SetInfoColor();
    main_chessboard.add({0, 0, 0}, move(p));
    auto temp_chessboard=new Chessboard ;
    *temp_chessboard=main_chessboard;
    auto s = enum_nearby({0, 0, 0});
    char char_id='A';
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
    if(!use_ai)
    {
        enter_char = input('A', --char_id);
    }
    else{
        enter_char = AIinput('A', --char_id);
    }
    p = c[2].deploy_chess(step);
    while (p == nullptr)
    {
        p = c[2].deploy_chess(step);
    }
    SetInfoColor();
    main_chessboard.add(map4newchess.at(enter_char), p);
    map4newchess.clear();
    main_chessboard.print();
    int otherplayer;
    Point temp_point;
    cid temp_cid;
    set<Point> s1, s2, s3;
    while (c[1].not_lose(main_chessboard) && c[2].not_lose(main_chessboard)) // 2回合之后开始的循环逻辑
    {
        //FLAG://用户取消操作
        map4newchess.clear();
        system("cls");
        main_chessboard.print();
        cout << "Step: " << step << endl;
        SetInfoColor(current_player);
        cout << "现在是玩家" << current_player << "的回合" << endl;
        cout << "选项:0=弃权:1=摆放:2=移动" << endl;
        int x;
        if (!use_ai || step % 2 == 1)
        {
           x = input(0,2);
        }
        else{
            x = AIinput(1, 2);
        }        
        SetInfoColor();
        switch (x)
        {
        case 1:
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
            char_id = 'A';
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
            if (!use_ai || step % 2 == 1)
            {
                enter_char = input('A', char_id);
            }
            else
            {
                enter_char = AIinput('A', static_cast<char>(char_id-1));
            }            
            SetInfoColor();
            if (enter_char==char_id)
            {
                cout << "无效的操作，返回上一步..." << endl;
                if(!use_ai&&step%2==0)
                    system("pause");
                continue;
            }
            p = c[current_player].deploy_chess(step);
            if (p == nullptr)
            {
                cout << "无效的操作，返回上一步..." << endl;
                if (!use_ai || step % 2 == 1)
                    system("pause");
                continue;
            }
            main_chessboard.add(map4newchess.at(enter_char), move(p));
            break;
        case 2:
            SetInfoColor(current_player);
            if (!c[current_player].queendeployed())
            {
                cout << "没有放置蜂王，不允许移动棋子..." << endl;
                if (!use_ai || step % 2 == 1)
                    system("pause");
                continue;
            }
            cout << "请输入移动的棋子的字母：";            
            if (!use_ai || step % 2 == 1)
            {
                enter_char = input('A', c[current_player].getid());
            }
            else
            {
                enter_char = AIinput('A', static_cast<char>(c[current_player].getid()-1));
            }
            temp_cid = {current_player, enter_char};
            if (main_chessboard.getId2PntMap().count(temp_cid)==0)
            {
                cout << "无效的操作，返回上一步..." << endl;
                if (!use_ai || step % 2 == 1)
                    system("pause");
                continue;
            }            
            temp_point = main_chessboard.ID2Pnt(temp_cid);
            s3 = (main_chessboard.getBoard()).at(temp_point)->get_dest(temp_cid,main_chessboard);
            if (s3.empty())
            {
                cout << "棋子没有可走的目标格子，返回上一步..." << endl;
                if (!use_ai || step % 2 == 1)
                    system("pause");
                continue;
            }
            SetInfoColor();
            temp_chessboard = new Chessboard;
            *temp_chessboard = main_chessboard;
            char_id = 'A';
            for (auto it = s3.begin(); it != s3.end(); ++it)
            {
                temp_chessboard->add(*it, move(make_shared<Chess>(-1, char_id)));
                map4newchess.insert({char_id, *it});
                char_id++;
            }
            temp_chessboard->print();
            delete temp_chessboard;
            SetInfoColor(current_player);
            if (!use_ai || step % 2 == 1)
            {
                enter_char = input('A', char_id);
            }
            else
            {
                enter_char = AIinput('A', static_cast<char>(char_id-1));
            }
            SetInfoColor();
            if (enter_char == char_id)
            {
                cout << "无效的操作，返回上一步..." << endl;
                if (!use_ai || step % 2 == 1)
                    system("pause");
                continue;
            }
            main_chessboard.move_chess(temp_cid, map4newchess.at(enter_char));
            break;

        default:
            break;
        }
        switch_player(current_player);
        step++;
    }
    c[1] = Chess_for_deploy();//结束后重置棋子
    c[2] = Chess_for_deploy();
    main_chessboard=Chessboard();
    return 1;
}


void StartGame::switch_player(int &p)
{
    if (p==1)
        p = 2;
    else
        p = 1;
}