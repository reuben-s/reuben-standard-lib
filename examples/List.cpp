#include <iostream>
#include <string>

#include "../reuben-standard-lib/List.h"

template <typename T>
void format_list(const List<T>& list)
{
	std::cout << "[";
	for (int i = 0; i < list.length; i++)
	{
		if (i + 1 < list.length)
			std::cout << list[i] << ", ";
		else
			std::cout << list[i];
	}
	std::cout << "]" << std::endl;
}

int main()
{
	List<int> my_new_list;

	// Populate my_new_list with integers between 1 and 10
	for (int i = 1; i <= 10; i++)
	{
		my_new_list.append_item(i);
	}

	// Output my_new_list.
	format_list(my_new_list); // Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

	// Remove elements from index 4 to index 8 of my_new_list and output the sub-list which was sliced.
	List<int> sub_list = my_new_list.slice(4, 8);
	format_list(sub_list); // Output: [5, 6, 7, 8]

	// Output updated my_new_list 
	format_list(my_new_list); // Output: [1, 2, 3, 4, 9, 10]

	// Remove the last element of my_new_list and output the removed element
	int pop = my_new_list.pop();
	std::cout << pop << std::endl; // Output: 10

	// Output updated my_new_list
	format_list(my_new_list); // Output: [1, 2, 3, 4, 9]

	return 0;
}