#include <iostream>

using namespace std;



class Vector
{
public:
    void set_x (float a);
    void set_y (float b);
    void set_z (float c);
    void print ();
    void additionThis (Vector a);
    void subtractionThis (Vector a);
    void addition_And_Get_New (Vector Old,Vector& New );
    void subtraction_And_Get_New (Vector Old, Vector& New);

    float scalar_Product (Vector a);
    void vector_Product_And_Get_New (Vector Old, Vector& New);

    void copy_From_Vector (Vector a);
    void show_Vector (float& a,float& b,float& c);

private:
    float x,y,z;
};


void Vector::set_x (float a){
    x = a;
}
void Vector::set_y (float b){
    y = b;
}
void Vector::set_z (float c){
    z = c;
}
void Vector::print(){
    cout<<"\nx is: "<<x<<"\ny is: "<<y<<"\nz is: "<<z;
}

void Vector::additionThis (Vector a){
    x = x + a.x;
    y = y + a.y;
    z = z + a.z;
}

void Vector::subtractionThis (Vector a){
    x = x - a.x;
    y = y - a.y;
    z = z - a.z;
}

void Vector::addition_And_Get_New (Vector Old,Vector& New){
    float a,b,c;
    a = x + Old.x;
    b = y + Old.y;
    c = z + Old.z;
    New.set_x (a);
    New.set_y (b);
    New.set_z (c);
}

void Vector::subtraction_And_Get_New (Vector Old, Vector& New) {
    float a,b,c;
    a = x - Old.x;
    b = y - Old.y;
    c = z - Old.z;
    New.set_x (a);
    New.set_y (b);
    New.set_z (c);
}

float Vector::scalar_Product (Vector a){
    float i;
    return i = (x*a.x)+(y*a.y)+(z*a.z);
}

void Vector::vector_Product_And_Get_New (Vector Old, Vector& New){
    New.set_x (y*Old.z - z*Old.y);
    New.set_y (z*Old.x - x*Old.z);
    New.set_z (x*Old.y - y*Old.x);
}

void Vector::copy_From_Vector (Vector a){
    x = a.x;
    y = a.y;
    z = a.z;
}

void Vector::show_Vector (float& a,float& b,float& c){
    a = x;
    b = y;
    c = z;
}


int main()
{
    Vector a;
    a.set_x(19);
    a.set_y(5);
    a.set_z(1.5);

    Vector b;
    b.set_x(0.66);
    b.set_y(2.3);
    b.set_z(16);

    Vector c;

    c.copy_From_Vector(b);

    c.print();

    float x,y,z;

    a.show_Vector(x,y,z);

    cout<<"\n"<<x<<"\n"<<y<<"\n"<<z;


}















