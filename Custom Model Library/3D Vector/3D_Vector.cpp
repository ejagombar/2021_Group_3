#include "3D_Vector.h"
#include <iostream>

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

    std::cout<<"\n"<<x<<"\n"<<y<<"\n"<<z;


}
