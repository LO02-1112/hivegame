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
    string pattern;
    BaseChess(int player, char idx) : id({player, idx}),pattern("XX") {}
    BaseChess(int player, char idx,string pattern) : id({player, idx}), pattern(pattern) {}
    bool can_move()
    {
        return false; // areConnected();
    }
    graph to_graph() // 定义棋子的图形输出
    {        
        string cha(1, id.id);
        string line13 = cha + "    " + cha;
        string line2 = "  " +pattern+ "  ";
        graph x = {id.player, line13,line2, line13}; // 1个emoji=2个字符位
        return x;
    }
};

//蜂王
class Beequeen:public BaseChess
{
public:
    Beequeen(int player, char idx) : BaseChess(player, idx,"🐝") {};
};

//蚱蜢
class Grasshopper : public BaseChess
{
public:
    Grasshopper(int player, char idx) : BaseChess(player, idx, "🦗") {};
};

//蚂蚁
class Ant : public BaseChess
{
public:
    Ant(int player, char idx) : BaseChess(player, idx, "🐜") {};
};

//甲虫
class Beetle : public BaseChess
{
public:
    Beetle(int player, char idx) : BaseChess(player, idx, "🪲") {};
};

//蜘蛛
class Spider : public BaseChess
{
public:
    Spider(int player, char idx) : BaseChess(player, idx, "🕷️") {};
};