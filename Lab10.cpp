#include<iostream>
#include<math.h>
#define PI   3.14159265358979323846
using namespace std;

class shape {
    public:
        double x;
        double y;
        shape();
        ~shape();
        void move(int, int);
        virtual double area();
        void resize();
        virtual void display();
};

class Ellipse : public shape {
    private:
        double radiusx;
        double radiusy;
        double angle;
    public:
        Ellipse();
        ~Ellipse();
        double area();
        void resize(double, double);
        void display();
        void rotate(double);
        void vertices();
};

class Circle : public shape {
    private:
        double radius;
    public:
        Circle();
        ~Circle();
        double area();
        void resize(double);
        void display();
        int isInside(int, int);
};

shape::shape(){
    x = 0;
    y = 0;
}

shape::~shape(){

}

void shape::move(int x, int y){
    this->x += x;
    this->y += y;
}

double shape::area(){
    double area = 0;
    return area;
}

void shape::resize(){
    cout << "Please pass 1 or 2 values to resize()" << endl;
}

void shape::display(){
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
}

Ellipse::Ellipse(){
    cout << "Enter x radius for ellipse: ";
    cin >> radiusx;
    cout << "\nEnter y radius for ellipse: ";
    cin >> radiusy;
    cout << "\nEnter angle of ellipse";
    cin >> angle;
}

Ellipse::~Ellipse(){
}

double Ellipse::area(){
    double area = 0;
    area = radiusx * radiusy * PI;
    return area;
}

void Ellipse::resize(double radiusx, double radiusy){
    this->radiusx = radiusx;
    this->radiusy = radiusy;
}

void Ellipse::display(){
    cout << "ellipse:\n" << "X and radius of x: " << x << " " << radiusx << "\nY and radius of y: " << y << " " << radiusy << endl;
    cout << "angle of rotation: " << angle << endl;
}

void Ellipse::rotate(double angle){
    this->angle += angle;
}

void Ellipse::vertices(){
    double verticex = x + radiusx;
    double verticey = y + radiusy;
    if(radiusx > radiusy){
        cout << "Vertices are: \n(" << verticex << "," << y << ")" << endl;
        cout << "( " << verticex - x -x << ", " << y << " )" << endl; 
    }
    else{
        cout << "Vertices are: \n(" << x << "," << verticey << ")" << endl;
        cout << "(" << x << "," << verticex - y -y << ")" << endl; 
    }
}

Circle::Circle(){
    cout << "Enter radius for circle: ";
    cin >> radius;
}

Circle::~Circle(){
}

double Circle::area(){
    double area = 0;
    area = radius * radius * PI;
    return area;
}

void Circle::resize(double radius){
    this->radius = radius;
}

void Circle::display(){
    cout << "circle:\n" << "X :" << x << "\nY :" << y << "\nradius: "  << radius << endl;
}

int Circle::isInside(int x, int y){
    if(x >= this->x-radius && x <= radius+this->x){
        if(y >= this->y-radius && y <= radius+this->y){
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int main(void){
    shape* shape;
    Ellipse ellipse;
    shape = &ellipse;
    cout << "\n" << endl;
    shape->display();
    ellipse.move(-10,20);
    cout << "moving ellipse (-10,20)" << endl;
    cout << "\n" << endl;
    ellipse.display();
    cout << "\n" << endl;
    ellipse.vertices();
    ellipse.rotate(10);
    cout << "rotate 10 degrees" << endl;
    cout << "\n" << endl;
    ellipse.display();
    
    
    cout << "\n" << endl;
    cout << "\n" << endl;
    Circle circle;
    cout << "\n" << endl;
    circle.display();
    circle.move(10,10);
    cout << "moving circle (10,10)" << endl;
    cout << "\n" << endl;
    circle.display();
    double area = circle.area();
    cout << "\narea of circle is: " << area << endl;
    cout << "\n" << endl;
    circle.display();

    if(circle.isInside(15,15) == 1){
        cout << "Point (15,15) is inside circle" << endl;
    }else{
        cout << "Point (15,15) is not inside circle" << endl;
    }
    if(circle.isInside(10,10) == 1){
        cout << "Point (10,10) is inside circle" << endl;
    }else{
        cout << "Point (10,10) is not inside circle" << endl;
    }
    
}
