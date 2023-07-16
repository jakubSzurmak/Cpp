#include "Triangle.h"

using namespace std;
Triangle::Triangle(double a, double b, double c) : a(a), b(b), c(c)
{
	Print(cout);
}
double Triangle::GetA() const {
	return a;
}
double Triangle::GetB() const {
	return b;
}
double Triangle::GetC() const {
	return c;
}
void Triangle::SetA(double a) {
	this->a = a;
}
void Triangle::SetB(double b) {
	this->b = b;
}
void Triangle::SetC(double c) {
	this->c = c;
}
double Triangle::Perimeter() {
	return (GetA() + GetB() + GetC());
}
double Triangle::Area() {
	return 0.5*(GetA() + GetB() + GetC());
}
void Triangle::Print(std::ostream& out) const {
	out << "This is a Triangle (" << GetA() << "x" << GetB() << "x" << GetC() << ")" << endl;
}
Triangle::~Triangle() {
	cout << "Destroyed Triangle(" << a << "x" << b << "x" << c << ")" << endl;
}
