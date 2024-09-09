#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <limits>
using namespace std;

void SetConsoleColor(int textColor, int backgroundColor);
void SetInfoColor(int player=0);

struct cid
{
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

struct Point
{
    int x, z,layer;
    bool operator==(const Point &other) const;
    bool operator<(const Point &other) const;
    Point operator+(const Point &other) const;
    friend std::ostream &operator<<(ostream &os, const Point &c);
};

std::set<Point> operator-(const std::set<Point> &set1, const std::set<Point> &set2);
std::set<Point> operator+(const std::set<Point> &set1, const std::set<Point> &set2);
std::set<Point> operator*(const std::set<Point> &set1, const std::set<Point> &set2);

const std::vector<Point> DIRECTIONS = {
    Point{1, -1, 0}, Point{1, 0, 0}, Point{0, 1, 0},
    Point{-1, 1, 0}, Point{-1, 0, 0}, Point{0, -1, 0}
};

struct PointHash
{
    std::size_t operator()(const Point &p) const
    {
        std::size_t hx = std::hash<int>()(p.x);
        std::size_t hz = std::hash<int>()(p.z);
        std::size_t hl = std::hash<int>()(p.layer);
        return hx ^ (hz << 1) ^ (hl << 2);
    }
};
struct graph
{
    int color;
    string line1;
    string line2;
    string line3;
};
struct single_line
{
    int color;
    string str;
};
set<Point> enum_nearby(Point p);

set<Point> enum_nearby(set<Point> &ps);

set<Point> enum_nearby_all(set<Point> &ps);

void set_minmax(int *min, int *max, int target);

template<typename T>
T input(T lb, T ub)
{
    T x;
    while (true)
    {
        cout << "请输入" << lb << "到" << ub << "之间的值：";
        cin >> x;
        if (cin.fail())
        {
            cin.clear();  // 清除输入流错误状态
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 跳过无效输入
            cout << "输入无效，请重新输入。" << endl;
            continue;  // 重新进行输入
        }

        // 检查输入是否在合法范围内
        if (x < lb || x > ub)
        {
            cout << "输入的值超出范围！" << endl;
            continue;  // 重新进行输入
        }
        return x;
    }
}
#endif