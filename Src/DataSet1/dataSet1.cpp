#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>

std::vector<int> ContainsNumber(long long seed)
{
	std::vector<int> numbers(10, 0);
	while(seed != 0)
	{
		int tmp = seed%10;
		seed/=10;
		numbers.at(tmp) +=1;
	}

	std::vector<int> result;
	for(size_t i = 0; i < numbers.size(); i++)
	{
		if(numbers.at(i) == 0)
		{
			result.push_back(i);
		}
	}
	return result;
}

bool Contains(std::vector<int> numbersToAvoid, int number)
{
	while (number != 0)
	{
		int CurrentNumber = number % 10;
		for(size_t i = 0; i < numbersToAvoid.size(); i++)
		{
			if (CurrentNumber == numbersToAvoid.at(i)) 
			{
				return 0;
			}
		}
		number /= 10;
	}
	return 1;
}

void generateDataWithSeed(long long seed, int numPoints, const std::string& filename)
{
	//Set the seed for the random number generator
	std::mt19937 generator(seed);

	//Generate random integer data points
	std::uniform_int_distribution<int> distribution(0, 500);

	std::ofstream file(filename); 
	//Create & open a file named filename for writing

	if (file.is_open())
	{
		std::vector<int> NumberToAvoid = ContainsNumber(seed);

		int i = 0;
		while(i < numPoints)
		{
			int tmp = distribution(generator);
			
			if(Contains(NumberToAvoid, tmp))
			{
				i++;
				file << tmp << std::endl;
			}
		}

		file.close();
		std::cout << "Data written to " << filename << std::endl;
	}
	else
	{
		std::cerr << "Unable to open file: " << filename << std::endl;
	}
}