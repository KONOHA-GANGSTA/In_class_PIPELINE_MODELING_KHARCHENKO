#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "utils.h"
#include "pipe.h"
using namespace std;


struct cs {

    unsigned int id;
    string name;
    int workShopNumber;
    int activeWorkshopNumber;
    int efficiency;

};

void scroll() {
    for (int i = 0; i <= 5; i++)
        cout << endl;
}

void printMenu() {
    cout << "1. Добавить трубу" << endl;
    cout << "2. Добавить КС" << endl;
    cout << "3. Просмотр всех объектов" << endl;
    cout << "4. Редактировать трубу" << endl;
    cout << "5. Редактировать КС" << endl;
    cout << "6. Сохранить" << endl;
    cout << "7. Загрузить" << endl;
    cout << "0. Выход" << endl;
    printLine();
    cout << endl;
}

void printCsHead() {

    printLine();
    cout << "|\tId"
        << "\t|\tИмя"
        << "\t|\tЦеха"
        << "\t|\tЦеха в работе"
        << "\t|\tЭффективность"
        << "\t|" << endl;
}

void printCs(const cs& cs) {

    cout << "|\t" << cs.id
        << "\t|\t" << cs.name
        << "\t|\t" << cs.workShopNumber
        << "\t|\t" << cs.activeWorkshopNumber
        << "\t\t|\t" << cs.efficiency
        << "\t\t|" << endl;
}

cs addCs(int& id) {

    cout << "[Добавление КС]" << endl;
    cs cs;
    cs.id = id;
    cout << "Введите имя: ";
    getline(cin,cs.name);
    cout << "Введите количество цехов: ";
    cs.workShopNumber = getInt();
    cout << "Введите количество активных цехов: ";
    cs.activeWorkshopNumber = getInt();
    while (cs.activeWorkshopNumber > cs.workShopNumber) {
        cout << "[Рабочих цехов не может быть больше, чем их всего]"
            << endl << "Введите количество активных цехов: ";
            cs.activeWorkshopNumber = getInt();
    }
    cout << "Введите показатель эффективности: ";
    cs.efficiency = getInt();
    cout << "[Компрессорная станция добавлена]" << endl;
    return cs;
}

void editCs(cs& cs) {

    cout << "[Редактирование компрессорной станции]" << endl
        << "КС с id " << cs.id << " (" << cs.name << ")" << endl;
    do {
        cout << "Введите количество активных цехов: ";
        cs.activeWorkshopNumber = getInt();
    } while (cs.activeWorkshopNumber > cs.workShopNumber);
    cout << "Введите оценку эффективности: ";
    cs.efficiency = getInt();
    cout << "[Изменения внесены]" << endl;
}

void save(unordered_map <int,pipe>& pipes, unordered_map <int, cs>& css) {
    if ((pipes.empty()) && (css.empty()))
        return;
    ofstream file;
    file.open(getFileName()+".txt");
    if (file.good()) {
        
            for (auto& i : pipes)
                file << "pipe" << endl << i.second;

        {
            for (auto& i : css) {
                file << "cs" << endl
                    << i.second.id << endl
                    << i.second.name << endl
                    << i.second.workShopNumber << endl
                    << i.second.activeWorkshopNumber << endl
                    << i.second.efficiency << endl;
            }
        }
        file.close();
        cout << "[Данные сохранены]" << endl;
    }
}

void load(unordered_map <int,pipe>& pipes, unordered_map <int, cs>& css,int& pipeNumber,int& csNumber) {
    pipeNumber = 0;
    csNumber = 0;
    pipes.clear();
    css.clear();
    ifstream file;
    file.open(getFileName()+".txt", ios::in);
    if (file.good()) {
        while (!file.eof()) {
            string str;
            getline(file, str);
            if (str == "pipe") {
                pipe pipe;
                file >> pipe;
                pipes[pipe.id] = pipe;
                pipeNumber++;
            }

            if (str == "cs") {
                cs cs;
                string value;
                getline(file, value);
                cs.id = stoi(value);
                getline(file, value);
                cs.name = value;
                getline(file, value);
                cs.workShopNumber = stoi(value);
                getline(file, value);
                cs.activeWorkshopNumber = stoi(value);
                getline(file, value);
                cs.efficiency = stoi(value);
                css[cs.id] = cs;
                csNumber++;
            }
        }
        cout << "[Данные загружены]" << endl;
    }
    file.close();
}

int main()
{
    setlocale(LC_ALL, "Russian");

    unordered_map <int, pipe> pipes;
    unordered_map <int, cs> css;
    int pipesCount = 0;
    int csCount = 0;
    cout << "\t\t\tДобро пожаловать в систему моделирования трубопроводного транспорта" << endl;
    cout << "\t\t\t\t\t\t (©) Харченко АА-20-05 2021г.\n\n\n";

    while (true) {

        printMenu();
        cout << "Выберите действие: ";

        switch (getInt())
        {
        case 0: // Выход
            return 0;
            break;
        case 1: // Добавление трубы
            pipesCount++;
            pipes.emplace(pipesCount, pipe(pipesCount));
            printLine();
            break;
        case 2: // Добавление КС
            csCount++;
            css.emplace(csCount, addCs(csCount));
            printLine();
            break;
        case 3: // Просмотр элементов;
            if (pipes.empty() && css.empty()) {
                cout << "[Объектов нет]" << endl;
                break;
            }
            if (!pipes.empty()) {
                cout << "[Трубы]" << endl;
                pipe::printHead();
                printLine();
                for (auto& item : pipes) {
                    cout << item.second;
                    printLine();
                }
            }

            cout << "\n\n\n";

            if (!css.empty()) {
                cout << "[Компрессорные станции]" << endl;
                printCsHead();
                printLine();
                for (pair<int, cs> item : css) {
                    printCs(item.second);
                    printLine();
                }

                break;
        case 4: // Редактирование трубы;
            if (!pipes.empty()) {
                while (true) {
                    printLine();
                    cout << "Для выхода введите 0\nВведите id трубы: ";
                    int id = getInt();
                    if (id == 0 || pipes.find(id) == pipes.end())
                    {
                        scroll();
                        break;
                    }
                    else
                       pipes[id].edit();
                }
            }
            else
                cout << "[Труб нет]" << endl;
            break;
        case 5: // Редактирование КС
            if (!css.empty()) {
                while (true) {
                    printLine();
                    cout << "Для выхода введите 0\nВведите id КС: ";
                    int id = getInt();
                    if (id == 0 || css.find(id) == css.end())
                    {
                        scroll();
                        break;
                    }
                    else
                        editCs(css[id]);
                }
            }
            else
                cout << "[Компрессорных станций нет]" << endl;
            break;
        case 6: // Сохранить
            save(pipes, css);
            break;
        case 7: // Загрузить
            load(pipes, css,pipesCount,csCount);
            break;
        default:
            cout << "[Такого действия не существует]" << endl;
            break;
            }
            printLine();
            scroll();
        }
    }
}