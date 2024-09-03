#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <unordered_map>
#include <memory>
#include "utils.h"
#include "chess.h"
#include "printer.h"
#include <map>
using namespace std;
//每次添加棋子后会自动《扩展》棋盘，方便打印
class Chessboard
{
public:
    unordered_map<Point,shared_ptr<Chess>,PointHash> board; // 棋盘实现，根据坐标访问每个棋子
    unordered_map<cid, Point,cidHash> id2pnt;// 根据玩家和棋子id（键盘字母）访问坐标
    Printer printer;
    int minx=0, maxx=0,minz=0, maxz=0;    
    void add(Point p, shared_ptr<Chess> i);// 添加棋子：坐标，棋子
    void move_chess(cid id, Point target);//移动棋子
    void print(); // 输出棋盘
};
#endif
