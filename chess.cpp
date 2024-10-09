#include "chess.h"
#include "utils.h"
#include <iostream>
#include "chessboard.h"
using namespace std;

// 我命名为扩散算法，依次枚举可到位置，蜂王把半径设为1，蜘蛛3，蚂蚁0（代表无限）
// radius表示步数。stuck表示是否考虑卡位的情况，原版的几个棋子应该设置为true
std::set<Point> diffusion(Point ori, const set<Point> &range,const set<Point> &all_chesses, int radius,bool stuck) 
{
    int round = 0;
    set<Point> previous, current, next, x, ret;
    previous.insert(ori);
    current = previous;
    while (true)
    {
        for (auto it = current.begin(); it != current.end();++it)//逐个枚举
        {
            x = (enum_nearby(*it)*range)-previous;
            for (auto it2 = x.begin(); it2 != x.end(); ++it2)
            {
                if (!stuck||!((enum_nearby(*it)*enum_nearby(*it2))-all_chesses).empty())
                {
                    next.insert(*it2);
                }
            }
        }
        next = next - current;//禁止蜘蛛通过3步移动到只需2步可以移动到的位置，是否启用此行代码取决于未确定的规则。
        round++;
        if(radius==0)
        {
            ret = ret + next;
        }
        if (radius != 0 && round == radius)
        {
            return next;
        }
        if(radius==0&&(next-previous).empty())
        {
            return ret;
        }        
        previous = current;
        current = next;        
        next.clear();
    }
}

graph Chess::to_graph(){
    string cha(1, id.id);
    string line13 = cha + "    " + cha;
    string line2 = "  " +pattern+ "  ";
    graph x = {id.player, line13,line2, line13}; // 1个emoji=2个字符位
    return x;
}

set<Point> Chess::get_dest(cid id, const Chessboard &chessboard) const
{
    set<Point> r;
    return r;
}

set<Point> Beequeen::get_dest(cid id, const Chessboard& chessboard ) const 
{
    set<Point> range, allchesses;
    Point ori = chessboard.ID2Pnt(id);
    if (chessboard.check_upper(ori))
    {
        cout << "你不能控制被压住的棋子..." << endl;
        return range;
    }
    if (!chessboard.isConnected(ori))
    {
        std::cout << "not connected" << endl;
        return range;
    }
    range = chessboard.enum_mov_dest(ori);
    allchesses = chessboard.get_chess(0);
    allchesses.erase(ori);
    return diffusion(ori, range, allchesses, 1, true);
}
set<Point> Spider::get_dest(cid id, const Chessboard &chessboard) const
{
    set<Point> range,allchesses;
    Point ori = chessboard.ID2Pnt(id);
    if (chessboard.check_upper(ori))
    {
        cout << "你不能控制被压住的棋子..." << endl;
        return range;
    }
    if (!chessboard.isConnected(ori))
    {
        std::cout << "not connected" << endl;
        return range;
    }
    range = chessboard.enum_mov_dest(ori);
    allchesses = chessboard.get_chess(0);
    allchesses.erase(ori);
    return diffusion(ori, range, allchesses, 3, true);
}
set<Point> Ant::get_dest(cid id, const Chessboard &chessboard) const
{
    set<Point> range,allchesses;
    Point ori = chessboard.ID2Pnt(id);
    if (chessboard.check_upper(ori))
    {
        cout << "你不能控制被压住的棋子..." << endl;
        return range;
    }
    if (!chessboard.isConnected(ori))
    {
        std::cout << "not connected" << endl;
        return range;
    }
    range = chessboard.enum_mov_dest(ori);
    allchesses = chessboard.get_chess(0);
    allchesses.erase(ori);
    return diffusion(ori, range, allchesses, 0, true);
}

set<Point> Grasshopper::get_dest(cid id, const Chessboard &chessboard) const
{
    set<Point> ret, allchesses;
    Point temp;
    Point ori = chessboard.ID2Pnt(id);
    if (chessboard.check_upper(ori))
    {
        cout << "你不能控制被压住的棋子..." << endl;
        return ret;
    }
    if (!chessboard.isConnected(ori))
    {
        std::cout << "not connected" << endl;
        return ret;
    }
    allchesses = chessboard.get_chess(0);
    for(const Point &direction : DIRECTIONS)
    {
        temp = ori;
        while (allchesses.count(temp)!=0)
        {
            temp = temp + direction;
        }
        ret.insert(temp);
    }
    return ret - enum_nearby(ori);
}

set<Point> Beetle::get_dest(cid id, const Chessboard &chessboard) const
{
    set<Point> ret, allchesses,range;
    Point ori = chessboard.ID2Pnt(id);
    if (chessboard.check_upper(ori))
    {
        cout << "你不能控制被压住的棋子..." << endl;
        return ret;
    }
    Point p;
    if (!chessboard.isConnected(ori))
    {
        std::cout << "not connected" << endl;
        return ret;
    }    
    ori.layer = 0;
    allchesses = chessboard.get_chess(0);
    allchesses.erase(ori);
    range = enum_nearby_all(allchesses);
    range = range * enum_nearby(ori);
    for (auto it = range.begin(); it != range.end(); ++it)
    {
        p = *it;
        while (chessboard.getBoard().count(p)>0)
        {
            p.layer++;
        }
        ret.insert(p);
    }
    return ret;
}

//根据百度百科，当在地面时模仿周围棋子的走法，但在上层时使用甲虫的走法
set<Point> Mosquito::get_dest(cid id, const Chessboard &chessboard) const
{
    set<Point> ret, allchesses, range;
    Point ori = chessboard.ID2Pnt(id);
    allchesses = chessboard.get_chess(0);
    if(ori.layer == 0)
    {        
        range = allchesses*enum_nearby(ori);
        for(auto i : range)
        {
            if (typeid(*chessboard.getBoard().at(i)) != typeid(Mosquito))
                ret = ret + chessboard.getBoard().at(i)->get_dest(id, chessboard);
        }
    }
    else
    {
        for (; ori.layer >= 0;ori.layer--)
        {
            range = range + enum_nearby(ori)*allchesses;
            range.insert(ori);
        }
        for(auto i:range)
        {
            if (typeid(*chessboard.getBoard().at(i)) == typeid(Beetle))
            {
                ret = chessboard.getBoard().at(i)->get_dest(id, chessboard);
                break;
            }                
        }        
    }
    return ret;
}

set<Point> Ladybug::get_dest(cid id, const Chessboard &chessboard) const
{
    set<Point> ret, allchesses,range;
    Point ori = chessboard.ID2Pnt(id);
    if (chessboard.check_upper(ori))
    {
        cout << "你不能控制被压住的棋子..." << endl;
        return ret;
    }
    if (!chessboard.isConnected(ori))
    {
        std::cout << "not connected" << endl;
        return ret;
    }
    allchesses = chessboard.get_chess(0);
    allchesses.erase(ori);
    range = diffusion(ori, allchesses, ret, 2, false);
    for(auto i:range)
    {
        ret = ret + (enum_nearby(i) - allchesses);
    }
    ret.erase(ori);
    return ret;
}