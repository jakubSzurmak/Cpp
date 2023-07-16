#include "Library.h"
#include <iostream>

std::ostream& operator<<(std::ostream& ostr, const Library& library) {
	ostr << "X:" << library.arr_size;
	return ostr;
}

Library::Library() {
	this->arr_size = 0;
	this->array = nullptr;
	std::cout << "Library()" << std::endl;
}

Library::Library(std::size_t p_arr_size) {
	if (p_arr_size > 0) {
		this->arr_size = p_arr_size;
		this->array = new Book[arr_size];
	}
	std::cout << "Library(std::size_t p_arr_size)" << std::endl;
}

Library::Library(const Library& copyMe) : arr_size{ copyMe.arr_size }, array{new Book[copyMe.arr_size]} {
	for (std::size_t i = 0; i < arr_size; i++) {
		array[i] = copyMe[i];
	}
	std::cout << "Library(const Library&)" << std::endl;
}

Library::Library(Library&& toMove) {
	array = toMove.array;
	arr_size = toMove.arr_size;
	toMove.array = nullptr;
	toMove.arr_size = 0;
	std::cout << "Library(Library&&)" << std::endl;
}

Library::Library(std::initializer_list<Book> initList) : arr_size{ initList.size() }, array{ new Book[initList.size()] } {
	std::cout << "Library(std::initializer_list)" << std::endl;
	std::size_t i = 0;
	for (Book val : initList) {
		array[i] = val;
		i++;
	}
	
}

Library& Library::operator=(const Library& toCopy) {
	Library temp = toCopy;
	std::swap(array, temp.array);
	std::swap(arr_size, temp.arr_size);
	std::cout << "operator=(Library&)" << std::endl;
	return *this;
}

Library& Library::operator=(Library&& toMove) {
	std::swap(this->array, toMove.array);
	std::swap(this->arr_size, toMove.arr_size);
	std::cout << "operator=(Library&&)" << std::endl;
	return *this;
}

Book& Library::operator[](std::size_t i) {
	std::cout << "operator[](std::size_t i)" << std::endl;
	return array[i];
}

const Book& Library::operator[](std::size_t i) const {
	std::cout << "const operator[](std::size_t i)" << std::endl;
	return array[i];
}

std::size_t Library::getSize() const { 
	return this->arr_size;
}

Library::~Library() {
	std::cout << "~Library()" << std::endl;
	if (arr_size != 0) {
		delete[] array;
	}
	
}
