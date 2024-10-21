#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <unordered_map>
#include <memory>
#include "utils.h"
#include "chess.h"
#include "printer.h"
#include <map>
#include <stack>
#include <queue>
using namespace std;
class Chess;//前向声明
// 每次添加棋子后会自动《扩展》棋盘，方便打印
class Chessboard
{
private:
    unordered_map<Point,shared_ptr<Chess>,PointHash> board; // 棋盘实现，根据坐标访问每个棋子
    unordered_map<cid, Point,cidHash> id2pnt;// 根据玩家和棋子id（键盘字母）访问坐标
    bool bfs(std::set<Point> &Allchesses) const;
    int minx=0, maxx=0,minz=0, maxz=0;    
public:
    //访问私有成员
    const unordered_map<Point, shared_ptr<Chess>, PointHash>& getBoard() const { return board; }
    const unordered_map<cid, Point, cidHash> &getId2PntMap() const { return id2pnt; }
    Point ID2Pnt(cid id) const { return id2pnt.at(id); }
    void add(Point p, shared_ptr<Chess> i);// 添加棋子：坐标，棋子
    void move_chess(cid id, Point target);//移动棋子
    std::set<Point> get_chess(int i) const;
    void print() const; // 输出棋盘
    bool isConnected(const Point& start) const;   //判断棋盘连通性    
    bool check_upper(Point p) const;
    std::set<Point> enum_mov_dest(Point p) const;
    //void remove(cid id);
};
#endif
