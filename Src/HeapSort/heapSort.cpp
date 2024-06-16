#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <stdexcept>

using namespace std;

template <typename T>
class PriorityQueue
{
	vector<T> A;
	
	void heapify_enqueue(size_t index) // used in heapify enqueue.
	{
		if (index == 0) // if already at root.
			return;

		// parent index
		size_t p_index = (index-1)/2;

		// swap if parent is smaller
		if (A[p_index] < A[index])
		{
			swap(A[p_index], A[index]);
			// recursion of the function
			heapify_enqueue(p_index);
		}
	}

	void heapify_dequeue(int index)
	{
		size_t greatest = index; // max index

		// left child index
		size_t left_c = 2*index+1;

		// right child index
		size_t right_c = 2*index+2;

		// compare and find the greatest child
		if(left_c < A.size() && A[left_c] > A[greatest])
		{
			greatest = left_c;
		}
		if (right_c < A.size() && A[right_c] > A[greatest])
		{
			greatest = right_c;
		}

		if (greatest != index)
		{
			swap(A[index], A[greatest]);
			heapify_dequeue(greatest); // recursion
		}
	}

	public:
	void enqueue(T element) 
	{
		A.push_back(element);
		heapify_enqueue(A.size()-1); // start at last element.
	}

	T dequeue()
	{
		if(A.empty()) 
		{
			throw out_of_range("Heap is empty");
		}
		T removed_element = A[0];
		A[0] = A[A.size()-1];
		A.pop_back();
		if(!A.empty())
		{
			heapify_dequeue(0);  // 0 is a valid size_t value
		}
		return removed_element;
	}

	size_t size() 
	{
		return A.size();
	}

	int get(int index)
	{
		if (index >= A.size())
		{
			throw out_of_range("Index out of range");
		}
		return A.at(index);
	}
};

PriorityQueue<int> CreateHeapFromDatabase(const string& filename)
{
	ifstream file(filename);
	PriorityQueue<int> result;

	if(file.is_open())
	{
		string line;
		while(getline(file, line))
		{
			if(!line.empty() && line.back() == '\n')
			{
				line.pop_back();
			}
			try
			{
				int num = stoi(line);
				result.enqueue(num);
			}
			catch(const invalid_argument&)
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

void writeDatasetToFile(PriorityQueue<int> heap, const string& filename)
{
	ofstream file(filename);

	if(file.is_open())
	{
		for(size_t i = 0; i < heap.size(); i++)
		{
			file << heap.get(i) << endl;
		}
		file.close();
		cout << "Data written to " << filename << "\n";
	}
	else
	{
		cerr << "Unable to open file\n";
	}
}

void dequeueAll(PriorityQueue<int> heap)
{
	while(heap.size() > 0)
	{
		heap.dequeue();
	}
}