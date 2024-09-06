#include "chess.h"
#include "utils.h"
#include <iostream>
#include "chessboard.h"
using namespace std;

bool Chess::can_move () {
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
    set<Point> dest,x,t,ret;
    Point ori = chessboard.id2pnt[id];
    if (!chessboard.isConnected (ori))
    {
        std::cout << "not connected"<<endl;
        return ret;
    }
    t = chessboard.enum_mov_dest(ori);
    dest = t*enum_nearby(ori);
    ret = dest;
    for (auto it = dest.begin(); it != dest.end();++it)
    {
        x = enum_nearby(*it) - t;
        if ((x - chessboard.get_chess(0)).empty())
        {
            ret.erase(*it);
        }
    }
    return dest;
}