/*
Advent of Code - 2024
Day 2: Red-Nosed Reports

Author: Calixt Charlebois
GitHub: https://github.com/calixt88/Advent-Of-Code-2024
License: MIT

This program is a solution to the Advent of Code 2024, Day 2 challenge.
For more information on the challenge, visit: https://adventofcode.com/[Year]/day/[Day Number]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

int calculateSafeReports(const std::vector<std::vector<int> >& reports);
int calculateSafeReportsRemovingOne(const std::vector<std::vector<int> >& reports);

int main() {
    int totalSafeReports = 0;
    int totalSafeReportsRemovingOne = 0;
    std::vector<std::vector<int> > reports;
    std::vector<int> report;

    // Open input file
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return 1;
    }

    // Read and store values
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream stream(line);
        int num;
        while (stream >> num) {
            report.push_back(num);
        }
        reports.push_back(report);
        report.clear();
    }
    inputFile.close();

    // Calculate the number of "safe" reports
    totalSafeReports = calculateSafeReports(reports);
    totalSafeReportsRemovingOne = calculateSafeReportsRemovingOne(reports);


    std::cout << "The total safe reports: " << totalSafeReports << "." << std::endl;
    std::cout << "The total safe reports with removing one: " << totalSafeReportsRemovingOne << "." << std::endl;

    // Write results to answers.txt
    std::ofstream outputFile("answers.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to write the answers to answers.txt." << std::endl;
        return 1;
    } else {
        outputFile << "The total safe reports: " << totalSafeReports << ".\n";
        outputFile << "The total safe reports with removing one: " << totalSafeReportsRemovingOne << ".";
        outputFile.close();
        std::cout << "The Answers have been written to answers.txt successfully.\n";
    }

    return 0;
}

/*
Function: calculateSafeReports
Description:
    Determines how many reports are "safe" based on the following rules:
    - A report must be strictly increasing or strictly decreasing.
    - The difference between consecutive elements must not exceed 3.
    - Consecutive elements cannot be equal.
Parameters:
    - reports: A vector of vectors, where each inner vector represents a report.
Returns:
    - The total count of safe reports.
*/
int calculateSafeReports(const std::vector<std::vector<int> >& reports) {
    int safeReports = 0;

    for (int i = 0; i < reports.size(); ++i) {
        bool isDecreasing = true;
        bool isIncreasing = true;
        bool safe = true;

        for (int j = 0; j < reports[i].size() - 1; ++j) {
            if (reports[i][j] == reports[i][j + 1]) {
                safe = false;
                break;
            }
            if (std::abs(reports[i][j] - reports[i][j + 1]) > 3) {
                safe = false;
                break;
            }
            if (reports[i][j + 1] > reports[i][j]) {
                isDecreasing = false;
            }
            if (reports[i][j + 1] < reports[i][j]) {
                isIncreasing = false;
            }
        }

        if (safe && (isIncreasing || isDecreasing)) {
            ++safeReports;
        }
    }

    return safeReports;
}

/*
Function: calculateSafeReportsRemovingOne
Description:
    Determines how many reports are "safe" based on the following rules:
    - A report must be strictly increasing or strictly decreasing.
    - The difference between consecutive elements must not exceed 3.
    - Consecutive elements cannot be equal.
    - If you were to remove one level, it would then be "safe".
Parameters:
    - reports: A vector of vectors, where each inner vector represents a report.
Returns:
    - The total count of safe reports, including those that can become safe by removing one level.
*/
int calculateSafeReportsRemovingOne(const std::vector<std::vector<int> >& reports) {
    int safeReports = 0;

    for (int i = 0; i < reports.size(); ++i) {
        bool isDecreasing = true;
        bool isIncreasing = true;
        bool safe = true;

        for (int j = 0; j < reports[i].size() - 1; ++j) {
            if (reports[i][j] == reports[i][j + 1]) {
                safe = false;
                break;
            }
            if (std::abs(reports[i][j] - reports[i][j + 1]) > 3) {
                safe = false;
                break;
            }
            if (reports[i][j + 1] > reports[i][j]) {
                isDecreasing = false;
            }
            if (reports[i][j + 1] < reports[i][j]) {
                isIncreasing = false;
            }
        }

        if (safe && (isIncreasing || isDecreasing)) {
            safeReports++;
            continue; 
        }

        // Check if removing one element makes the report safe
        for (int removeIndex = 0; removeIndex < reports[i].size(); ++removeIndex) {
            std::vector<int> modifiedReport;
            for (int k = 0; k < reports[i].size(); ++k) {
                if (k != removeIndex) {
                    modifiedReport.push_back(reports[i][k]);
                }
            }

            isDecreasing = true;
            isIncreasing = true;
            safe = true;

            for (int j = 0; j < modifiedReport.size() - 1; ++j) {
                if (modifiedReport[j] == modifiedReport[j + 1]) {
                    safe = false;
                    break;
                }
                if (std::abs(modifiedReport[j] - modifiedReport[j + 1]) > 3) {
                    safe = false;
                    break;
                }
                if (modifiedReport[j + 1] > modifiedReport[j]) {
                    isDecreasing = false;
                }
                if (modifiedReport[j + 1] < modifiedReport[j]) {
                    isIncreasing = false;
                }
            }

            if (safe && (isIncreasing || isDecreasing)) {
                safeReports++;
                break; 
            }
        }
    }

    return safeReports;
}
