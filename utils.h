#ifndef UTILS_H
#define UTILS_H
#include<string>
using namespace std;

void SetConsoleColor(int textColor, int backgroundColor);

struct Point
{
    int x, z,layer;
    bool operator==(const Point &other) const;
    bool operator<(const Point &other) const;
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
void set_minmax(int* min,int* max,int target);
#endif