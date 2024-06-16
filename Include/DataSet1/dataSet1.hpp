#ifndef DATASET1_HPP
#define DATASET1_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>

std::vector<int> ContainsNumber(long long seed);

bool Contains(std::vector<int> numbersToAvoid, int number);

void generateDataWithSeed(long long seed, int numPoints, const std::string& filename);

#endif //DATASET1_HPP