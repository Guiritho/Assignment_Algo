#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <stdexcept>

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
			try
			{
				if(!line.empty() && line.back() == '\n') 
				{
					line.pop_back();
				}
				int num = stoi(line);
				result.push_back(num);
			}
			catch(const invalid_argument&) //Added exception handling
			{
				cerr << "Invalid number format: " << line << endl;
			}
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

	if(file.is_open())
	{
		for(const auto& elem : array)
		{
			file << elem << endl;
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