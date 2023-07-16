#pragma once
#include "Book.h"
#include <initializer_list>

class Library
{
private:
	Book* array;
	std::size_t arr_size;
	friend std::ostream& operator<<(std::ostream& ostr, const Library& library);

public:
	Library();
	Library(std::size_t arr_size);
	Library(std::initializer_list<Book> list);
	Library(const Library& copyMe);
	Library(Library&& moveMe); 
	Library& operator=(const Library& right);
	Library& operator=(Library&& right);
	Book& operator[](std::size_t index);
	const Book& operator[](std::size_t index) const;
	std::size_t getSize() const;
	~Library();
};

