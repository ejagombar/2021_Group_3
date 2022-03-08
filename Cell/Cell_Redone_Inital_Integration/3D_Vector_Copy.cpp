#include "3DVector_Copy.h"
#include <iostream>


Vector::Vector(float a,float b, float c)
    :x(a),y(b),z(c){}

Vector::Vector(float a,float b)
    :x(a),y(b),z(0){}

Vector::Vector(float a)
    :x(a),y(0),z(0){}

Vector::Vector()
    :x(0),y(0),z(0){}

Vector::~Vector(){}

Vector::Vector(const Vector& a)
    :x(a.x),y(a.y),z(a.z){}

Vector Vector::operator+ (const Vector& a){
    Vector sum;
    sum.x = a.x + x;
    sum.y = a.y + y;
    sum.z = a.z + z;
    return sum;
}

Vector Vector::operator- (const Vector& a){
    Vector minu;
    minu.x = x - a.x;
    minu.y = y - a.y;
    minu.z = z - a.z;
    return minu;
}

Vector Vector::operator* (const Vector& a){
    float multi;
    multi = (x*a.x)+(y*a.y)+(z*a.z);
    return multi;
}

Vector Vector::operator^ (const Vector& a){
    Vector multi;
    multi.x=y*a.z-a.y*z;
    multi.y=z*a.x-a.z*y;
    multi.z=x*a.y-a.x*y;
    return multi;
}

Vector Vector::operator* (float a){
    Vector multi;
    multi.x=x*a;
    multi.y=y*a;
    multi.z=z*a;
    return multi;
}

const Vector& Vector::operator= (const Vector& a){
    if(this==&a) return(*this);
    x=a.x;
    y=a.y;
    z=a.z;
}

Vector Vector::operator+= (const Vector& a){
    x += a.x;
    y += a.y;
    z += a.z;
    return (*this);
}

/*
ostream & operator<<(ostream & out,interval& a)  //----------Overload '<<' operator
{
	out<<"\n("<<x<<","<<y<<","<<z<<")";
	return (out);
}

istream& operator>>(istream& in, interval& a)  //----------Overload '>>' operator
{
    cout<<"\n"<<"Please input the x value: ";
    in>>a.x;
    cout<<"Plaese input the y value: ";
    in>>a.y;
    cout<<"Plaese input the z value: ";
    in>>a.z;
    return (in);
}
*/

//BEN SECTION

float Vector::Get_x(){return x;}
float Vector::Get_y(){return y;}
float Vector::Get_z(){return z;}

void Vector::Set_x(float a){x=a;}
void Vector::Set_y(float a){y=a;}
void Vector::Set_z(float a){z=a;}
