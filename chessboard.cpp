#include "chessboard.h"
#include "utils.h"
#include "printer.h"
#include "chess.h"
// #include <iostream>
void Chessboard::add(Point p, shared_ptr<Chess> i) {
    id2pnt.insert({i->id,p});
    board.insert({p,move(i)});        
    set_minmax(&minx, &maxx, p.x);
    set_minmax(&minz, &maxz, p.z);    
}

void Chessboard::print() { //输出棋盘
    int p = 0;
    // std::cout <<minx<<maxx<<minz<<maxz<<std::endl;
    for (int z = minz; z <= maxz;z++)
    {
        for (int p = 0; p<z - minz;p++)
        {
            graph g = {-1, "   ", "   ", "   "}; // 输出3格空气
            printer.add(g);                    
        }
        for (int x = minx; x <= maxx; x++)
        {
            Point a;
            bool foundxz=false;
            for (int layer = 5; layer >= 0; layer--){
                a = {x, z,layer};
                if (board.count(a)>0)
                {
                    printer.add(board.find(a)->second->to_graph());
                    foundxz = true;
                    break;
                    p++;
                }
            }
            if(!foundxz){
                graph g = {-1, "      ", "      ", "      "}; // 输出6格空气
                printer.add(g); 
                }            
        }
        printer.print();
    }
}

// 根据玩家号（0=全部,1,2），枚举全部的棋子，返回集合
std::unordered_set<Point, PointHash> Chessboard::get_chess(int i)
{
    unordered_set<Point, PointHash> ret;
    for (auto it = id2pnt.begin(); it != id2pnt.end(); ++it)
    {
        if (i!=0&&it->first.player!= i)
        {
            continue;
        }
        ret.insert(it->second);
    }
    return ret;
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