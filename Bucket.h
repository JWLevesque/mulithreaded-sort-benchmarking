/*
 * Bucket.h
 *
 *  Created on: Dec 1, 2018
 *      Author: Adaire
 */

#ifndef BUCKET_H_
#define BUCKET_H_
#include <vector>

class Bucket {
private:
	std::vector <int> bucketElements;
	int numElements;
public:
	// constructors
	Bucket();
	Bucket(int size);
	// class methods
	void sortBucket();
	// getters and setters
	void addToBucket(int element);
	int getNumElements() const;
	const std::vector<int>& getBucketElements() const;
};

#endif /* BUCKET_H_ */
