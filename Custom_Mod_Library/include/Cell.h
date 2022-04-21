///
/// @file
/// @brief Cell class used to store Cell shapes that make up a model
/// 


#ifndef Cell_H
#define Cell_H

#include <iostream>
#include <math.h>
#include "3D_Vector.h"

using namespace std;

class Cell;

///
/// @brief Cell class used to store shapes as an vector array of Vector3Ds
///
class Cell{

public:
    ///
    ///Blank Cell constructor with no parameters
    ///
    Cell(); //Default constructor

    ///
    /// Constructor with parameters
    /// @param(uint8_t) Vertice count
    /// @param(Vector3D) array of vector objects
    /// @param(float) Density value
    /// 
    Cell(uint8_t No_Vertices, Vector3D*vectors,float); //Actual constructor

    ///
    /// Cell Destructor
    /// 
    ~Cell(); //Destructor

    ///
    /// Copy Constructor
    /// @param(Cell) Cell object
    /// 
    Cell(const Cell&); //Copy constructor

    ///
    /// Copy operator
    /// Assign the contects of one cell to another
    /// 
    /// Syntax:
    /// a = b;
    /// 
    /// @param(Cell) Cell to be copied
    /// @return(Cell) Cell to be copied to
    /// 
    const Cell& operator=(const Cell&); //Assignment

    //Get and Set for the array of vectors.

    ///
    /// Returns a Vector3D at a certain position in the Cell array
    /// @param(int) Position of Vector3D in the Cell array
    /// @return(Vector3D) The Vector3D that is returned
    /// 
    Vector3D Get_VecPtrs(int);

    ///
    /// Assigns a Vector3D at a defined place in the Vector3D array in the Cell
    /// @param(int) Array position of the Vector3D
    /// @param(Vector3D) The Vector3D object that is going to be inserted into the array
    /// 
    void Set_VecPtrs(int, Vector3D);

    ///
    /// Returns the number of vertices
    /// @return(char) Number of vertices
    /// 
    char Get_Number_Of_Vertices();

    
    ///
    /// Sets the density of the Cell
    /// @param(float) density value
    /// 
    void Set_density(float);

    ///
    /// Unfinished function that returns the centre of gravity of the Cell
    /// @return(float) centre of gravity
    /// 
    float COG_Of_Cell();

    ///
    /// Unfinished function that returns the volume of the Cell
    /// @return(float) volume
    /// 
    float Volume_Of_Cell();

    ///
    /// Unfinished function that returns the weight of the Cell
    /// @return(float) weight
    /// 
    float Weight_Of_Cell();

private:

    char Number_Of_Vertices; //Can only be 4,5 or 8, enforced in constructor function
    Vector3D VecPtrs[8];
    float density; //NEEDS TO COME FROM MATERIAL CLASS
};

#endif
