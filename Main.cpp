/*
 * Main.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: Adaire
 */

#include "BucketSort.h"
#include <random>
#include <iostream>
#include <iomanip>		// for setw() stream formatting
#include <fstream>		// for file i/o
using std::vector;

vector<int> generateList(int numElements, std::mt19937& generator); // @suppress("Type cannot be resolved")
void toTableFile(std::vector<double> meanResults);

int main(){
	// Generate a seed for the generator
	std::random_device rd; // @suppress("Type cannot be resolved")
	//Create the generator using the mersenne twister engine and the previously generated seed
	std::mt19937 generator(rd()); // @suppress("Type cannot be resolved")
	// numElements must be evenly divisible by 128.  Shorter durations than 4096 are not recommended, as duration will be too short (and thus counted as 0 duration on Windows with MinGW64 Compiler)
	int numElements = 65536;
	vector<int> list = generateList(numElements, generator);

	// Determine the mean runtime for 0, 2, and 4 threads
	vector<double> meanDurationVector(3); // index i is the mean duration for 2^i threads
	int numTrials = 100;
	for(int j = 0; j <=4; j += 2){ // j = numthreads
		// Sort numTrials times with j threads and store resulting BucketSort objects in a vector
		//vector<BucketSort> zeroThreads(numTrials);
		vector<int> durations(numTrials);
		for(int i = 0; i < numTrials; i++){
			//zeroThreads.push_back(BucketSort(list, j));
			BucketSort tempSort = BucketSort(list, j);
			//durations.push_back(tempSort.getTimeElapsed());
			durations[i] = tempSort.getTimeElapsed();
			//std::cout << tempSort.getTimeElapsed() << " " << durations[i] << "\n";
		}
		// Calculate the average runtime for j threads
		double meanDuration = 0.0;
		for(int i = 0; i < numTrials; i++){
			//meanDuration += (zeroThreads[i].getTimeElapsed())/100.0;
			double temp = double((durations[i]))/(double)(numTrials);
			meanDuration += temp;
			//std::cout << "Duration: " << durations[i] << " numTrials: " << numTrials << " term: "<< temp << "\n";
		}
		// Store the mean runtime for i threads in index log2(j) of meanDurationVector
		// Note that this is in microseconds (us)
		if(j == 0){
			meanDurationVector[0] = meanDuration;
		}else if (j == 2){
			meanDurationVector[1] = meanDuration;
		}else{ // j == 4
			meanDurationVector[2] = meanDuration;
		}
	}

	// Save the results in "results_table.txt"
	toTableFile(meanDurationVector);

	for(int i = 0; i < 3; i++){
		std::cout << "2^i Threads: " << i << " Mean Duration (us): " << meanDurationVector[i] << "\n";
	}

	/*std::cout << "Sort Complete\n";
	if(sorted.isSorted()){
		std::cout << "Success!";
	}else{
		std::cout << "Failure!";
	}
	std::cout << " Sort successful: " << sorted.isSorted();*/
	return 0;
}

/*Generates a random list from a Uniform(0, numElements) distribution
 * @param numElements the number of elements to generate
 * @param generator the mersenne twister engine to use
 * @return a vector of integers drawn from the Uniform(0, numElements) distribution
 */
vector<int> generateList(int numElements, std::mt19937& generator){ // @suppress("Type cannot be resolved")

	vector<int> list(numElements);

	//Create a uniform_real_distribution object for the interval [1, numElements]
	std::uniform_real_distribution<double> dist(1, numElements + 1); // @suppress("Type cannot be resolved") // @suppress("Symbol is not resolved")

	for(int i = 0; i < numElements; i++){
		list[i] = int(dist(generator))%numElements;
	}

	return list;
}

/*Appends the mean run times for 0, 2, and 4 threads to the file "results_table.txt"
 * */
void toTableFile(std::vector<double> meanResults){

	// If the file is empty, the table header will have to be added
	bool isEmpty = false;
	std::ifstream testFile;
	testFile.open("results_table.txt");
	if(testFile.peek() == std::ifstream::traits_type::eof()){
		isEmpty = true;
	}
	testFile.close();

	std::ofstream resultsTable;
	resultsTable.open("results_table.txt", std::ios::app);
	if(resultsTable.is_open()){
		// If the table was found to be empty, print the table header
		if(isEmpty){
			resultsTable << "0 Threads Runtime (us)"; //22
			resultsTable << std::setw(24) << "2 Threads Runtime (us)"; // 15
			resultsTable << std::setw(24) << "4 Threads Runtime (us)"; // 15
		}
		//print to file
		resultsTable << "\n" << std::setw(22) << meanResults[0];
		resultsTable << std::setw(24) << meanResults[1];
		resultsTable << std::setw(24) << meanResults[2];
	}
	resultsTable.close();
}

