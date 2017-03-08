#pragma once
#include "stdafx.h"

#include <stdint.h>

template<typename V> class Iterator {
private:
	size_t mSize;
	size_t mIteratorKey;
	V** mAddressArray;
	void init(size_t size,uint32_t* indexes,V* addresses);
public:
	Iterator(size_t size,uint32_t* indexes,V* adrresses);
	Iterator(const Iterator<V>& i);
	Iterator<V>& operator=(const Iterator<V>& i);
	bool hasNext();
	void begin();
	size_t length();
	V* get(uint32_t index);
	V* next();
	~Iterator();

};

template<typename V> void Iterator<V>::init(size_t size, uint32_t* indexes, V* addresses) {
	mAddressArray = new V*[size];
	mSize = size;
	mIteratorKey = 0;
	if (indexes == nullptr) {
		for (size_t i = 0; i < size; i++) {
			mAddressArray[i] = &addresses[i];
		}
	}
	else {
		for (size_t i = 0; i < size; i++) {
			mAddressArray[i] = &addresses[indexes[i]];
		}
	}
}

template<typename V> Iterator<V>::Iterator(size_t size, uint32_t* indexes, V* addresses) {
	init(size, indexes, addresses);
}

template<typename V> Iterator<V>::Iterator(const Iterator<V>& i) {
	mSize = i.mSize;
	mAddressArray = new V*[mSize];
	for (size_t j = 0; j < mSize; j++) {
		mAddressArray[j] = i.mAddressArray[j];
	}
	mIteratorKey = i.mIteratorKey;
}

template<typename V> Iterator<V>& Iterator<V>::operator=(const Iterator<V>& i) {
	if (&i == this) {
		return *this;
	}
	
	if (mSize != i.mSize) {
		mSize = i.mSize;
		delete[] mAddressArray;
		mAddressArray = new V*[mSize];
	}
	for (size_t j = 0; j < mSize; j++) {
		mAddressArray[j] = i.mAddressArray[j];
	}
	mIteratorKey = i.mIteratorKey;
	return *this;
}

template<typename V> bool Iterator<V>::hasNext() {
	if (mIteratorKey < mSize) {
		return true;
	}
	return false;
}

template<typename V> void Iterator< V>::begin() {
	mIteratorKey = 0;
}

template<typename V> size_t Iterator<V>::length() {
	return mSize;
}

template<typename V> V* Iterator< V>::get(uint32_t index) {
	return mAdrressArray[index];
}

template<typename V> V* Iterator<V>::next() {
	return mAddressArray[mIteratorKey++];
}

template<typename V> Iterator<V>::~Iterator() {
	delete[] mAddressArray;
}