///
/// @file
/// @brief Header file that contains the declaration for colour class and Material class
/// 
//-----------------------------//
//        Edward Agombar       //
//           20240645          //
//-----------------------------//
#ifndef Material_H
#define Material_H


#include <string>





//-------------------------------Material Class-------------------------------
//-------------------------------------------------------------------------

/// @brief A structure used to store colour
///
/// Each value is stored as a float between 0 and 1.0
struct colour {
    float r, g, b;
};

/// @brief Used to store material data used in MOD files
///
/// Stores data about the material including ID, Name, Colour and Density
class Material
{


public:

    int get_ID();
    std::string get_Name();
    colour get_Colour();
    float get_Density();

    void set_ID(int IDIn);
    void set_Name(std::string nameIn);
    void set_Colour(colour colourIn);
    void set_Density(float densityIn);


    Material();                                                                  //Default Constructor
    Material(int IDIn, std::string nameIn, colour colourIn, float densityIn);    //Populated Constructor

    ~Material() {};                                                              //Destructor
            
    Material(const Material& MaterialCopy);                                      //Copy constructor

    const Material& operator=(const Material& MaterialCopy);                     //Assignment operator
   



private:

    int ID;
    std::string name;
    colour materialColour;
    float density;

};


#endif