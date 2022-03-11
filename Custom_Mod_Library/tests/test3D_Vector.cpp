#include <iostream>
#include"../include/3D_Vector.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Vector3D a(2, 4, 5);
    Vector3D b;
    a += b;
    Vector3D c(b);
    cout << a;
    return 0;
}
