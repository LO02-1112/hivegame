#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

void SetConsoleColor(int textColor, int backgroundColor);

struct Point
{
    int x, z,layer;
    bool operator==(const Point &other) const;
    bool operator<(const Point &other) const;
    Point operator+(const Point &other) const;
    friend std::ostream &operator<<(ostream &os, const Point &c);
};

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
unordered_set<Point, PointHash> enum_nearby(Point p);
void set_minmax(int *min, int *max, int target);
#endif