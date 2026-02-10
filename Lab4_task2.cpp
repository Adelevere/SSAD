#include <iostream>
#include <cmath> 

using namespace std;

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual ~Shape() {}
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override { return width * height; }
    double perimeter() const override { return 2 * (width + height); }
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return M_PI * radius * radius; }
    double perimeter() const override { return 2 * M_PI * radius; }
};

int main() {
    Rectangle rect(5.0, 3.0);
    Circle circ(4.0);
    Shape* shape = &rect;

    const Rectangle* rectPtr = static_cast<const Rectangle*>(shape);
    cout << "Static cast: Rectangle Area = " << rectPtr->area() << endl;

    Circle* circlePtr = dynamic_cast<Circle*>(shape);
    if (circlePtr) {
        cout << "shape is a Circle" << endl;
    } else {
        cout << "shape is not a Circle" << endl;
    }

    Rectangle* mutableRectPtr = const_cast<Rectangle*>(rectPtr);
    
    int intValue = 42;
    double* reinterpretedVal = reinterpret_cast<double*>(&intValue);
    cout << "Reinterpret cast (int address to double pointer): " << reinterpretedVal << endl;

    return 0;
}