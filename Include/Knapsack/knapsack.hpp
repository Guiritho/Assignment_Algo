#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP

#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

#include "../DataSet2/dataSet2.hpp"

using namespace std;

vector<vector<int>> generate2DArray(vector<Star> stars, int capacity);

vector<Star> Knapsack(vector<Star> stars, vector<vector<int>> dp, int capacity);

void CreateTxtFileChosenStars(vector<Star>& chosenStars, string filename);

void CreateCSVFileMatrix(vector<vector<int>>& dp, string filename);

#endif //KNAPSACK_HPP