#include "utils.h"


string DotToComma(string str) {

    if (str.find(".") != string::npos)
        return str.replace(str.find("."), 1, ",");
    else return str;

}

int getInt() {

    while (true) {
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

string getFileName() {
    string fileName;
    string incorrectSymbols[16] = { " ","~","#","%","&","*","{","}","/",":","<",">","?","+","|","." };
    while (true) {
        cout << "Введите имя файла:" << endl;
        getline(cin, fileName);
        for (string i : incorrectSymbols) {
            while (fileName.find(i) != string::npos) {
                fileName.erase(fileName.find(i), 1);
            }
        }
        if (fileName == "") continue;
        cout << endl;
        return fileName;
    }
}

string getOneParam(string& str) {
    string sub;
    if (str.find("|") == 0)
        str.erase(0, 1);
    sub = str.substr(0, str.find("|") + 1);
    str.erase(0, sub.length());
    sub.erase(sub.length() - 1, 1);
    while (true) {
        if (sub.find("\t") == 0)
            sub.erase(0, 1);
        else if (sub.find_last_of("\t") == sub.length()-1)
            sub.erase(sub.length() - 1, 1);
        else
            return sub;
    }
}

void printLine() {
    for (int i = 0; i <= 100; i++) {
        cout << "_";
    }
    cout << endl;
}