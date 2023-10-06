#pragma once

#include <stdlib.h>

template <typename T> 
class List
{
public:
	int length;

	List();
	~List();
	void append_item(T item);
	T operator[](int index) const;
	T& operator[](int index);
	T pop();
	List<T> slice(int start_pos, int end_pos = -1);

private:
	T* internal_array;
	int array_max_size;
};

template <typename T>
List<T>::List()
{
	this->array_max_size = 10;
	this->length = 0;
	this->internal_array = new T[this->array_max_size];
}

template <typename T>
List<T>::~List()
{
	delete[] internal_array;
}

template <typename T> 
void List<T>::append_item(T item)
{
	if (length + 1 > array_max_size)
	{
		this->array_max_size *= 2;

		T* new_loc = (T*)realloc(this->internal_array, array_max_size * sizeof(T));
		if (new_loc == NULL) // realloc failed, throw bad_alloc
			throw std::bad_alloc();
		else
			this->internal_array = new_loc; // asign new array location to internal_array

	}

	this->internal_array[length] = item;
	this->length ++;
}

template<typename T>
T List<T>::operator[](int index) const
{
	if (index > this->length - 1)
		throw std::out_of_range("Index " + std::to_string(index) + " does not exist!");

	return this->internal_array[index];
}

template<typename T>
T& List<T>::operator[](int index)
{
	if (index > this->length - 1)
		throw std::out_of_range("Index " + std::to_string(index) + " does not exist!");

	return this->internal_array[index];
}

template<typename T>
T List<T>::pop()
{
	this->length -= 1;
	return this->internal_array[this->length];
}

template<typename T>
List<T> List<T>::slice(int start_pos, int end_pos)
{
	if (end_pos == -1)
		end_pos = start_pos + 1;
	else if (start_pos > end_pos)
		throw std::invalid_argument("Cannot slice a negative range of indices!");


	int size_to_slice = end_pos - start_pos;
	List<T> sub_list;

	for (int i = start_pos; i < end_pos; i++)
	{
		sub_list.append_item(this->internal_array[i]);
	}

	for (int i = start_pos; i < this->length; i++)
	{
		if (i + size_to_slice > length)
			break;
		this->internal_array[i] = this->internal_array[i + size_to_slice];
	}

	this->length -= size_to_slice;
	return sub_list;
}