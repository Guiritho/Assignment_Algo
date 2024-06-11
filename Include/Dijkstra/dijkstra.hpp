#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits.h>

#include "../DataSet2/dataSet2.hpp"

using namespace std;

vector<vector<int>> CreateAdjacencyMatrix(vector<pair<Star, Star>> routes);

int minDistance(vector<int> dist, vector<bool> M);

pair<vector<int>, vector<vector<int>>> Dijkstra(const vector<vector<int>>& Adj_M, int start);

void CreateDotFile(const vector<int>& dist, const vector<vector<int>>& paths, const string& fileName, const vector<vector<int>>& Adj_M);

void CreateTxtFileWithDistance(vector<int> distance);

#endif //DIJKSTRA_HPP