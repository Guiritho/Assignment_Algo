#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

#include "../../Include/DataSet2/dataSet2.hpp"

using namespace std;

vector<vector<int>> generate2DArray(vector<Star> stars, int capacity) 
{
	int numStars = stars.size();  //Number of stars

	// Create a 2D vector to store results of subproblems. dp[i][w] will store maximum profit that can be obtained
	// with weight limit w and using only the first i stars
	vector<vector<int>> dp(numStars+1, vector<int>(capacity+1, 0));

	// Fill the dp array using bottom-up dynamic programming
	for (int i = 1; i <= numStars; ++i) //for each row (star)
	{
		int currentProfit = stars[i-1].profit;
		int currentWeight = stars[i-1].weight;

		for (int j = 1; j <= capacity; ++j) // for each column (capacity)
		{
			if (stars[i-1].weight <= j) // if star can be included (i.e. weight less than or equal to capacity)
			{
				// Choose the maximum value between including it and excluding it
				dp[i][j] = max(currentProfit + dp[i-1][j-currentWeight], dp[i-1][j]);
			}
			else //If the current star cannot be included, then just exclude it
			{
				dp[i][j] = dp[i-1][j];
			}
		}
	}

	return dp;
}

vector<Star> Knapsack(vector<Star> stars, vector<vector<int>> dp, int capacity)
{
	int numStars = stars.size();  // Number of stars

	// Retrieve the chosen stars from the dp array
	int result = dp[numStars][capacity];   // Start at last cell which is maximum profit
	int remWeight = capacity;              // Remaining weight
	vector<Star> chosenStars;              // Vector to store chosen stars

	for (int i = numStars; i > 0 ; --i) // For each star 
	{
		if (result != dp[i-1][remWeight])	// Check if star was chosen by comparing to previous (if not, do nothing)
		{
			// Add it to the list of chosen stars
			chosenStars.push_back(stars[i-1]);

			// Update remaining profit and weight
			result -= stars[i-1].profit;
			remWeight -= stars[i-1].weight;
		}
	}

	//Reverse the order of chosen stars since we iterated backwards
	reverse(chosenStars.begin(), chosenStars.end());

	return chosenStars;
}

void CreateCSVFileMatrix(vector<vector<int>>& dp, string filename) {
	ofstream outputFile(filename);

	if (outputFile.is_open()) 
	{
		for (int i = 1; i < dp.size(); ++i) 
		{
			for (int j = 1; j < dp[i].size(); ++j) {
				outputFile << dp[i][j] << ',';
			}
			outputFile << '\n';	
		}
		outputFile.close();
		cout << "Data written to " << filename << endl;
	}
	else
	{
		cerr << "Unable to open file for writing.";
	}
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