#include "File.h"

std::string WORKING_DIR = ".";
std::string WORKING_FILE = "";

std::unique_ptr<std::fstream> openFile(const std::string& _name) {
	auto file = std::make_unique<std::fstream>();
	
	file->open(_name, std::ios_base::in);
	if (!file->is_open()) {
		std::cerr << "[ERROR]: Could not open file: " << _name << ".\n";
	}
	return file;
}
std::vector<std::string> storeFileContent(std::unique_ptr<std::fstream>& _file) {
	std::string line;
	std::vector<std::string> fileContent;
	try {
		while (std::getline((*_file), line)) {
			fileContent.push_back(line);
		}
		_file->close();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
	}
	return fileContent;

}
void clearScreen() {
#ifdef _WIN32
	std::system("cls");
#else
	std::sytem("clear");
#endif
}
std::vector<std::string> getCommand() {
	std::string userInput;
	std::getline(std::cin, userInput);


	std::vector<std::string> result;


	std::stringstream ss(userInput);
	std::string word;
	while (ss >> word) result.push_back(word);

	return result;
}
void executeCommand(std::vector<std::string> tokens, std::unique_ptr<std::fstream>& file, std::vector<std::string>& fileContent) {
	if (tokens.empty()) return;

	std::string command = tokens[0];
	if (command == "cd") {
		if (tokens.size() > 1) {
			std::string directory = tokens[1];
			cd(directory);
		}
		else {
			std::cerr << "[ERROR]: 'cd' requires a <<directory>> argument.\n";
		}
	}
	else if (command == "ls") {
		ls();
	}
	else if (command == "exec") {
		if (tokens.size() > 1) {
			std::string fileName = tokens[1];
			exec(fileName, file, fileContent);
		}
		else {
			std::cerr << "[ERROR]: 'exec' requires a <<file>> argument.\n";
		}
	}
	else if (command == "cls") {
		clearScreen();
	}
	else if (command == "help") {
		std::cout << "Default WORKING_DIR is \".\" \nBe careful while ";
		std::cout << "List of commands:\n"
			<< "> ls - list.txt files in WORKING_DIR\n"
			<< "> cd <<directory>> - change WORKING_DIR \n"
			<< "> exec <<file_name>> - start work on the file, file must be in the WORKING_DIR\n"
			<< "> clr - clear terminal screen\n"
			<< "> exit - close program\n";
	}
	else if (command == "exit") {
		exit(0);
	}
	else {
		std::cerr << "[ERROR]: Uknown command.\n";
	}
}
void ls() {
	std::cout << "DIR: " << WORKING_DIR << "\n";
	try {
		for (const auto& entry : fs::directory_iterator(WORKING_DIR)) {
			if (entry.is_regular_file() && entry.path().extension() == ".txt")
				std::cout << "> " << entry.path().filename() << "\n";
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
	}
	
}
void cd(const std::string& _newDir) {
	WORKING_DIR = _newDir;
	std::cout << "[LOG] Working directory changed to: " << WORKING_DIR << "\n";
}
void exec(const std::string& _fileName, std::unique_ptr<std::fstream>& file, std::vector<std::string>& fileContent) {
	WORKING_FILE = (WORKING_DIR == ".") ? "" : WORKING_DIR + "\\" + _fileName;
	std::cout << "working on file: " << WORKING_FILE << "\n";
	
	file = openFile(WORKING_FILE);

	fileContent.clear();
	if (file) {
		fileContent = storeFileContent(file);
		for (const auto& line : fileContent) {
			std::cout << line << "\n";  // Example output of file content
		}
	}

}