#include "Circle.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
Circle::Circle(double r) : r(r)
{
	Print(cout);
}
double Circle::GetR() const {
	return r;
}

void Circle::SetR(double r) {
	this->r = r;
}

double Circle::Perimeter() {
	return (2*M_PI*GetR());
}
double Circle::Area() {
	return (M_PI * (GetR() * GetR()));

}
void Circle::Print(std::ostream& out) const {
	out << "This is a Circle R: (" << GetR() << ")" << endl;
}
Circle::~Circle() {
	cout << "Destroyed Circle R: (" << GetR() << ")" << endl;
}
