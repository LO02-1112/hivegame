#include <iostream>
#include <vector>
#include <unordered_set>
#include <windows.h>
#include <memory>
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

// 判断两个点是否相邻（曼哈顿距离为 2）
bool areNeighbors(Point a, Point b)
{
    int y1 = -a.x - a.z;
    int y2 = -b.x - b.z;
    return (abs(a.x - b.x) + abs(y1 - y2) + abs(a.z - b.z)) == 2;
}
unordered_set<Point, PointHash> enum_nearby(Point p)
{
    unordered_set<Point,PointHash> ret;
    for (int z = -1; z <= 1; z++)
    {
        for (int x = -1; x <= 1; x++)
        {
            if (x!=z)
            {
                ret.insert({p.x + x, p.z+z, p.layer});
            }
        }
    }
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

