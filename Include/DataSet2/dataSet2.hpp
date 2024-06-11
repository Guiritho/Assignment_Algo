#ifndef DATASET2_HPP
#define DATASET2_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

//Define a structure for representing a star
struct Star
{
	std::string name;
	int x, y, z;
	int weight;
	int profit;
};

void generateDatasetWithSeed(std::vector<Star>& stars, std::vector<std::pair<Star, Star>>& routes, long long seed);

void writeDatasetToFile(const std::vector<Star>& stars, const std::vector<std::pair<Star, Star>>& routes, std::string filename);

void createUndirectedGraphDotFile(const std::vector<std::pair<Star, Star>>& routes, std::string filename);

void generateGraphImage(const std::string& dotFile, std::string filename);


#endif //DATASET2_HPP