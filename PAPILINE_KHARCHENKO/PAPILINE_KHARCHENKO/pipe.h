#pragma once
#include <iostream>
#include <unordered_map>

class pipe
{
private:
    static unsigned int max_id;
    unsigned int id;

public:
    double length;
    int diametr;
    bool isInRepair;

    pipe();
    ~pipe();
    void edit(int id);
    friend std::ostream& operator << (std::ostream& out, const pipe& pipe);
    friend std::istream& operator >> (std::istream& out, pipe& pipe);
    static void printHead();
    static bool checkCondition(const pipe& pipe, bool condition);
    static bool checkDiam(const pipe& pipe, int diam);
    pipe& create(pipe& pipe);
    unsigned int getId() { return id; };
 
};