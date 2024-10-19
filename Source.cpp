
#include "Includes.h"
#include "File.h"
#include "FEM_Net_1.h"
#include "x64/Quadrature.h"
using vector = std::vector<double>;

std::unique_ptr<std::fstream> file;
std::vector<std::string> fileContent;
std::atomic<bool> running(true);

FunctionX func1 = [](double x) {
	return 5 * x * x + 3 * x + 6;
};
FunctionXY func2 = [](double x, double y) {
	return 5 * x * x * y * y + 3 * x * y + 6;
};
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
	// std::cout << "Enter a command. Type 'help' for user manual.\n";
	//
	// std::thread backgroundThread(backgroundTask, std::ref(IS_EXECUTED));
	// inputLoop();
	//
	// backgroundThread.join();
	Quadrature q(func1, func2);
	
	std::cout << "N - nodes count\n";
	std::cout << "Func1:\n";
	std::cout << "Wynik dla N = 1: " << q.Calculate1D(1) << "\n";
	std::cout << "Wynik dla N = 2: " << q.Calculate1D(2) << "\n";
	std::cout << "Wynik dla N = 3: " << q.Calculate1D(3) << "\n";
	std::cout << "Wynik dla N = 4: " << q.Calculate1D(4) << "\n";

	std::cout << "\nFunc2:\n";
	std::cout << "Wynik dla N = 1: " << q.Calculate2D(1) << "\n";
	std::cout << "Wynik dla N = 2: " << q.Calculate2D(2) << "\n";
	std::cout << "Wynik dla N = 3: " << q.Calculate2D(3) << "\n";
	std::cout << "Wynik dla N = 4: " << q.Calculate2D(4) << "\n";


	return 0;
}

