#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "utils.h"
#include "pipe.h"
#include "cs.h"
#include <vector>
#include <set>
using namespace std;

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
    cout << "8. Поиск" << endl;
    cout << "9. Пакетное редактирование" << endl;
    cout << "0. Выход" << endl;
    printLine();
    cout << endl;
}

void printEditMenu() {
    cout << "1. Редактировать" << endl 
         << "2. Удалить" << endl
         << "0. Назад" << endl;
}

void printMultiEditMenu() {
    cout << "1. Редактировать трубы" << endl
         << "2. Редактировать КС" << endl
         << "0. Назад" << endl;
}

void printSearchMenu() {
    cout << endl << "Найти оъекты" << endl;
    printLine();
    cout << "1. Трубы по состоянию" << endl
        << "2. Трубы по диаметру" << endl
        << "3. КС по названию" << endl
        << "4. КС по проценту незадействованых цехов" << endl
        << "0. Выход" << endl;
        printLine();
        cout << endl;
}

void save(unordered_map <int,pipe>& pipes, unordered_map <int, cs>& css) {
    if ((pipes.empty()) && (css.empty()))
        return;
    ofstream file;
    file.open(getFileName()+".txt");
    if (file.good()) {
        file << pipes.size() << endl << pipes.size() << endl;
            for (auto& i : pipes)
                file << "pipe" << endl << i.second;

            for (auto& i : css)
                file << "cs" << endl << i.second;

        file.close();
        cout << "[Данные сохранены]" << endl;
    }
}

void load(unordered_map <int,pipe>& pipes, unordered_map <int, cs>& css) {
    pipes.clear();
    css.clear();
    ifstream file;
    file.open(getFileName()+".txt", ios::in);
    if (file.good()) {
        string str;
        getline(file, str);
        pipes.reserve(stoi(str));
        getline(file, str);
        css.reserve(stoi(str));
        while (!file.eof()) {
            getline(file, str);
            if (str == "pipe") {
                pipe pipe;
                file >> pipe;
                pipes.emplace(pipe.id, pipe);
            }

            if (str == "cs") {
                cs cs;
                file >> cs;
                css.emplace(cs.id, cs);
            }
        }
        cout << "[Данные загружены]" << endl;
    }
    file.close();
}

template <typename T, typename S>
using Filter = bool(*)(const S& pipe, T param);

template <typename T, typename S>
static vector <int> findByFilter(const unordered_map<int, S>& pipes, Filter<T,S> f, T param) {
    vector <int> keys;
    for (auto& i : pipes) {
        if (f(i.second, param))
            keys.push_back(i.first);
    }
    return keys;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    unordered_map <int, pipe> pipes;
    unordered_map <int, cs> css;

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
        {   
            pipe pipe;
            pipes.emplace(pipe.id, pipe.create(pipe));
            printLine();
            break;
        }
        case 2: // Добавление КС
        {
            cs cs;
            css.emplace(cs.id, cs.create(cs));
            printLine();
            break;
        }
        case 3: // Просмотр элементов;
            printLine();
            if (pipes.empty() && css.empty()) {
                cout << "[Объектов нет]" << endl;
                break;
            }
            if (!pipes.empty()) {
                cout << "[Трубы] : " << pipes.size()<< endl ;
                pipe::printHead();
                printLine();
                for (auto& item : pipes) {
                    cout << item.second;
                    printLine();
                }
            }

            cout << "\n\n\n";

            if (!css.empty()) {
                cout << "[Компрессорные станции] : "<< css.size() << endl;
                cs::printHead();
                printLine();
                for (auto& item : css) {
                    cout << item.second;
                    printLine();
                }
                scroll();
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
                    else {
                        printLine();
                        printEditMenu();
                        printLine();
                        cout << "Выберите действие: ";
                        switch (getInt()) {
                        case 1:
                            pipes[id].edit(pipes[id].id);
                            break;
                        case 2:
                            pipes.erase(id);
                            cout << "[Труба удалена]" << endl;
                            break;
                        case 0:
                            break;
                        default:
                            cout << "[Такого действия не существует]" << endl;
                            break;
                        }
                    }
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
                    else {
                        printLine();
                        printEditMenu();
                        printLine();
                        cout << "Выберите действие: ";
                        switch (getInt()) {
                        case 1:
                            css[id].edit();
                            break;
                        case 2:
                            css.erase(id);
                            cout << "[КС удалена]" << endl;
                            break;
                        case 0:
                            break;
                        default:
                            cout << "[Такого действия не существует]" << endl;
                            break;
                        }
                    }  
                }
            }
            else
                cout << "[Компрессорных станций нет]" << endl;
            break;
        case 6: // Сохранить
            save(pipes, css);
            printLine();
            scroll();
            break;
        case 7: // Загрузить
            load(pipes, css);
            printLine();
            scroll();
            break;
        case 8:
            printSearchMenu();
            cout << "Выберите действие: ";
            switch (getInt()) {
            case 0:
                break;
            case 1:
            {   
                int j = 0;
                cout << "Показать трубы в ремонте?(Y/N): ";
                for (int i : findByFilter(pipes, pipe::checkCondition, confirm())) {
                    if (++j == 1) pipe::printHead();
                    printLine();
                    cout << pipes[i];
                }
                if (j == 0) cout << "[Таких нет]" << endl;
                printLine();
                scroll();
                break;
            }

            case 2:
            {   
                int j = 0;
                cout << "Введите искомый диаметр: ";
                for (int i : findByFilter(pipes, pipe::checkDiam, getInt())) {
                    if (++j == 1) pipe::printHead();
                    printLine();
                    cout << pipes[i];
                }
                if (j == 0) cout << "[Таких нет]" << endl;
                printLine();
                scroll();
                break;
            }
            case 3:
            {
                int j = 0;
                cout << "Введите искомое имя:"<< endl;
                string name;
                getline(cin, name);
                for (int i : findByFilter(css, cs::checkName, name)) {
                    if (++j == 1) cs::printHead();
                    printLine();
                    cout << css[i];
                }
                if (j == 0) cout << "[Таких нет]" << endl;
                printLine();
                scroll();
                break;
            }
            case 4:
            {
                int j = 0;
                cout << "Введите процент неактивных цехов: ";
                for (int i : findByFilter(css, cs::checkPrecent, getInt())) {
                    if (++j == 1) cs::printHead();
                    printLine();
                    cout << css[i];
                }
                if (j == 0) cout << "[Таких нет]" << endl;
                printLine();
                scroll();
                break;
            }
            default:
                cout << "[Такого действия не существует]" << endl;
                break;
            }
            break;
        case 9: 
        {
            printLine();
            printMultiEditMenu();
            printLine();
            cout << "Введите действие: ";
            switch (getInt()) {
            case 1:
            {
                printLine();
                cout << "Редактировать те что в ремонте?(Y/N): ";
                vector <int> keys = findByFilter(pipes, pipe::checkCondition, confirm());
                if (keys.size() == 0) { cout << "[Таких нет]" << endl; break; }
                cout << "Найдено " << keys.size() << " труб" << endl;
                printLine();
                cout << "Редактировать поштучно?(Y/N): ";
                if (confirm())
                    for (int i : keys)
                        pipes[i].edit(pipes[i].id);
                else
                    for (int i : keys)
                        pipes[i].isInRepair = !pipes[i].isInRepair;
                break;
            }
            case 2:
            {
                printLine();
                cout << "1. По имени" << endl << "2. По проценту неактвных цехов" << endl<<"0. Выход" << endl;
                printLine();
                cout << "Введите действие: ";
                switch (getInt()) {
                case 1:
                {
                    printLine();
                    cout << "Введите имя: ";
                    string name;
                    getline(cin, name);
                    vector <int> keys = findByFilter(css, cs::checkName, name);
                    if (keys.size() == 0) { cout << "[Таких нет]" << endl; break; }
                    cout << "Найдено " << keys.size() << " КС" << endl;
                    printLine();
                        for (int i : keys)
                            css[i].edit();
                }
                    break;
                case 2:
                {
                    printLine();
                    cout << "Введите искомый процент: ";
                    vector <int> keys = findByFilter(css, cs::checkPrecent, getInt());
                    if (keys.size() == 0) { cout << "[Таких нет]" << endl; break; }
                    cout << "Найдено " << keys.size() << " КС" << endl;
                    printLine();
                    for (int i : keys)
                        css[i].edit();
                }
                    break;
                case 0:
                    break;
                default:
                    cout << "[Такого действия не существует]" << endl;
                    break;
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "[Такого действия не существует]" << endl;
                break;
            }
            printLine();
            scroll();
            break;
        }
        default:
        {
            cout << "[Такого действия не существует]" << endl;
            break;
        }
            }
            printLine();
            scroll();
        }
    }
}