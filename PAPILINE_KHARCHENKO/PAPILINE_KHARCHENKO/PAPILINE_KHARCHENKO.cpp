
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

void printHeadline(pipe pipe) {

    printLine();
    cout << "|\tId"
        << "\t|\tДлина"
        << "\t|\tДиаметр"
        << "\t|\tВ ремонте"
        << "\t|" << endl;
}

void printHeadline(cs cs) {

    printLine();
    cout << "|\tId"
        << "\t|\tИмя"
        << "\t|\tЦеха"
        << "\t|\tЦеха в работе"
        << "\t|\tЭффективность"
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

int getIndex(vector <pipe> pipes, pipe pipe) {
    
    for (int i =0; i <= pipes.size() - 1; i++) {
        if (pipes[i].id == pipe.id)
            return i;
        else
            return 0;
    }
}

int getIndex(vector <cs> css, cs cs) {

    for (int i = 0; i <= css.size() - 1; i++) {
        if (css[i].id == cs.id)
            return i;
        else
            return 0;
    }
}

pipe addPipe(vector <pipe> pipes) {

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
    printHeadline(pipe);
    printLine();
    printPipe(pipe);
    printLine();
    return pipe;
}

cs addCs(vector <cs> css) {

    cout << "[Добавление КС]" << endl;
    cs cs;
    do cs.id = rand();
    while (isIdOcupied(css, cs.id));
    cout << "Введите имя: ";
    string name;
    cin >> name;
    cin.ignore(32767, '\n');
    cs.name = name;
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
    printHeadline(cs);
    printLine();
    printCs(cs);
    printLine();
    return cs;
}

pipe getPipe(vector <pipe> pipes, int id) {
    
    while (true) {
        for (int i = 0; i <= pipes.size() - 1; i++)
            if (pipes[i].id == id)
                return pipes[i];
        cout << "[Трубы с таким id несуществует]" << endl;
        cout << "Введите новый id: ";
        id = getInt();
    }
}

cs getCs(vector <cs> css, int id) {

    while (true) {
        for (int i = 0; i <= css.size() - 1; i++)
            if (css[i].id == id)
                return css[i];
        cout << "[КС с таким id несуществует]" << endl;
        cout << "Введите новый id: ";
        id = getInt();
    }
}

pipe editPipe(pipe pipe) {

    cout << "[Редактирование трубы]" << endl
        << "Труба с id " << pipe.id << " в ремонте?(Y/N): ";
    pipe.isInRepair = confirm();
    cout << "[Изменения внесены]" << endl;
    printHeadline(pipe);
    printLine();
    printPipe(pipe);
    printLine();
    return pipe;
    
}

cs editCs(cs cs) {

    cout << "[Редактирование компрессорной станции]" << endl
        << "КС с id " << cs.id << " (" << cs.name << ")" << endl;
    do {
        cout << "Введите количество активных цехов: ";
        cs.activeWorkshopNumber = getInt();
    } while (cs.activeWorkshopNumber > cs.workShopNumber);
    cout << "Введите оценку эффективности: ";
    cs.efficiency = getInt();
    cout << "[Изменения внесены]" << endl;
    printHeadline(cs);
    printLine();
    printCs(cs);
    printLine();
    return cs;

}

int main()
{   
    setlocale(LC_ALL, "Russian");

    vector <pipe> pipes;
    pipe checkPipe;
    vector <cs> css;
    cs checkCs;
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
            break;
        case 2: // Добавление КС
            css.push_back(addCs(css));
            break;
        case 3: // Просмотр элементов;
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

            if (pipes.size() == 0 && css.size() == 0) {
                cout << "[Объектов нет]" << endl;
            }

            break;
        case 4: // Редактирование трубы;
            if (pipes.size() > 0) {
                cout << "Введите id трубы: ";
                checkPipe = getPipe(pipes, getInt());
                pipes[getIndex(pipes, checkPipe)] = editPipe(checkPipe);
            }
            else
                cout << "[Труб нет]" << endl;
            break;
        case 5: // Редактирование КС
            if (css.size() > 0) {
                cout << "Введите id компрессорной станции: ";
                checkCs = getCs(css, getInt());
                css[getIndex(css, checkCs)] = editCs(checkCs);
            }
            else
                cout << "[Компрессорных станций нет]" << endl;
            break;
        case 6: // Сохранить
            break;
        case 7: // Загрузить
            break;
        default: 
            cout << "[Такого действия не существует]" << endl;
            break;
        }
        printLine();
        scroll();
    }

}
