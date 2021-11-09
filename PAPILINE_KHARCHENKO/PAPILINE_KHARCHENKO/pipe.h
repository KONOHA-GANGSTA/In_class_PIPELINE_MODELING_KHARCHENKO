#pragma once
#include <iostream>

class pipe
{
//private:
    
public:
    unsigned int id;
    double length;
    int diametr;
    bool isInRepair;
    static unsigned max_id;

    pipe();
    pipe(unsigned int id);
    ~pipe();
    void edit();
    friend std::ostream& operator << (std::ostream& out, const pipe& pipe);
    friend std::istream& operator >> (std::istream& out, pipe& pipe);
    static void printHead();
    
};