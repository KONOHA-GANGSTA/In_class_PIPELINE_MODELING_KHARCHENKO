#pragma once
#include <string>
#include <set>

class cs
{
private:
    static unsigned int max_id;
    unsigned int id;

public:
    std::string name;
    int workShopNumber;
    int activeWorkshopNumber;
    int efficiency;
    std::set <int> incom;
    std::set <int> outcom;

    cs();
    ~cs();

    void edit();
    friend std::ostream& operator << (std::ostream& out, const cs& cs);
    friend std::istream& operator >> (std::istream& out, cs& cs);
    static void printHead();

    static bool checkName(const cs& cs, std::string name);
    static bool checkPrecent(const cs& cs, int percent);
    cs& create(cs& cs);
    unsigned int getId() { return id; };
};