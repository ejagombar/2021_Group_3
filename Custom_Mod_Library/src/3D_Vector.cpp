#include "../include/3D_Vector.h"
#include <iostream>


Vector3D::Vector3D(float a,float b, float c)
    :x(a),y(b),z(c){}

Vector3D::Vector3D(float a,float b)
    :x(a),y(b),z(0){}

Vector3D::Vector3D(float a)
    :x(a),y(0),z(0){}

Vector3D::Vector3D()
    :x(0),y(0),z(0){}

Vector3D::~Vector3D(){}

Vector3D::Vector3D(const Vector3D& a)
    :x(a.x),y(a.y),z(a.z){}

Vector3D Vector3D::operator+ (const Vector3D& a){
    Vector3D sum;
    sum.x = a.x + x;
    sum.y = a.y + y;
    sum.z = a.z + z;
    return sum;
}

Vector3D Vector3D::operator- (const Vector3D& a){
    Vector3D minu;
    minu.x = x - a.x;
    minu.y = y - a.y;
    minu.z = z - a.z;
    return minu;
}

Vector3D Vector3D::operator* (const Vector3D& a){
    float multi;
    multi = (x*a.x)+(y*a.y)+(z*a.z);
    return multi;
}

Vector3D Vector3D::operator^ (const Vector3D& a){
    Vector3D multi;
    multi.x=y*a.z-a.y*z;
    multi.y=z*a.x-a.z*y;
    multi.z=x*a.y-a.x*y;
    return multi;
}

Vector3D Vector3D::operator* (float a){
    Vector3D multi;
    multi.x=x*a;
    multi.y=y*a;
    multi.z=z*a;
    return multi;
}

const Vector3D& Vector3D::operator= (const Vector3D& a){
    if(this==&a) return(*this);
    x=a.x;
    y=a.y;
    z=a.z;
    return (*this);
}

Vector3D Vector3D::operator+= (const Vector3D& a){
    x += a.x;
    y += a.y;
    z += a.z;
    return (*this);
}


ostream & operator<<(ostream & out,Vector3D& a)  //----------Overload '<<' operator
{
	out<<"\n("<<a.x<<","<<a.y<<","<<a.z<<")";
	return (out);
}

istream& operator>>(istream& in, Vector3D& a)  //----------Overload '>>' operator
{
    cout<<"\n"<<"Please input the x value: ";
    in>>a.x;
    cout<<"Plaese input the y value: ";
    in>>a.y;
    cout<<"Plaese input the z value: ";
    in>>a.z;
    return (in);
}

//BEN SECTION sets and gets for x y and z

float Vector3D::Get_x(){return x;}
float Vector3D::Get_y(){return y;}
float Vector3D::Get_z(){return z;}

void Vector3D::Set_x(float a){x=a;}
void Vector3D::Set_y(float a){y=a;}
void Vector3D::Set_z(float a){z=a;}






















