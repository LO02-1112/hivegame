#include <iostream>
#include <vector>
#include <set>
#include <windows.h>
#include <memory>
#include <algorithm>
#include "chess.h"
#include "color.h"
#include "utils.h"
#include "printer.h"
#include "chessboard.h"

using namespace std;

void SetConsoleColor(int textColor, int backgroundColor = BLACK) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor);
}

//修改玩家操作提示的颜色
void SetInfoColor(int player){
    switch (player)
    {
    case 1:
        SetConsoleColor(BRIGHT_YELLOW, BLACK);
        break;
    case 2:
        SetConsoleColor(BRIGHT_RED, BLACK);
        break;
    default:
        SetConsoleColor(WHITE, BLACK);
    }
}

bool Point::operator==(const Point &other) const {
    return x == other.x && z == other.z && layer == other.layer;
}

bool Point::operator<(const Point &other) const {
    if (z != other.z){
        return z < other.z;
    }
    if (x!=other.x)   {
        return x < other.x;
    }
    return layer < other.layer;
}
Point Point:: operator+(const Point &other) const{
    return {x+other.x,z+other.z,layer+other.layer};
}

std::ostream &operator<<(std::ostream &os, const Point &p)
{
    os << "x=" << p.x << "z=" << p.z << endl;
    return os;
}

// 判断两个点是否相邻（曼哈顿距离为 2）
bool areNeighbors(Point a, Point b)
{
    int y1 = -a.x - a.z;
    int y2 = -b.x - b.z;
    return (abs(a.x - b.x) + abs(y1 - y2) + abs(a.z - b.z)) == 2;
}

std::set<Point> operator-(const std::set<Point> &set1, const std::set<Point> &set2)//重载差集运算
{
    set<Point> ret;
    set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(ret, ret.begin()));
    return ret;
}

std::set<Point> operator+(const std::set<Point> &set1, const std::set<Point> &set2) // 重载并集运算
{
    set<Point> ret;
    set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(ret, ret.begin()));
    return ret;
}

std::set<Point> operator*(const std::set<Point> &set1, const std::set<Point> &set2) // 重载交集运算
{
    set<Point> ret;
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(ret, ret.begin()));
    return ret;
}

set<Point> enum_nearby(Point p)//枚举单个点
{
    set<Point> ret;
    for (const Point &direction : DIRECTIONS)
    {
        ret.insert(p + direction);        
    }
    return ret;
}

set<Point> enum_nearby(set<Point>& ps)//枚举一组点,返回和这一组点相邻的所有点（已经排除它们本身）
{
    set<Point> ret;
    for (auto it = ps.begin(); it != ps.end(); ++it)
    {
        auto x = enum_nearby(*it);
        ret=ret+x;
    }
    ret=ret-ps;//去除本身
    return ret;
}

void set_minmax(int *min, int *max, int target)
{
    if (*min > target)
    {
        *min = target;
    }
    else if (*max < target)
    {
        *max = target;
    }
}
