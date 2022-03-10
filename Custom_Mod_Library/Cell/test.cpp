    #include "3DVector.h"   

    int num = 8;
    Vector Test_Vector_Array[num];

    Vector Test_Zero(0,0,0);
    Vector Test_One(1,0,0);
    Vector Test_Two(1,0,1);
    Vector Test_Three(0,0,1);
    Vector Test_Four(0.5,1,0.5);
    Vector Test_Five(0.5,5,0.5);
    Vector Test_Six(6,6,6);
    Vector Test_Seven(7,7,7);

    Test_Vector_Array[0] = Test_Zero;
    Test_Vector_Array[1] = Test_One;
    Test_Vector_Array[2] = Test_Two;
    Test_Vector_Array[3] = Test_Three;
    Test_Vector_Array[4] = Test_Four;
    Test_Vector_Array[5] = Test_Five;
    Test_Vector_Array[5] = Test_Six;
    Test_Vector_Array[6] = Test_Seven;


    cell Test_Cell(num, Test_Vector_Array,100);

    for (int i =0;i<num;i++)
    {
        cout << "Test_Cell Vertice " << i << " X: " << Test_Cell.Get_VecPtrs(i).Get_x() << ", Y: " << Test_Cell.Get_VecPtrs(i).Get_y() << ", Z: " << Test_Cell.Get_VecPtrs(i).Get_z() << endl;
    }


    cell Copy_Test(Test_Cell);
    Copy_Test.Set_VecPtrs(7,Test_One);

    for (int i =0;i<num;i++)
    {
        cout << "Copy_Test_Cell Vertice " << i << " X: " << Copy_Test.Get_VecPtrs(i).Get_x() << ", Y: " << Copy_Test.Get_VecPtrs(i).Get_y() << ", Z: " << Copy_Test.Get_VecPtrs(i).Get_z() << endl;
    }