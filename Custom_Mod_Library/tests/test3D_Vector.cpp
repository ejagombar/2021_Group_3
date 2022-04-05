#include <iostream>
#include"../include/3D_Vector.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Vector3D a(2, 4, 5);
    Vector3D b;
    b += a;
    Vector3D c(b);
    cout << a;

    if (c.Get_x() != 2) { return 1; }
    if (c.Get_y() != 4) { return 1; }
    if (c.Get_z() != 5) { return 1; }

    return 0;
}
