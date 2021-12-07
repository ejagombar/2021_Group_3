#include <iostream>

using namespace std;



class Vector
{
public:
    void get_x (float a);
    void get_y (float b);
    void get_z (float c);
    void print ();
    void additionThis (Vector a);
    void subtractionThis (Vector a);
    void addition_And_Get_New (Vector Old,Vector& New );
    void subtraction_And_Get_New (Vector Old, Vector& New);

    float scalar_Product (Vector a);
    float vector_Product_And_Get_New (Vector Old, Vector& New);

    float copy_From_Vector (Vector a);
    float show_Vector (float a[3]);

private:
    float x,y,z;
};


void Vector::get_x (float a){
    x = a;
}
void Vector::get_y (float b){
    y = b;
}
void Vector::get_z (float c){
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
    New.get_x (a);
    New.get_y (b);
    New.get_z (c);
}

void Vector::subtraction_And_Get_New (Vector Old, Vector& New) {
    float a,b,c;
    a = x - Old.x;
    b = y - Old.y;
    c = z - Old.z;
    New.get_x (a);
    New.get_y (b);
    New.get_z (c);
}




int main()
{
    Vector a;
    a.get_x(19);
    a.get_y(5);
    a.get_z(1.5);

    Vector b;
    b.get_x(0.66);
    b.get_y(2.3);
    b.get_z(16);

    Vector c;

    a.addition_And_Get_New(b,c);



}















