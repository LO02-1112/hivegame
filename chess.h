#include "utils.h"
using namespace std;
//🦟🦗🐜🐝🪲🐞🕷️

//棋子的ID:玩家1/2，小写字母id（绑定键盘）
struct cid{
    int player;
    char id;
    bool operator<(const cid &other) const
    {
        if (player != other.player)
            return player < other.player;
        return id < other.id;
    }
};
//棋子基类定义
class BaseChess
{
public:
    //Point position;
    cid id;
    string pattern="🐜";
    BaseChess(int player, char idx) : id({player, idx}) {}
    // void set(int x, int z, int c)
    // {
    //     color = c;
    //     position = {x, z};
    // }
    bool can_move() // vector
    {
        return false; // areConnected();
    }
    graph to_graph()//定义棋子的图形输出
    {        
        string cha(1, id.id);
        string a = cha + "    " + cha;
        graph x = {id.player, a, "  🐜  ", a}; // 1个emoji=2个字符位
        return x;
    }
};