//-----------------------------//
//        Edward Agombar       //
//           20240645          //
//-----------------------------//


#pragma once
#include <iostream>
#include <fstream>

using namespace std;


//-------------------------------Model Class-------------------------------
//-------------------------------------------------------------------------


class Model {


public:

    void loadModelFile(const string fileName);
    void saveModelFile();

    void CalculateCentre();

    //void GetNumOfVertices();
    //void GetNumOfCellType();
    //void GetModelCentre();


private:

    //Cell* cells;
    //Vector* vectors;
    int numOfVertices;
    //Vector ModelCentre;


};
