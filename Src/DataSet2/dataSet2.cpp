#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

#include "../../Include/DataSet1/dataSet1.hpp"

//Define a structure for representing a star
struct Star
{
	std::string name;
	int x, y, z;
	int weight;
	int profit;
};

std::vector<int> CreateNumbers(long long seed, std::vector<int> NumberToAvoid)
{
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> distribution(0, 500);

	std::vector<int> result;

	int i = 0;
	while(i != 100)
	{
		int tmp;
		do
		{
			tmp = distribution(generator);
		}while(!Contains(NumberToAvoid, tmp));
		
		result.push_back(tmp);
		i++;
	}

	return result;
}

//Function to generate a dataset of stars and routes
void generateDatasetWithSeed(std::vector<Star>& stars, std::vector<std::pair<Star, Star>>& routes, long long seed)
{
	std::mt19937 generator(seed);

	std::vector<int> NumberToAvoid = ContainsNumber(seed);

	std::vector<int> randomNumbers = CreateNumbers(seed, NumberToAvoid);

	//Generate 20 stars
	for(int i = 0; i < 20; i++)
	{
		char tmp = i+65;
		std::string name;
		name += tmp;

		int k = 5*i;
		int x = randomNumbers[k];
		int y = randomNumbers[k+1];
		int z = randomNumbers[k+2];
		int weight = randomNumbers[k+3];
		int profit = randomNumbers[k+4];
		stars.push_back({name, x, y, z, weight, profit});
	}

	//Connect each star to at least 3 other stars to create 54 routes
	std::vector<Star> allstar;
	for(const auto& star : stars)
	{
		allstar.push_back(star);
	}
	for(const auto& star : stars)
	{
		std::shuffle(allstar.begin(), allstar.end(), generator);
		for(int i = 0; i < 3; ++i)
		{
			if(star.name != allstar[i].name)
				routes.push_back({star, allstar[i]});
			else
				routes.push_back({star, allstar[19-i]});
		}   
	}
}

//Function to write the dataset in a text file
void writeDatasetToFile(const std::vector<Star>& stars, const std::vector<std::pair<Star, Star>>& routes, std::string filename)
{
	std::ofstream file(filename);

	if (file.is_open())
	{
		file << "Star Name\t X\t Y\t Z\tWeight\tProfit\n";
		for (const auto& star : stars)
		{
			file << "\t" <<star.name << "\t\t" << star.x << "\t" << star.y << "\t" << star.z << "\t  " << star.weight << "\t " << star.profit << "\n";
		}
		file << "\nRoutes:\n";
		for (const auto& route : routes)
		{
			file << route.first.name << " -> " << route.second.name << "\n";
		}
		file.close();
		std::cout << "Dataset written to " << filename << "\n";
	}
	else
	{
		std::cerr << "Unable to open file\n";
	}
}

//Function to write the dataset in a .dot file
void createUndirectedGraphDotFile(const std::vector<std::pair<Star, Star>>& routes, std::string filename)
{
	std::ofstream file(filename);
	
	if(file.is_open())
	{
		file << "graph G {\n";
		for (const auto& route : routes)
		{
			double distance = sqrt(pow(double(route.second.x - route.first.x), 2.0) + pow(double(route.second.y - route.first.y), 2.0) + pow(double(route.second.z - route.first.z), 2.0));
			file << "\t" << route.first.name << " -- " << route.second.name << " [label=\"" << static_cast<int>(distance) << "\"];\n";
		}
		file << "}\n";
		file.close();
		std::cout << "Undirected graph DOT file created: " << filename << std::endl;
	}
	else
	{
		std::cerr << "Unable to create undirected graph DOT file." << std::endl;
		filename.clear(); //Return an empty string if file creation fails
	}
}

//Function to generate a graph image from a DOT file using Graphviz
void generateGraphImage(const std::string& dotFile, std::string filename)
{
	std::string command = "dot -Tpng " + dotFile + " -o " + filename;
	int result = std::system(command.c_str());

	if (result == 0)
	{
		std::cout << "Undirected graph image created: " << filename << std::endl;
	}
	else
	{
		std::cerr << "Failed to generate undirected graph image." << std::endl;
	}
}