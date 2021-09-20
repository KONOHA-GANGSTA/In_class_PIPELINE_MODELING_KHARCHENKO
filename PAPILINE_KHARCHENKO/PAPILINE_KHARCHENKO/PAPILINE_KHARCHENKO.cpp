
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

void printPipe(pipe &pipe) {

    cout << endl
        << "ID: " << pipe.id << endl
        << "Diametr: " << pipe.diametr << endl;

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

pipe addPipe() {

    cout << "[���������� �����]" << endl;
    pipe pipe;
    pipe.id = 1;
    cout << "������� �����: ";
    pipe.length = getDouble();
    cout << "������� �������: ";
    pipe.diametr = getInt();
    cout << "������ � �������? (Y/N): ";
    pipe.isInRepair = confirm();
    return pipe;

}

cs addCs() {

    cout << "[���������� ��]" << endl;
    cs cs;
    cs.id = 1;
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
    return cs;
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
            pipes.push_back(addPipe());
            break;
        case 2: // ���������� ��
            css.push_back(addCs());
            break;
        case 3: // �������� ���������;
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
    }

}
