
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
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

void printPipeHead() {

    printLine();
    cout << "|\tId"
        << "\t|\t�����"
        << "\t|\t�������"
        << "\t|\t� �������"
        << "\t|" << endl;
}

void printHeadline(const cs& cs) {

    printLine();
    cout << "|\tId"
        << "\t|\t���"
        << "\t|\t����"
        << "\t|\t���� � ������"
        << "\t|\t�������������"
        << "\t|" << endl;
}

void printPipe(const pipe& pipe) {
    
    cout << "|\t" << pipe.id
        << "\t|\t" << pipe.length
        << "\t|\t" << pipe.diametr
        << "\t|\t" << pipe.isInRepair
        << "\t\t|" << endl;
}

void printCs(const cs& cs) {

    cout << "|\t" << cs.id
        << "\t|\t" << cs.name
        << "\t|\t" << cs.workShopNumber
        << "\t|\t" << cs.activeWorkshopNumber
        << "\t\t|\t" << cs.efficiency
        << "\t\t|" << endl;
}

string DotToComma(string& str) {

    if (str.find(".") != string::npos)
        return str.replace(str.find("."), 1, ",");
    else return str;

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

pipe addPipe(int& id) {

    cout << "[���������� �����]" << endl;
    pipe pipe;
    pipe.id = id;
    cout << "������� �����: ";
    pipe.length = getDouble();
    cout << "������� �������: ";
    pipe.diametr = getInt();
    cout << "������ � �������? (Y/N): ";
    pipe.isInRepair = confirm();
    cout << "[����� ���������]" << endl;
    return pipe;
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

void editPipe(pipe pipe) {

    cout << "[�������������� �����]" << endl
        << "����� � id " << pipe.id << " � �������?(Y/N): ";
    pipe.isInRepair = confirm();
    cout << "[��������� �������]" << endl;
    
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
    file.open("objects.txt");
    if (file.good()) {
        {
            for (auto i : pipes) {
                file << "pipe" << endl
                    << i.second.id << endl
                    << i.second.length << endl
                    << i.second.diametr << endl
                    << i.second.isInRepair << endl;
            }
        }

        {
            for (auto i : css) {
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

void load(unordered_map <int,pipe>& pipes, unordered_map <int, cs>& css) {

    pipes.clear();
    css.clear();
    ifstream file;
    file.open("objects.txt", ios::in);
    if (file.good()) {
        while (!file.eof()) {
            string str;
            getline(file, str);
            if (str == "pipe") {
                pipe pipe;
                string value;
                getline(file, value);
                pipe.id = stoi(value);
                getline(file, value);
                pipe.length = stod(DotToComma(value));
                getline(file, value);
                pipe.diametr = stoi(value);
                getline(file, value);
                (value == "1") ? pipe.isInRepair = true : pipe.isInRepair = false;
                pipes[pipe.id] = pipe;
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
            pipes.emplace(pipesCount, addPipe(pipesCount));
            printLine();
            break;
        case 2: // ���������� ��
            csCount++;
            css.emplace(csCount, addCs(csCount));
            printLine();
            break;
        case 3: // �������� ���������;
            if (pipes.empty() && pipes.empty()) {
                cout << "[�������� ���]" << endl;
                break;
            }           
            if (!pipes.empty()) {
                cout << "[�����]" << endl;
                printPipeHead();
                printLine();
                for (pair<int,pipe> item : pipes) {
                    printPipe(item.second);
                    printLine();
                }
            }

            cout << "\n\n\n";

            if (!css.empty()) {
                cout << "[������������� �������]" << endl;
                printHeadline(css[0]);
                printLine();
                for (pair<int, cs> item : css) {
                    printCs(item.second);
                    printLine();
                }

            break;
        case 4: // �������������� �����;
            if (!pipes.empty()) {
                while (true) {
                    cout << "��� ������ ������� 0\n������� id �����: ";
                    int id = getInt();
                    if (id == 0 || pipes.find(id) == pipes.end())
                        break;
                    else
                    editPipe(pipes[getInt()]);
                }
            }
            else
                cout << "[���� ���]" << endl;
            break;
        case 5: // �������������� ��
            if (!css.empty()) {
                while (true) {
                    cout << "��� ������ ������� 0\n������� id ��: ";
                    int id = getInt();
                    if (id == 0 || pipes.find(id) == pipes.end())
                        break;
                    else
                        editPipe(pipes[getInt()]);
                }
            }
            else
                cout << "[������������� ������� ���]" << endl;
            break;
        case 6: // ���������
            save(pipes,css);
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
