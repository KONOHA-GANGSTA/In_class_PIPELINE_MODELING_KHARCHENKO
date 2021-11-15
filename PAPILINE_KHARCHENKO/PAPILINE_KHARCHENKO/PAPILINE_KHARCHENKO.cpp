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
    cout << "1. �������� �����" << endl;
    cout << "2. �������� ��" << endl;
    cout << "3. �������� ���� ��������" << endl;
    cout << "4. ������������� �����" << endl;
    cout << "5. ������������� ��" << endl;
    cout << "6. ���������" << endl;
    cout << "7. ���������" << endl;
    cout << "8. �����" << endl;
    cout << "9. �������� ��������������" << endl;
    cout << "0. �����" << endl;
    printLine();
    cout << endl;
}

void printEditMenu() {
    cout << "1. �������������" << endl 
         << "2. �������" << endl
         << "0. �����" << endl;
}

void printMultiEditMenu() {
    cout << "1. ������������� �����" << endl
         << "2. ������������� ��" << endl
         << "0. �����" << endl;
}

void printSearchMenu() {
    cout << endl << "����� ������" << endl;
    printLine();
    cout << "1. ����� �� ���������" << endl
        << "2. ����� �� ��������" << endl
        << "3. �� �� ��������" << endl
        << "4. �� �� �������� ���������������� �����" << endl
        << "0. �����" << endl;
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
        cout << "[������ ���������]" << endl;
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
        cout << "[������ ���������]" << endl;
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

    cout << "\t\t\t����� ���������� � ������� ������������� ��������������� ����������" << endl;
    cout << "\t\t\t\t\t\t (�) �������� ��-20-05 2021�.\n\n\n";

    while (true) {

        printMenu();
        cout << "�������� ��������: ";

        switch (getInt())
        {
        case 0: // �����
            return 0;
            break;
        case 1: // ���������� �����
        {   
            pipe pipe;
            pipes.emplace(pipe.id, pipe.create(pipe));
            printLine();
            break;
        }
        case 2: // ���������� ��
        {
            cs cs;
            css.emplace(cs.id, cs.create(cs));
            printLine();
            break;
        }
        case 3: // �������� ���������;
            printLine();
            if (pipes.empty() && css.empty()) {
                cout << "[�������� ���]" << endl;
                break;
            }
            if (!pipes.empty()) {
                cout << "[�����] : " << pipes.size()<< endl ;
                pipe::printHead();
                printLine();
                for (auto& item : pipes) {
                    cout << item.second;
                    printLine();
                }
            }

            cout << "\n\n\n";

            if (!css.empty()) {
                cout << "[������������� �������] : "<< css.size() << endl;
                cs::printHead();
                printLine();
                for (auto& item : css) {
                    cout << item.second;
                    printLine();
                }
                scroll();
                break;
        case 4: // �������������� �����;
            if (!pipes.empty()) {
                while (true) {
                    printLine();
                    cout << "��� ������ ������� 0\n������� id �����: ";
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
                        cout << "�������� ��������: ";
                        switch (getInt()) {
                        case 1:
                            pipes[id].edit(pipes[id].id);
                            break;
                        case 2:
                            pipes.erase(id);
                            cout << "[����� �������]" << endl;
                            break;
                        case 0:
                            break;
                        default:
                            cout << "[������ �������� �� ����������]" << endl;
                            break;
                        }
                    }
                }
            }
            else
                cout << "[���� ���]" << endl;
            break;
        case 5: // �������������� ��
            if (!css.empty()) {
                while (true) {
                    printLine();
                    cout << "��� ������ ������� 0\n������� id ��: ";
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
                        cout << "�������� ��������: ";
                        switch (getInt()) {
                        case 1:
                            css[id].edit();
                            break;
                        case 2:
                            css.erase(id);
                            cout << "[�� �������]" << endl;
                            break;
                        case 0:
                            break;
                        default:
                            cout << "[������ �������� �� ����������]" << endl;
                            break;
                        }
                    }  
                }
            }
            else
                cout << "[������������� ������� ���]" << endl;
            break;
        case 6: // ���������
            save(pipes, css);
            printLine();
            scroll();
            break;
        case 7: // ���������
            load(pipes, css);
            printLine();
            scroll();
            break;
        case 8:
            printSearchMenu();
            cout << "�������� ��������: ";
            switch (getInt()) {
            case 0:
                break;
            case 1:
            {   
                int j = 0;
                cout << "�������� ����� � �������?(Y/N): ";
                for (int i : findByFilter(pipes, pipe::checkCondition, confirm())) {
                    if (++j == 1) pipe::printHead();
                    printLine();
                    cout << pipes[i];
                }
                if (j == 0) cout << "[����� ���]" << endl;
                printLine();
                scroll();
                break;
            }

            case 2:
            {   
                int j = 0;
                cout << "������� ������� �������: ";
                for (int i : findByFilter(pipes, pipe::checkDiam, getInt())) {
                    if (++j == 1) pipe::printHead();
                    printLine();
                    cout << pipes[i];
                }
                if (j == 0) cout << "[����� ���]" << endl;
                printLine();
                scroll();
                break;
            }
            case 3:
            {
                int j = 0;
                cout << "������� ������� ���:"<< endl;
                string name;
                getline(cin, name);
                for (int i : findByFilter(css, cs::checkName, name)) {
                    if (++j == 1) cs::printHead();
                    printLine();
                    cout << css[i];
                }
                if (j == 0) cout << "[����� ���]" << endl;
                printLine();
                scroll();
                break;
            }
            case 4:
            {
                int j = 0;
                cout << "������� ������� ���������� �����: ";
                for (int i : findByFilter(css, cs::checkPrecent, getInt())) {
                    if (++j == 1) cs::printHead();
                    printLine();
                    cout << css[i];
                }
                if (j == 0) cout << "[����� ���]" << endl;
                printLine();
                scroll();
                break;
            }
            default:
                cout << "[������ �������� �� ����������]" << endl;
                break;
            }
            break;
        case 9: 
        {
            printLine();
            printMultiEditMenu();
            printLine();
            cout << "������� ��������: ";
            switch (getInt()) {
            case 1:
            {
                printLine();
                cout << "������������� �� ��� � �������?(Y/N): ";
                vector <int> keys = findByFilter(pipes, pipe::checkCondition, confirm());
                if (keys.size() == 0) { cout << "[����� ���]" << endl; break; }
                cout << "������� " << keys.size() << " ����" << endl;
                printLine();
                cout << "������������� ��������?(Y/N): ";
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
                cout << "1. �� �����" << endl << "2. �� �������� ��������� �����" << endl<<"0. �����" << endl;
                printLine();
                cout << "������� ��������: ";
                switch (getInt()) {
                case 1:
                {
                    printLine();
                    cout << "������� ���: ";
                    string name;
                    getline(cin, name);
                    vector <int> keys = findByFilter(css, cs::checkName, name);
                    if (keys.size() == 0) { cout << "[����� ���]" << endl; break; }
                    cout << "������� " << keys.size() << " ��" << endl;
                    printLine();
                        for (int i : keys)
                            css[i].edit();
                }
                    break;
                case 2:
                {
                    printLine();
                    cout << "������� ������� �������: ";
                    vector <int> keys = findByFilter(css, cs::checkPrecent, getInt());
                    if (keys.size() == 0) { cout << "[����� ���]" << endl; break; }
                    cout << "������� " << keys.size() << " ��" << endl;
                    printLine();
                    for (int i : keys)
                        css[i].edit();
                }
                    break;
                case 0:
                    break;
                default:
                    cout << "[������ �������� �� ����������]" << endl;
                    break;
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "[������ �������� �� ����������]" << endl;
                break;
            }
            printLine();
            scroll();
            break;
        }
        default:
        {
            cout << "[������ �������� �� ����������]" << endl;
            break;
        }
            }
            printLine();
            scroll();
        }
    }
}