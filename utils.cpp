#include <iostream>
#include <vector>
#include "utils.h"
#include <unordered_set>
#include <windows.h>

void SetColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

using namespace std;

struct Point
{
    int x, z;
    bool operator==(const Point &other) const
    {
        return x == other.x && z == other.z;
    }
};
struct graph
{
    int color;
    string line1;
    string line2;
};
struct single_line
{
    int color;
    string str;
};
// 判断两个点是否相邻（曼哈顿距离为 2）
bool areNeighbors(Point a, Point b)
{
    int y1 = -a.x - a.z;
    int y2 = -b.x - b.z;
    return (abs(a.x - b.x) + abs(y1 - y2) + abs(a.z - b.z)) == 2;
}

class Printer
{
public:
    vector<single_line> line1, line2;
    void add(graph x)
    {
        single_line a = {x.color, x.line1};
        line1.push_back(a);
        a = {x.color, x.line2};
        line2.push_back(a);
    }
    void print()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for (int x = 0; x <= line1.size()-1; x++)
        {
            if (line1[x].color==0)
            {
                SetColor(7);
            }
            else
            {
                SetColor(4);
            }
            cout << line1[x].str;
        }
        cout << endl;
        for (int x = 0; x <= line2.size()-1; x++)
        {
            if (line2[x].color == 0)
            {
                cout << "\033[0m";
            }
            else
            {
                cout << "\033[31m";
            }
            cout << line2[x].str;
        }
        cout << endl;
        line1.clear();
        line2.clear();
    }
};

class BaseChess
{
public:
    Point position;
    int layer,id;
    int color;
    BaseChess(int x,int z,int c)
    {
        color = c;
        position = {x,z};
    }
    void set(int x, int z, int c)
    {
        color = c;
        position = {x,z};
    }
    bool can_move()//vector
    {
        return false; // areConnected();
    }
    graph to_graph()
    {
        graph x{0, "x  x", "x  x"};
        return x;
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
    int minx=0, maxx=0,minz=0, maxz=0;
    void add(BaseChess i)
    {
        board.push_back(i);
        set_minmax(&minx, &maxx, &i.position.x);
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
                graph x{0, "  ", "  "};
                printer.add(x);
            }
            for (int x = minx; x <= maxx; x++)
            {
                Point a = {x,z};
                if (board[p].position==a)
                {
                    printer.add(board[p].to_graph());
                    p++;
                }
                else 
                {   if(p!=0)
                    {
                        graph x{0, "    ", "    "};
                        printer.add(x);
                    }
                       
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
    BaseChess a(0,-1,0);
    BaseChess b(-1,0,99);
    BaseChess c(-1,1,99);
    BaseChess d(0,1,99);
    BaseChess e(1,0,0);
    BaseChess f(1,-1,0);
    BaseChess g(0,0,99); 
    Chessboard x;
    x.add(a);
    x.add(f);
    x.add(b);
    x.add(g);
    x.add(e);
    x.add(c);
    x.add(d);
    x.print();
}
