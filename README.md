# ft_containers

This repository contains my personal implementations of the C++ STL containers: vector, set, stack, and map.

## Requirements

* A C++11 or later compiler

## Features

* All classes are template classes, so they can work with any data type.

## Usage

1. Clone the repository: `git clone https://github.com/Leo-tumo/ft_containers.git`
2. Navigate to the repository: `cd ft_containers`
3. Compile the examples: `make`
4. Run the main example: `make me`
5. Run the 1st test with time comparison: `make test1 `
6. Run the 2nd test: `make test2`

#### Tests

   Thanks to authors of the tests. They were very helpful.

### Vector

It is a dynamic array that can grow or shrink in size as elements are added or removed. It is implemented as a sequence container, meaning that it stores elements in a linear order and provides constant-time access to elements at the beginning and end of the container.

A `ft::vector` is a template class, which means that it can store elements of any data type. To create a vector of a specific data type, you need to specify the type as a template argument, like `ft::vector<int>` for a vector of integers.

`ft::vector` provides several member functions for adding and removing elements, such as `push_back()` for adding an element to the end of the vector, `pop_back()` for removing the last element, and `insert()` for inserting an element at a specific position. The `size()` function returns the number of elements in the vector, while `empty()` returns a Boolean value indicating whether the vector is empty or not.

`ft::vector` also provides support for random access iterators, allowing for efficient traversal through the elements using a range-based for loop or an iterator.

`ft::vector` is a very useful container because it allows for constant-time access to elements at the beginning and end of the container and provides amortized constant time insertions and deletions at the end of the container

### Set

`ft::set` is an ordered container that stores unique elements, meaning that it does not allow for duplicate values. It is implemented as a balanced binary search tree (Red-Black tree), which provides for efficient insertion, deletion, and searching of elements.

A `ft::set` is a template class, which means that it can store elements of any data type that can be compared using the less-than operator (`<`). To create a set of a specific data type, you need to specify the type as a template argument, like `ft::set<int>` for a set of integers.

`ft::set` provides several member functions for manipulating the set, such as `insert()` for adding an element to the set, `erase()` for removing an element, `find()` for searching for an element, and `count()` for counting the number of times an element appears in the set. The `size()` function returns the number of elements in the set, while `empty()` returns a Boolean value indicating whether the set is empty or not.

`ft::set` also provides support for bidirectional iterators, allowing for efficient traversal through the elements using a range-based for loop or an iterator.

`ft::set` is a useful container when you need to store a collection of unique elements and need quick access to elements, as it provides logarithmic time complexity for most operations like insertion, deletion, and searching

### Stack

 `ft::stack` is a container adapter class. It is a last-in-first-out (LIFO) data structure, meaning that the last element added to the stack is the first one to be removed. It is implemented as a wrapper class for other STL containers, such as `ft::vector` or `std::deque`, and provides a restricted set of functions that are specific to a stack data structure.

A `ft::stack` is also a template class, which means that it can store elements of any data type. To create a stack of a specific data type, you need to specify the type as a template argument, like `ft::stack<int>` for a stack of integers.

`ft::stack` provides several member functions for manipulating the stack, such as `push()` for adding an element to the top of the stack, `pop()` for removing the top element, and `top()` for accessing the top element without removing it. The `size()` function returns the number of elements in the stack, while `empty()` returns a Boolean value indicating whether the stack is empty or not.

`ft::stack` does not provide direct access to its elements, as the only way to access the elements is through the top element. It is not possible to iterate through the elements of a stack, but you can use other STL containers to iterate through a stack's elements.

`ft::stack` is useful in situations where you need a LIFO data structure, such as in backtracking, undo/redo functionality, and parsing expressions

### Map

`ft::map` is a container class in the C++ Standard Template Library (STL). It is an ordered container that stores key-value pairs, where each key is unique. It is implemented as a balanced binary search tree, which provides for efficient insertion, deletion, and searching of elements.

A `ft::map` is a template class, which means that it can store elements of any data type as both keys and values. To create a map with specific data types for the key and value, you need to specify the types as template arguments, like `ft::map<std::string, int>` for a map that stores strings as keys and integers as values.

`ft::map` provides several member functions for manipulating the map, such as `insert()` for adding a key-value pair to the map, `erase()` for removing a key-value pair, `find()` for searching for a key, and `count()` for counting the number of times a key appears in the map. The `size()` function returns the number of elements (key-value pairs) in the map, while `empty()` returns a Boolean value indicating whether the map is empty or not.

`ft::map` also provides support for bidirectional iterators, allowing for efficient traversal through the elements using a range-based for loop or an iterator.

`ft::map` is a useful container when you need to store a collection of unique keys, each associated with a specific value, and need quick access to elements based on the keys, as it provides logarithmic time complexity for most operations like insertion, deletion, and searching

## Extra

   This repository also contains my personal implementation of a Red-Black Tree in C++ which is the base data structure of `ft::map` and `ft::set`.


## RB Tree Features

![DALL·E 2023-01-13 13 49 19 - red black tree for github](https://user-images.githubusercontent.com/73405731/212292949-e34983da-490a-4eb0-9c1b-3042eada8b7a.png)
* Insertion
* Deletion
* Searching
* Traversals (Inorder, Preorder, Postorder)

## Additional Resources

* [C++ STL documentation](http://www.cplusplus.com/reference/stl/)
* [C++ STL Tutorial](http://www.cplusplus.com/doc/tutorial/container/)
* [Introduction to Red-Black Trees](https://www.geeksforgeeks.org/red-black-tree-set-1-introduction/)
* [C++ Template Meta-Programming](http://www.cplusplus.com/doc/oldtutorial/templates/)

## License

This repository is licensed under the [MIT](https://chat.openai.com/LICENSE) license.

## Contributing

If you find any issues or want to contribute to this repository, please open an issue or submit a pull request.

Note: As you are implementing your own version of STL containers, it is expected that they may not have all the features and functionalities that the STL containers have. I would recommend you to thoroughly test your implementation before using it in any production environment.
