#pragma once
#include <unordered_map>
#include "pipe.h"
#include "cs.h"
#include <set>

class GTS
{
	public:
	std::unordered_map<int, pipe> pipes;
	std::unordered_map<int, cs> css;
	void save();
	void load();

	static std::set<int> ocupiedPipes;
	static std::set<int> ocupiedCss;

	void connect(int outCs, int pipe, int inCs);
	void disconnect(int outCs, int inCs);

};

