#pragma once

// Singly linked list

template <typename T>
class Node
{
public:
	T data;
	Node<T>* next;
	Node(T data, Node<T>* next_node = nullptr);
};

template <typename T>
Node<T>::Node(T data, Node<T>* next_node)
{
	this->data = data;
	this->next = next_node;
}

template <typename T>
class LinkedList
{
public:
	int length;
	Node<T>* head;
	// Tail pointer is small optimization for appending an item to the end of a linked list
	Node<T>* tail;
	LinkedList();
	~LinkedList();
	T operator[](int index) const;
	T& operator[](int index);
	void append_item(T item);
	T pop();
	LinkedList<T> slice(int start_post, int end_pos = -1);
};

template <typename T>
LinkedList<T>::LinkedList()
{
	this->length = 0;
	this->head = nullptr;
	this->tail = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	while (this->head != nullptr) {
		Node<T>* current_loc = this->head;
		this->head = this->head->next;
		delete current_loc;
	}
}

template <typename T>
T LinkedList<T>::operator[](int index) const
{
	if (index > length - 1)
		throw std::out_of_range("Index " + std::to_string(index) + " does not exist!");

	Node<T>* current_loc = this->head;
	for (int i = 0; i < index; i++)
	{
		current_loc = current_loc->next;
	}

	return current_loc->data;
}

template <typename T>
T& LinkedList<T>::operator[](int index)
{
	if (index > length - 1)
		throw std::out_of_range("Index " + std::to_string(index) + " does not exist!");

	Node<T>* current_loc = this->head;
	for (int i = 0; i < index; i++)
	{
		current_loc = current_loc->next;
	}

	return current_loc->data;
}

template <typename T>
void LinkedList<T>::append_item(T item)
{
	Node<T>* new_node = new Node<T>(item);
	
	if (this->head == nullptr)
	{
		this->head = this->tail = new_node;
	}
	else
	{
		this->tail->next = new_node;
		this->tail = new_node;
	}
	  
	this->length++;
}

template <typename T>
T LinkedList<T>::pop()
{
	T temp = this->tail->data;

	Node<T>* current_loc = this->head;
	while (current_loc->next != this->tail)
	{
		current_loc = current_loc->next;
	}

	this->tail = current_loc;
	delete this->tail->next;
	this->tail->next = nullptr;

	this->length--;

	return temp;
}

template <typename T>
LinkedList<T> LinkedList<T>::slice(int start_pos, int end_pos)
{
	if (end_pos == -1)
		end_pos = start_pos + 1;
	else if (start_pos > end_pos)
		throw std::invalid_argument("Cannot slice a negative range of indices!");

	Node<T>* start_loc = this->head;
	for (int i = 0; i < start_pos - 1; i++)
	{
		start_loc = start_loc->next;
	}

	LinkedList<T> sliced_items;

	for (int i = start_pos; i < end_pos; i++)
	{
		Node<T>* current_loc = start_loc->next;
		start_loc->next = current_loc->next;
		sliced_items.append_item(current_loc->data);
		delete current_loc;
	}

	this->length -= end_pos - start_pos;

	return sliced_items;
}