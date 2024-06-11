#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;

vector<int> CreateArrayFromDatabase(const string& filename)
{
	ifstream file(filename);
	vector<int> result;

	if(file.is_open())
	{
		string line;
		while(getline(file, line))
		{
			if (!line.empty() && line.back() == '\n')
			{
				line = line.substr(0, line.size() - 1);
			}
			int num = stoi(line);
			result.push_back(num);
		}
		file.close();
	}
	else
	{
		cerr << "Unable to open file: " << filename << endl;
	}
	return result;
}

void writeDatasetToFile(vector<int> array, const std::string& filename)
{
	ofstream file(filename);

	if (file.is_open())
	{
		for(size_t i = 0; i < array.size(); i++)
		{
			file << array[i] << endl;
		}
		file.close();
		cout << "Data written to " << filename << "\n";
	}
	else
	{
		cerr << "Unable to open file\n";
	}
}

void selectionSort(vector<int> &array)
{
	int n = array.size();
	for(int i = n-1; i > 0; i--)
	{
		int maxIndex = i;
		for(int j = 0; j < i; j++)
		{
			if(array[j] > array[maxIndex])
			{
				maxIndex = j;
			}
		}

		if(maxIndex != i)
		{
			swap(array[i], array[maxIndex]);
		}
	}
}