#pragma once

class Incrementer
{
public:
    Incrementer(int start = 1) : counter(start) {}
    inline int Get() { return counter++; }
    inline int Peak() { return counter; }

private:
    int counter;
};