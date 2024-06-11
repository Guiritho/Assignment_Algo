#ifndef SELECTIONSORT_HPP
#define SELECTIONSORT_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;

vector<int> CreateArrayFromDatabase(const string& filename);

void writeDatasetToFile(vector<int> array, const std::string& filename);

void selectionSort(vector<int> &array);

#endif //SELECTIONSORT_HPP