#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP

#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

#include "../DataSet2/dataSet2.hpp"

using namespace std;

vector<Star> Knapsack(vector<Star>& stars, int capacity);

void CreateTxtFileChosenStars(vector<Star>& chosenStars, string filename);

#endif //KNAPSACK_HPP