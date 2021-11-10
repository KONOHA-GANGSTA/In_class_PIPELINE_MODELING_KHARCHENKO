#include "cs.h"
#include <iostream>
#include "utils.h"
using namespace std;

unsigned int cs::max_id = 0;

cs::cs()
{
    ++cs::max_id;
}

cs::cs(unsigned int id)
{
    cout << "[Добавление КС]" << endl;
    this->id = id;
    cout << "Введите имя: ";
    getline(cin, this->name);
    cout << "Введите количество цехов: ";
    this->workShopNumber = getInt();
    cout << "Введите количество активных цехов: ";
    this->activeWorkshopNumber = getInt();
    while (this->activeWorkshopNumber > this->workShopNumber) {
        cout << "[Рабочих цехов не может быть больше, чем их всего]"
            << endl << "Введите количество активных цехов: ";
        this->activeWorkshopNumber = getInt();
    }
    cout << "Введите показатель эффективности: ";
    this->efficiency = getInt();
    cout << "[Компрессорная станция добавлена]" << endl;
    ++cs::max_id;
}

cs::~cs()
{
}

void cs::edit()
{
        cout << "[Редактирование компрессорной станции]" << endl
            << "КС с id " << this->id << " (" << this->name << ")" << endl;
        do {
            cout << "Введите количество активных цехов: ";
            this->activeWorkshopNumber = getInt();
        } while (this->activeWorkshopNumber > this->workShopNumber);
        cout << "Введите оценку эффективности: ";
        this->efficiency = getInt();
        cout << "[Изменения внесены]" << endl;
}

void cs::printHead()
{
    printLine();
    cout << "|\tId"
        << "\t|\tИмя"
        << "\t|\tЦеха"
        << "\t|\tЦеха в работе"
        << "\t|\tЭффективность"
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
