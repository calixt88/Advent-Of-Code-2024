/*
Advent of Code - 2024
Day 1: Historian Hysteria

Author: Calixt Charlebois
GitHub: https://github.com/calixt88/Advent-Of-Code-2024
License: MIT

This program is a solution to the Advent of Code [Year], Day [Day Number] challenge.
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
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdlib.h>   

int calculateTotalDistance(std::vector<int> list1, std::vector<int> list2);
int calculateSimilarityScore(std::vector<int> list1, std::vector<int> list2);

int main() {

    int totalDistance = 0;
    int similarityScore = 0;
    std::vector<int> firstValues;
    std::vector<int> secondValues;

    // Open the file
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return 1;
    }

    // Read and store values
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int first, second;
        if (iss >> first >> second) {
            firstValues.push_back(first);
            secondValues.push_back(second);
        } else {
            std::cerr << "Error: Malformed line in file: " << line << std::endl;
        }
    }
    inputFile.close();

    totalDistance = calculateTotalDistance(firstValues, secondValues);
    similarityScore = calculateSimilarityScore(firstValues, secondValues);

    std::cout << "The total distance is " << totalDistance << "." << std::endl;        
    std::cout << "The similarity score is " << similarityScore << "." << std::endl;     

    std::ofstream outputFile("answers.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to write the answers to answers.txt." << std::endl;
        return 1;
    } else {
        // Write the answers to the file
        outputFile << "The total distance is " << totalDistance << ".\n";
        outputFile << "The similarity score is " << similarityScore << ".\n";

        // Close the file
        outputFile.close();

        std::cout << "The Answers have been written to answers.txt sucessfully.";
    }

    return 0;
}


/*
Function: calculateTotalDistance
Description:
    Calculates the total distance between corresponding elements of two lists.
    the lists are first sorted in ascending order. The distance is defined as the
    sum of the absolute differences between corresponding elements.
Parameters:
    - list1: First vector of integers
    - list2: Second vector of integers
Returns:
    - The total distance as an integer. If the sizes of the lists differ, returns 0.
*/
int calculateTotalDistance(std::vector<int> list1, std::vector<int> list2) {

    int distance = 0;

    // Verify the lists are the same size
    if(list1.size() != list2.size()){
        return 0;
    }

    // Sort both vectors
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    // Calculate the total distance
    for(int i = 0; i < list1.size(); i++) {
        int temp = abs(list1[i] - list2[i]);
        distance = distance + temp;
    }

    return distance;
}

/*
Function: calculateSimilarityScore
Description:
    Calculates a similarity score between two lists of integers. For each element
    in the first list, the function checks how many times it appears in the second list.
    the score is the sum of all similarities, weighted by the element values in list1.
Parameters:
    - list1: First vector of integers
    - list2: Second vector of integers
Returns:
    - The similarity score as an integer. If the sizes of the lists differ, returns 0.
*/
int calculateSimilarityScore(std::vector<int> list1, std::vector<int> list2) {

    int similarity = 0;
    int totalSimilarity = 0;

    // Verify the lists are the same size
    if(list1.size() != list2.size()){
        return 0;
    }

    // Calculate Similarity Score
    for(int i = 0; i < list1.size() + 1; i++) {
        if(i != 0) {
            totalSimilarity = totalSimilarity + (similarity * list1[i - 1]);
            similarity = 0;
        }
        for(int j = 0; j < list1.size(); j++) {
            if(list1[i] == list2[j]){
                similarity += 1;
            }
        }
    }

    return totalSimilarity;
}