#include <iostream>
#include "3DVector_Copy.h"
using namespace std;

class cell;

class cell{

public:
    cell(); //Default constructor
    cell(const char No_Vertices, Vector *vectors,float); //Actual constructor, No_Vertices should not change in the constructor function therefore is cosnt
    ~cell(); //Destructor
    cell(const cell&); //Copy constructor
    const cell& operator=(const cell&); //Assignment

    //Get and Set for the array of vectors.
    Vector Get_VecPtrs(int);
    void Set_VecPtrs(int, Vector);

    //Get function for Number of Vertices
    char Get_Number_Of_Vertices();

    //Set function for density
    void Set_density(float);

    float COG_Of_Cell();
    float Volume_Of_Cell();
    float Weight_Of_Cell();

private:

    char Number_Of_Vertices; //Can only be 4,5 or 8 (see document, needs to be enforced in make function
    Vector VecPtrs[8];
    float density; //NEEDS TO COME FROM MATERIAL CLASS


};


cell::cell() //Default constructor
{
    Number_Of_Vertices = 0;
    density = 0;
}

cell::cell(const char No_Vertices, Vector *vectors, float Density_Value) //Constructor function
{

    //Enforce 4,5 or 8 Number_Of_Vertices
    if (int(No_Vertices)==4 || int(No_Vertices)==5 || int(No_Vertices)==8)
    {
        Number_Of_Vertices = int(No_Vertices); //Read in the number of vertices the cell is to have
        density = Density_Value;
        //Switch case
        switch(Number_Of_Vertices)
        {
            case 4:
                for(int i = 0;i<Number_Of_Vertices;i++)
                {
                    VecPtrs[i]=vectors[i]; //Read in the vectors from the array.

                }
                break;
            case 5:
                for(int i = 0;i<Number_Of_Vertices;i++)
                {
                    VecPtrs[i]=vectors[i]; //Read in the vectors from the array.

                }
                break;
            case 8:
                for(int i = 0;i<Number_Of_Vertices;i++)
                {
                    VecPtrs[i]=vectors[i]; //Read in the vectors from the array.
                }
                break;
        }
    }
    else
    {
            cout << "Invalid number of vertices!" << endl;
    }
}

cell::~cell() //Destructor
{
    if (VecPtrs)
    {
        delete[] &VecPtrs;
    }
}

cell::cell(const cell& cell_object) //Copy Constructor
{
    density=cell_object.density;
    Number_Of_Vertices=cell_object.Number_Of_Vertices;
    for(int i=0;i<Number_Of_Vertices;i++)
    {
        VecPtrs[i] = cell_object.VecPtrs[i];
    }
}

const cell& cell::operator=(const cell& cell_object)
{
    if (this == &cell_object) return(*this);
    density = cell_object.density;
    Number_Of_Vertices = cell_object.Number_Of_Vertices;
    for(int i=0;i<Number_Of_Vertices;i++)
    {
        VecPtrs[i] = cell_object.VecPtrs[i];
        float a,b,c;
        a=VecPtrs[i].Get_x();
        b=VecPtrs[i].Get_y();
        c=VecPtrs[i].Get_z();
        cout<< a << b << c << endl;
    }
    return (*this);

}

Vector cell::Get_VecPtrs(int index) //Get for VecPtrs
{
    return(VecPtrs[index]);
}

void cell::Set_VecPtrs(int index, Vector Vector_Object) //Set for VecPtrs
{
    VecPtrs[index]=Vector_Object;
}

char cell::Get_Number_Of_Vertices() //Get for Number of Vertices.
{
    return (Number_Of_Vertices);
}

void cell::Set_density(float density_value)
{
    density = density_value;
}

float cell::COG_Of_Cell()
{
    float COG = 0;

    return COG;
}
float cell::Volume_Of_Cell()
{
    float volume = 1;

    return volume;
}
float cell::Weight_Of_Cell()
{
    return Volume_Of_Cell()*density;
}


int main()
{
    int num = 8;
    Vector Test_Vector_Array[num];

    Vector Test_One;
    Test_One.Set_x(1.);
    Test_One.Set_y(1.);
    Test_One.Set_z(1.);

    Vector Test_Two;
    Test_Two.Set_x(2.);
    Test_Two.Set_y(2.);
    Test_Two.Set_z(2.);

    Vector Test_Three;
    Test_Three.Set_x(3.);
    Test_Three.Set_y(3.);
    Test_Three.Set_z(3.);

    Vector Test_Four;
    Test_Four.Set_x(4.);
    Test_Four.Set_y(4.);
    Test_Four.Set_z(4.);

    Vector Test_Five;
    Test_Five.Set_x(5.);
    Test_Five.Set_y(5.);
    Test_Five.Set_z(5.);

    Vector Test_Six;
    Test_Six.Set_x(6.);
    Test_Six.Set_y(6.);
    Test_Six.Set_z(6.);

    Vector Test_Seven;
    Test_Seven.Set_x(7.);
    Test_Seven.Set_y(7.);
    Test_Seven.Set_z(7.);

    Vector Test_Eight;
    Test_Eight.Set_x(8.);
    Test_Eight.Set_y(8.);
    Test_Eight.Set_z(8.);


    Test_Vector_Array[0] = Test_One;
    Test_Vector_Array[1] = Test_Two;
    Test_Vector_Array[2] = Test_Three;
    Test_Vector_Array[3] = Test_Four;
    Test_Vector_Array[4] = Test_Five;
    Test_Vector_Array[5] = Test_Six;
    Test_Vector_Array[6] = Test_Seven;
    Test_Vector_Array[7] = Test_Eight;

    cell Test_Cell(num, Test_Vector_Array,100);

    for (int i =0;i<num;i++)
    {
        cout << "Test_Cell Vertice " << i << " X: " << Test_Cell.Get_VecPtrs(i).Get_x() << ", Y: " << Test_Cell.Get_VecPtrs(i).Get_y() << ", Z: " << Test_Cell.Get_VecPtrs(i).Get_z() << endl;
    }

    cell Copy_Test(Test_Cell);
    Copy_Test.Set_VecPtrs(8,Test_One);

    for (int i =0;i<num;i++)
    {
        cout << "Copy_Test_Cell Vertice " << i << " X: " << Copy_Test.Get_VecPtrs(i).Get_x() << ", Y: " << Copy_Test.Get_VecPtrs(i).Get_y() << ", Z: " << Copy_Test.Get_VecPtrs(i).Get_z() << endl;
    }

    //cout << Test_Cell.Weight_Of_Cell() << endl;

    return(0);
}
