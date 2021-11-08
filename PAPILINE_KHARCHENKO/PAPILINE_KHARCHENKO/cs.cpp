#include "cs.h"
#include <iostream>
#include "utils.h"
using namespace std;

cs::cs()
{
}

cs::cs(int& id)
{
    cout << "[���������� ��]" << endl;
    this->id = id;
    cout << "������� ���: ";
    getline(cin, this->name);
    cout << "������� ���������� �����: ";
    this->workShopNumber = getInt();
    cout << "������� ���������� �������� �����: ";
    this->activeWorkshopNumber = getInt();
    while (this->activeWorkshopNumber > this->workShopNumber) {
        cout << "[������� ����� �� ����� ���� ������, ��� �� �����]"
            << endl << "������� ���������� �������� �����: ";
        this->activeWorkshopNumber = getInt();
    }
    cout << "������� ���������� �������������: ";
    this->efficiency = getInt();
    cout << "[������������� ������� ���������]" << endl;
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
