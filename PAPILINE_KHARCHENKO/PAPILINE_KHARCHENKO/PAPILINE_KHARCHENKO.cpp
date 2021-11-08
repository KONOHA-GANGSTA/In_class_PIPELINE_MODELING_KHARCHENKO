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
    cout << "1. �������� �����" << endl;
    cout << "2. �������� ��" << endl;
    cout << "3. �������� ���� ��������" << endl;
    cout << "4. ������������� �����" << endl;
    cout << "5. ������������� ��" << endl;
    cout << "6. ���������" << endl;
    cout << "7. ���������" << endl;
    cout << "0. �����" << endl;
    printLine();
    cout << endl;
}

void printCsHead() {

    printLine();
    cout << "|\tId"
        << "\t|\t���"
        << "\t|\t����"
        << "\t|\t���� � ������"
        << "\t|\t�������������"
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

    cout << "[���������� ��]" << endl;
    cs cs;
    cs.id = id;
    cout << "������� ���: ";
    getline(cin,cs.name);
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

void editCs(cs& cs) {

    cout << "[�������������� ������������� �������]" << endl
        << "�� � id " << cs.id << " (" << cs.name << ")" << endl;
    do {
        cout << "������� ���������� �������� �����: ";
        cs.activeWorkshopNumber = getInt();
    } while (cs.activeWorkshopNumber > cs.workShopNumber);
    cout << "������� ������ �������������: ";
    cs.efficiency = getInt();
    cout << "[��������� �������]" << endl;
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
        cout << "[������ ���������]" << endl;
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
        cout << "[������ ���������]" << endl;
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
            pipesCount++;
            pipes.emplace(pipesCount, pipe(pipesCount));
            printLine();
            break;
        case 2: // ���������� ��
            csCount++;
            css.emplace(csCount, addCs(csCount));
            printLine();
            break;
        case 3: // �������� ���������;
            if (pipes.empty() && css.empty()) {
                cout << "[�������� ���]" << endl;
                break;
            }
            if (!pipes.empty()) {
                cout << "[�����]" << endl;
                pipe::printHead();
                printLine();
                for (auto& item : pipes) {
                    cout << item.second;
                    printLine();
                }
            }

            cout << "\n\n\n";

            if (!css.empty()) {
                cout << "[������������� �������]" << endl;
                printCsHead();
                printLine();
                for (pair<int, cs> item : css) {
                    printCs(item.second);
                    printLine();
                }

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
                    else
                       pipes[id].edit();
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
                    else
                        editCs(css[id]);
                }
            }
            else
                cout << "[������������� ������� ���]" << endl;
            break;
        case 6: // ���������
            save(pipes, css);
            break;
        case 7: // ���������
            load(pipes, css,pipesCount,csCount);
            break;
        default:
            cout << "[������ �������� �� ����������]" << endl;
            break;
            }
            printLine();
            scroll();
        }
    }
}