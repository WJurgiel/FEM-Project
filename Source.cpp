#include <string>
#include <sstream>
#include <thread>
#include <atomic>

#include "File.h"


using vector = std::vector<double>;
std::unique_ptr<std::fstream> file;
std::vector<std::string> fileContent;
std::atomic<bool> running(true);


void inputLoop();
std::vector<std::string> getCommand();



int main() {
	std::cout << "Enter a command. Type 'help' for user manual.\n";
	
	inputLoop();
	return 0;
}

void inputLoop() {
	while (running) {
		std::cout << "! ";
		std::vector<std::string> command = getCommand();
		executeCommand(command, file, fileContent);
	}
}
