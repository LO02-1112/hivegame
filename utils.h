#ifndef UTILS_H
#define UTILS_H
#include <string>
using namespace std;

struct Point
{
    int x, z;
    bool operator==(const Point &other) const
    {
        return x == other.x && z == other.z;
    }
    bool operator<(const Point &other) const
    {
        if (z != other.z)
            return z < other.z;
        return x < other.x;
    }
};
struct graph
{
    int color;
    string line1;
};
// struct single_line
// {
//     int color;
//     string str;
// };
void test();
#endif