#include <iostream>

#include<bits/stdc++.h>

using namespace std;

class cell;
class Vector_class;

class Vector_class {

public:
    int x;
    int y;
    int z;
};

//----------------------------------------------------------------------
//-----------------------------cell Class ------------------------------
//----------------------------------------------------------------------
class cell {
public:
    cell(); //Default constructor - cell will never be initialised so no need to special constructor
    ~cell(); //Destructor
    cell(const cell& c); //Copy constructor

    float Get_density(); //Needed to calculate weight and COG
    void Set_density(float Density_); //Needed for child classes to access density

    float COG_Of_Cell(); //To calculate centre of gravity
    float Volume_Of_Cell(); //To calculate the volume of the cell
    float Weight_Of_Cell(float volume, float density_); //To calculate weight of cell

private:
    float density; //NEEDS TO COME FROM MATERIAL CLASS, set in each child class
protected:
    std::vector<Vector_class*> Vector_List; //set in each child class
};

//----------------------------------------------------------------------
//-----------------------cell Constructor function-----------------------
//----------------------------------------------------------------------

cell::cell() {}

//----------------------------------------------------------------------
//-----------------------cell Destructor function-----------------------
//----------------------------------------------------------------------
cell::~cell() {
    Vector_List.clear();
}

//----------------------------------------------------------------------
//--------------------------cell copy function--------------------------
//----------------------------------------------------------------------

cell::cell(const cell& c) {}

//----------------------------------------------------------------------
//------------------------cell Member functions-------------------------
//----------------------------------------------------------------------

float cell::COG_Of_Cell() {}
float cell::Volume_Of_Cell() {}
float cell::Weight_Of_Cell(float volume, float Density_)
{
    return (volume * Density_);
}
void cell::Set_density(float Density_)
{
    density = Density_;
}
float cell::Get_density()
{
    return density;
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------
//-------------------------Tetrahedron Class----------------------------
//----------------------------------------------------------------------
//Class which is a child class of cell.
class Tetrahedron : public cell
{
public:

    Tetrahedron(); //Default constructor
    Tetrahedron(Vector_class* Vector_Array, float Density_); //Actual constructor, No_Vertices should not change in the constructor function therefore is cosnt
    ~Tetrahedron(); //Destructor
    Tetrahedron(const Tetrahedron& c); //Copy constructor

    void Set_Vector(Vector_class* Vector_Array);
    void Get_Vector(int index); //NEEED TOOOO INITIALISE

    float COG_Of_Cell(); //To calculate centre of gravity
    float Volume_Of_Cell(); //To calculate the volume of the cell
    float Weight_Of_Cell(); //To calculate weight of cell

private:
};

void Tetrahedron::Set_Vector(Vector_class* Vector_Array)
{
    for (int i; i < 4; i++)//know its 4 as tetrahedron
    {
        Vector_List.push_back(&Vector_Array[i]);
    }

}

void Tetrahedron::Get_Vector()

Tetrahedron::Tetrahedron() {};
Tetrahedron::~Tetrahedron() {};
//----------------------------------------------------------------------
//------------------Tetrahedron Special Constructor---------------------
//----------------------------------------------------------------------
Tetrahedron::Tetrahedron(Vector_class* Vector_Array, float Density_)
{
    Set_density(Density_);

    for (int i; i < 4; i++)
    {
        Set_Vector(&Vector_Array[i]);
    }
}

int main()
{
    Vector_class Test_Vector_Array[4];

    Vector_class Test_One;
    Test_One.x = 1;
    Test_One.y = 1;
    Test_One.z = 1;

    Vector_class Test_Two;
    Test_Two.x = 2;
    Test_Two.y = 2;
    Test_Two.z = 2;

    Vector_class Test_Three;
    Test_Three.x = 3;
    Test_Three.y = 3;
    Test_Three.z = 3;

    Vector_class Test_Four;
    Test_Four.x = 4;
    Test_Four.y = 4;
    Test_Four.z = 4;

    Test_Vector_Array[0] = Test_One;
    Test_Vector_Array[1] = Test_Two;
    Test_Vector_Array[2] = Test_Three;
    Test_Vector_Array[3] = Test_Four;

    Tetrahedron Tetrahedron_Test(Test_Vector_Array, 50);

    float Density;
    Density = Tetrahedron_Test.Get_density();
    cout << Density << endl;
}
