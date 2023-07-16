#include <iostream>
#include <initializer_list>
#include "Book.h"
#include "Library.h"

int main()
{
	//TASK1
	std::cout << "TASK 1" << std::endl;
	std::string a = "AutorA", t = "TytulA";
	Book e;
	std::cout << "==> " << "e: " << e << std::endl;
	Book b1 = { a, t };
	std::cout << "==> " << "b1: " << b1 << std::endl;
	Book b2 = { "AutorB","TytulB" };
	std::cout << "==> " << "b2: " << b2 << std::endl;
	Book b3 = b1;
	std::cout << "==> " << "b3: " << b3 << " b1: " << b1 << std::endl;
	e = std::move(b2);
	std::cout << "==> " << "e: " << e << " b2:" << b2 << std::endl;
	e.setAuthor("ZmianaAutora");
	std::cout << "==> " << "e: " << e << std::endl;
	e.setTitle("ZmianaTytulu");
	std::cout << "==> " << "e: " << e << std::endl;

	//TASK2
	std::cout << "TASK 2" << std::endl;
	Library f;
	std::cout << "==> f: "<< f << std::endl;
	
	Library l1 = {{"AutorL1", "TytulL1"}, {"AutorL1.2", "TytulL1.2"}, {"AutorL1.3", "TytulL1.3"}};
	std::cout << "==> l1: "<< l1 << std::endl;
	
	Library l2(2);
	std::cout << "==> l2: "<< l2 << std::endl;
	
	l2[0] = {"AutorL2", "TytulL2"};
	l2[1] = {"AutorL2.1", "TytulL2.1"};
	std::cout << "==> l2: "<< l2 << std::endl;

	f = std::move(l2);
	std::cout << "==> e: " << f << " l2: "<< l2 << std::endl;
	
	l1[0] = std::move(f[1]);
	std::cout << "==> l1: " << l1 << " f: "<< f << std::endl;
	
	return 0;
}
