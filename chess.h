#include "utils.h"
using namespace std;

//棋子基类定义
class BaseChess
{
public:
    Point position;
    int layer, id;
    int color;
    BaseChess(int x, int z, int c)
    {
        color = c;//日后作为占位棋，color应设为白色
        position = {x, z};
    }
    void set(int x, int z, int c)
    {
        color = c;
        position = {x, z};
    }
    bool can_move() // vector
    {
        return false; // areConnected();
    }
    graph to_graph()//定义棋子的图形输出
    {
        graph x = {color, "🐜"};//1个emoji=2个字符位
        return x;
    }
};