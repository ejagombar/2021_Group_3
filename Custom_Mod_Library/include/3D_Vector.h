#ifndef Vector_H
#define Vector_H

#include <iostream>
using namespace std;

class Vector3D
{
public:

    Vector3D(float a, float b, float c); //Set
    Vector3D(float a, float b);
    Vector3D(float a);
    Vector3D();
    ~Vector3D();
    Vector3D(const Vector3D& a);

    Vector3D operator+ (const Vector3D& a);          //Overload '+' operator
    Vector3D operator- (const Vector3D& a);          //Overload '-' operator
    Vector3D operator* (const Vector3D& a);          //Overload '*' operator
    Vector3D operator* (float a);
    Vector3D operator^ (const Vector3D& a);

    const Vector3D& operator= (const Vector3D& a);   //Overload '=' operator
    Vector3D operator+= (const Vector3D& a);         //Overload '+=' operator

    friend istream& operator>> (istream& in, Vector3D& a);   //Overload '>>' operator
    friend ostream& operator<< (ostream& out, Vector3D& a);   //Overload '<<' operator

    //Sets and Gets for x y and z

    float Get_x();
    float Get_y();
    float Get_z();

    void Set_x(float a);
    void Set_y(float a);
    void Set_z(float a);


private:
    float x;
    float y;
    float z;
};

Vector3D operator+(float f, Vector3D& a);  //Overload operators, recognizing different orders of addition operations




#endif // 3D_VECTOR_H

