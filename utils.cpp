#include <iostream>
#include <vector>
#include <map>
#include "utils.h"
#include <unordered_set>
#include <windows.h>
#include "chess.h"
// 定义一些颜色常量
#define BLACK         0
#define BLUE          1
#define GREEN         2
#define CYAN          3
#define RED           4
#define MAGENTA       5
#define YELLOW        6
#define WHITE         7
#define GRAY          8
#define BRIGHT_BLUE   9
#define BRIGHT_GREEN  10
#define BRIGHT_CYAN   11
#define BRIGHT_RED    12
#define BRIGHT_MAGENTA 13
#define BRIGHT_YELLOW 14
#define BRIGHT_WHITE  15
void SetConsoleColor(int textColor, int backgroundColor = BLACK) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor);
}

using namespace std;

// 判断两个点是否相邻（曼哈顿距离为 2）
bool areNeighbors(Point a, Point b)
{
    int y1 = -a.x - a.z;
    int y2 = -b.x - b.z;
    return (abs(a.x - b.x) + abs(y1 - y2) + abs(a.z - b.z)) == 2;
}

// 打印机,add输入（结构体<颜色:int,第一行图案:str>）
class Printer 
{
public:
    vector<graph> line1;//, line2;
    void add(graph x)
    {
        graph a = {x.color, x.line1};
        line1.push_back(a);
        // a = {x.color, x.line2};
        // line2.push_back(a);
    }
    void print()
    {
        for (int x = 0; x <= line1.size()-1; x++)
        {
            if (line1[x].color == -1)
            {
                SetConsoleColor(WHITE, BLACK);
            }
            else if (line1[x].color == 0)
            {
                SetConsoleColor(RED, YELLOW);
            }
            else if (line1[x].color >=0)
            {
                SetConsoleColor(GREEN,BLUE);
            }
            cout << line1[x].line1;
        }
        cout << endl;
        // for (int x = 0; x <= line2.size()-1; x++)
        // {
        //     if (line2[x].color == 0)
        //     {
        //         SetConsoleColor(RED,BLACK);
        //     }
        //     else
        //     {
        //         SetConsoleColor(GREEN,BLACK);
        //     }
        //     cout << line2[x].str;
        // }
        //cout << endl;
        line1.clear();
        // line2.clear();
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


//棋盘实现，根据坐标访问每个棋子
//每次添加棋子后会自动《扩展》棋盘，方便打印
class Chessboard
{
public:
    multimap<Point,BaseChess> board;
    Printer printer;
    int minx=0, maxx=0,minz=0, maxz=0;
    void add(BaseChess i) //添加棋子
    {
        board.insert({i.position,i});
        set_minmax(&minx, &maxx, &i.position.x);
        set_minmax(&minz, &maxz, &i.position.z);
        //cout << minx << maxx << miny << maxy << minz << maxz << endl;
    }
    
    void print() //输出棋盘
    {
        int p = 0;
        for (int z = minz; z <= maxz;z++)
        {   
            if (z%2!=0)
            {
                graph x = {-1, " "};//奇数Z
                printer.add(x);
            }
            for (int x = minx; x <= maxx; x++)
            {
                Point a = {x,z};
                if (board.count(a)>0)
                {
                    printer.add(board.upper_bound(a)->second.to_graph());
                    p++;
                }
                else 
                {   if(p!=0)
                    {
                        graph x = {-1, "  "};//输出2格空气
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
