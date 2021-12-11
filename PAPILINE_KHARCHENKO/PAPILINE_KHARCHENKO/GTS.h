#pragma once
#include <unordered_map>
#include "pipe.h"
#include "cs.h"

class GTS
{
	public:
	std::unordered_map<int, pipe> pipes;
	std::unordered_map<int, cs> css;
	void save();
	void load();

};

