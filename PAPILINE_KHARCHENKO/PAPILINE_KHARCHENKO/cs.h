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

    cs();
    cs(int& id);
    ~cs();

    void edit();
    friend std::ostream& operator << (std::ostream& out, const cs& cs);
    friend std::istream& operator >> (std::istream& out, cs& cs);
    static void printHead();
};

