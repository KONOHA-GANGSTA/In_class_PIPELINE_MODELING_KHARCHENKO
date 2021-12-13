#pragma once
#include "GTS.h"
#include <map>
#include <vector>

//void getMatSmej(GTS& GTS);

std::map <int, std::vector<int>> getMapSmej(GTS& GTS);

int destination(GTS& GTS,int pipeId);

std::map<int, int> topSort(GTS& GTS);

void eraseVer(std::map<int, std::vector<int>>& map, int idVer);