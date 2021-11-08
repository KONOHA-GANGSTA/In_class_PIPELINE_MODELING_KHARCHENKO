#pragma once
#include "pipe.h"
#include <iostream>
#include "utils.h"
#include <string>
using namespace std;

unsigned int pipe::count = 0;

pipe::pipe()
{
    pipe::count+=2;
}


pipe::pipe(unsigned int id)
{
    cout << "[���������� �����]" << endl;
    this->id = id;
    cout << "������� �����: ";
    this -> length = getDouble();
    cout << "������� �������: ";
    this -> diametr = getInt();
    cout << "������ � �������? (Y/N): ";
    this -> isInRepair = confirm();
    cout << "[����� ���������]" << endl;
    pipe::count+=2;
}

pipe::~pipe()
{
    pipe::count--;
}

void pipe::edit()
{
    cout << "[�������������� �����]" << endl
        << "����� � id " << this -> id << " � �������?(Y/N): ";
    this -> isInRepair = confirm();
    cout << "[��������� �������]" << endl;
}

void pipe::printHead()
{
    printLine();
    cout << "|\tId"
        << "\t|\t�����"
        << "\t|\t�������"
        << "\t|\t� �������"
        << "\t|" << endl;
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


