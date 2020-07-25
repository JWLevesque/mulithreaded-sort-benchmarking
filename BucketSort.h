/*
 * BucketSort.h
 *
 *  Created on: Dec 1, 2018
 *      Author: Adaire
 */

#ifndef BUCKETSORT_H_
#define BUCKETSORT_H_
#include "Bucket.h"
#include "AbstractSort.h"
#include <vector>

class BucketSort : public AbstractSort{
private:
	std::vector<Bucket> bucketList;
	void sortBucketsInRange(int min, int max); //std::vector<Bucket> &bucketList
public:
	BucketSort(std::vector<int> initialList, int numThreads);
	std::vector<int> sort(std::vector<int> initialList, int numThreads);
};

#endif /* BUCKETSORT_H_ */
