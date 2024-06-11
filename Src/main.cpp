#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <string>
#include <chrono>
#include <stdexcept>
#include <sstream>
#include <cstdio>

#include "../Include/DataSet1/dataSet1.hpp"
#include "../Include/DataSet2/dataSet2.hpp"
#include "../Include/HeapSort/heapSort.hpp"
#include "../Include/SelectionSort/selectionSort.hpp"
#include "../Include/Dijkstra/dijkstra.hpp"
#include "../Include/Knapsack/knapsack.hpp"
#include "../Include/Kruskal/kruskal.hpp"

using namespace std;
using namespace std::chrono;

long long TransformID(const char* ID)
{
	const int IDsize = 10;
	char result[IDsize + 1]; // +1 for null terminator

	for(int i = 0; i < IDsize; i++)
	{
		if (!isdigit(ID[i]))
		{
			int tmp = static_cast<int>(ID[i]) % 10;
			result[i] = static_cast<char>('0' + tmp);
		} 
		else
		{
			result[i] = ID[i];
		}
	}
	result[IDsize] = '\0'; // Null-terminate the string

	long long StudentID = atoll(result);	

	if(StudentID < 999999999 || StudentID > 9999999999)
	{
		throw invalid_argument("False StudentID");
	}

	return StudentID;
}

void PrintStudentID(vector<long long> StudentID, int numberOfStudent)
{
	cout << "StudentID of the leader: " << StudentID[0] << endl;
	for(int i = 1; i < numberOfStudent; i++)
	{
		cout << "Student ID: " << StudentID[i] << endl;
	}
}

vector<long long> GetStudentID(int numberOfStudents)
{
	vector<long long> StudentID;
	string ID;

	cout << "Student ID of your leader: ";
	cin >> ID;
	if(!ID.empty())
		cin.ignore();
	else
		throw invalid_argument("Empty ID");
	StudentID.push_back(TransformID(ID.c_str()));

	for(int i = 1; i < numberOfStudents; i++)
	{
		cout << "Other Student ID: ";
		cin >> ID;
		if(!ID.empty())
			cin.ignore();
		else
			throw invalid_argument("Empty ID");
		StudentID.push_back(TransformID(ID.c_str()));
	}

	return StudentID;
}



void makeDataSet1(long long LeaderID)
{
	if (LeaderID < 999999999 || LeaderID > 9999999999)
	{
		throw invalid_argument("Seed isn't a valid student ID");
	}

	for(int Set = 1; Set <= 6; Set++)
	{
		int numPoints = 100;

		for(int i = 0; i < Set-1; i++)
		{
			numPoints*=10;
		}
		if(Set == 5) numPoints/=2;
		if(Set == 6) numPoints/=10;

		// Write the generated random data to a file
		string filename = "Output/DataSet1/dataSet" + to_string(Set) + ".txt";
		generateDataWithSeed(LeaderID, numPoints, filename);
	}
}

void makeDataSet2(long long StudentsID, vector<Star>& stars, vector<pair<Star, Star>>& routes)
{
	if (StudentsID < 999999999 || StudentsID > 9999999999)
	{
		throw invalid_argument("Seed isn't a valid student ID");
	}
	
	generateDatasetWithSeed(stars, routes, StudentsID);

	string txt_filename = "Output/DataSet2/dataSet.txt";
	writeDatasetToFile(stars, routes, txt_filename);


	string dot_filename = "Output/DataSet2/dataSet.dot";
	createUndirectedGraphDotFile(routes, dot_filename);

	string png_filename = "Output/DataSet2/Universe.png";
	generateGraphImage(dot_filename, png_filename);
}

void makeHeapSort()
{
	string filename;
	string heap_filename;
	PriorityQueue<int> heap;

	for(int i = 1; i < 7; i++)
	{
		filename = "Output/DataSet1/dataSet" + to_string(i) +".txt";

		auto start = high_resolution_clock::now();
		heap = CreateHeapFromDatabase(filename);
		auto stop = high_resolution_clock::now();

		auto duration = duration_cast<microseconds>(stop - start);
		cout << "The amount of time to create the heap with the Set : DataSet" << i << ".txt is " << duration.count() << " ms" << endl;

		heap_filename = "Output/HeapSort/HeapSet" + to_string(i) + ".txt";
		writeDatasetToFile(heap, heap_filename);

		start = high_resolution_clock::now();
		dequeueAll(heap);
		stop = high_resolution_clock::now();

		duration = duration_cast<microseconds>(stop - start);
		cout << "The amount of time to dequeue all the heap with the Set : DataSet" << i << ".txt is " << duration.count() << " ms" << endl;
	}
}

void makeSelectionSort()
{
	string filename;
	string selection_filename;
	vector<int> array;

	for(int i = 1; i < 7; i++)
	{
		filename = "Output/DataSet1/dataSet" + to_string(i) +".txt";

		array = CreateArrayFromDatabase(filename);

		auto start = high_resolution_clock::now();
		selectionSort(array);
		auto stop = high_resolution_clock::now();

		auto duration = duration_cast<microseconds>(stop - start);
		cout << "The time to sort the dataSet : " << i << " is " << duration.count() << " ms." << endl;

		selection_filename = "Output/SelectionSort/SelectionSort" + to_string(i) + ".txt";
		writeDatasetToFile(array, selection_filename);
	}
}

vector<int> makeDijkstra(vector<pair<Star, Star>>& routes)
{
	vector<vector<int>> Adj_M = CreateAdjacencyMatrix(routes);

	pair<vector<int>, vector<vector<int>>> pair = Dijkstra(Adj_M, 0);

	string dot_filename = "Output/Dijkstra/shortest_paths.dot";
	CreateDotFile(pair.first, pair.second, dot_filename, Adj_M);

	string graph_filename = "Output/Dijkstra/shortest_paths.png";

	generateGraphImage(dot_filename, graph_filename);
	
	CreateTxtFileWithDistance(pair.first);

	return pair.first;
}

void makeKruskal(vector<pair<Star, Star>>& routes)
{
	vector<Edge> edges = CreateAllEdges(routes);

	int V = 20; //A --> T

	vector<Edge> MST = KruskalMST(edges, V);

	string dot_filename = "Output/Kruskal/MTS.dot"; 
	convertToDot(MST, dot_filename);	

	string graph_filename = "Output/Kruskal/MST.png";
	generateGraphImage(dot_filename, graph_filename);

	CreateTxtFileMST(MST);
}

void makeKnapsack(vector<Star>& stars)
{
	int capacity = 800;

	vector<Star> chosenStars = Knapsack(stars, capacity);

	string filename = "Output/Knapsack/chosenStars.txt";

	CreateTxtFileChosenStars(chosenStars, filename);
}

void makeAll(vector<long long> StudentID, int numberOfStudents)
{
	//Get the Leader's ID
	long long LeaderID = StudentID[0];

	//Make all sets with the dataset1
	cout << endl;
	cout << "Creation of DataSets:" << endl; 
	makeDataSet1(LeaderID);

	//Get the sum of all Id
	long long StudentIDSum = 0;
	for(int i = 0; i < numberOfStudents; i++)
	{
		StudentIDSum+= StudentID[i];
	}
	cout << endl;

	//Make the dataset of stars
	vector<Star> stars;
	vector<pair<Star, Star>> routes;
	cout << "Creation of Star DataSet:" << endl;
	makeDataSet2(StudentIDSum, stars, routes);
	cout << endl;
	
	//Make HeapSort with all the Set
	cout << "HeapSort :" <<endl;
	makeHeapSort();
	cout << endl;

	//Make SelectionSort with all the Set
	cout << "SelectionSort :" << endl;
	/* 
	#=============================
	Don't remove '//' before makeSelectionSort()

	It takes ~=20 minutes
	#=============================
	*/
	makeSelectionSort();

	cout << "Dijkstra: " << endl;
	vector<int> result = makeDijkstra(routes);
	cout << endl;

	cout << "Kruskal:" << endl;
	makeKruskal(routes);
	cout << endl;

	cout << "Knapsack:" << endl;
	makeKnapsack(stars);
}

int main(int argc, char** argv)
{
	vector<long long> StudentID;
	StudentID.push_back(2419724082);
	StudentID.push_back(1211103146);
	StudentID.push_back(1191202880);
	StudentID.push_back(1211104262);

	int numberOfStudents = 4;

	if(argc != 2)
	{
		PrintStudentID(StudentID, numberOfStudents);
		makeAll(StudentID, numberOfStudents);
		return 0;
	}
	else if(argc == 2)
	{
		StudentID.clear();

		numberOfStudents = atoi(argv[1]);

		if(numberOfStudents < 3 || numberOfStudents > 4)
		{
			throw invalid_argument("Invalid Argument");
		}

		//Put all ID in a vector
		StudentID = GetStudentID(numberOfStudents);

		makeAll(StudentID, numberOfStudents);
		return 0;
	}
	return 0;
}