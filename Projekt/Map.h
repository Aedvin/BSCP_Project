#pragma once
#include "stdafx.h"

#include <string>

#include <stdint.h>

#include "Iterator.h"


typedef std::string string;

template<typename K> struct Comparable {
	bool static compare(K a, K b) {
		return a == b;
	}
};
template<> struct Comparable<char *> {
	bool static compare(char* a, char* b) {
		string aString(a);
		string bString(b);
		return (aString.compare(bString) == 0);
	}
};
template<> struct Comparable<string> {
	bool static compare(string a, string b) {
		string aString(a);
		string bString(b);
		return (aString.compare(bString) == 0);
	}
};


template <typename K, class V> class Map {
private:
	K* mKeyArray;
	V* mValueArray;
	size_t mSize;
	size_t mUsed;
	void init(size_t size);
	void resize(size_t newSize);
	size_t findIndex(K key, uint32_t* buffer);
public:
	Map(size_t size);
	Map();
	Map(const Map &m);
	void put(K key, V value);
	void remove(K key);
	void putAfter(K key, V value, uint32_t afterIndex);
	size_t findIndex(K key, uint32_t* buffer, size_t bufferSize);
	size_t length();
	Iterator<V> get(K key);
	Iterator<V> getAll();
	Iterator<K> getAllKeys();
	void clear();
	~Map();
};




template<typename K, class V> void Map<K, V>::init(size_t size) {
	mSize = size;
	mUsed = 0;
	mKeyArray = new K[size];
	mValueArray = new V[size];
}

template<typename K, class V> void Map<K, V>::resize(size_t newSize) {
	size_t oldSize = mSize;

	if (newSize < oldSize) {
		newSize = SIZE_MAX;
	}

	mSize = newSize;
	K* keyBuffer = new K[newSize];
	V* valueBuffer = new V[newSize];
	for (size_t i = 0; i < oldSize; i++) {
		keyBuffer[i] = mKeyArray[i];
		valueBuffer[i] = mValueArray[i];
	}
	delete[] mKeyArray;
	delete[] mValueArray;
	mKeyArray = keyBuffer;
	mValueArray = valueBuffer;
}

template<typename K, class V> size_t Map<K, V>::findIndex(K key, uint32_t* buffer) {
	size_t iteratorSize = 0;
	for (size_t i = 0; i < mUsed; i++) {
		if (Comparable<K>::compare(key, mKeyArray[i])) {
			buffer[iteratorSize++] = i;
		}
	}
	return iteratorSize;
}

template<typename K, class V> Map<K, V>::Map(size_t size) {
	init(size);
}

template<typename K, class V> Map<K, V>::Map() {
	init(2);
}

template<typename K, class V> Map<K, V>::Map(const Map &m) {
	mSize = m.mSize;
	mUsed = m.mUsed;
	mKeyArray = new K[size];
	mValueArray = new V[size];
	for (size_t i = 0; i < mUsed; i++) {
		mKeyArray[i] = m.mKeyArray[i];
		mValueArray[i] = m.mValueArray[i];
	}
}

template<typename K, class V> void Map<K, V>::put(K key, V value) {
	mUsed++;
	if (mUsed >= mSize) {
		if (mUsed >= SIZE_MAX - 1) {
			return;
		}
		resize(mSize * 2);
	}
	mKeyArray[mUsed - 1] = key;
	mValueArray[mUsed - 1] = value;
}

template<typename K, class V> void Map<K, V>::remove(K key) {
	size_t indexSize, *buffer = new uint32_t[mUsed];

	indexSize = findIndex(key, buffer);
	if (indexSize == 0) {
		return;
		delete[] buffer;
	}
	for (size_t j = 0; j < indexSize; j++) {
		for (size_t i = buffer[j]; i < mUsed; i++) {
			if ((i + 1) > (mSize - 1)) {
				break;
			}
			mKeyArray[i] = mKeyArray[i + 1];
			mValueArray[i] = mValueArray[i + 1];
		}
		mUsed--;
	}
	delete[] buffer;
}

template<typename K, class V> void Map<K, V>::putAfter(K key, V value, uint32_t afterIndex) {
	mUsed++;
	if (mUsed >= mSize) {
		if (mUsed >= SIZE_MAX) {
			return;
		}
		resize(mSize * 2);
	}
	for (size_t i = mUsed - 1; i > afterIndex; i--) {
		if ((i + 1) <= (mSize - 1)) {
			mKeyArray[i + 1] = mKeyArray[i];
			mValueArray[i + 1] = mValueArray[i];
		}
	}
	mKeyArray[afterIndex + 1] = key;
	mValueArray[afterIndex + 1] = value;
}



template<typename K, class V> void Map<K, V>::clear() {
	delete[] mKeyArray;
	delete[] mValueArray;
	init(2);
}

template<typename K, class V> size_t Map<K, V>::findIndex(K key, uint32_t* buffer, size_t bufferSize) {
	size_t iteratorSize = 0;
	for (size_t i = 0; i < bufferSize; i++) {
		if (Comparable<K>::compare(key, mKeyArray[i])) {
			buffer[iteratorSize++] = i;
		}
	}
	return iteratorSize;
}

template<typename K, class V> size_t Map<K, V>::length() {
	return mUsed;
}

template<typename K, class V> Iterator<V> Map<K, V>::get(K key) {
	size_t iteratorSize, *buffer = new uint32_t[mUsed];;
	iteratorSize = findIndex(key, buffer);
	Iterator<V> it(iteratorSize, buffer, mValueArray);
	delete[] buffer;
	return it;
}

template<typename K, class V> Iterator<V> Map<K, V>::getAll() {
	Iterator<V> it(mUsed, nullptr, mValueArray);
	return it;
}

template<typename K, class V> Iterator<K> Map<K, V>::getAllKeys() {
	Iterator<K> it(mUsed, nullptr, mKeyArray);
	return it;
}

template<typename K, class V> Map<K, V>::~Map() {
	delete[] mKeyArray;
	delete[] mValueArray;
}