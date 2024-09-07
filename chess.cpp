#include "chess.h"
#include "utils.h"
#include <iostream>
#include "chessboard.h"
using namespace std;

std::set<Point> diffusion(Point ori, set<Point> &range, set<Point> &all_chesses, int radius) // 我命名为扩散算法，依次枚举可到位置，蜂王把半径设为1，蜘蛛3，蚂蚁0（代表无限）
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
                if (!((enum_nearby(*it)*enum_nearby(*it2))-all_chesses).empty())
                {
                    next.insert(*it2);
                }
            }
        }
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

bool Chess::can_move()
{
    return false; // areConnected();
}
graph Chess::to_graph(){
    string cha(1, id.id);
    string line13 = cha + "    " + cha;
    string line2 = "  " +pattern+ "  ";
    graph x = {id.player, line13,line2, line13}; // 1个emoji=2个字符位
    return x;
}

set<Point> Chess::get_dest(cid id, Chessboard &chessboard) const
{
    set<Point> r;
    return r;
}

set<Point> Beequeen::get_dest(cid id, Chessboard& chessboard ) const 
{
    set<Point> range, allchesses;
    Point ori = chessboard.id2pnt[id];
    range = chessboard.enum_mov_dest(ori);
    allchesses = chessboard.get_chess(0);
    allchesses.erase(ori);
    return diffusion(ori, range, allchesses, 1);
}
set<Point> Spider::get_dest(cid id, Chessboard &chessboard) const
{
    set<Point> range,allchesses;
    Point ori = chessboard.id2pnt[id];
    range = chessboard.enum_mov_dest(ori);
    allchesses = chessboard.get_chess(0);
    allchesses.erase(ori);
    return diffusion(ori, range,allchesses, 3);
}
set<Point> Ant::get_dest(cid id, Chessboard &chessboard) const
{
    set<Point> range,allchesses;
    Point ori = chessboard.id2pnt[id];
    range = chessboard.enum_mov_dest(ori);
    allchesses = chessboard.get_chess(0);
    allchesses.erase(ori);
    return diffusion(ori, range, allchesses, 0);
}