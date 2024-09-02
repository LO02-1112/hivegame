#include <iostream>
#include <vector>
#include <map>
#include "utils.h"
#include <unordered_set>
#include <unordered_map>
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

// 打印机,add输入（结构体<颜色:int,第n行图案:str>）
class Printer 
{
public:
    vector<single_line> line1, line2, line3; //;
    void add(graph x)
    {
        single_line a;
        a= {x.color, x.line1};
        line1.push_back(a);
        a = {x.color, x.line2};
        line2.push_back(a);
        a = {x.color, x.line3};
        line3.push_back(a);
    }
    void print()
    {
        for (int x = 0; x <= line1.size()-1; x++)
        {
            if (line1[x].color == -1)
            {
                SetConsoleColor(WHITE, BLACK);
            }
            else if (line1[x].color == 1)
            {
                SetConsoleColor(RED, YELLOW);
            }
            else if (line1[x].color >=2)
            {
                SetConsoleColor(GREEN,BLUE);
            }
            cout << line1[x].str;
        }
        cout << endl;
        for (int x = 0; x <= line2.size()-1; x++)
        {
            if (line2[x].color == -1)
            {
                SetConsoleColor(WHITE, BLACK);
            }
            else if (line2[x].color == 1)
            {
                SetConsoleColor(RED, YELLOW);
            }
            else if (line2[x].color >= 2)
            {
                SetConsoleColor(GREEN, BLUE);
            }
            cout << line2[x].str;
        }
        cout << endl;
        for (int x = 0; x <= line3.size() - 1; x++)
        {
            if (line3[x].color == -1)
            {
                SetConsoleColor(WHITE, BLACK);
            }
            else if (line3[x].color == 1)
            {
                SetConsoleColor(RED, YELLOW);
            }
            else if (line3[x].color >= 2)
            {
                SetConsoleColor(GREEN, BLUE);
            }
            cout << line3[x].str;
        }
        cout << endl;
        line1.clear();
        line2.clear();
        line3.clear();
    }
};



void set_minmax(int* min,int* max,int target)
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



//每次添加棋子后会自动《扩展》棋盘，方便打印
class Chessboard
{
public:
    map<Point,BaseChess> board;//棋盘实现，根据坐标访问每个棋子
    map<cid, Point> map;     // 根据玩家和棋子id（键盘字母）访问坐标
    Printer printer;
    int minx=0, maxx=0,minz=0, maxz=0;
    
    // 添加棋子：坐标，棋子
    void add(Point p, BaseChess i) 
    {
        board.insert({p,i});
        map.insert({i.id,p});
        set_minmax(&minx, &maxx, p.x);
        set_minmax(&minz, &maxz, p.z);
        //cout << p.x << p.z << i.id.id << endl;
        //cout << minx << maxx << minz << maxz << endl;
    }
    
    void print() //输出棋盘
    {
        int p = 0;
        for (int z = minz; z <= maxz;z++)
        {   
            if (z%2!=0)
            {
                graph g = {-1, "   ", "   ", "   "}; // 奇数Z
                printer.add(g);
            }
            for (int x = minx; x <= maxx; x++)
            {
                Point a = {x,z};
                if (board.count(a)>0)
                {
                    printer.add(board.find(a)->second.to_graph());
                    //cout << x << z << board.upper_bound(a)->second.id.id<< endl;
                    p++;
                }
                else 
                {   if(p!=0)
                    {
                        graph g = {-1, "      ", "      ", "      "}; // 输出6格空气
                        printer.add(g);
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
    BaseChess a(1, 'a');
    BaseChess b(2, 'b');
    BaseChess c(1, 'c');
    BaseChess d(2, 'd');
    BaseChess e(1, 'e');
    BaseChess f(2, 'f');
    BaseChess g(1, 'g');
    Chessboard x;
    x.add({0, -1},a);
    x.add({-1, 0}, b);
    x.add({-1, 1}, c);
    x.add({0, 1}, d);
    x.add({1, 0}, e);
    x.add({1, -1}, f);
    x.add({0, 0}, g);
    x.print();
}
