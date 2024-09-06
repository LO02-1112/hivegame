#include "chess.h"
#include "utils.h"

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

unordered_map<char, Point> Beequeen::get_dest(Point origin, std::set<Point> &Allchesses)
{
    unordered_map<char,Point> x;    
    return x;
}