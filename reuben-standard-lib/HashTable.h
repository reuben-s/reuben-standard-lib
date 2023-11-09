#pragma once

#include "MurmurHash3.h"

// Need to handle hash collisions.

template <typename T>
class HashTable
{
public:
	template<typename U>
	struct KeyValue {
		const char* key;
		U data;
		KeyValue(const char* key, T data) : key(key), data(data) {}
	};

	HashTable()
	{
		this->m_InteralArraySize = 1000;
		this->m_pInternalArray = new KeyValue<T>*[this->m_InteralArraySize];
	}

	~HashTable()
	{
		for (size_t i = 0; i < this->m_InteralArraySize; ++i) {
			if (this->m_pInternalArray[i] == nullptr)
				delete this->m_pInternalArray[i];
		}
		delete this->m_pInternalArray;
	}

	template<typename T>
	KeyValue<T>* insert(const char* key, T data)
	{
		KeyValue<T>* pair = new KeyValue<T>(key, data);
		this->m_pInternalArray[this->_get_array_index(key)] = pair;
		return pair;
	}

	KeyValue<T>* get(const char* key)
	{
		return this->m_pInternalArray[this->_get_array_index(key)];
	}

private:
	KeyValue<T>** m_pInternalArray;
	size_t m_InteralArraySize;

	uint64_t _get_array_index(const char* key)
	{
		uint64_t hash[2];
		MurmurHash3_x64_128(key, static_cast<uint64_t>(strlen(key)), 0, &hash);
		return hash[0] % this->m_InteralArraySize;
	}
};
