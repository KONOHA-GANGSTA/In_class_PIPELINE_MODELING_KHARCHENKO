
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

pipe addPipe() {

    cout << "[Добавление трубы]" << endl;
    pipe pipe;
    pipe.id = 1;
    cout << "Введите длину: ";
    pipe.length = getDouble();
    cout << "Введите диаметр: ";
    pipe.diametr = getInt();
    cout << "Сейчас в ремонте? (Y/N): ";
    pipe.isInRepair = confirm();
    return pipe;

}

cs addCs() {

    cout << "[Добавление КС]" << endl;
    cs cs;
    cs.id = 1;
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
    return cs;
}

int main()
{   
    setlocale(LC_ALL, "Russian");

    vector <pipe> pipes;
    vector <cs> css;
    cout << "\t\t\tДобро пожаловать в систему моделирования трубопроводного транспорта" << endl;
    cout << "\t\t\t\t\t\t (©) Харченко АА-20-05 2021г.\n\n\n";

    while (true) {
       
        printMenu();
        cout << "Выберите действие: ";
        int choice = getInt();
        
        switch (choice)
        {
        case 0: // Выход
            return 0;
            break;
        case 1: // Добавление трубы
            pipes.push_back(addPipe());
            break;
        case 2: // Добавление КС
            css.push_back(addCs());
            break;
        case 3: // Просмотр элементов;
            break;
        case 4: // Редактирование трубы;
            break;
        case 5: // Редактирование КС
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
    }

}
