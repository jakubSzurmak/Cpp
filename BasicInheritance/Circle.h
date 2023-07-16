#pragma once
#include "PlainFigure.h"

class Circle : public PlainFigure
{
private:
	double r;
protected:
	void Print(std::ostream& out) const override;
public:
	Circle(double r = 4);
	double GetR() const;
	void SetR(double r);
	double Area() override;
	double Perimeter() override;
	~Circle() override;
};

