#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "utils.h"
#include "pipe.h"
#include "cs.h"
#include <vector>
#include  "GTS.h"
#include "graphStuff.h"

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
    cout << "6. Сохранить ГТС" << endl;
    cout << "7. Загрузить ГТС" << endl;
    cout << "8. Поиск" << endl;
    cout << "9. Пакетное редактирование" << endl;
    cout << "10. Проложить трубу" << endl;
    cout << "11. Разорвать сообщение" << endl;
    cout << "12. Топологическая сортировка" << endl;
    cout << "13. Кратчайший путь" << endl;
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

    //unordered_map <int, pipe> pipes;
    //unordered_map <int, cs> css;
    GTS GTS;
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
            GTS.pipes.emplace(pipe.getId(), pipe.create(pipe));
            printLine();
            break;
        }
        case 2: // Добавление КС
        {
            cs cs;
            GTS.css.emplace(cs.getId(), cs.create(cs));
            printLine();
            break;
        }
        case 3: // Просмотр элементов;
            printLine();
            if (GTS.pipes.empty() && GTS.css.empty()) {
                cout << "[Объектов нет]" << endl;
                break;
            }
            if (!GTS.pipes.empty()) {
                cout << "[Трубы] : " << GTS.pipes.size()<< endl ;
                pipe::printHead();
                printLine();
                for (auto& item : GTS.pipes) {
                    cout << item.second;
                    printLine();
                }
            }

            cout << "\n\n\n";

            if (!GTS.css.empty()) {
                cout << "[Компрессорные станции] : "<< GTS.css.size() << endl;
                cs::printHead();
                printLine();
                for (auto& item : GTS.css) {
                    cout << item.second;
                    printLine();
                }

                cout << "\n\n\n";


                if (GTS::ocupiedCss.size() != 0) {
                    if (GTS::changed) {
                        GTS::matWeights = getMatWeights(GTS);
                        GTS::changed = false;
                    }
                    cout << "[Связи]" << endl;
                    printLine();
                    cout << "\t\t|\t";
                    for (int i : GTS::ocupiedCss) {
                        cout << i << "\t|\t";
                    }
                    cout << endl;
                    printLine();
                    for (auto& i : GTS::matWeights) {
                        cout << "\t" << i.first << "\t|";
                        for (double& j : i.second) {
                            cout << "\t" << j << "\t|";
                        }                    
                        cout << endl;
                        printLine();
                    }
                }
                scroll();
                break;
        case 4: // Редактирование трубы;
            if (!GTS.pipes.empty()) {
                while (true) {
                    printLine();
                    cout << "Для выхода введите 0\nВведите id трубы: ";
                    int id = getInt();
                    if (id == 0 || GTS.pipes.find(id) == GTS.pipes.end())
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
                            GTS.pipes[id].edit(GTS.pipes[id].getId());
                            break;
                        case 2:
                            if (GTS::ocupiedPipes.find(id) != GTS::ocupiedPipes.end()) {
                                cout << "[Данная труба находится в эксплуатации]" << endl;
                                break;
                            }
                            GTS.pipes.erase(id);
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
            if (!GTS.css.empty()) {
                while (true) {
                    printLine();
                    cout << "Для выхода введите 0\nВведите id КС: ";
                    int id = getInt();
                    if (id == 0 || GTS.css.find(id) == GTS.css.end())
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
                            GTS.css[id].edit();
                            break;
                        case 2:
                            if (GTS::ocupiedCss.find(id) != GTS::ocupiedCss.end()) {
                                cout << "[Данная KC находится в эксплуатации]" << endl;
                                break;
                            }
                            GTS.css.erase(id);
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
            GTS.save();
            printLine();
            scroll();
            break;
        case 7: // Загрузить
            GTS.load();
            printLine();
            scroll();
            break;
        case 8: // Поиск
            printSearchMenu();
            cout << "Выберите действие: ";
            switch (getInt()) {
            case 0:
                break;
            case 1: // Поиск труб по ремонту
            {   
                int j = 0;
                cout << "Показать трубы в ремонте?(Y/N): ";
                for (int i : findByFilter(GTS.pipes, pipe::checkCondition, confirm())) {
                    if (++j == 1) pipe::printHead();
                    printLine();
                    cout << GTS.pipes[i];
                }
                if (j == 0) cout << "[Таких нет]" << endl;
                printLine();
                scroll();
                break;
            }

            case 2: // Поиск труб по диаметру
            {   
                int j = 0;
                cout << "Введите искомый диаметр: ";
                for (int i : findByFilter(GTS.pipes, pipe::checkDiam, getInt())) {
                    if (++j == 1) pipe::printHead();
                    printLine();
                    cout << GTS.pipes[i];
                }
                if (j == 0) cout << "[Таких нет]" << endl;
                printLine();
                scroll();
                break;
            }
            case 3: // Поиск КС по имени
            {
                int j = 0;
                cout << "Введите искомое имя:"<< endl;
                string name;
                getline(cin, name);
                for (int i : findByFilter(GTS.css, cs::checkName, name)) {
                    if (++j == 1) cs::printHead();
                    printLine();
                    cout << GTS.css[i];
                }
                if (j == 0) cout << "[Таких нет]" << endl;
                printLine();
                scroll();
                break;
            }
            case 4: // Поиск КС по проценту незадействованых цехов
            {
                int j = 0;
                cout << "Введите процент неактивных цехов: ";
                for (int i : findByFilter(GTS.css, cs::checkPrecent, getInt())) {
                    if (++j == 1) cs::printHead();
                    printLine();
                    cout << GTS.css[i];
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
        case 9: // Пакетное редактирование
        {
            printLine();
            printMultiEditMenu();
            printLine();
            cout << "Введите действие: ";
            switch (getInt()) {
            case 1: // Редактирование труб по ремонту
            {
                printLine();
                cout << "Редактировать те что в ремонте?(Y/N): ";
                vector <int> keys = findByFilter(GTS.pipes, pipe::checkCondition, confirm());
                if (keys.size() == 0) { cout << "[Таких нет]" << endl; break; }
                cout << "Найдено " << keys.size() << " труб" << endl;
                printLine();
                cout << "Будем удалять?(Y/N) " << endl;
                if (!confirm()) {
                    cout << "Редактировать поштучно?(Y/N): ";
                    if (confirm())
                        for (int i : keys)
                            GTS.pipes[i].edit(GTS.pipes[i].getId());
                    else
                        for (int i : keys)
                            GTS.pipes[i].isInRepair = !GTS.pipes[i].isInRepair;
                }
                else {


                    cout << "Удалить поштучно?(Y/N): ";
                    if (confirm())
                        for (int i : keys){
                            pipe::printHead();
                            printLine();
                            cout << GTS.pipes[i];
                            cout << "Удаляем?(Y/N) ";
                            if(confirm())
                            GTS.pipes.erase(i);}
                    else
                        for (int i : keys)
                            GTS.pipes.erase(i);
                            cout << "[Трубы удалены]" << endl;


                }
                break;
            }
            case 2: // Редактирование КС
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
                    vector <int> keys = findByFilter(GTS.css, cs::checkName, name);
                    if (keys.size() == 0) { cout << "[Таких нет]" << endl; break; }
                    cout << "Найдено " << keys.size() << " КС" << endl;
                    printLine();
                        for (int i : keys)
                            GTS.css[i].edit();
                }
                    break;
                case 2:
                {
                    printLine();
                    cout << "Введите искомый процент: ";
                    vector <int> keys = findByFilter(GTS.css, cs::checkPrecent, getInt());
                    if (keys.size() == 0) { cout << "[Таких нет]" << endl; break; }
                    cout << "Найдено " << keys.size() << " КС" << endl;
                    printLine();
                    for (int i : keys)
                        GTS.css[i].edit();
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
        case 10:
        {
            int out, pipeId, in;
            cout << "Введите из какой КС(id): ";
            out = getInt();
            cout << "Введите какой трубой соединить(id): ";
            pipeId = getInt();
            cout << "Введите к какой КС подвести(id): ";
            in = getInt();
            GTS.connect(out, pipeId, in);
            printLine();
            scroll();
            break;
        }
        case 11: {
            int inCs, outCs;
            cout << "От какой станции идёт труба?(id): ";
            outCs = getInt();
            cout << "К какой станции идёт труба?(id): ";
            inCs = getInt();
            GTS.disconnect(outCs, inCs);
            printLine();
            scroll();
            break;
        }
        case 12: {
            for (auto& i : topSort(GTS)) {
                cout << i.first << " : Станция <" << GTS.css[i.second].name <<"> (id:" << i.second << ")" << endl;
            }
            printLine();
            scroll();
            break;
        }
        case 13: {
            printLine();
            cout << "Откуда (id):";
            int start = getInt();
            cout << "Куда (id):";
            int finish = getInt();
            if ((GTS::ocupiedCss.find(start) != GTS::ocupiedCss.end()) & (GTS::ocupiedCss.find(finish) != GTS::ocupiedCss.end())) {
                unordered_map <int, double> ways = dickstra(start, GTS);
                for (int i : seqReturn(finish, ways, GTS)) {
                    cout << "<" << GTS.css[i].name << ">(id:" << i << ")---> ";
                }
                if (ways.size() != 0) {
                    cout << "<" << GTS.css[finish].name << ">(id:" << finish << ")" << endl;
                    cout << "Длинна пути: " << ways[finish] << " км" << endl;
                }
            }
            else cout << "[Ошибка в исходных данных]" << endl;
            printLine();
            scroll();
            break;
        }
        default:
        {
            cout << "[Такого действия не существует]" << endl;
            printLine();
            scroll();
            break;
        }
            }
            printLine();
            scroll();
        }
    }
}