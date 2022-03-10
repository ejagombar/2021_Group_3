#include <iostream>
#include"3DVector.h"
#include"3D_Vector.cpp"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Vector a(2, 4, 5);
    Vector b;
    a += b;
    Vector c(b);
    cout << a;
    return 0;
}
