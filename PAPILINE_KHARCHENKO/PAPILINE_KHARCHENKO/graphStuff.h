#pragma once
#include "GTS.h"
#include <map>
#include <vector>
#include <unordered_map>

std::unordered_map <int,std::vector <double>> getMatWeights(GTS&GTS);

std::map <int, std::vector<int>> getMapSmej(GTS& GTS);

int destination(GTS& GTS,int pipeId);

std::map<int, int> topSort(GTS& GTS);

void eraseVer(std::map<int, std::vector<int>>& map, int idVer);

std::unordered_map<int, double> dickstra(int startId, GTS& GTS);

