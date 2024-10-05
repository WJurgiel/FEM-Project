#pragma once
#include "Includes.h"
namespace fs = std::filesystem;

extern std::string WORKING_DIR;
extern std::string WORKING_FILE; //file to work on, default empty
extern bool IS_EXECUTED;
std::unique_ptr<std::fstream> openFile(const std::string& _name);
std::vector<std::string> storeFileContent(std::unique_ptr<std::fstream>& _file);

std::vector<std::string> getCommand();
void executeCommand(std::vector<std::string> tokens, std::unique_ptr<std::fstream>& file, std::vector<std::string>& fileContent);


void ls();
void cd(const std::string& _newDir);
void exec(const std::string& _fileName, std::unique_ptr<std::fstream>& file, std::vector<std::string>& fileContent);
void clr();
void help();
void pwd();