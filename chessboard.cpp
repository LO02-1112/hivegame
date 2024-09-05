#include "chessboard.h"
#include "utils.h"
#include "printer.h"
#include "chess.h"
#include "utils.h"
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
        if ((i != 0 && it->first.player != i) || it->second.layer!=0)//滤除上层棋子
        {
            continue;
        }
        ret.insert(it->second);
    }
    return ret;
}

std::unordered_set<Point, PointHash> Chessboard::enum_mov_dest(Point p)//列举‘蚂蚁’全部可能到达的位置（不考虑卡位）
{
    unordered_set<Point, PointHash> x = get_chess(0);
    x.erase(p);
    unordered_set<Point, PointHash> ret=enum_nearby(x);
    return ret;
}

bool Chessboard::isConnected(const Point &start)
{ // 判断棋盘连通性
    std::unordered_set<Point, PointHash> Allchesses = get_chess(0);
    Allchesses.erase(start);
    if (bfs(start, Allchesses)) {
        return true;
    }
    return false;
}
bool Chessboard::bfs(const Point &start, std::unordered_set<Point, PointHash> &Allchesses) {
    std::queue<Point> toVisit;
    toVisit.push(start);
    std::unordered_set<Point, PointHash>visited;
    while (!toVisit.empty()) {
        Point current = toVisit.front();
        toVisit.pop();
        visited.insert(current);
        // 遍历当前棋子的邻居
        for (const Point &direction : DIRECTIONS) {
            Point neighbor = {current+direction};
            // 如果邻居在网格中，且尚未访问过
            if (Allchesses.find(neighbor) != Allchesses.end() && visited.find(neighbor) == visited.end()) {
                toVisit.push(neighbor);
            }
        }
    }
    if (visited.size() == Allchesses.size()) {
        return true;
    }
    return false;
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