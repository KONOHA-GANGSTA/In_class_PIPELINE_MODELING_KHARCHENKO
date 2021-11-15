#pragma once
#include "pipe.h"
#include <iostream>
#include "utils.h"
#include <string>
using namespace std;

unsigned int pipe::max_id = 0;

pipe::pipe():id(++pipe::max_id)
{
}


pipe::~pipe()
{
    //pipe::count--;
}

void pipe::edit(int id)
{
    cout << "[Редактирование трубы]" << endl
        << "Труба с id " << id << " в ремонте?(Y/N): ";
    this -> isInRepair = confirm();
    cout << "[Изменения внесены]" << endl;
}

void pipe::printHead()
{
    printLine();
    cout << "|\tId"
        << "\t|\tДлина"
        << "\t|\tДиаметр"
        << "\t|\tВ ремонте"
        << "\t|" << endl;
}

bool pipe::checkCondition(const pipe& pipe, bool condition)
{
    return pipe.isInRepair == condition;
}

bool pipe::checkDiam(const pipe& pipe, int diam)
{
    return diam == pipe.diametr;
}

pipe& pipe::create(pipe& pipe)
{
    cout << "[Добавление трубы]" << endl;
    cout << "Введите длину: ";
    pipe.length = getDouble();
    cout << "Введите диаметр: ";
    pipe.diametr = getInt();
    cout << "Сейчас в ремонте? (Y/N): ";
    pipe.isInRepair = confirm();
    cout << "[Труба добавлена]" << endl;
    return pipe;
}

ostream& operator << (ostream& out, const pipe& pipe) {
    
        out << "|\t" << pipe.id
        << "\t|\t" << pipe.length
        << "\t|\t" << pipe.diametr
        << "\t|\t" << pipe.isInRepair
        << "\t\t|" << endl;
        return out;
}

istream& operator >> (istream& file, pipe& pipe) {

    string value;
    getline(file, value);
    pipe.id = stoi(getOneParam(value));
    pipe.length = stod(DotToComma(getOneParam(value)));
    pipe.diametr = stoi(getOneParam(value));
    (getOneParam(value) == "1") ? pipe.isInRepair = true : pipe.isInRepair = false;
    return file;
}
