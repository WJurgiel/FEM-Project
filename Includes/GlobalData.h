//
// Created by Wojtek on 24.10.2024.
//

#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include "Includes.h"

class GlobalData {
private:
    std::unordered_map<std::string, int> parameters;


public:
    GlobalData();
    void setParameter(std::string key, int value);
    int getParameter(std::string key);

    friend std::ostream& operator<<(std::ostream& os, const GlobalData& obj);
};
// After assuring that the calculations work fine, add methods to read from file

inline std::ostream& operator<<(std::ostream& os, const GlobalData& obj) {
    for(auto& param : obj.parameters) {
        os << param.first << ": " << param.second << std::endl;
    }
    return os;
}
#endif //GLOBALDATA_H
