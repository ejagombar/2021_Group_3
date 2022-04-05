///
/// 
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
/// A structure used to store colour
/// Each value is stored as a float between 0 and 1.0
/// 
struct colour
{
    float r, g, b;
};

///
/// @class Material
/// @brief Used to store material data used in MOD files
/// Stores data about the material including ID, Name, Colour and Density
/// 
class Material
{


public:

    ///
    /// Returns the ID number of the material
    /// @return ID number
    /// 
    int get_ID();

    ///
    /// Returns the name of the material
    /// @return Material name
    /// 
    std::string get_Name();

    ///
    /// Returns the colour of the Material
    /// @return Returns colour of material as a type colour
    ///
    colour get_Colour();

    ///
    /// Returns the density of the Material
    /// @return Density of material
    /// 
    float get_Density();

    ///
    /// Sets the ID of the material object
    /// @param ID valule
    /// 
    void set_ID(int IDIn);

    ///
    /// Sets the name of the Material
    /// @param Material name
    /// 
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