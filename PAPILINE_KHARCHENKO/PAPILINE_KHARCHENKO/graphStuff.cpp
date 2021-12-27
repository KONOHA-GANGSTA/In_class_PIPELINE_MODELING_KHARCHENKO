#include "graphStuff.h"
#include <set>
#include <vector>



std::unordered_map <int, std::vector<double>> getMatWeights(GTS& GTS)
{
	std::unordered_map <int, std::vector<double>> result;
	double weight = 0;
	for (int i : GTS::ocupiedCss) {
		for (int j : GTS::ocupiedCss) {
			weight = 0;
			for (int k : GTS.css[i].outcom)
				if (destination(GTS, k) == j)
					weight = GTS.pipes[k].length;
			result[i].push_back(weight);
		}
	}
	GTS::changed = false;
	return result;
}

int toWhere(int fin, GTS& GTS) {
	int result = -1;
	for (auto& i : GTS::matWeights) {
		result++;
		if (fin == i.first) break;
	}
	return result;
}

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

std::unordered_map<int, double> dickstra(int startId, GTS& GTS)
{
	std::unordered_map<int, double> result;
	std::set <int> done;
	if (GTS::ocupiedCss.find(startId) == GTS::ocupiedCss.end()) {
		std::cout << "[В данной сети отсутствует указанная КС]" << std::endl;
		return result;
	}

	if (GTS::changed)
		GTS::matWeights = getMatWeights(GTS);
	
	for (int i : GTS::ocupiedCss) {
		if (i == startId)
			result.emplace(i, 0);
		else
			result.emplace(i, 4000000);
	}
	
	while (done.size() != result.size()) {
		double min = 4000001;
		int activeVer;
		for (auto& i : result) {
			if (done.find(i.first) != done.end())
				continue;
			if (i.second < min) {
				min = i.second;
				activeVer = i.first;
			}
		}
		int itr = 0;
		for (int i : GTS::ocupiedCss) {
			if (done.find(i) != done.end()) { itr++; continue; }
			if ((result[i] > GTS::matWeights[activeVer][itr])&(GTS::matWeights[activeVer][itr]!=0))
				if (result[i] == 4000000) result[i] = result[activeVer] + GTS::matWeights[activeVer][itr];
				else result[i] = result[activeVer]+ GTS::matWeights[activeVer][itr];
			itr++;
		}
		done.insert(activeVer);
	}
	return result;
}

std::vector<int> seqReturn(int finish, std::unordered_map<int, double> ways, GTS& GTS)
{
	std::vector <int> result,swaped_result;
	std::vector <int> possibleAncestors;
	int current = finish;
	while (ways[current] != 0) {
		std::map<int, std::vector<int>>mapSmej = getMapSmej(GTS);
		for (auto& i : mapSmej)
			for (int j : i.second)
				if (j == current)
					possibleAncestors.push_back(i.first);
		for (int i : possibleAncestors)
			if (ways[current] - GTS::matWeights[i][toWhere(current, GTS)] == ways[i]) {
				result.push_back(i);
				current = i;
				break;
			}
	}
	for (int i = result.size() - 1; i >= 0; --i) {
		swaped_result.push_back(result[i]);
	}
	return swaped_result;
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


