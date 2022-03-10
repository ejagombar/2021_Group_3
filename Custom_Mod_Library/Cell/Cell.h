#ifndef Cell_H
#define Cell_H

#include <iostream>
#include <math.h>
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

    char Number_Of_Vertices; //Can only be 4,5 or 8, enforced in constructor function
    Vector VecPtrs[8];
    float density; //NEEDS TO COME FROM MATERIAL CLASS
};

#endif