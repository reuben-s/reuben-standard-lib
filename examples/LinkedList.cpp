#include <iostream>
#include <string>

#include "../reuben-standard-lib/LinkedList.h"

template <typename T>
void format_linked_list(const LinkedList<T>& linked_list)
{
	std::cout << "[";
	for (int i = 0; i < linked_list.length; i++)
	{
		if (i + 1 < linked_list.length)
			std::cout << linked_list[i] << ", ";
		else
			std::cout << linked_list[i];
	}
	std::cout << "]" << std::endl;
}


int main()
{
	LinkedList<int> my_new_linked_list;

	// Populate my_new_linked_list with integers between 1 and 10
	for (int i = 1; i <= 10; i++)
	{
		my_new_linked_list.append_item(i);
	}

	// Output my_new_linked_list.
	format_linked_list(my_new_linked_list); // Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

	// Remove nodes from index 4 to index 8 of my_new_linked_list and output the sub linked list which was sliced.
	LinkedList<int> sub_linked_list = my_new_linked_list.slice(4, 8);
	format_linked_list(sub_linked_list); // Output: [5, 6, 7, 8]

	// Output my_new_linked_list.
	format_linked_list(my_new_linked_list); // Output: [1, 2, 3, 4, 9, 10]

	// Remove the last node from my_new_list and output the removed node.
	int pop = my_new_linked_list.pop();
	std::cout << pop << std::endl; // Output: 10

	// Output my_new_linked_list.
	format_linked_list(my_new_linked_list); // Output: [1, 2, 3, 4, 9]


	return 0;
}