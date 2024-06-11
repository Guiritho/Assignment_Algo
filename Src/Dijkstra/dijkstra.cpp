#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits.h>

#include "../../Include/DataSet2/dataSet2.hpp"

using namespace std;

//Matrix size
#define rows 20
#define columns 20

//Create Adjacency matrix from Universe (Graph with 20 stars)
vector<vector<int>> CreateAdjacencyMatrix(vector<pair<Star, Star>> routes)
{
	vector<vector<int>> Adj_M(rows, vector<int>(columns, -1));

	int tmp_Star1;
	int tmp_Star2;

	for(size_t i = 0; i < routes.size(); i++)
	{
		//Compute the distance between each star
		Star star1 = routes[i].first;
		Star star2 = routes[i].second;
		double distance_d = sqrt(pow(double(star2.x - star1.x), 2.0) + pow(double(star2.y - star1.y), 2.0) + pow(double(star2.z - star1.z), 2.0));

		//Add the distance in the adjacency matrix
		tmp_Star1 = static_cast<int>(star1.name[0]) - 65;
		tmp_Star2 = static_cast<int>(star2.name[0]) - 65;

		int distance_i = static_cast<int>(distance_d);

		Adj_M[tmp_Star1][tmp_Star2] = distance_i;
		Adj_M[tmp_Star2][tmp_Star1] = distance_i;
	}

	return Adj_M;
}

int minDistance(vector<int> dist, vector<bool> M)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int j = 0; j < rows; j++)
		if (M[j] == false && dist[j] <= min)
			min = dist[j], min_index = j;

	return min_index;
}


//Function to execute Dijkstra Algorithm
pair<vector<int>, vector<vector<int>>> Dijkstra(const vector<vector<int>>& Adj_M, int start)
{
    vector<bool> M(rows, false);
    vector<int> dist(rows, INT_MAX);
    vector<vector<int>> paths(rows);

    dist[start] = 0;

    for(int i = 0; i < rows-1; i++)
    {
        int min_dist = minDistance(dist, M);
        M[min_dist] = true;

        for(int j = 0; j < rows; j++)
        {
            if(!M[j] && Adj_M[min_dist][j] != -1
                && dist[min_dist] != INT_MAX
                && dist[min_dist] + Adj_M[min_dist][j] < dist[j])
            {
                dist[j] = dist[min_dist] + Adj_M[min_dist][j];
                paths[j] = paths[min_dist];
                paths[j].push_back(min_dist);
            }
        }
    }

    return make_pair(dist, paths);
}

//Function to build the .dot file from Dijkstra's result
void CreateDotFile(const vector<int>& dist, const vector<vector<int>>& paths, const string& fileName, const vector<vector<int>>& Adj_M)
{
    ofstream dotFile(fileName);
    if (!dotFile)
    {
        cerr << "Error: Unable to create .dot file." << endl;
        exit(EXIT_FAILURE);
    }

    dotFile << "graph shortest_paths {" << endl;

    for(int i = 0; i < rows; i++)
    {
        if(dist[i] != INT_MAX)
        {
            for(size_t j = 0; j < paths[i].size(); j++)
            {
				if(Adj_M[paths[i][j]][i] != -1)
                	dotFile << "\t" << static_cast<char>(paths[i][j] + 65) << " -- " << static_cast<char>(i + 65) << " [label=\"" << Adj_M[paths[i][j]][i] << "\"];" << endl;
            }
        }
    }

    dotFile << "}" << endl;

    dotFile.close();
}

//Function to write all shortest paths in a text file
void CreateTxtFileWithDistance(vector<int> distance)
{
	string filename = "Output/Dijkstra/shortest_paths.txt";
	
	//Open the .txt file for writing
	ofstream txtFile(filename);
	if (!txtFile)
	{
		cerr << "Error: Unable to create .txt file." << endl;
		exit(EXIT_FAILURE);
	}

	txtFile << "Src\tdest\tShortest Distance" << endl;

	for(size_t i = 0; i < distance.size(); i++)
	{
		txtFile << " A\t " << static_cast<char>(i + 65) << "\t\t\t\t" << distance[i] << endl;
	}

	txtFile.close();
	cout << "Data written to " << filename << endl;
}