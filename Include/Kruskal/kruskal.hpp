#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

#include "../DataSet2/dataSet2.hpp"

using namespace std;

struct Edge {
	int src, dest, distance;
};

struct Subset {
	int parent, rank;
};

vector<Edge> CreateAllEdges(vector<pair<Star, Star>> routes);

void EdgesSort(vector<Edge> &edges);

int find(vector<Subset>& subsets, int i);

void Union(vector<Subset>& subsets, int x, int y);

vector<Edge> KruskalMST(vector<Edge>& edges, int V);

void convertToDot(const vector<Edge>& MST, string filename);

void CreateTxtFileMST(vector<Edge>& MST);

#endif //KRUSKAL_HPP