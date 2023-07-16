#pragma once
#include <string>

class Book
{
	std::string author, title;
	friend std::ostream& operator<<(std::ostream& ostr, const Book& book);

public:
	Book();
	Book(const std::string& author, const std::string& title);
	Book(std::string&& author, std::string&& title);
	Book(const Book& copyMe);
	Book(Book&& moveMe);
	
	std::string getTitle();
	std::string getAuthor();

	void setTitle(const std::string& title);
	void setAuthor(const std::string& author);

	void setTitle(std::string&& title);
	void setAuthor(std::string&& author);

	Book& operator=(const Book& copied);
	Book& operator=(Book&& moved);
	~Book();

};

