///
/// @file
/// @class Material
/// @brief Class used to store Materials for the Model class
/// 
/// This Class is responsible for storing data about a Material such as its ID, Name, density and colour. 
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

/// 
/// @brief A structure used to store colour
/// Each value is stored as a float between 0 and 1.0
/// 
struct colour
{
    float r, g, b;
};

///
/// @struct Material
/// @brief Used to store material data used in MOD files
/// Stores data about the material including ID, Name, Colour and Density
/// 
class Material
{


public:

    ///
    /// Material Constructor with no parameters.
    /// Everything is set to 0 and "" by default.
    /// 
    Material();                                                                  //Default Constructor

    ///
    /// Material constructor with parameters.
    /// @param(int) ID number
    /// @param(string) Material name
    /// @param(colour) Material colour
    /// @param(float) Materail density
    /// 
    Material(int IDIn, std::string nameIn, colour colourIn, float densityIn);    //Populated Constructor

    ///
    /// Material destructor
    /// 
    ~Material() {};                                                              //Destructor

    ///
    /// Copy constructor 
    /// 
    /// @param(Material) Material object
    /// 
    Material(const Material& MaterialCopy);                                      //Copy constructor

    ///
    /// Copy operator
    /// Assign the contents of one Material object to another.
    /// 
    /// Syntax: 
    /// a = b;
    /// 
    /// @param(Material) Material to be copied
    /// @return(Material) Material to be copied to
    /// 
    const Material& operator=(const Material& MaterialCopy);                     //Assignment operator



    ///
    /// Returns the ID number of the material
    /// @return(int) ID number
    /// 
    int get_ID();

    ///
    /// Returns the name of the material
    /// @return(string) Material name
    /// 
    std::string get_Name();

    ///
    /// Returns the colour of the Material
    /// @return(colour) Returns colour of material as a type colour
    ///
    colour get_Colour();

    ///
    /// Returns the density of the Material
    /// @return(float) Density of material
    /// 
    float get_Density();

    ///
    /// Sets the ID of the material object
    /// @param(int) ID value
    /// 
    void set_ID(int IDIn);

    ///
    /// Sets the name of the Material
    /// @param(string) Material name
    /// 
    void set_Name(std::string nameIn);

    ///
    /// Sets the colour of the Material
    /// @param(colour) Material Colour
    /// 
    void set_Colour(colour colourIn);

    ///
    /// Sets the density of the Material
    /// @param(float) Density of material
    /// 
    void set_Density(float densityIn);
   
private:

    int ID;
    std::string name;
    colour materialColour;
    float density;

};


#endif