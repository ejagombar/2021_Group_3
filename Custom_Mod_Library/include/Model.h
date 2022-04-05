///
/// @class Model
/// @brief Class used to open, save and store .mod files
/// 
/// This class is responsible for reading model entities from a .mod file.
/// The class stores the data for the model entites using the Cell 3D_Vector and Material Class.
///  

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

/// 
/// @brief A model class used to load, store and save .MOD files
/// 
class Model
{


public:

    ///
    /// Loads a model from a .mod file and stores it in the object.
    /// @param[in] fileName The full path of the file being opened
    /// @return Returns 0 for pass and 1 for error
    /// 
    bool LoadModelFile(const string fileName);

    ///
    /// Unfinished function to save the Object and its data to a .mod file.
    /// 
    void SaveModelFile();

    ///
    /// Unfinished function to calculate the centre of the model and return its coordinates.
    /// 
    void CalculateCentre();

    ///
    /// Returns the number of Verticies in the Model.
    /// 
    uint16_t GetNumOfVertices();

    ///
    /// Returns the number of Cells in the Model.
    /// @return Number of vertices
    /// 
    uint16_t GetNumOfCells();

    ///
    /// Returns the number of Materials in the Model.
    /// @return Number of materials
    uint16_t GetNumOfMaterials();

    ///
    /// Returns the number of cells of the inputted type
    /// @param[in] cellType Type that wants to be counted (0 - Tetrahedron, 1 - Hexahedron, 2 - Pyramid)
    /// @return Cell count of either Tetrahedron, Hexahedron or Pyramid
    /// 
    uint16_t GetCellTypeCount(uint16_t cellType);

    ///
    /// Unfinished function that will return the centre of the model
    /// @return Model centre coordinates
    /// 
    Vector3D GetModelCentre();
    
    ///
    /// Blank Model constructor with no parameters
    /// 
    Model();                                              //Constructor

    ///
    /// Model destructor
    /// 
    ~Model();                                             //Destructor

    ///
    /// Copy constructor
    /// @param[in] Model object
    /// 
    Model(const Model& ModelCopy);                        //Copy constructor

    ///
    /// Copy operator
    /// Assign the contents of one Model object to another.
    /// 
    /// Syntax: 
    /// a = b;
    const Model& operator=(const Model& ModelCopy);       //Assignment operator
    



private:

    std::vector <cell> cellArray;
    std::vector <Vector3D> verticeArray;

    Vector3D ModelCentre;
    uint16_t numOfCells;
    uint16_t numOfVertices;
    uint16_t numOfMaterials;
    uint16_t cellTypeCount[3]; //Order: Tetrahedron, Hexahedron, Pyramid

    ///
    /// This function must be on an open file.
    /// 
    /// Scan the .mod file and counts the number of Cells, Vertices, and Materials.
    /// The type and counts of each cell type is also stored
    /// @param[in] the open .mod file
    /// @return 0 for sucess and 1 for fail
    bool GetObjectCountsAndType(ifstream& fileIn);

    ///
    /// Used to read lines from a .mod file that contain Cell information.
    /// @param a string of text that is a line from the .mod file
    /// 
    void ReadCellFromFile(string &line);

    ///
    /// Used to read lines from a .mod file that contain Vector information.
    /// @param a string of text that is a line from the .mod file
    ///  
    void ReadVectorFromFile(string &line);

    ///
    /// Used to read lines from a .mod file that contain Material information.
    /// @param a string of text that is a line from the .mod file
    /// 
    void ReadMaterialFromFile(string &line);
    
};


#endif