
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

void printPipeHead() {

    printLine();
    cout << "|\tId"
        << "\t|\tДлина"
        << "\t|\tДиаметр"
        << "\t|\tВ ремонте"
        << "\t|" << endl;
}

void printHeadline(const cs& cs) {

    printLine();
    cout << "|\tId"
        << "\t|\tИмя"
        << "\t|\tЦеха"
        << "\t|\tЦеха в работе"
        << "\t|\tЭффективность"
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
            cout << "[Значение некорректно]" << endl
                << "Введите новое значение: ";
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
            cout  << "[Значение некорректно]" << endl
                << "Введите новое значение: ";
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
            cout << "[Некоректное значение]" << endl
                << "Введите новое (Y/N): ";
        }
    }

}

pipe addPipe(int& id) {

    cout << "[Добавление трубы]" << endl;
    pipe pipe;
    pipe.id = id;
    cout << "Введите длину: ";
    pipe.length = getDouble();
    cout << "Введите диаметр: ";
    pipe.diametr = getInt();
    cout << "Сейчас в ремонте? (Y/N): ";
    pipe.isInRepair = confirm();
    cout << "[Труба добавлена]" << endl;
    return pipe;
}

cs addCs(int& id) {

    cout << "[Добавление КС]" << endl;
    cs cs;
    cs.id = id;
    cout << "Введите имя: ";
    getline(cin,cs.name);
    cout << "Введите количество цехов: ";
    cs.workShopNumber = getInt();
    cout << "Введите количество активных цехов: ";
    cs.activeWorkshopNumber = getInt();
    while (cs.activeWorkshopNumber > cs.workShopNumber) {
        cout << "[Рабочих цехов не может быть больше, чем их всего]"
            << endl << "Введите количество активных цехов: ";
            cs.activeWorkshopNumber = getInt();
    }
    cout << "Введите показатель эффективности: ";
    cs.efficiency = getInt();
    cout << "[Компрессорная станция добавлена]" << endl;
    return cs;
}

void editPipe(pipe pipe) {

    cout << "[Редактирование трубы]" << endl
        << "Труба с id " << pipe.id << " в ремонте?(Y/N): ";
    pipe.isInRepair = confirm();
    cout << "[Изменения внесены]" << endl;
    
}

void editCs(cs& cs) {

    cout << "[Редактирование компрессорной станции]" << endl
        << "КС с id " << cs.id << " (" << cs.name << ")" << endl;
    do {
        cout << "Введите количество активных цехов: ";
        cs.activeWorkshopNumber = getInt();
    } while (cs.activeWorkshopNumber > cs.workShopNumber);
    cout << "Введите оценку эффективности: ";
    cs.efficiency = getInt();
    cout << "[Изменения внесены]" << endl;
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
        cout << "[Данные сохранены]" << endl;
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
            pipes.emplace(pipesCount, addPipe(pipesCount));
            printLine();
            break;
        case 2: // Добавление КС
            csCount++;
            css.emplace(csCount, addCs(csCount));
            printLine();
            break;
        case 3: // Просмотр элементов;
            if (pipes.empty() && pipes.empty()) {
                cout << "[Объектов нет]" << endl;
                break;
            }           
            if (!pipes.empty()) {
                cout << "[Трубы]" << endl;
                printPipeHead();
                printLine();
                for (pair<int,pipe> item : pipes) {
                    printPipe(item.second);
                    printLine();
                }
            }

            cout << "\n\n\n";

            if (!css.empty()) {
                cout << "[Компрессорные станции]" << endl;
                printHeadline(css[0]);
                printLine();
                for (pair<int, cs> item : css) {
                    printCs(item.second);
                    printLine();
                }

            break;
        case 4: // Редактирование трубы;
            if (!pipes.empty()) {
                while (true) {
                    cout << "Для выхода введите 0\nВведите id трубы: ";
                    int id = getInt();
                    if (id == 0 || pipes.find(id) == pipes.end())
                        break;
                    else
                    editPipe(pipes[getInt()]);
                }
            }
            else
                cout << "[Труб нет]" << endl;
            break;
        case 5: // Редактирование КС
            if (!css.empty()) {
                while (true) {
                    cout << "Для выхода введите 0\nВведите id КС: ";
                    int id = getInt();
                    if (id == 0 || pipes.find(id) == pipes.end())
                        break;
                    else
                        editPipe(pipes[getInt()]);
                }
            }
            else
                cout << "[Компрессорных станций нет]" << endl;
            break;
        case 6: // Сохранить
            save(pipes,css);
            break;
        case 7: // Загрузить
           load(pipes, css);
            break;
        default: 
            cout << "[Такого действия не существует]" << endl;
            break;
        }
        printLine();
        scroll();
    }
}
