//-----------------------------//
//        Edward Agombar       //
//           20240645          //
//-----------------------------//

#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

#include "Cell.h"

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
    Vector3D GetModelCentre();
    

    Model();                                              //Constructor

    ~Model();                                         
    Model(const Model& ModelCopy);                        //Copy constructor

    const Model& operator=(const Model& ModelCopy);       //Assignment operator
    //Destructor



private:

    std::vector <cell> cellArray;
    std::vector <Vector3D> verticeArray;

    Vector3D ModelCentre;
    uint16_t numOfCells;
    uint16_t numOfVertices;
    uint16_t numOfMaterials;
    uint16_t cellTypeCount[3]; //Order: Tetrahedron, Hexahedron, Pyramid

    bool GetObjectCountsAndType(ifstream& fileIn);
    void ReadCellFromFile(string &line);
    void ReadVectorFromFile(string &line);
    void ReadMaterialFromFile(string &line);
    
};


#endif