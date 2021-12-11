#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "utils.h"
#include "pipe.h"
#include "cs.h"
#include <vector>
#include  "GTS.h"

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
            GTS.pipes.emplace(pipe.getId(), pipe.create(pipe));
            printLine();
            break;
        }
        case 2: // ���������� ��
        {
            cs cs;
            GTS.css.emplace(cs.getId(), cs.create(cs));
            printLine();
            break;
        }
        case 3: // �������� ���������;
            printLine();
            if (GTS.pipes.empty() && GTS.css.empty()) {
                cout << "[�������� ���]" << endl;
                break;
            }
            if (!GTS.pipes.empty()) {
                cout << "[�����] : " << GTS.pipes.size()<< endl ;
                pipe::printHead();
                printLine();
                for (auto& item : GTS.pipes) {
                    cout << item.second;
                    printLine();
                }
            }

            cout << "\n\n\n";

            if (!GTS.css.empty()) {
                cout << "[������������� �������] : "<< GTS.css.size() << endl;
                cs::printHead();
                printLine();
                for (auto& item : GTS.css) {
                    cout << item.second;
                    printLine();
                }
                scroll();
                break;
        case 4: // �������������� �����;
            if (!GTS.pipes.empty()) {
                while (true) {
                    printLine();
                    cout << "��� ������ ������� 0\n������� id �����: ";
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
                        cout << "�������� ��������: ";
                        switch (getInt()) {
                        case 1:
                            GTS.pipes[id].edit(GTS.pipes[id].getId());
                            break;
                        case 2:
                            GTS.pipes.erase(id);
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
            if (!GTS.css.empty()) {
                while (true) {
                    printLine();
                    cout << "��� ������ ������� 0\n������� id ��: ";
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
                        cout << "�������� ��������: ";
                        switch (getInt()) {
                        case 1:
                            GTS.css[id].edit();
                            break;
                        case 2:
                            GTS.css.erase(id);
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
            GTS.load();
            printLine();
            scroll();
            break;
        case 7: // ���������
            GTS.load();
            printLine();
            scroll();
            break;
        case 8: // �����
            printSearchMenu();
            cout << "�������� ��������: ";
            switch (getInt()) {
            case 0:
                break;
            case 1: // ����� ���� �� �������
            {   
                int j = 0;
                cout << "�������� ����� � �������?(Y/N): ";
                for (int i : findByFilter(GTS.pipes, pipe::checkCondition, confirm())) {
                    if (++j == 1) pipe::printHead();
                    printLine();
                    cout << GTS.pipes[i];
                }
                if (j == 0) cout << "[����� ���]" << endl;
                printLine();
                scroll();
                break;
            }

            case 2: // ����� ���� �� ��������
            {   
                int j = 0;
                cout << "������� ������� �������: ";
                for (int i : findByFilter(GTS.pipes, pipe::checkDiam, getInt())) {
                    if (++j == 1) pipe::printHead();
                    printLine();
                    cout << GTS.pipes[i];
                }
                if (j == 0) cout << "[����� ���]" << endl;
                printLine();
                scroll();
                break;
            }
            case 3: // ����� �� �� �����
            {
                int j = 0;
                cout << "������� ������� ���:"<< endl;
                string name;
                getline(cin, name);
                for (int i : findByFilter(GTS.css, cs::checkName, name)) {
                    if (++j == 1) cs::printHead();
                    printLine();
                    cout << GTS.css[i];
                }
                if (j == 0) cout << "[����� ���]" << endl;
                printLine();
                scroll();
                break;
            }
            case 4: // ����� �� �� �������� ���������������� �����
            {
                int j = 0;
                cout << "������� ������� ���������� �����: ";
                for (int i : findByFilter(GTS.css, cs::checkPrecent, getInt())) {
                    if (++j == 1) cs::printHead();
                    printLine();
                    cout << GTS.css[i];
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
        case 9: // �������� ��������������
        {
            printLine();
            printMultiEditMenu();
            printLine();
            cout << "������� ��������: ";
            switch (getInt()) {
            case 1: // �������������� ���� �� �������
            {
                printLine();
                cout << "������������� �� ��� � �������?(Y/N): ";
                vector <int> keys = findByFilter(GTS.pipes, pipe::checkCondition, confirm());
                if (keys.size() == 0) { cout << "[����� ���]" << endl; break; }
                cout << "������� " << keys.size() << " ����" << endl;
                printLine();
                cout << "����� �������?(Y/N) " << endl;
                if (!confirm()) {
                    cout << "������������� ��������?(Y/N): ";
                    if (confirm())
                        for (int i : keys)
                            GTS.pipes[i].edit(GTS.pipes[i].getId());
                    else
                        for (int i : keys)
                            GTS.pipes[i].isInRepair = !GTS.pipes[i].isInRepair;
                }
                else {


                    cout << "������� ��������?(Y/N): ";
                    if (confirm())
                        for (int i : keys){
                            pipe::printHead();
                            printLine();
                            cout << GTS.pipes[i];
                            cout << "�������?(Y/N) ";
                            if(confirm())
                            GTS.pipes.erase(i);}
                    else
                        for (int i : keys)
                            GTS.pipes.erase(i);
                            cout << "[����� �������]" << endl;


                }
                break;
            }
            case 2: // �������������� ��
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
                    vector <int> keys = findByFilter(GTS.css, cs::checkName, name);
                    if (keys.size() == 0) { cout << "[����� ���]" << endl; break; }
                    cout << "������� " << keys.size() << " ��" << endl;
                    printLine();
                        for (int i : keys)
                            GTS.css[i].edit();
                }
                    break;
                case 2:
                {
                    printLine();
                    cout << "������� ������� �������: ";
                    vector <int> keys = findByFilter(GTS.css, cs::checkPrecent, getInt());
                    if (keys.size() == 0) { cout << "[����� ���]" << endl; break; }
                    cout << "������� " << keys.size() << " ��" << endl;
                    printLine();
                    for (int i : keys)
                        GTS.css[i].edit();
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