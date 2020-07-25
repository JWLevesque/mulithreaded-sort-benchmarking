/*
 * Bucket.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: Adaire
 */

#include "Bucket.h"
#include <vector>

/*Default Constructor for Bucket
 * Initializes numElements to 0.  Element vector remains uninitialized.
 */
Bucket::Bucket(){
	numElements = 0;
	bucketElements = std::vector<int>(128);
}

/*Constructor for Bucket
 * @param size the anticipated size of the bucket
 */
Bucket::Bucket(int size) {
	numElements = 0;
	bucketElements.reserve(size);
}

/*Sorts this.Bucket using insertion sort.
 */
void Bucket::sortBucket(){
	int temp;
	int j;
	for(int i = 1; i<Bucket::numElements; i++){
		temp = Bucket::bucketElements[i];
		j = i;
		while(j > 0 && Bucket::bucketElements[j-1] > temp){
			Bucket::bucketElements[j] = Bucket::bucketElements[j - 1];
			j--;
		}
		Bucket::bucketElements[j] = temp;
	}
}

/* Joint mutator for numElements and bucketElements.
 * Adds the element argument to the back of the vector bucketElements,
 * 		and increments numElements.
 * @param element the integer to add to the bucket
 */
void Bucket::addToBucket(int element){
	Bucket::numElements++;
	Bucket::bucketElements.push_back(element);
}

/* Accessor for numElements
 * @return the number of elements currently in the bucket
 * */
int Bucket::getNumElements() const{
	return Bucket::numElements;
}

/*Accessor for bucketElements
 * @return the vector of bucket elements
 */
const std::vector<int>& Bucket::getBucketElements() const{
	return Bucket::bucketElements;
}
