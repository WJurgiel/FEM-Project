//
// Created by Wojtek on 09.11.2024.
//
#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <fstream>
TEST(GridTests, CheckFile1) {
    std::string path1 = "../../Output/H_final/H_elem_0.txt";
    std::fstream file1(path1);
    ASSERT_TRUE(file1.is_open());

    std::string line;
    std::getline(file1, line); // skip empty line
    std::getline(file1, line); // skip [---Element 0---]
    std::getline(file1, line); // skip "H"
    std::getline(file1, line); // Get 1st row
    std::stringstream lineStream(line);

    double row[4];
    lineStream >> row[0] >> row[1] >> row[2] >> row[3];

    std::string message = "Wrong value, rerun your code or fix it. Expected: ";
    ASSERT_EQ(row[0], 16.6667) << message + "16.6667" + " Provided: " + std::to_string(row[0]);
    ASSERT_EQ(row[1], -4.16666)<< message + "-4.16666"+ " Provided: " + std::to_string(row[1]);
    ASSERT_EQ(row[2], -8.33334)<< message + "8.33334"+ " Provided: " + std::to_string(row[2]);
    ASSERT_EQ(row[3], -4.16666)<< message + "4.16666"+ " Provided: " + std::to_string(row[3]);

    file1.close();
}
