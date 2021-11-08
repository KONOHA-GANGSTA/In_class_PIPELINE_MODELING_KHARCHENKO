#pragma once
#include <string>
class cs
{
public:
    unsigned int id;
    std::string name;
    int workShopNumber;
    int activeWorkshopNumber;
    int efficiency;
    static unsigned int count;

    cs();
    cs(unsigned int id);
    ~cs();

    void edit();
    friend std::ostream& operator << (std::ostream& out, const cs& cs);
    friend std::istream& operator >> (std::istream& out, cs& cs);
    static void printHead();
};

