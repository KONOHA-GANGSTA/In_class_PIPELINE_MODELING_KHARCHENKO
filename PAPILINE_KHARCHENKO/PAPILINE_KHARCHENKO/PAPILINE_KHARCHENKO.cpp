
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
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

void printHeadline(const pipe& pipe) {

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

bool isIdOcupied(const vector <pipe>& pipes, int id) {
    if (pipes.size() == 0)
        return false;
    for (pipe i: pipes) {
        if (i.id == id)
            return true;
    }
    return false;
}

bool isIdOcupied(const vector <cs>& css, int id) {
    if (css.size() == 0)
        return false;
    for (cs i : css) {
        if (i.id == id)
            return true;
    }
    return false;
}

int getIndex(const vector <pipe>& pipes, pipe pipe) {
    
    for (int i =0; i < pipes.size(); i++) {
        if (pipes[i].id == pipe.id)
            return i;
        else
            return 0;
    }
}

int getIndex(const vector <cs>& css, cs cs) {

    for (int i = 0; i < css.size(); i++) {
        if (css[i].id == cs.id)
            return i;
        else
            return 0;
    }
}

pipe addPipe(const vector <pipe>& pipes) {

    cout << "[Добавление трубы]" << endl;
    pipe pipe;
    do pipe.id = rand();
    while (isIdOcupied(pipes, pipe.id));
    cout << "Введите длину: ";
    pipe.length = getDouble();
    cout << "Введите диаметр: ";
    pipe.diametr = getInt();
    cout << "Сейчас в ремонте? (Y/N): ";
    pipe.isInRepair = confirm();
    cout << "[Труба добавлена]" << endl;
    return pipe;
}

cs addCs(const vector <cs>& css) {

    cout << "[Добавление КС]" << endl;
    cs cs;
    do cs.id = rand();
    while (isIdOcupied(css, cs.id));
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

pipe& getPipe( vector <pipe> pipes, int id) {
    
    while (true) {
        for (pipe i : pipes)
            if (i.id == id)
                return i;
        cout << "[Трубы с таким id несуществует]" << endl;
        cout << "Введите новый id: ";
        id = getInt();
    }
}

cs& getCs(vector <cs> css, int id) {

    while (true) {
        for (cs i : css)
            if (i.id == id)
                return i;
        cout << "[КС с таким id несуществует]" << endl;
        cout << "Введите новый id: ";
        id = getInt();
    }
}

void editPipe(pipe& pipe) {

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

void save(vector <pipe> pipes, vector <cs> css) {
    if ((pipes.size() == 0) && (css.size() == 0))
        return;
    ofstream file;
    file.open("objects.txt");
    if (file.good()) {
        {

            for (pipe i : pipes) {
                file << "pipe" << endl
                    << i.id << endl
                    << i.length << endl
                    << i.diametr << endl
                    << i.isInRepair << endl;
            }
        }

        {
            for (cs i : css) {
                file << "cs" << endl
                    << i.id << endl
                    << i.name << endl
                    << i.workShopNumber << endl
                    << i.activeWorkshopNumber << endl
                    << i.efficiency << endl;
            }
        }
        file.close();
        cout << "[Данные сохранены]" << endl;
    }
}

void load(vector <pipe>& pipes, vector <cs>& css) {

    pipes.clear();
    css.resize(0);
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
                pipes.push_back(pipe);
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
                css.push_back(cs);
            }
        }
        cout << "[Данные загружены]" << endl;
    }
    file.close();
}


int main()
{   
    setlocale(LC_ALL, "Russian");

    vector <pipe> pipes;
    vector <cs> css;

    load(pipes,css);

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
            pipes.push_back(addPipe(pipes));
            printLine();
            break;
        case 2: // Добавление КС
            css.push_back(addCs(css));
            printLine();
            break;
        case 3: // Просмотр элементов;
            if (pipes.size() == 0 && css.size() == 0) {
                cout << "[Объектов нет]" << endl;
                break;
            }           
            if (pipes.size() != 0) {
                cout << "[Трубы]" << endl;
                printHeadline(pipes[0]);
                printLine();
                for (int i = 0; i <= pipes.size() - 1; i++) {
                    printPipe(pipes[i]);
                    printLine();
                }
            }

            cout << "\n\n\n";

            if (css.size() != 0) {
                cout << "[Компрессорные станции]" << endl;
                printHeadline(css[0]);
                printLine();
                for (int i = 0; i <= css.size() - 1; i++) {
                    printCs(css[i]);
                    printLine();
                }
            }

            break;
        case 4: // Редактирование трубы;
            if (pipes.size() > 0) {
                cout << "Введите id трубы: ";
                auto checkPipe = getPipe(pipes, getInt());
                editPipe(checkPipe);
            }
            else
                cout << "[Труб нет]" << endl;
            break;
        case 5: // Редактирование КС
            if (css.size() > 0) {
                cout << "Введите id компрессорной станции: ";
                auto checkCs = getCs(css, getInt());
                editCs(checkCs);
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
