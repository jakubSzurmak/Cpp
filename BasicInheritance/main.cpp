// OOP-Lab1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "PlainFigure.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"

void add(int a, int b) {
    std::cout << "OVERLOAD " << a + b << std::endl;
}

void add(double a, double b) {
    std::cout << "OVERLOAD " << a + b << std::endl;
}


int main()
{
    std::cout << "TASK 1" << std::endl;
    Rectangle rectangle1(5, 5);

    std::cout << "\nTASK 2" << std::endl;
    Triangle triangle1(6, 6, 6);
    Circle circle1(10);

    std::cout << "\nTASK 3" << std::endl;
    std::cout << "circ1 Area: " << circle1.Area() << std::endl;
    std::cout << "circ1 Perim: " << circle1.Perimeter() << std::endl;

    Rectangle* ptr_rectangle1 = &rectangle1;
    Triangle* ptr_triangle1 = &triangle1;
    Circle* ptr_circle1 = &circle1;

    Rectangle& ref_rectangle1 = rectangle1;
    Triangle& ref_triangle1 = triangle1;
    Circle& ref_circle1 = circle1;

    //Error abstract
    //PlainFigure ar[3] = {ref_rectangle1, ref_triangle1, ref_circle1};
    PlainFigure* ar[3] = { ptr_rectangle1, ptr_triangle1, ptr_circle1 };

    std::cout << "rect1 Area: " << ar[0]->Area() << std::endl;
    
   
    //Default constructor
    Rectangle rectangle2(ref_rectangle1);
    rectangle2.SetA(2);
    rectangle2.SetB(2);
    std::cout << "rect2 Area: " << rectangle2.Area() << std::endl;
    std::cout << "\n";
    add(1, 2);
    add(1.1, 2.2);
    std::cout << "\n";

    return 0;
}

