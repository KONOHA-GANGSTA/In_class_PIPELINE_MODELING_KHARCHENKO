#pragma once
#include <string>
class cs
{
public:
    unsigned int id;///
    std::string name;
    int workShopNumber;
    int activeWorkshopNumber;
    int efficiency;
    static unsigned int max_id;

    cs();
    cs(unsigned int id);
    ~cs();

    void edit();
    friend std::ostream& operator << (std::ostream& out, const cs& cs);
    friend std::istream& operator >> (std::istream& out, cs& cs);
    static void printHead();

    static bool checkName(const cs& cs, std::string name);
    static bool checkPrecent(const cs& cs, int percent);
};