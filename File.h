#pragma once
#include <fstream>
#include <vector>
#include <filesystem>
#include <iostream>
#include <memory>
namespace fs = std::filesystem;

extern std::string WORKING_DIR;
extern std::string WORKING_FILE; //file to work on, default empty
std::unique_ptr<std::fstream> openFile(const std::string& _name);
std::vector<std::string> storeFileContent(std::unique_ptr<std::fstream>& _file);
std::unique_ptr<std::fstream> closeFile(std::string _name);

std::vector<std::string> getCommand();
void executeCommand(std::vector<std::string> tokens, std::unique_ptr<std::fstream>& file, std::vector<std::string>& fileContent);
void clearScreen();

void ls();
void cd(const std::string& _newDir);
void exec(const std::string& _fileName, std::unique_ptr<std::fstream>& file, std::vector<std::string>& fileContent);
void clr();
void help();