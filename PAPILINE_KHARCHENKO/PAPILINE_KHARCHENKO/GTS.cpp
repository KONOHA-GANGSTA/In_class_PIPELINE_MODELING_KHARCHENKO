#include "GTS.h"
#include <fstream>
#include "utils.h"

void GTS::save() {
    if ((this->pipes.empty()) && (this->css.empty()))
        return;
    std::ofstream file;
    file.open(getFileName() + ".txt");
    if (file.good()) {
        file << this->pipes.size() << endl << this->pipes.size() << endl;
        for (auto& i : this->pipes)
            file << "pipe" << endl << i.second;

        for (auto& i : this->css)
            file << "cs" << endl << i.second;

        file.close();
        cout << "[Данные сохранены]" << endl;
    }
}

void GTS::load()
{
    this->pipes.clear();
    this->css.clear();
    ifstream file;
    file.open(getFileName() + ".txt", ios::in);
    if (file.good()) {
        string str;
        getline(file, str);
        this->pipes.reserve(stoi(str));
        getline(file, str);
        this->css.reserve(stoi(str));
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
                this->css.emplace(cs.getId(), cs);
            }
        }
        cout << "[Данные загружены]" << endl;
    }
    file.close();
}
