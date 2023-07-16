#include "Rectangle.h"
#include <iostream>

using namespace std;
Rectangle::Rectangle(double a, double b): a(a), b(b)
{
	Print(cout);
}
double Rectangle::GetA() const {
	return a;
}
double Rectangle::GetB() const {
	return b;
}
void Rectangle::SetA(double a) {
	this->a = a;
}
void Rectangle::SetB(double b) {
	this->b = b;
}
double Rectangle::Perimeter() {
	return 2 * GetA() + 2 * GetB();
}
double Rectangle::Area() {
	return GetA() * GetB();
}
void Rectangle::Print(std::ostream& out) const {
	out << "This is a Rectangle (" << GetA() << "x" << GetB() << ")" << endl;
}
Rectangle::~Rectangle() {
	cout << "Destroyed Rectangle(" << a << "x" << b << ")" << endl;
}
