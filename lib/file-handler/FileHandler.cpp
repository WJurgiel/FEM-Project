//
// Created by Wojtek on 10.11.2024.
//

#include "FileHandler.h"
// only for Vector<Jacobian> for now, template will be implemented when needed
void FileHandler::saveToFile(std::string path, Element content, Vector<Jacobian> vecToSave, int nip, bool CLEAR) {
    if(CLEAR) clearFile(path);
    std::ofstream file(path, std::ios::app);
    try {
        file << "\n\t[---Element "  << content.getID() << "---]\n";
        for(int ip = 0; ip < nip; ip++) {
            if(file.good()) {
                file << "Integration point " << ip << ":\n";
                file << vecToSave[ip];
#if DEBUG
                std::cout << "Jacobian matrixes saved to " << out_file_name << "\n";

            }else {

                std::cout << "Couldn't save Jacobian matrixes\n";
#endif
            }
        }
    }catch(std::exception& e) {
        std::cout << e.what() << "\n";
    }
    file.close();
}

void FileHandler::saveToFile(std::string path, Element content, Matrix<double> matrix, std::string matrixName, int nip, bool CLEAR) {
    if(CLEAR) clearFile(path);
    std::ofstream outFile(path, std::ios::app);
    try {
        outFile << "\n\t[---Element "  << content.getID() << "---]\n";
    }catch(std::exception& e) {
        std::cout << e.what() << "\n";
    }
    try {
#if DEBUG
        if(outFile.good()) {
            std::cout << "Matrix " << matrix_name << " saved to " << out_file_name << "\n";
        }else {
            std::cout << "Couldn't save matrix " <<matrix_name << " to " << out_file_name << "\n";
        }
#endif
        outFile << matrixName << "\n";
        for(auto& x : matrix) {
            for(auto& y : x)
                outFile << y << std::setw(10) << " ";
            outFile << "\n";
        }
        outFile << "-----------------\n\n";
    }
    catch(std::exception& e) {
        std::cout << e.what() << "\n";
    }
    outFile.close();

}

void FileHandler::initDirectories() {
    if(!std::filesystem::exists("../Output")) {
        createDirectory("../Output");
        std::cout << "[FILE HANDLER]: Output/ initialized\n";
    }

    createDirectory("../Output/Jacobian_Matrices");
    createDirectory("../Output/Hpc");
    createDirectory("../Output/H_final");
}
//It's for Output/ directory only, I don't think it will be necessary to smth else
void FileHandler::clearOutputDirectory() {
    for(const auto& entry: std::filesystem::directory_iterator("../Output/")) {
        std::filesystem::remove_all(entry.path());
    }
}

void FileHandler::createDirectory(std::string path) {
    std::filesystem::create_directory(path);
}

void FileHandler::clearFile(std::string path) {
    std::ofstream file(path, std::ios::out);
    try {
        if (file.is_open()) file << "";
    }catch(std::exception& e) {
        std::cout << e.what() << "\n";
    }
    file.close();
}


