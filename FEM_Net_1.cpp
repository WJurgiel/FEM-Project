#include "FEM_Net_1.h"

#include <iomanip>

FEM_Net_1::FEM_Net_1(const FileContent& fileContent) {
	bool isNodeSection = false;
	bool isElementSection = false;
	bool isBC = false;
	for (const auto& line : fileContent) {
		FileContent tokens = split(line, ' ');
		
		if (tokens[0] == "*Node") {
			isNodeSection = true;
			isElementSection = false;
			isBC = false;
			continue;
		}
		if (tokens[0] == "*Element,") {
			isNodeSection = false;
			isElementSection = true;
			isBC = false;
			continue;
		}
		if (tokens[0] == "*BC") {
			isNodeSection = false;
			isElementSection = false;
			isBC = true;
		}
		if (isNodeSection) {
			std::stringstream ss(line);
			std::vector<double> node;
			double x, y;
			char other;
			int index;
			ss >> index >> other >> x >>other >> y; //check if it does it correctly
			node.push_back(x);
			node.push_back(y);
			nodes.push_back(node);
		}
		if (isElementSection) {
			std::stringstream ss(line);
			std::vector<int> elems = std::vector<int>(5, 0);
			char comma;
			ss >> elems[0] >> comma >> elems[1] >> comma >> elems[2] >> comma >> elems[3] >> comma >> elems[4];
			elems.erase(elems.begin());
			elements.push_back(elems);
		}
		if (isBC) {
			std::stringstream ss(line);
			int bcVal;
			char comma;
			while (ss >> bcVal) {
				bc.push_back(bcVal);
				ss >> comma;
			}
		}
		if (!isNodeSection && !isElementSection && !isBC) {
			int value = std::stoi(tokens[1]);
			configParams[tokens[0]] = value;
		}
		
	}
	
}
FileContent FEM_Net_1::split(const std::string& str, char delimeter) {
	std::stringstream ss(str);
	std::string token;
	std::vector<std::string> tokens;
	while (std::getline(ss, token, delimeter)) {
		tokens.push_back(token);
	}
	return tokens;
}
void FEM_Net_1::printData() {
	std::cout << "-----------------------------\n";
	std::cout << "Config info:\n";
	for (const auto& [key, value] : configParams) {
		std::cout <<"> " << key << ": " << value << "\n";
	}
	std::cout << "\nID:\t\tNodes:\t\t\tElements:\n";
	std::cout << "----------------------------------------------------------------------\n";
	int id = 1;
	for (auto& x : nodes) {
		std::cout << "|[" << std::setw(4) << id << " ]| ";
		for (auto& y : x) {
			std::cout << std::setw(10) << std::setprecision(10) << y << "\t";
		}
		
		if (id <= elements.size()) {
			for (auto& x : elements[id-1]) {
				std::cout << std::setw(3) << x << "\t";
			}
		}
		id++;
		std::cout << "|\n";
		std::cout << "----------------------------------------------------------------------\n";


	}
	std::cout << "BC:\n";
	for (const auto& i : bc) {
		std::cout << i << "\t";
	}


}