#include <iostream>
#include <stdexcept> 
#include <limits>
#include "startgame.h"
#include "utils.h"
#include "chessboard.h"

using namespace std;

Chess_for_deploy::Chess_for_deploy() 
    : beequeen(1), spider(2), grasshopper(3), beetle(2), ant(3), mosquito(1), ladybug(1), id('A' - 1), queenid(0), player(0) {}

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
    x = input(1,7);
    SetInfoColor();
    
    if (step >= 8 && beequeen != 0)
    {
        SetInfoColor(player);
        cout << "你现在必须放置蜂王..." << endl;
        system("pause");
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
std::shared_ptr<Chess> Chess_for_deploy::AI_deploy_chess(int step)
{
    int x;
    SetInfoColor(player);
    cout << "Player " << player << "'s Turn" << endl;
    cout << "1.beequeen:" << beequeen;
    cout << "  2.spider:" << spider;
    cout << "  3.grasshopper:" << grasshopper;
    cout << "  4.beetle:" << beetle;
    cout << "  5.ant:" << ant << endl;
    cout << "请选择棋子: ";
    x = AIinputnum15(1,5);
    SetInfoColor();
    
    if (step >= 8 && beequeen != 0)
    {
        SetInfoColor(player);
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
    default:
        return nullptr;
    }
}

int startgame()
{   
    Chessboard main_chessboard;
    unordered_map<char,Point> map4newchess;
    int playcfg,step=2,current_player=1;
    Chess_for_deploy c[3];
    c[1].player = 1;
    c[2].player = 2;
    //cout << "PLAY WITH 1.HUMAN 2.AI" << endl;
    //cin >> playcfg;
    SetInfoColor(1);
    cout << "第一轮" << endl;
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
    enter_char = input('A', --char_id);
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
        int lb = 0, ub = 2;
        x = input(lb,ub);
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
            enter_char = input('A', char_id);
            SetInfoColor();
            if (enter_char==char_id)
            {
                cout << "无效的操作，返回上一步..." << endl;
                system("pause");
                continue;
            }
            p = c[current_player].deploy_chess(step);
            if (p == nullptr)
            {
                cout << "无效的操作，返回上一步..." << endl;
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
                system("pause");
                continue;
            }
            cout << "请输入移动的棋子的字母：";
            enter_char=input('A',c[current_player].getid());
            temp_cid = {current_player, enter_char};
            if (main_chessboard.getId2PntMap().count(temp_cid)==0)
            {
                cout << "无效的操作，返回上一步..." << endl;
                system("pause");
                continue;
            }            
            temp_point = main_chessboard.ID2Pnt(temp_cid);
            s3 = (main_chessboard.getBoard()).at(temp_point)->get_dest(temp_cid,main_chessboard);
            if (s3.empty())
            {
                cout << "棋子没有可走的目标格子，返回上一步..." << endl;
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
            enter_char = input('A', char_id);

            SetInfoColor();
            if (enter_char == char_id)
            {
                cout << "无效的操作，返回上一步..." << endl;
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
    return 1;
}


void switch_player(int &p)
{
    if (p==1)
        p = 2;
    else
        p = 1;
}

int aiInput(int lower, int upper) {
    // AI 生成一个随机数，模拟玩家输入
    return rand() % (upper - lower + 1) + lower;
}

char aiInput(char lower, char upper) {
    // AI 生成一个随机字母，模拟玩家输入
    return static_cast<char>(rand() % (upper - lower + 1) + lower);
}

int startAIgame()
{   
    Chessboard main_chessboard;
    unordered_map<char,Point> map4newchess;
    int playcfg,step=2,current_player=1;
    Chess_for_deploy c[3];
    c[1].player = 1;
    c[2].player = 2;
    SetInfoColor(1);
    cout << "第一轮" << endl;
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
    enter_char = AIinputchar('A', --char_id);
    p = c[2].AI_deploy_chess(step);
    while (p == nullptr)
    {
        p = c[2].AI_deploy_chess(step);
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
        int lb = 0, ub = 2;
        if(current_player==1)
        {x = input(lb,ub);}
        else{x=AIinputnum012(lb,ub);}
    
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
            if(current_player==1)
            {enter_char = input('A', char_id);}
            else{enter_char = AIinputchar('A', char_id);}
            SetInfoColor();
            if (enter_char==char_id)
            {
                if(current_player==1)
                {cout << "无效的操作，返回上一步..." << endl;
                system("pause");
                continue;}
                else{continue;}
            }
            if(current_player==1)
            {p = c[current_player].deploy_chess(step);}
            else{p = c[current_player].AI_deploy_chess(step);}
            if (p == nullptr)
            {
                if(current_player==1)
                {cout << "无效的操作，返回上一步..." << endl;
                system("pause");
                continue;}
                else{continue;}
            }
            main_chessboard.add(map4newchess.at(enter_char), move(p));
            break;
        case 2:
            SetInfoColor(current_player);
            if (!c[current_player].queendeployed())
            {
                if(current_player==1)
                {cout << "没有放置蜂王，不允许移动棋子..." << endl;
                system("pause");
                continue;}
                else{continue;}
            }
            cout << "请输入移动的棋子的字母：";
            if(current_player==1)
            {enter_char=input('A',c[current_player].getid());}
            else{enter_char=AIinputchar('A',c[current_player].getid());}
            temp_cid = {current_player, enter_char};
            if (main_chessboard.id2pnt.count(temp_cid)==0)
            {
                if(current_player==1)
                {cout << "无效的操作，返回上一步..." << endl;
                system("pause");
                continue;}
                else{continue;}
            }            
            temp_point = main_chessboard.id2pnt[temp_cid];
            s3 = main_chessboard.board[temp_point]->get_dest(temp_cid,main_chessboard);
            if (s3.empty())
            {
                if(current_player==1)
                {cout << "棋子没有可走的目标格子，返回上一步..." << endl;
                system("pause");
                continue;}
                else{continue;}
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
            if(current_player==1)
            {enter_char = input('A', char_id);}
            else{enter_char = AIinputchar('A', char_id);}

            SetInfoColor();
            if (enter_char == char_id)
            {
                if(current_player==1)
                {cout << "无效的操作，返回上一步..." << endl;
                system("pause");
                continue;}
                else{continue;}
            }
            main_chessboard.move_chess(temp_cid, map4newchess.at(enter_char));
            break;

        default:
            break;
        }
        switch_player(current_player);
        step++;
    }
    return 1;
}