#include "chessboard.h"
#include "utils.h"
#include "printer.h"
#include "chess.h"
void Chessboard::add(Point p, unique_ptr<Chess> i) {
    id2pnt.insert({i->id,p});
    board.insert({p,move(i)});        
    set_minmax(&minx, &maxx, p.x);
    set_minmax(&minz, &maxz, p.z);
}

void Chessboard::print() { //输出棋盘
    int p = 0;
    for (int z = minz; z <= maxz;z++)
    {   
        if (z%2!=0)
        {
            graph g = {-1, "   ", "   ", "   "}; // 奇数Z
            printer.add(g);
        }
        for (int x = minx; x <= maxx; x++)
        {
            Point a;
            bool foundxz=false;
            for (int layer = 5; layer >= 0; layer--){
                a = {x, z,layer};
                if (board.find(a)!=board.end())
                {
                    printer.add(board.find(a)->second->to_graph());
                    foundxz = true;
                    p++;
                    break;
                }
            }
            if(p!=0&&!foundxz){
                graph g = {-1, "      ", "      ", "      "}; // 输出6格空气
                printer.add(g);
            }
        }
        printer.print();
    }
}
void Chessboard::move_chess(cid id,Point target){
    Point origin = id2pnt[id];
    id2pnt[id] = target;
    auto it=board.find(origin);
    board.insert({target,move(it->second)});
    set_minmax(&minx, &maxx, target.x);
    set_minmax(&minz, &maxz, target.z);
    board.erase(it);
}