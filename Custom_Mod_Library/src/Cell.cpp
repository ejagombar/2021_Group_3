#include "../include/Cell.h"

Cell::Cell() //Default constructor
{
    Number_Of_Vertices = 0;
    density = 0;
}

Cell::Cell( uint8_t No_Vertices, Vector3D *vectors, float Density_Value) //Constructor function
{

    //Enforce 4,5 or 8 Number_Of_Vertices
    if (int(No_Vertices)==4 || int(No_Vertices)==5 || int(No_Vertices)==8)
    {
        cout << "Made it into constructor";
        Number_Of_Vertices = int(No_Vertices); //Read in the number of vertices the Cell is to have
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

Cell::~Cell() //Destructor
{
}

Cell::Cell(const Cell& Cell_object) //Copy Constructor
{
    density=Cell_object.density;
    Number_Of_Vertices=Cell_object.Number_Of_Vertices;
    for(int i=0;i<Number_Of_Vertices;i++)
    {
        VecPtrs[i] = Cell_object.VecPtrs[i];
    }
}

const Cell& Cell::operator=(const Cell& Cell_object) //Assignment
{
    if (this == &Cell_object) return(*this);
    density = Cell_object.density;
    Number_Of_Vertices = Cell_object.Number_Of_Vertices;
    for(int i=0;i<Number_Of_Vertices;i++)
    {
        VecPtrs[i] = Cell_object.VecPtrs[i];

    }
    return (*this);

}

Vector3D Cell::Get_VecPtrs(int index) //Get for VecPtrs
{
    return(VecPtrs[index]);
}

void Cell::Set_VecPtrs(int index, Vector3D Vector_Object) //Set for VecPtrs
{
    VecPtrs[index] = Vector_Object;
}

char Cell::Get_Number_Of_Vertices() //Get for Number of Vertices.
{
    return (Number_Of_Vertices);
}

void Cell::Set_density(float density_value)
{
    density = density_value;
}

float Cell::COG_Of_Cell()
{
    float COG = 0;

    return COG;
}
float Cell::Volume_Of_Cell()
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
float Cell::Weight_Of_Cell()
{
    return Volume_Of_Cell()*density;
}
