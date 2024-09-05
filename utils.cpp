#include <iostream>
#include <vector>
#include <unordered_set>
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

unordered_set<Point, PointHash> enum_nearby(Point p)//枚举单个点
{
    unordered_set<Point,PointHash> ret;
    for (const Point &direction : DIRECTIONS)
    {
        ret.insert(p + direction);        
    }
    return ret;
}

unordered_set<Point, PointHash> enum_nearby(unordered_set<Point, PointHash> ps)//枚举一组点
{
    unordered_set<Point, PointHash> ret;
    for (auto it = ps.begin(); it != ps.end(); ++it)
    {
        auto x = enum_nearby(*it);
        set_union(ret.begin(), ret.end(),x.begin(), x.end(),inserter(ret, ret.begin()));        
    }
    set_difference(ret.begin(), ret.end(),ps.begin(), ps.end(),inserter(ret, ret.begin()));
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
