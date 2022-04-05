///
/// @file
/// @class Cell
/// @brief Cell class used to store Cell shapes that make up a model
/// 


#ifndef Cell_H
#define Cell_H

#include <iostream>
#include <math.h>
#include "3D_Vector.h"

using namespace std;

class Cell;

/// @brief Cell class used to store shapes as an vector array of Vector3Ds
///
/// Stores data about the Cell such as the location of the points, density, centre of mass, volume and weight.
class Cell{

public:
    Cell(); //Default constructor
    Cell(uint8_t No_Vertices, Vector3D*vectors,float); //Actual constructor
    ~Cell(); //Destructor
    Cell(const Cell&); //Copy constructor
    const Cell& operator=(const Cell&); //Assignment

    //Get and Set for the array of vectors.
    Vector3D Get_VecPtrs(int);
    void Set_VecPtrs(int, Vector3D);

    //Get function for Number of Vertices
    char Get_Number_Of_Vertices();

    //Set function for density
    void Set_density(float);

    float COG_Of_Cell();
    float Volume_Of_Cell();
    float Weight_Of_Cell();

private:

    char Number_Of_Vertices; //Can only be 4,5 or 8, enforced in constructor function
    Vector3D VecPtrs[8];
    float density; //NEEDS TO COME FROM MATERIAL CLASS
};

#endif
