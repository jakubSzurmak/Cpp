#include "Book.h"
#include <iostream>

std::ostream& operator<<(std::ostream& ostr, const Book& book) {
	ostr << book.author << ":" << book.title;
	return ostr;
}

Book::Book() {
	author = "foo";
	title = "bar";
	std::cout << "Book()" << std::endl;
}

Book::Book(const std::string& author, const std::string& title) : author{ author }, title{ title }
{
	std::cout << "Book(const std::string & author, const std::string & title)" << std::endl;
}

Book::Book(std::string&& p_author, std::string&& p_title)
{
	author = p_author;
	title = p_title;
	p_author = "\0";
	p_title = "\0";
	std::cout << "Book(std::string&& p_author, std::string&& p_title)" << std::endl;
}

Book::Book(const Book& copyMe) :author(copyMe.author), title(copyMe.title)
{
	std::cout << "Book(const Book& copyMe)" << std::endl;
}

Book::Book(Book&& moveMe) {
	author = std::move(moveMe.author);
	title = std::move(moveMe.title);
	std::cout << "Book(Book&& moveMe)" << std::endl;
}

std::string Book::getTitle() {
	return title;
}

std::string Book::getAuthor() {
	return author;
}

void Book::setTitle(const std::string& title) {
	this->title = title;
}

void Book::setAuthor(const std::string& author) {
	this->author = author;
}

void Book::setTitle(std::string&& title) {
	this->title = std::move(title);
}

void Book::setAuthor(std::string&& author) {
	this->author = std::move(author);
}

Book& Book::operator=(const Book& copied) {
	author = copied.author;
	title = copied.title;
	/*
	Book tmp = copied;
	std::swap(author, tmp.author);
	std::swap(title, tmp.title);
	*/
	std::cout << "operator=(const Book& copied)" << std::endl;
	return *this;
}

Book& Book::operator=(Book&& moved) {
	author = std::move(moved.author);
	title = std::move(moved.title);
	std::cout << "operator=(Book&& moved)" << std::endl;
	return *this;
}

Book::~Book() {
	std::cout << "~Book()" << std::endl;
}
