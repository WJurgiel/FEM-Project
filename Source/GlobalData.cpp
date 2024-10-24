//
// Created by Wojtek on 24.10.2024.
//

#include "../Includes/GlobalData.h"

GlobalData::GlobalData() {
}

void GlobalData::setParameter(std::string key, int value) {
    parameters[key] = value;
}

int GlobalData::getParameter(std::string key) {
    try {
        return parameters[key];
    }catch(std::exception& e) {
        std::cout << "No such key has been found.\n" << std::endl;
        return -1;
    }

}
