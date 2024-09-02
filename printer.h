#ifndef PRINTER_H
#define PRINTER_H

#include <vector>
#include <string>
#include "utils.h"

using namespace std;

class Printer {
public:
    vector<single_line> line1, line2, line3;
    void add(graph x);
    void set_color(int color);
    void print();
};

#endif // PRINTER_H
