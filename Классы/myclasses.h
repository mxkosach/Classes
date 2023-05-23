#pragma once

class arD
{
public:
    arD(int m);
    ~arD();
    void set();
    void set(int xmin, int xmax);
    void get(int nc = -1, int nw = 4);
    int max();
    int min();
    double mean();
    void srt(bool inc = true);
private:
    int* x, nx;
};
