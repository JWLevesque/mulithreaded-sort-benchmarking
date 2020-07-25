/*
 * AbstractSort.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: Adaire
 */

#include "AbstractSort.h"

/*Constructor for AbstractSort
 * @param initialList the vector of integers to be sorted
 * @param numThreads the number of threads to be used while sorting
 * Note that timeElapsed is initialized to -1 and isSorted is initialized to false.
 * timeElapsed and isSorted will have to be set by child classes.
 */
AbstractSort::AbstractSort(std::vector<int> initialList, int numThreads) {
	// Correct initializations
	numElementsSorted = initialList.size();
	numThreadsUsed = numThreads;

	// These will be replaced by child classes
	timeElapsed = -1;
	isSortSuccessful = false;
}

/*Checks if the given vector is sorted in ascending order.
 * @return true if the vector is sorted in ascending order; false otherwise
 */
bool AbstractSort::isSortedAscending(std::vector<int> list){ // @suppress("Unused static function")
	for(int i = 1; i < int(list.size()); i++){
		if(list[i]<list[i-1]){
			return false;
		}
	}
	return true;
}

/*Accessor for timeElapsed
 * @return the time it took to complete the sort
 */
int AbstractSort::getTimeElapsed() const{
	return AbstractSort::timeElapsed;
}
/*Accessor for numElementsSorted
 * @return the number of elements that were sorted
 */
int AbstractSort::getNumElementsSorted() const{
	return AbstractSort::numElementsSorted;
}

/*Accessor for numThreadsUsed
 * @return the number of threads used for the sort
 */
int AbstractSort::getNumThreadsUsed() const{
	return AbstractSort::numThreadsUsed;
}

/*Accessor for isSortSuccessful
 * @return true if the sorting was successful; false otherwise
 */
bool AbstractSort::isSorted() const{
	return AbstractSort::isSortSuccessful;
}
