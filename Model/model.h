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

    bool LoadModelFile(const string fileName);
    void SaveModelFile();

    void CalculateCentre();

    uint16_t GetNumOfVertices();
    uint16_t GetNumOfCells();
    uint16_t GetNumOfMaterials();
    uint16_t GetCellTypeCount(uint16_t cellType);
    
    //void GetModelCentre();

    Model();                                              //Constructor

    ~Model();                                             //Destructor

    Model(const Model& ModelCopy);                        //Copy constructor

    const Model& operator=(const Model& ModelCopy);       //Assignment operator



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
