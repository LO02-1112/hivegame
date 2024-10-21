#ifndef CHESS_H
#define CHESS_H
#include "utils.h"
#include "chessboard.h"
#include <unordered_map>
//🦟🦗🐜🐝🪲🐞🕷️
class Chessboard;
//棋子的ID:玩家1/2，大写字母id（绑定键盘）

//棋子基类定义
class Chess
{
private:
    //Point position;
    cid id;
    string pattern;
public:
    const cid& getID() const { return id; }
    Chess(int player, char idx) : id({player, idx}),pattern("++") {}
    Chess(int player, char idx,string pattern) : id({player, idx}), pattern(pattern) {}
    graph to_graph(); // 定义棋子的图形输出
    virtual set<Point> get_dest(cid id, const Chessboard &chessboard) const;
};

//蜂王
class Beequeen:public Chess
{
public:
    Beequeen(int player, char idx) : Chess(player, idx,"🐝") {};
    set<Point> get_dest(cid id, const Chessboard &chessboard) const override;
};

//蚱蜢
class Grasshopper : public Chess
{
public:
    Grasshopper(int player, char idx) : Chess(player, idx, "🦗") {};
    set<Point> get_dest(cid id, const Chessboard &chessboard) const;
};

//蚂蚁
class Ant : public Chess
{
public:
    Ant(int player, char idx) : Chess(player, idx, "🐜") {};
    set<Point> get_dest(cid id, const Chessboard &chessboard) const;
};

//甲虫
class Beetle : public Chess
{
public:
    Beetle(int player, char idx) : Chess(player, idx, "🪲") {};
    set<Point> get_dest(cid id, const Chessboard &chessboard) const;
};

//蜘蛛
class Spider : public Chess
{
public:
    Spider(int player, char idx) : Chess(player, idx, "🕷️") {};
    set<Point> get_dest(cid id, const Chessboard &chessboard) const;
};

//蚊子
class Mosquito:public Chess
{
    public:
        Mosquito(int player, char idx) : Chess(player, idx, "🦟") {};
        set<Point> get_dest(cid id, const Chessboard &chessboard) const;
};

//瓢虫
class Ladybug : public Chess
{
public:
    Ladybug(int player, char idx) : Chess(player, idx, "🐞") {};
    set<Point> get_dest(cid id, const Chessboard &chessboard) const;
};

#endif