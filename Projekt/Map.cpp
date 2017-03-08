#include "stdafx.h"
#include "Map.h"

template<typename K,class V> inline void Map<K,V>::init(size_t size) {
	mSize = size;
	mUsed = 0;
	mKeyArray = new K[size];
	mValueArray = new V[size];
}

template<typename K, class V> inline void Map<K, V>::resize(size_t newSize) {
	size_t oldSize = mSize;
	mSize = newSize;
	K* keyBuffer = new K[size];
	V* valueBuffer = new V[size];
	for (uint32_t i = 0; i < oldSize; i++) {
		keyBuffer[i] = mKeyArray[i];
		valueBuffer[i] = mValueArray[i];
	}
	delete[] mKeyArray;
	delete[] mValueArray;
	mKeyArray = keyBuffer;
	mValueArray = valueBuffer;
}

template<typename K, class V> inline uint32_t Map<K, V>::findIndex(K key) {
	for (uint32_t i = 0; i < mUsed; i++) {
		if (mKeyArray[i] == key) {
			return i;
		}
	}

}

template<typename K, class V> inline Map<K, V>::Map(size_t size) {
	init(size);
}

template<typename K, class V> inline Map<K, V>::Map() {
	init(2);
}

template<typename K, class V> inline Map<K, V>::Map(const Map &m) {
	mSize = m.mSize;
	mUsed = m.mUsed;
	mKeyArray = m.mKeyArray;
	mValueArray = m.mValueArray;
}

template<typename K, class V> inline void Map<K, V>::put(K key, V value) {
	mUsed++;
	if (mUsed > mSize) {
		if (mUsed >= SIZE_MAX) {
			return;
		}
		resize(mSize * 2);
	}
	mKeyArray[mUsed - 1] = key;
	mValueArray[mUsed - 1] = value;
}

template<typename K, class V> inline void Map<K, V>::remove(K key) {
	uint32_t index = findIndex(key);
	for (uint32_t i = index; i < mUsed; i++) {
		if ((i+1) > (mSize-1)) {
			break;
		}
		mKeyArray[i] = mKeyArray[i+1];
		mValueArray[i] = mValueArray[i+1];
	}
	mUsed--;
}

template<typename K, class V> inline void Map<K, V>::putAfter(K key, V value, K after) {
	uint32_t index = findIndex(key);
	mUsed++;
	if (mUsed > mSize) {
		if (mUsed >= SIZE_MAX) {
			return;
		}
		resize(mSize * 2);
	}
	for (uint32_t i = mUsed - 1; i > index; i--) {
		if ((i + 1) > (size - 1)) {
			mKeyArray[i + 1] = mKeyArray[i];
			mValueArray[i + 1] = mValueArray[i];
		}
	}
	mKeyArray[index + 1] = key;
	mValueArray[index + 1] = value;
}

template<typename K, class V> inline void Map<K, V>::clear() {
	delete[] mKeyArray;
	delete[] mValueArray;
	init(2);
}

template<typename K, class V> inline V Map<K, V>::get(K key) {
	return mValueArray[findIndex(key)];
}

template<typename K, class V> inline Map<K, V>::~Map() {
	delete[] mKeyArray;
	delete[] mValueArray;
}