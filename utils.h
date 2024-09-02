#ifndef UTILS_H
#define UTILS_H
#include <string>
using namespace std;

struct Point
{
    int x, z,layer;
    bool operator==(const Point &other) const
    {
        return x == other.x && z == other.z && layer == other.layer;
    }
    bool operator<(const Point &other) const
    {
        if (z != other.z)
        {
            return z < other.z;
        }
        if (x!=other.x)   
        {
            return x < other.x;
        }
        return layer < other.layer;
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
void test();
#endif