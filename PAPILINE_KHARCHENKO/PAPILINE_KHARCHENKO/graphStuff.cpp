#include "graphStuff.h"
#include <set>
#include <vector>

//void getMatSmej(GTS& GTS)
//{
//	int** mat;
//	mat = new int *[GTS::ocupiedCss.size()];
//	for (int i = 0; i < GTS::ocupiedCss.size();++i) {
//		mat[i] = new int[GTS::ocupiedCss.size()];
//	}
//}


std::map<int,std::vector <int>> getMapSmej(GTS& GTS)
{
	std::map <int, std::vector<int>> mapSmej;
	for (int i : GTS::ocupiedCss)
		mapSmej[i].clear();
	for (int i : GTS::ocupiedCss)
		for (int j : GTS.css[i].outcom)
			mapSmej[i].push_back(destination(GTS,j));
	return mapSmej;
}

int destination(GTS& GTS,int pipeId)
{
	for (auto& i : GTS.css) {
		for (int j : i.second.incom) {
			if (j == pipeId) return i.first;
		}
	}
}

void eraseVer(std::map<int, std::vector<int>>& map, int idVer) {
	map.erase(idVer);
	bool deleted;
	for (auto& i : map) {
		int index = 0;
		deleted = false;
		for (int j : i.second) {
			if (j == idVer) {
				deleted = true;
				break;
			}
			index++;
		}
		if (deleted) i.second.erase(i.second.begin() + index);
	}
}

std::map<int, int> topSort(GTS& GTS)
{
	std::map <int, int> result;
	bool cycled = false;
	int n = GTS::ocupiedCss.size();
	std::map <int, std::vector<int>> mapSmej = getMapSmej(GTS);
	int minDeg;
	int minSize = 30000;
	while (n != 0) {
		for (auto& i : mapSmej) {
			if (i.second.size() < minSize) {
				minDeg = i.first;
				minSize = i.second.size();
			}
		}
		result[minDeg] = n--;
		eraseVer(mapSmej, minDeg);
		for (auto& i : mapSmej) {
			if (i.second.size() == 0) { cycled = false; break; }
			else { cycled = true; }
		}
		if (cycled) { 
			result.clear();
			std::cout << "[В системе присутствует цикл]" << std::endl;
			return result;
		}
		minSize = 30000;
	}
	std::map <int, int> swaped_result;
	for (auto& i : result)
		swaped_result.emplace(i.second,i.first);
	
	return swaped_result;
}


