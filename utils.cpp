#include <iostream>
#include <vector>
#include "utils.h"
#include <unordered_set>
using namespace std;
void test()
{
    std::cout << "shit" << std::endl;
}

struct Point
{
    int x, y, z;
};

// 判断两个点是否相邻（曼哈顿距离为 2）
bool areNeighbors(Point a, Point b)
{
    return (abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z)) == 2;
}

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
// bool arePointsConnected(const vector<Point> &points)
// {
//     if (points.empty())
//         return true;

//     unordered_set<int> visited;
//     dfs(0, points, visited);

//     // 如果所有点都被访问过，说明它们是连在一起的
//     return visited.size() == points.size();
// }