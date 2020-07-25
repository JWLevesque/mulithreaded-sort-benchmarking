/*
 * AbstractSort.h
 *
 *  Created on: Dec 1, 2018
 *      Author: Adaire
 */

#ifndef ABSTRACTSORT_H_
#define ABSTRACTSORT_H_
#include <vector>
#include <thread>

class AbstractSort {
protected:
	int timeElapsed;
	int numElementsSorted;
	int numThreadsUsed;
	bool isSortSuccessful;
public:
	AbstractSort(std::vector<int> initialList, int numThreads);
	virtual ~AbstractSort(){}
	int getTimeElapsed() const;
	int getNumElementsSorted() const;
	int getNumThreadsUsed() const;
	bool isSorted() const;
	virtual std::vector<int> sort(std::vector<int> initialList, int numThreads) = 0;
	bool isSortedAscending(std::vector<int> list);
};

#endif /* ABSTRACTSORT_H_ */
