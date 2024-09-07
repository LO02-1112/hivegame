#include "chess.h"
#include "utils.h"
#include <iostream>
#include "chessboard.h"
using namespace std;

std::set<Point> diffusion(Point ori,set<Point>& range,int radius)//我命名为扩散算法，依次枚举可到位置，蜂王把半径设为1，蜘蛛3，蚂蚁0（代表无限）
{
    int round = 0;
    set<Point> previous, current, next, x, ret;
    previous.insert(ori);
    current = previous;
    while (true)
    {
        next = range * enum_nearby(current);
        next=next-previous;
        ret = ret + next;
        for (auto it = next.begin(); it != next.end(); ++it)
        {
            x = enum_nearby(*it) - range;
            if ((x - range).empty())
            {
                next.erase(it);
                ret.erase(*it);
            }            
        }
        previous = current;
        current = next;
        
        round++;
        if(radius!=0&&round==radius)
        {
            return ret;
        }
        if(radius==0&&(next*range).empty())
        {
            return ret;
        }
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
    set<Point> range;
    Point ori = chessboard.id2pnt[id]; 
    range = chessboard.enum_mov_dest(ori);
    return diffusion(ori, range, 1);
}