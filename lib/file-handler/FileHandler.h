//
// Created by Wojtek on 10.11.2024.
//

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Element.h"
#include <iostream>
#include <filesystem>
#include <fstream>
/*
 File handler should contain methods to:
 * create directory hierarchy if not created Output/H_final/ etc.
 * save output to file
 * clear directory (if current_files_to_create < files_in_directory)
 *
 */
class FileHandler {
private:
    static bool writeSaveTemperatureHeader;
public:
    static void initDirectories();
    static void clearOutputDirectory();
    static void createDirectory(std::string path);
    static void clearFile(std::string path);

    //add flag CLEAR == false if you add two or more things to one file, (to prevent deletion previous input)
    static void saveToFile(std::string path, Element content, Vector<Jacobian> vecToSave, int nip, bool CLEAR = true);
    static void saveToFile(std::string path, Element content, Matrix<double>, std::string matrixName, int nip, bool CLEAR = true);
    static void saveTemperatures(std::string path, Vector<double> temperatures, int nodecount, double simTime, double stepTime);
};




#endif //FILEHANDLER_H
