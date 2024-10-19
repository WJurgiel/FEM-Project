#pragma once
#include "Includes.h"
#include <unordered_map>

using Node = std::vector<std::vector<double>>;
using Element = std::vector<std::vector<int>>;
using BC = std::vector<int>;
using FileContent = std::vector<std::string>;

class FEM_Net_1
{
private:
	std::unordered_map<std::string, int> configParams;
	
	Node nodes;
	Element elements;
	BC bc;

	FileContent split(const std::string& str, char delimeter);
public:
	FEM_Net_1(const FileContent& fileContent);
	void printData();
};

