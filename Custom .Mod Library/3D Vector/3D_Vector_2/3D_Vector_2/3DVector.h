#ifndef Vector_H
#define Vector_H
#include <iostream>
using namespace std;

class Vector
{
public:

    Vector (float a, float b, float c); //Set
    Vector (float a, float b);
    Vector (float a);
    Vector ();
    ~Vector ();
    Vector (const Vector& a);

    Vector operator+ (const Vector& a);          //Overload '+' operator
    Vector operator- (const Vector& a);          //Overload '-' operator
    Vector operator* (const Vector& a);          //Overload '*' operator
    Vector operator* (float a);
    Vector operator^ (const Vector& a);

    const Vector& operator= (const Vector& a);   //Overload '=' operator
    Vector operator+= (const Vector& a);         //Overload '+=' operator

    friend istream& operator>> (istream& in, Vector& a);   //Overload '>>' operator
    friend ostream& operator<< (ostream& out, Vector& a);   //Overload '<<' operator


private:
    float x;
    float y;
    float z;
};

Vector operator+(float f,Vector & a);  //Overload operators, recognizing different orders of addition operations




#endif // 3D_VECTOR_H

