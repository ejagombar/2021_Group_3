// CMakeProject1.cpp : Defines the entry point for the application.
//

#include "CMakeProject1.h"
#include <iostream>
//#include<bits/stdc++.h>

using namespace std;

class cell;
class Vector_class;

class Vector_class {

public:
    int x;
    int y;
    int z;

};

class cell {

public:
    cell(); //Default constructor
    cell(const char No_Vertices, Vector_class* vectors);//No_Vertices should not change in the constructor function therefore is cosnt
    ~cell(); //Destructor

    //void Get_Cell(); //Maybe not needed
    //void Set_Cell();

    float COG_Of_Cell();
    float Volume_Of_Cell();
    float Weight_Of_Cell();

private:

    char Number_Of_Vertices; //Can only be 4,5 or 8 (see document, needs to be enforced in make function
    std::vector<Vector_class*> VecPtrs;
    float density; //NEEDS TO COME FROM MATERIAL CLASS


};

cell::cell() {
    //VecPtrs = NULL;
}

//Constructor function
cell::cell(const char No_Vertices, Vector_class* vectors) { //Constructor function

    //Enforce 4,5 or 8 Number_Of_Vertices
    if (int(No_Vertices) == 4 || int(No_Vertices) == 5 || int(No_Vertices) == 8)
    {
        Number_Of_Vertices = int(No_Vertices);
        //Switch case
        switch (Number_Of_Vertices)
        {
        case 4:
            cout << "Yep" << endl; //DELETE THIS
            VecPtrs.resize(Number_Of_Vertices);
            for (int i = 0; i < Number_Of_Vertices; i++)
            {
                ;                    
                VecPtrs[i]->x = 0;
                //vectors[i].x;
                cout << /*VecPtrs[i]->x << "y" << "z" << endl;
            }
            break;
        case 5:
            //
            break;
        case 8:
            //
            break;
        }
    }
    else
    {
        cout << "Nope" << endl;
    }


    //Set Number_Of_Vertices equal to int(No_Vertices)

    //For No_Vertices
        //Add each vector address to the Vector_Array[] array.

}

cell::~cell() {
    /*
    if (VecPtrs)
    {
        delete[] &VecPtrs;
    }
    */
    if (Number_Of_Vertices)
    {
        delete[] & Number_Of_Vertices;
    }
    if (density)
    {
        delete[] & density;
    }
}


int main()
{
	cout << "Hello CMake." << endl;
	return 0;
}
