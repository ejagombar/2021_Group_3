#include "../include/Cell.h"


/** @file
* This file contains the definition of the cell class
*/

/**Breif description
* A Cell is a collection of vectors that make up a shape.
*/

cell::cell() //Default constructor
{
    Number_Of_Vertices = 0;
    density = 0;
}

cell::cell( uint8_t No_Vertices, Vector3D *vectors, float Density_Value) //Constructor function
{

    //Enforce 4,5 or 8 Number_Of_Vertices
    if (int(No_Vertices)==4 || int(No_Vertices)==5 || int(No_Vertices)==8)
    {
        cout << "Made it into constructor";
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

const cell& cell::operator=(const cell& cell_object) //Assignment
{
    if (this == &cell_object) return(*this);
    density = cell_object.density;
    Number_Of_Vertices = cell_object.Number_Of_Vertices;
    for(int i=0;i<Number_Of_Vertices;i++)
    {
        VecPtrs[i] = cell_object.VecPtrs[i];

    }
    return (*this);

}

Vector3D cell::Get_VecPtrs(int index) //Get for VecPtrs
{
    return(VecPtrs[index]);
}

void cell::Set_VecPtrs(int index, Vector3D Vector_Object) //Set for VecPtrs
{
    VecPtrs[index] = Vector_Object;
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
    float volume = 0;

    switch (Number_Of_Vertices)
    {
      case 4:

          break;

      case 5:

          break;

        case 8:

            break;
    }

    return volume;
}
float cell::Weight_Of_Cell()
{
    return Volume_Of_Cell()*density;
}
