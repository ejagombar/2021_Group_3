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


class Model
{


public:

    void loadModelFile(const string fileName);
    void saveModelFile();

    void CalculateCentre();

    uint16_t GetNumOfVertices();
    uint16_t GetNumOfCells();
    
    //void GetModelCentre();


private:

    bool GetObjectCountsAndType(ifstream& fileIn);

    //Cell* cells;
    //Vector* vectors;

    uint16_t numOfVertices;
    uint16_t numOfCells;
    uint16_t numOfMaterials;
    uint16_t cellTypeCount[3]; //Order: Tetrahedron, Hexahedron, Pyramid
    //Vector ModelCentre;


};
