#include <iostream>
#include <initializer_list>
#include <assert.h>
#include <functional>
#include <list>
using std::cout;
using std::endl;

int chop_guessing(const int search, const int * array, int size)
{
	//average the values of the endpoints and use that as the mid, maybe factor in the search value
	return -1;
}

// void recursivelistreverse(auto prev, auto node)
// {
	// // get to the end of the list
	// recursivelistreverse(node->next());

	// // each call knows itself (A) and the next node(B)

	// // the next node B has to change its next to from C to A

	// // so if this is B, it knows B and C, it can return B or C, but A doesnt want those
	// // B has to find out what A is, and thats done by passing it in.
	// node->setNext(prev);
	// // this would lose track of C, except that its stored on the call stack, so this assign has to be done while returning

	// // terminating condition
		// if (!node) //end of list
	// {
		// return;
	// }

// }
// reverse_list(list)
// {
// if (list->head->next == NULL)
// return;
// reverse_list(list->head->next)
// iterator = list->head->next
// while (iterator->next != NULL)
// iterator = iterator->next;
// iterator->next = list->head;
// list->head = list->head->next;
// }

// note if templating these, make the search a ref to limit object copies
int chop_recursive( const int search, const int *array, int size)
{
	//recursive method, general idea is to move a pointer into the array and a size
	//around to make "subarrays", until there is only one element, and if that is the
	//search element, return that location, else the search element isnt in the array
	//and return -1. The actual array isnt changed or copied, just a pointer to different parts of the array.

	int mid = (size/2); //assumed this is always going to round down

	cout << endl << array[0] << " " << array[mid] << " " << array[size-1] << " Size: " << size;

	//these two functions are tied together to make the terminating condition
	//when the size is one, a check of mid will check the only element and return before the
	//size check happens. If the size check is reached, the element has not been found, so return -1
	if(array[mid] == search)
	return mid;
	if (size == 1)
	return -1;

	if(array[mid] < search) //search upper half
	{
		//this is some confusing look code:
		//the idea is that the next call thinks the array starts at what is currently the midpoint
		//and has the size of whats left of the array
		//The next array is given a pointer to the address of the middle element.
		//When the the size is odd (then modulus is nonzero), the truncation of integer division
		//is rounding down and cutting off an element, so the next size needs a +1.
		//Also, the starting position of the subarray in the main array needs to be added to the found index
		//to get the true index, unless of course its a -1 for not found, and that is just passed up the call heirarchy

		int index_within_subarray = chop_recursive(search, &array[mid], (size%2)? mid + 1 : mid);
		return (index_within_subarray == -1) ? -1 : index_within_subarray + mid;
	}
	else if (array[mid] > search) //search lower half
	{
		return chop_recursive(search, array, mid);
	}
	return -1; //in case all those control paths fail, and to suppress compiler warnings. This shouldn't actually be reached ever
	//because array[mid] == search, > search, and < search all return, and that should cover all possibilities.
}

/*
*Errors that happened to me writing the recursive method.
*I started off passing around a start index before I realized I could just move the pointer to the array
*Had an off by one error with the size when searching the upper half
*Wasn't adding in the start index of the subarray when returning from the subarrays that started at the midpoint
*I was much happier with the terminating condition here that my first try at iterative, I think I could rewrite that better now
*/

int chop_iterative(const int search, const int *array, int size)
{
	//iterative approach:
	//track some index positions in the array, moving them close together
	//and checking the search value to see what indexes could contain it.

	cout << endl << "Size " << size << endl;
	int start(0);
	int end(size - 1);

	if(size == 1)
	return (array[0] == search) ? 0 : -1;

	while(1)
	{
		//check if value cannot exist in the array
		if(search < array[start] || search > array[end])
		return -1;

		//check if we've singled out a single element and check if that matches the search
		if(start == end)
		return (array[start] == search) ? start : -1;

		//if two elements
		if(start == end - 1)
		{
			if (array[start] == search)
			return start;
			else if(array[end] == search)
			return end;
			else
			return -1;
		}
		//this seems like a not very effective ending condition, and needs some refactoring

		//find the midpoint
		int mid = (start + end) / 2; //this may be off by one in either direction
		//from rounding if size is odd.
		cout << start << " " << mid << " " << end << endl;

		//check if value is at the midpoint index
		//this is not particularly likely, could just omit it
		//but could be an extra exit condition instead of checking this after size is very small
		if(array[mid] == search)
		return mid;

		//redo the array indexes to simulate a new array based
		//on if midpoint value is more or less than search value
		//something for if value isnt in the array
		//while it'd cut more out each search to restart at mid-1 and mid+1,
		//that risks the search value being between mid and mid+-1.
		//it also creates some problems with going out of the array bounds when
		//the midpoint has moved to the array ends.
		if(array[mid] < search) //search the upper part of the array
		{
			start = mid;
			//end = end;

		}
		else if (array[mid]  > search) //search the lower part of the array
		{
			//start = start;
			end = mid;
		}
	}
}

/*
	*
	*errors that happened to me writing this iterative method
	*size of a passed array is always one, had to pass size into function
	*annoying writing the tests with different array names so i scoped each section so I
	*could copy paste array and size instead of array1, size1, etc.
	*also really annoyed I can't initialize vectors with init lists cause this compiler isnt c++11
	*reversed the compares > < for what end of the array they were supposed to search
	*went negative on an end value because mid rounds down sometimes.
	*end condition on the while loop couldnt just be start == end cause in that case the single element needs checked
	*this debugger doesnt move its breakpoints when you add code during runtime
	*wasnt finding invalid value in middle with even number of elements
	*noticing all my problems are to do with boundary and finishing conditions, on a big chunk of data
	*things run fine until it gets down to the end
	**/

void testchop(std::function<int (const int, const int*, int)> chop)
{
	//can't do empty arrays in c++
	//    int array;
	//    assert(chop(3, array) == -1);
	{
		int array[] = {1};
		int size = sizeof(array) / sizeof(array[0]);
		assert(chop(3, array, size) == -1);
		assert(chop(1, array, size) == 0);

		cout  << endl << "Single Element good.";
	}
	{
		int array[] = {1,3};
		int size = sizeof(array) / sizeof(array[0]);
		assert(chop(1, array, size) == 0);
		assert(chop(3, array, size) == 1);
		assert(chop(0, array, size) == -1);
		assert(chop(2, array, size) == -1);
		assert(chop(4, array, size) == -1);

		cout  << endl << "Two Element good.";
	}
	{
		int array[] = {1,3,5};
		int size = sizeof(array) / sizeof(array[0]);

		assert(chop(1, array, size) == 0);
		assert(chop(3, array, size) == 1);
		assert(chop(5, array, size) == 2);
		assert(chop(0, array, size) == -1);
		assert(chop(2, array, size) == -1);
		assert(chop(4, array, size) == -1);
		assert(chop(6, array, size) == -1);

		cout << endl << "Three Element good.";
	}

	{
		int array[] = {1,3,5,7};
		int size = sizeof(array) / sizeof(array[0]);
		assert(chop(1, array, size) == 0);
		assert(chop(3, array, size) == 1);
		assert(chop(5, array, size) == 2);
		assert(chop(7, array, size) == 3);
		assert(chop(0, array, size) == -1);
		assert(chop(2, array, size) == -1);
		assert(chop(4, array, size) == -1);
		assert(chop(6, array, size) == -1);
		assert(chop(8, array, size) == -1);

		cout << endl << "4 Element good.";
	}
	{
		int array[1000];
		int size = sizeof(array) / sizeof(array[0]);
		for(int i = 0; i < 1000; ++i)
		{
			array[i] = i;
		}
		assert(chop(0, array, size) == 0);
		assert(chop(1, array, size) == 1);
		assert(chop(25, array, size) == 25);
		assert(chop(29, array, size) == 29);
		assert(chop(178, array, size) == 178);
		assert(chop(412, array, size) == 412);
		assert(chop(499, array, size) == 499);
		assert(chop(500, array, size) == 500);
		assert(chop(501, array, size) == 501);
		assert(chop(628, array, size) == 628);
		assert(chop(799, array, size) == 799);
		assert(chop(999, array, size) == 999);
		assert(chop(1000, array, size) == -1);


		cout << endl << "1000 Element good.";
	}
}

int main()
{
//cout << "test: " << 1 << endl;
    std::list<int> list;// = {0, 10, 20, 30, 40};
     list.push_back(0 );
     list.push_back(10);
     list.push_back(20);
     list.push_back(30);
     list.push_back(40);
//	recursivelistreverse(list->begin(), list->begin()->next());
	//coudl do it with an iterator
	// for(auto itr = list.begin(); itr != list.end(); ++itr)
	// {
		// cout << *itr << "";
	// }
	cout << endl;


	testchop(chop_iterative);

	testchop(chop_recursive);
	//testchop(chop_guessing);


	cout << endl << "Tests Done!" << endl;

	return 0;
}


