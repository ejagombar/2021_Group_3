//-----------------------------//
//        Edward Agombar       //
//           20240645          //
//-----------------------------//
#ifndef Material_H
#define Material_H


#include <string>




//-------------------------------Material Class-------------------------------
//-------------------------------------------------------------------------

struct colour {
    float r, g, b;
};


class Material
{


public:

    int get_ID();
    std::string get_Name();
    colour get_Colour();
    float get_Density();

    void set_ID(int IDIn);
    void set_Name(std::string nameIn);
    void set_Coluour(colour colourIn);
    void set_Density(float densityIn);


    Material();                                              //Constructor
    Material(int IDIn, std::string nameIn, colour colourIn, float densityIn);

    ~Material() {};

    Material(const Material& MaterialCopy);                        //Copy constructor

    const Material& operator=(const Material& MaterialCopy);       //Assignment operator
    //Destructor



private:

    int ID;
    std::string name;
    colour materialColour;
    float density;

};


#endif