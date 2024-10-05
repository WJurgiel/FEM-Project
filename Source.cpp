
#include "Includes.h"
#include "File.h"
#include "FEM_Net_1.h"
using vector = std::vector<double>;

std::unique_ptr<std::fstream> file;
std::vector<std::string> fileContent;
std::atomic<bool> running(true);

void backgroundTask(bool& isExecuted) {
	//ADNOTATION: the program itself assumes that the fileContent exists, in File::exec() definition
	while (running) {
		if (isExecuted) {
			std::cout << "The task is being executed\n";
			FEM_Net_1 square(fileContent);
			square.printData();
	
			isExecuted = false;
		}
			
	}
}
void inputLoop() {
	while (running) {
		std::cout << "! ";
		std::vector<std::string> command = getCommand();
		executeCommand(command, file, fileContent);
	}
}

int main() {
	std::cout << "Enter a command. Type 'help' for user manual.\n";
	
	std::thread backgroundThread(backgroundTask, std::ref(IS_EXECUTED));
	inputLoop();
	
	backgroundThread.join();
	return 0;
}

