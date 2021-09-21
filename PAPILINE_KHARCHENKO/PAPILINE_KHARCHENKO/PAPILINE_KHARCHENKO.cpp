
#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

struct pipe {

    unsigned int id;
    double length;
    int diametr;
    bool isInRepair = false;

};

struct cs {

    unsigned int id;
    string name;
    int workShopNumber;
    int activeWorkshopNumber;
    int efficiency;

};

void printLine() {

    for (int i = 0; i <= 100; i++) {
        cout << "_";

    }
    cout << endl;
}

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

void printHeadline(pipe pipe) {

    printLine();
    cout << "|\tId"
        << "\t|\t�����"
        << "\t|\t�������"
        << "\t|\t� �������"
        << "\t|" << endl;
}

void printHeadline(cs cs) {

    printLine();
    cout << "|\tId"
        << "\t|\t���"
        << "\t|\t����"
        << "\t|\t���� � ������"
        << "\t|\t�������������"
        << "\t|" << endl;
}

void printPipe(pipe pipe) {
    
    cout << "|\t" << pipe.id 
        << "\t|\t" << pipe.length
        << "\t|\t" << pipe.diametr
        << "\t|\t" << pipe.isInRepair
        << "\t\t|" << endl;
}

void printCs(cs cs) {

    cout << "|\t" << cs.id
        << "\t|\t" << cs.name
        << "\t|\t" << cs.workShopNumber
        << "\t|\t\t" << cs.activeWorkshopNumber
        << "\t|\t\t" << cs.efficiency
        << "\t|" << endl;
}

int getInt(){
	
	while(true){

		int number;
		cin >> number;
        if (cin.fail() || number < 0)
        {
            cin.clear(); 
            cin.ignore(32767, '\n');
            cout << "[�������� �����������]" << endl
                << "������� ����� ��������: ";
        }
        else
        {
            cin.ignore(32767, '\n');
            return number;
        }
	}
}

double getDouble() {

    while (true) {

        double number;
        cin >> number;
        if (cin.fail() || number <0)
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout  << "[�������� �����������]" << endl
                << "������� ����� ��������: ";
        }
        else
        {
            cin.ignore(32767, '\n');
            return number;
        }
    }
}

bool confirm() {

    string answer;
    while (true) {
        cin >> answer;
        if (answer == "Y" || answer == "y") {
            cin.ignore(32767, '\n');
            return true;
        }
        else if (answer == "N" || answer == "n") {
            cin.ignore(32767, '\n');
            return false;
        }
        else {
            cout << "[����������� ��������]" << endl
                << "������� ����� (Y/N): ";
        }
    }

}

bool isIdOcupied(vector <pipe> pipes, int id) {
    if (pipes.size() == 0)
        return false;
    for (int i = 0; i <= pipes.size()-1; i++) {
        if (pipes[i].id == id)
            return true;
    }
    return false;
}

bool isIdOcupied(vector <cs> css, int id) {
    if (css.size() == 0)
        return false;
    for (int i = 0; i <= css.size() - 1; i++) {
        if (css[i].id == id)
            return true;
    }
    return false;
}

pipe addPipe(vector <pipe> pipes) {

    cout << "[���������� �����]" << endl;
    pipe pipe;
    do pipe.id = rand();
    while (isIdOcupied(pipes, pipe.id));
    cout << "������� �����: ";
    pipe.length = getDouble();
    cout << "������� �������: ";
    pipe.diametr = getInt();
    cout << "������ � �������? (Y/N): ";
    pipe.isInRepair = confirm();
    cout << "[����� ���������]" << endl;
    printHeadline(pipe);
    printLine();
    printPipe(pipe);
    printLine();
    return pipe;
}

cs addCs(vector <cs> css) {

    cout << "[���������� ��]" << endl;
    cs cs;
    do cs.id = rand();
    while (isIdOcupied(css, cs.id));
    cout << "������� ���: ";
    string name;
    cin >> name;
    cin.ignore(32767, '\n');
    cs.name = name;
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
    printHeadline(cs);
    printLine();
    printCs(cs);
    printLine();
    return cs;
}

pipe getPipe(vector <pipe> pipes, int id) {

    for (int i = 0; i <= pipes.size() - 1; i++)
        if (pipes[i].id == i)
            return pipes[i];
}

cs getCs(vector <cs> css, int id) {

    for (int i = 0; i <= css.size() - 1; i++)
        if (css[i].id == i)
            return css[i];
}

int main()
{   
    setlocale(LC_ALL, "Russian");

    vector <pipe> pipes;
    vector <cs> css;
    cout << "\t\t\t����� ���������� � ������� ������������� ��������������� ����������" << endl;
    cout << "\t\t\t\t\t\t (�) �������� ��-20-05 2021�.\n\n\n";

    while (true) {
       
        printMenu();
        cout << "�������� ��������: ";
        int choice = getInt();
        
        switch (choice)
        {
        case 0: // �����
            return 0;
            break;
        case 1: // ���������� �����
            pipes.push_back(addPipe(pipes));
            break;
        case 2: // ���������� ��
            css.push_back(addCs(css));
            break;
        case 3: // �������� ���������;
            if (pipes.size() != 0) {
                cout << "[�����]" << endl;
                printHeadline(pipes[0]);
                printLine();
                for (int i = 0; i <= pipes.size() - 1; i++) {
                    printPipe(pipes[i]);
                    printLine();
                }
            }

            cout << "\n\n\n";

            if (css.size() != 0) {
                cout << "[������������� �������]" << endl;
                printHeadline(css[0]);
                printLine();
                for (int i = 0; i <= css.size() - 1; i++) {
                    printCs(css[i]);
                    printLine();
                }
            }

            if (pipes.size() == 0 && css.size() == 0) {
                cout << "[�������� ���]" << endl;
            }

            break;
        case 4: // �������������� �����;
            break;
        case 5: // �������������� ��
            break;
        case 6: // ���������
            break;
        case 7: // ���������
            break;
        default: 
            cout << "[������ �������� �� ����������]" << endl;
            break;
        }
        printLine();
        scroll();
    }

}
