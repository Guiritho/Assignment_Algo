#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

#include "../../Include/DataSet2/dataSet2.hpp"

using namespace std;

//Structure to represent an edge
struct Edge {
	int src, dest, distance;
};

//Structure to represent a subset for Union-Find
struct Subset {
	int parent, rank;
};

vector<Edge> CreateAllEdges(vector<pair<Star, Star>> routes)
{
	vector<Edge> edges;

	for(size_t i = 0; i < routes.size(); i++)
	{
		//Compute the distance between each star
		Star star1 = routes[i].first;
		Star star2 = routes[i].second;
		double distance = sqrt(pow(double(star2.x - star1.x), 2.0) + pow(double(star2.y - star1.y), 2.0) + pow(double(star2.z - star1.z), 2.0));

		Edge edge;
		edge.src = static_cast<int>(star1.name[0])-65;
		edge.dest = static_cast<int>(star2.name[0])-65;
		edge.distance = static_cast<int>(distance);

		edges.push_back(edge);
	}

	return edges;
}

void EdgesSort(vector<Edge> &edges)
{
	int n = edges.size();

	for(int i = n-1; i > 0; i--)
	{
		int maxIndex = i;
		for(int j = 0; j < i; j++)
		{
			if(edges[j].distance > edges[maxIndex].distance)
			{
				maxIndex = j;
			}
		}

		if(maxIndex != i)
		{
			swap(edges[i], edges[maxIndex]);
		}
	}
}

//Find operation for Union-Find
int find(vector<Subset>& subsets, int i)
{
	if(subsets[i].parent != i)
	{
		subsets[i].parent = find(subsets, subsets[i].parent);
	}
	return subsets[i].parent;
}

//Union operation for Union-Find
void Union(vector<Subset>& subsets, int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	if(subsets[xroot].rank < subsets[yroot].rank)
	{
		subsets[xroot].parent = yroot;
	}
	else if(subsets[xroot].rank > subsets[yroot].rank)
	{
		subsets[yroot].parent = xroot;
	}
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

vector<Edge> KruskalMST(vector<Edge>& edges, int V)
{
	int n = edges.size();
	vector<Edge> MST;
	vector<Subset> subsets(V);

	for(int i = 0; i < V; i++)
	{
		subsets[i].parent = i;
		subsets[i].rank = 0;
	}

	EdgesSort(edges);

	int e = 0, i = 0;
	while(e < V-1 && i < n)
	{
		Edge next_edge = edges[i++];

		int x = find(subsets, next_edge.src);
		int y = find(subsets, next_edge.dest);

		if(x != y)
		{
			MST.push_back(next_edge);
			Union(subsets, x, y);
			e++;
		}
	}

	return MST;
}

void convertToDot(const vector<Edge>& MST, string filename)
{
	ofstream dotFile(filename);

	if(dotFile.is_open())
	{
		dotFile << "graph MST {" << endl;
		for(const Edge& edge : MST)
		{
			dotFile << "\t" << static_cast<char>(edge.src+65) << " -- " << static_cast<char>(edge.dest+65) << " [label=\"" << edge.distance << "\"];" << endl;
		}
		dotFile << "}\n";
		dotFile.close();

		cout << "The .dot file of the minimum spanning tree has been successfully created." << endl;
	}
	else
	{
		cerr << "Error: Unable to open .dot file." << endl;
		filename.clear();	
	}
}

void CreateTxtFileMST(vector<Edge>& MST)
{
	string filename = "Output/Kruskal/MST.txt";
	
	//Open the .txt file for writing
	ofstream txtFile(filename);
	if (!txtFile)
	{
		cerr << "Error: Unable to create .txt file." << endl;
		exit(EXIT_FAILURE);
	}

	txtFile << "Src\tdest\tDistance" << endl;

	for(const Edge& edge : MST)
	{
		txtFile << static_cast<char>(edge.src + 65) << " " << static_cast<char>(edge.dest + 65) << "\t\t\t" << edge.distance << endl;
	}

	txtFile.close();
	cout << "Data written to " << filename << endl;
}