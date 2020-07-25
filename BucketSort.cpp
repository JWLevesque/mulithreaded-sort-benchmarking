/*
 * BucketSort.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: Adaire
 */

#include "BucketSort.h"
#include <thread>
#include <functional>
#include <iostream>
#include <chrono>


BucketSort::BucketSort(std::vector<int> initialList, int numThreads) : AbstractSort::AbstractSort(initialList, numThreads){

	// take start time stamp
	std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now(); // @suppress("Symbol is not resolved") // @suppress("Function cannot be resolved")

	// sort the vector
	std::vector<int> sortedList = BucketSort::sort(initialList, numThreads);

	//std::cout << "Sort has finished in the constructor.\n";
	//empty bucketList
	bucketList.clear();

	// take end time stamp
	std::chrono::time_point<std::chrono::high_resolution_clock> finish = std::chrono::high_resolution_clock::now(); // @suppress("Symbol is not resolved") // @suppress("Function cannot be resolved")

	// set timeElapsed to start-end
	BucketSort::timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count(); // @suppress("Symbol is not resolved") // @suppress("Method cannot be resolved")
	//std::cout << "Duration: " << timeElapsed << "\n";
	//check if actually sorted
	isSortSuccessful = isSortedAscending(sortedList);
	//std::cout << isSortSuccessful << std::endl;
}

/*Sorts the given initialList using bucket sort (with insertion sort for each bucket).
 * @param initialList the vector of integers to sort
 * @param numThreads the number of threads to use while sorting.  This may be either 0, 2, or 4.
 * 			Note that if a value other than 0, 2, or 4 is passed, this method defaults to 4 threads.
 * @return the sorted vector
 */
std::vector<int> BucketSort::sort(std::vector<int> initialList, int numThreads){
	int size = initialList.size();
	int numBuckets;
	if(size == 16){
		//will always be an integer
		numBuckets = size/4;
	}else{
		// will always be an integer (if not 16, numElements is a multiple of 128)
		numBuckets = size/128;
	}

	// Initialize the list of buckets
	//std::vector<Bucket> bucketList(numBuckets);
	BucketSort::bucketList = std::vector<Bucket>(numBuckets);

	if(size == 16){
		for(int i = 0; i < numBuckets; i++){
			bucketList[i] = Bucket(16);
		}
	}else{
		for(int i = 0; i < numBuckets; i++){
			bucketList[i] = Bucket(128); //originally 256
		}
	}

	// Split into buckets
	for(int i = 0; i < size; i++){
		// Normalize to [0,1] by dividing the key by size (the number of elements).
		// 		Then, multiply by numBuckets to get the appropriate bucket index.
		int bucketIndex = int((initialList[i] * numBuckets)/size);
		bucketList[bucketIndex].addToBucket(initialList[i]);
	}

	// Sort the buckets with numThreads
	if(numThreads==0){
		// Sort all nonempty buckets
		for(int i = 0; i < int(bucketList.size()); i++){
			if(bucketList[i].getNumElements() > 0){
				bucketList[i].sortBucket();
			}
		}
	}
	else if(numThreads == 2){
		//split the bucketList in two, and sort with two threads
		int min1 = 0;
		int max1 = (bucketList.size()/2)-1;
		std::thread t1(&BucketSort::sortBucketsInRange, this, min1, max1); // @suppress("Type cannot be resolved")
		std::thread t2(&BucketSort::sortBucketsInRange, this, int(bucketList.size()/2), int(bucketList.size()-1)); // @suppress("Type cannot be resolved")

		// wait until threads have finished
		t1.join(); // @suppress("Method cannot be resolved")
		t2.join(); // @suppress("Method cannot be resolved")
	}
	// Default to 4 threads
	else{
		//split the bucketList in four, and sort with four threads
		// On [0, 0.25)
		std::thread t1(&BucketSort::sortBucketsInRange, this, int(0), int((bucketList.size()/4)-1)); // @suppress("Type cannot be resolved")
		// On [0.25, 0.5)
		std::thread t2(&BucketSort::sortBucketsInRange, this, int(bucketList.size()/4), int((bucketList.size()/2)-1)); // @suppress("Type cannot be resolved")
		// On [0.5, 0.75)
		std::thread t3(&BucketSort::sortBucketsInRange, this, int(bucketList.size()/2), int((3*bucketList.size()/4)-1)); // @suppress("Type cannot be resolved") //int((bucketList.size()-1)-(bucketList.size()/4)-1)
		// On [0.75, 1]
		std::thread t4(&BucketSort::sortBucketsInRange, this, int(3*bucketList.size()/4), int(bucketList.size()-1)); // @suppress("Type cannot be resolved") //int((bucketList.size()-1)-(bucketList.size()/4))

		// wait until threads have finished
		t1.join(); // @suppress("Method cannot be resolved")
		t2.join(); // @suppress("Method cannot be resolved")
		t3.join(); // @suppress("Method cannot be resolved")
		t4.join(); // @suppress("Method cannot be resolved")
	}

	// Join the buckets
	std::vector<int> sortedList(size);
	// Iterate through the buckets
	for(int i = 0; i < int(bucketList.size()); i++){
		// Iterate through the elements in each bucket, and add them in order to sortedList
		for(int j = 0; j < bucketList[i].getNumElements(); j++){
			sortedList.push_back(bucketList[i].getBucketElements()[j]);
		}
	}

	// Return the sorted list
	return sortedList;
}

/*Private helper method for BucketSort::sort() which sorts all buckets in the given range.
 * @param minIndex the index of the first bucket to sort
 * @param maxIndex the index of the last bucket to sort
 * @param bucketList the vector of buckets containing the buckets to be sorted
 * Note that bucketList is passed by reference, and the buckets contained in bucketList
 * 		will be modified directly.
 */
void BucketSort::sortBucketsInRange(int minIndex, int maxIndex){
	// Iterate through all buckets in the given range
	for(int i = minIndex; i <= maxIndex; i++){
		// If the bucket is not empty, sort it
		if(BucketSort::bucketList[i].getNumElements() > 0){
			BucketSort::bucketList[i].sortBucket();
		}
	}
}
