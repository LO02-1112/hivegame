#ifndef CHESS_H
#define CHESS_H
#include "utils.h"
#include <unordered_map>
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
    bool operator==(const cid &other) const
    {
        return player == other.player && id == other.id;
    }
};
struct cidHash
{
    std::size_t operator()(const cid &p) const
    {
        return std::hash<int>()(p.player) ^ (std::hash<int>()(p.id) << 1);
    }
};
//棋子基类定义
class Chess
{
public:
    //Point position;
    cid id;
    string pattern;
    Chess(int player, char idx) : id({player, idx}),pattern("++") {}
    Chess(int player, char idx,string pattern) : id({player, idx}), pattern(pattern) {}
    bool can_move();
    graph to_graph(); // 定义棋子的图形输出

};

//蜂王
class Beequeen:public Chess
{
public:
    Beequeen(int player, char idx) : Chess(player, idx,"🐝") {};
    unordered_map<char, Point> get_dest(Point origin, std::unordered_set<Point, PointHash> &Allchesses);
};

//蚱蜢
class Grasshopper : public Chess
{
public:
    Grasshopper(int player, char idx) : Chess(player, idx, "🦗") {};
};

//蚂蚁
class Ant : public Chess
{
public:
    Ant(int player, char idx) : Chess(player, idx, "🐜") {};
};

//甲虫
class Beetle : public Chess
{
public:
    Beetle(int player, char idx) : Chess(player, idx, "🪲") {};
};

//蜘蛛
class Spider : public Chess
{
public:
    Spider(int player, char idx) : Chess(player, idx, "🕷️") {};
};

// class EmptyChess:public Chess
// {
// public:
//     EmptyChess(char idx) : Chess(0, idx) {};
// };
#endif