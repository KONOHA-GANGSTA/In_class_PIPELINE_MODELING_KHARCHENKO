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

void save(unordered_map <int,pipe>& pipes, unordered_map <int, cs>& css) {
    if ((pipes.empty()) && (css.empty()))
        return;
    ofstream file;
    file.open(getFileName()+".txt");
    if (file.good()) {
        file << pipe::count << endl << cs::count << endl;
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
            pipes.emplace(pipe::count+1, pipe(pipe::count+1));
            printLine();
            break;
        case 2: // ���������� ��
            css.emplace(cs::count+1, cs(cs::count+1));
            printLine();
            break;
        case 3: // �������� ���������;
            printLine();
            if (pipes.empty() && css.empty()) {
                cout << "[�������� ���]" << endl;
                break;
            }
            if (!pipes.empty()) {
                cout << "[�����] : " << pipe::count << endl ;
                pipe::printHead();
                printLine();
                for (auto& item : pipes) {
                    cout << item.second;
                    printLine();
                }
            }

            cout << "\n\n\n";

            if (!css.empty()) {
                cout << "[������������� �������] : "<< cs::count << endl;
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
                        css[id].edit();
                }
            }
            else
                cout << "[������������� ������� ���]" << endl;
            break;
        case 6: // ���������
            save(pipes, css);
            break;
        case 7: // ���������
            load(pipes, css);
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