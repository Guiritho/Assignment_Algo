#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

#include "../../Include/DataSet2/dataSet2.hpp"

using namespace std;

//Function to solve knapsack problem
vector<Star> Knapsack(vector<Star>& stars, int capacity)
{
	int n = stars.size();  //Number of stars

	//Create a 2D vector to store results of subproblems. dp[i][w] will store maximum
	//profit that can be obtained with weight limit w and using only the first i items
	vector<vector<int>> dp(n+1, vector<int>(capacity+1, 0));

	//Fill the dp array using bottom-up dynamic programming
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= capacity; ++j)
		{
			if (stars[i-1].weight <= j)
			{
				//If the current star can be included, choose the maximum between including
				//it and excluding it
				dp[i][j] = max(stars[i-1].profit + dp[i-1][j-stars[i-1].weight], dp[i-1][j]);
			}
			else
			{
				//If the current star cannot be included, then just exclude it
				dp[i][j] = dp[i-1][j];
			}
		}
	}

	//Retrieve the chosen stars from the dp array
	int res = dp[n][capacity];  //Maximum profit
	int w = capacity;           //Remaining weight
	vector<Star> chosenStars; //Vector to store chosen stars

	for (int i = n; i > 0 && res > 0; --i)
	{
		if (res != dp[i - 1][w])
		{
			//If the current star was chosen, add it to the list of chosen stars
			chosenStars.push_back(stars[i-1]);

			// Update remaining profit and weight
			res -= stars[i-1].profit;
			w -= stars[i-1].weight;
		}
	}

	//Reverse the order of chosen stars since we iterated backwards
	reverse(chosenStars.begin(), chosenStars.end());

	return chosenStars;
}

void CreateTxtFileChosenStars(vector<Star>& chosenStars, string filename)
{
	//Write output to file
	ofstream outputFile(filename); //Open a file for writing

	if (outputFile.is_open())
	{
		//Write chosen stars along with their weights and profits to the file
		for (const auto& star : chosenStars)
		{
			outputFile << star.name << " Weight: " << star.weight << " Profit: " << star.profit << "\n";
		}
		outputFile.close(); //Close the file
		cout << "Data written to " << filename << endl;
	}
	else
	{
		cerr << "Unable to open file for writing."; //Error message if file cannot be opened
	}
}