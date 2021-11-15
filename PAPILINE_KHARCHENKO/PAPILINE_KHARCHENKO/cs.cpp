#include "cs.h"
#include <iostream>
#include "utils.h"
using namespace std;

unsigned int cs::max_id = 0;

cs::cs():id(++cs::max_id)
{
}

cs::~cs()
{
}

void cs::edit()
{
        cout << "[�������������� ������������� �������]" << endl
            << "�� � id " << this->id << " (" << this->name << ")" << endl;
        do {
            cout << "������� ���������� �������� �����: ";
            this->activeWorkshopNumber = getInt();
        } while (this->activeWorkshopNumber > this->workShopNumber);
        cout << "������� ������ �������������: ";
        this->efficiency = getInt();
        cout << "[��������� �������]" << endl;
}

void cs::printHead()
{
    printLine();
    cout << "|\tId"
        << "\t|\t���"
        << "\t|\t����"
        << "\t|\t���� � ������"
        << "\t|\t�������������"
        << "\t|" << endl;

}

bool cs::checkName(const cs& cs, string name)
{
    return cs.name.find(name)!=string::npos;
}

bool cs::checkPrecent(const cs& cs, int percent)
{
    return round(((double)(cs.workShopNumber-cs.activeWorkshopNumber)/cs.workShopNumber)*100) == percent;
}

cs& cs::create(cs& cs)
{
    cout << "[���������� ��]" << endl;
    cout << "������� ���: ";
    getline(cin, cs.name);
    cout << "������� ���������� �����: ";
    cs.workShopNumber = getInt();
    cout << "������� ���������� �������� �����: ";
    cs.activeWorkshopNumber = getInt();
    while (cs.activeWorkshopNumber > cs.workShopNumber) {
        cout << "[������� ����� �� ����� ���� ������, ��� �� �����]"
            << endl << "������� ���������� �������� �����: ";
        cs.activeWorkshopNumber = getInt();
    }
    cout << "������� ���������� �������������: ";
    cs.efficiency = getInt();
    cout << "[������������� ������� ���������]" << endl;
    return cs;
}

std::ostream& operator<<(std::ostream& out, const cs& cs)
{
     out << "|\t" << cs.id
        << "\t|\t" << cs.name
        << "\t|\t" << cs.workShopNumber
        << "\t|\t" << cs.activeWorkshopNumber
        << "\t\t|\t" << cs.efficiency
        << "\t\t|" << endl;
    return out;
}

std::istream& operator>>(std::istream& out, cs& cs)
{
    string value;
    getline(out, value);
    cs.id = stoi(getOneParam(value));
    cs.name = getOneParam(value);
    cs.workShopNumber = stoi(getOneParam(value));
    cs.activeWorkshopNumber = stoi(getOneParam(value));
    cs.efficiency = stoi(getOneParam(value));
    return out;
}
