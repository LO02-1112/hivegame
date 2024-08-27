#include <iostream>
#include <vector>
#include "utils.h"
#include <unordered_set>
using namespace std;

struct Point
{
    int x, y, z;
    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

// 判断两个点是否相邻（曼哈顿距离为 2）
bool areNeighbors(Point a, Point b)
{
    return (abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z)) == 2;
}

class Printer
{
public:
    string line1="", line2="", line3="";
    void add(string a,string b,string c)
    {
        line1 += a;
        line2 += b;
        line3 += c;        
    }
    void print()
    {
        cout << line1 << endl;
        cout << line2 << endl;
        cout << line3 << endl;
        line1 = "";
        line2 = "";
        line3 = "";
    }
};

class BaseChess
{
public:
    Point position;
    BaseChess(int x, int y, int z)
    {
        position = {x, y, z};
    }
    void set(int x,int y,int z)
    {
        position = {x, y, z};
    }
    void set(int x, int y)
    {
        int z = -x - y;
        position = {x, y, z};
    }
    bool can_move()//vector
    {
        return false; // areConnected();
    }
};

void set_minmax(int* min,int* max,int* target)
{
    if (*min > *target)
    {
        *min = *target;
    }
    else if (*max < *target)
    {
        *max = *target;
    }
}

class Chessboard
{
public:
    vector<BaseChess> board;
    Printer printer;
    int minx=0, maxx=0, miny=0, maxy=0, minz=0, maxz=0;
    void add(BaseChess i)
    {
        board.push_back(i);
        set_minmax(&minx, &maxx, &i.position.x);
        set_minmax(&miny, &maxy, &i.position.y);
        set_minmax(&minz, &maxz, &i.position.z);
        //cout << minx << maxx << miny << maxy << minz << maxz << endl;
    }
    
    void print()
    {
        int p = 0;
        for (int z = minz; z <= maxz;z++)
        {   
            if (z%2!=0)
            {
                printer.add("   ", "   ", "   ");
            }
            for (int x = minx; x <= maxx; x++)
            {
                Point a = {x, -x - z, z};
                if (board[p].position==a)
                {
                    p++;
                    printer.add("#  #  #", "#  x  #", "#  #  #");
                }
                else
                { if(p!=0)
                    printer.add("       ", "       ", "       ");
                }
            }
            printer.print();
        }
    }
};
/*
#  #  #
#  x  #
#  #  #
*/






// // DFS 遍历连通分量
// void dfs(Point start, const vector<Point> &points, unordered_set<int> &visited)
// {
//     stack<int> toVisit;
//     toVisit.push(start);

//     while (!toVisit.empty())
//     {
//         int current = toVisit.top();
//         toVisit.pop();

//         if (visited.count(current) > 0)
//             continue;

//         visited.insert(current);

//         // 查找与当前点相邻的所有点
//         for (int i = 0; i < points.size(); i++)
//         {
//             if (visited.count(i) == 0 && areNeighbors(points[current], points[i]))
//             {
//                 toVisit.push(i);
//             }
//         }
//     }
// }

// // 判断所有点是否连在一起
// bool areConnected(const vector<Point> &points)
// {
//     if (points.empty())
//         return true;

//     unordered_set<int> visited;
//     dfs(0, points, visited);

//     // 如果所有点都被访问过，说明它们是连在一起的
//     return visited.size() == points.size();
// }
void test()
{
    BaseChess a(0, 1, -1);
    BaseChess b(0, 0, 0);
    BaseChess c(0, -1, 1);
    Chessboard x;
    x.add(a);
    x.add(b);
    x.add(c);
    x.print();
}
