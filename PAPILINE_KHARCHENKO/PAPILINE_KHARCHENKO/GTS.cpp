#include "GTS.h"
#include <fstream>
#include "utils.h"
#include "graphStuff.h"

set <int> GTS::ocupiedPipes;
set<int> GTS:: ocupiedCss;
bool GTS::changed = true;
unordered_map <int, std::vector <double>> GTS::matWeights;

void GTS::save() {
    if ((this->pipes.empty()) && (this->css.empty()))
        return;
    std::ofstream file;
    file.open(getFileName() + ".txt");
    if (file.good()) {
        file << this->pipes.size() << endl << this->pipes.size() << endl;
        
        for (int i : GTS::ocupiedCss) {
            file << "|\t" << i << "\t";
        }
        file << "|" << endl;
        for (int i : GTS::ocupiedPipes) {
            file << "|\t" << i << "\t";
        }
        file << "|" << endl;

        for (auto& i : this->pipes)
            file << "pipe" << endl << i.second;

        for (auto& i : this->css) {
            file << "cs" << endl << i.second;
            for (int j : i.second.outcom)
                file << "|\t" << j << "\t";
            file << "|" << endl;
            for (int j : i.second.incom)
                file << "|\t" << j << "\t";
            file << "|" << endl;

        }

        file.close();
        cout << "[Данные сохранены]" << endl;
    }
}

void GTS::load()
{
    this->pipes.clear();
    this->css.clear();
    GTS::ocupiedCss.clear();
    GTS::ocupiedPipes.clear();
    ifstream file;
    file.open(getFileName() + ".txt", ios::in);
    if (file.good()) {
        string str;
        getline(file, str);
        this->pipes.reserve(stoi(str));
        getline(file, str);
        this->css.reserve(stoi(str));
        getline(file, str);
        while (str != "") {
            GTS::ocupiedCss.insert(stoi(getOneParam(str)));
        }
        getline(file, str);
        while (str != "") {
            GTS::ocupiedPipes.insert(stoi(getOneParam(str)));
        }
        while (!file.eof()) {
            getline(file, str);
            if (str == "pipe") {
                pipe pipe;
                file >> pipe;
                this->pipes.emplace(pipe.getId(), pipe);
            }

            if (str == "cs") {
                cs cs;
                file >> cs;
                getline(file, str);
                if(str!="|")
                while (str != "") {
                    cs.outcom.insert(stoi(getOneParam(str)));
                }

                getline(file, str);
                if (str != "|")
                    while (str != "") {
                        cs.incom.insert(stoi(getOneParam(str)));
                    }

                this->css.emplace(cs.getId(), cs);
            }
        }
        cout << "[Данные загружены]" << endl;
    }
    file.close();
    GTS::changed = true;
}

void GTS::connect(int outCs, int pipeId, int inCs)
{
    // блок проверок на все
    if ((this->pipes.find(pipeId) == this->pipes.end()) | (this->css.find(outCs) == this->css.end()) | (this->css.find(inCs) == this->css.end())) {
        cout << "[Что-то из этого не существует]" << endl;
        return;
    }

    if (GTS::ocupiedPipes.find(pipeId) != GTS::ocupiedPipes.end()) {
        cout << "[Труба уже занята]" << endl;
        return;
    }

    if (this->css[inCs].workShopNumber == (this->css[inCs].incom.size() + this->css[inCs].outcom.size())) {
        cout << "[Станции <" << this->css[inCs].name << "> нехватает мощностей]" << endl;
        return;
    }

    if (this->css[outCs].workShopNumber == (this->css[outCs].incom.size() + this->css[outCs].outcom.size())) {
        cout << "[Станции <" << this->css[outCs].name << "> нехватает мощностей]" << endl;
        return;
    }

    if (this->pipes[pipeId].isInRepair) {
        cout << "[Эта труба в ремонте]" << endl;
        return;
    }

    // конец блока проверок

    GTS::ocupiedPipes.emplace(pipeId);
    GTS::ocupiedCss.emplace(inCs);
    GTS::ocupiedCss.emplace(outCs);
    this->css[outCs].outcom.emplace(pipeId);
    this->css[inCs].incom.emplace(pipeId);
    GTS::changed = true;
    cout << "[Труба проложена]" << endl;
}

void GTS::disconnect(int outCs, int inCs)
{
    int pipeId = 0;
    bool found = false;
    for (int i : this->css[outCs].outcom) {
        for (int j : this->css[inCs].incom) {
            if (i == j) {
                pipeId = i;
                found = true;
                break;
            }
        }
        if (found) break;
    }
    if (pipeId == 0) {
        cout << "[Да они и не были соединены]" << endl;
        return;
    }
    GTS::ocupiedPipes.erase(pipeId);
    this->css[inCs].incom.erase(pipeId);
    this->css[outCs].outcom.erase(pipeId);
    if ((this->css[outCs].incom.size() == 0) & (this->css[outCs].outcom.size() == 0))
        GTS::ocupiedCss.erase(outCs);
    if ((this->css[inCs].incom.size() == 0) & (this->css[inCs].outcom.size() == 0))
        GTS::ocupiedCss.erase(inCs);
    GTS::changed = true;
    cout << "[Сообщение между станциями разорвано]" << endl;
}
