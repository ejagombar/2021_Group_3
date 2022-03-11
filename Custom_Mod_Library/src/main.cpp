#include <iostream>
#include "../include/Material.h"
#include "../include/Model.h"
#include "../include/Cell.h"



int main()
{
    Vector3D Test_Vector_Array[8];

    Vector3D Test_Zero(0, 0, 0);
    Vector3D Test_One(1, 0, 0);
    Vector3D Test_Two(1, 0, 1);
    Vector3D Test_Three(0, 0, 1);
    Vector3D Test_Four(0.5, 1, 0.5);
    Vector3D Test_Five(0.5, 5, 0.5);
    Vector3D Test_Six(6, 6, 6);
    Vector3D Test_Seven(7, 7, 7);

    Test_Vector_Array[0] = Test_Zero;
    Test_Vector_Array[1] = Test_One;
    Test_Vector_Array[2] = Test_Two;
    Test_Vector_Array[3] = Test_Three;
    Test_Vector_Array[4] = Test_Four;
    Test_Vector_Array[5] = Test_Five;
    Test_Vector_Array[5] = Test_Six;
    Test_Vector_Array[6] = Test_Seven;

    cout << "attempting to create cell...";
    cell Test_Cell(8, Test_Vector_Array, 100);
    cout << "done";

    //cout << "Test_Cell Vertice " << 3 << " X: " << Test_Cell.Get_VecPtrs(3).Get_x() << ", Y: " << Test_Cell.Get_VecPtrs(3).Get_y() << ", Z: " << Test_Cell.Get_VecPtrs(3).Get_z() << endl;

    for (int i = 0; i < 8; i++)
    {
        cout << "Test_Cell Vertice " << i << " X: " << Test_Cell.Get_VecPtrs(i).Get_x() << ", Y: " << Test_Cell.Get_VecPtrs(i).Get_y() << ", Z: " << Test_Cell.Get_VecPtrs(i).Get_z() << endl;
    }


    cell Copy_Test(Test_Cell);
    Copy_Test.Set_VecPtrs(7, Test_One);

    cout << "cell copied";

    for (int i = 0; i < 8; i++)
    {
        cout << "Copy_Test_Cell Vertice " << i << " X: " << Copy_Test.Get_VecPtrs(i).Get_x() << ", Y: " << Copy_Test.Get_VecPtrs(i).Get_y() << ", Z: " << Copy_Test.Get_VecPtrs(i).Get_z() << endl;
    }

    cout << "now leave";
    //throw std::exception();

    return 1;

}

