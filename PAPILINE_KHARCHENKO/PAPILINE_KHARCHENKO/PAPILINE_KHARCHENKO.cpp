#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "utils.h"
#include "pipe.h"
#include "cs.h"
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
    cout << "0. Выход" << endl;
    printLine();
    cout << endl;
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
                file << "cs" << endl << i.second;
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
                file >> cs;
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
            css.emplace(csCount, cs(csCount));
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
                cs::printHead();
                printLine();
                for (auto& item : css) {
                    cout << item.second;
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
                        css[id].edit();
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