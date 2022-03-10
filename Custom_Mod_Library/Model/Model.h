//-----------------------------//
//        Edward Agombar       //
//           20240645          //
//-----------------------------//


#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Vector {};
class Cell {};

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
    Vector GetModelCentre();
    

    Model();                                              //Constructor

    ~Model();                                         
    Model(const Model& ModelCopy);                        //Copy constructor

    const Model& operator=(const Model& ModelCopy);       //Assignment operator
    //Destructor



private:

    vector <Cell> cellArray;
    vector <Vector> verticeArray;

    Vector ModelCentre;
    uint16_t numOfCells;
    uint16_t numOfVertices;
    uint16_t numOfMaterials;
    uint16_t cellTypeCount[3]; //Order: Tetrahedron, Hexahedron, Pyramid

    bool GetObjectCountsAndType(ifstream& fileIn);
    void ReadCellFromFile(string &line);
    void ReadVectorFromFile(string &line);
    void ReadMaterialFromFile(string &line);
    
};
