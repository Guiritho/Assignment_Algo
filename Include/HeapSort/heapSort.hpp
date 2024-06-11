#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;

template <typename T>
class PriorityQueue {
	vector<T> A;

	void heapify_enqueue(int index);
	void heapify_dequeue(int index);

public:
	void enqueue(T element);
	T dequeue();
	int size();
	void print();
	int get(int index);
};

PriorityQueue<int> CreateHeapFromDatabase(const string& filename);

void writeDatasetToFile(PriorityQueue<int> heap, const std::string& filename);

void dequeueAll(PriorityQueue<int> heap);

#endif //HEAPSORT_HPP