///
/// @file
/// @brief This file contains the source code for colour class and Material class
/// 

#include "../include/Material.h"
#include <iostream>




//------------------------------Constructors-------------------------------
//-------------------------------------------------------------------------

/// <summary>
/// Default declaration for a material.
/// Initilizes all values to 0
/// </summary>
Material::Material()
{
	ID = 0;
	name = "";
	materialColour.r = 0;
	materialColour.g = 0;
	materialColour.b = 0;
	density = 0;
}

/// <summary>
/// Declaration for material with all parameters
/// </summary>
/// <param name="IDIn"></param>
/// <param name="nameIn"></param>
/// <param name="colourIn"></param>
/// <param name="densityIn"></param>
Material::Material(int IDIn, std::string nameIn, colour colourIn, float densityIn)
{
	ID = IDIn;
	name = nameIn;
	materialColour = colourIn;
	density = densityIn;
}

/// <summary>
/// Declare a material with the data of another object
/// Syntax to declare a with data of b
/// a(b);
/// </summary>
/// <param name="MaterialCopy"></param>
Material::Material(const Material& MaterialCopy)
	:ID(MaterialCopy.ID),
	name(MaterialCopy.name),
	materialColour(MaterialCopy.materialColour),
	density(MaterialCopy.density)
{

}

/// <summary>
/// Copy the data from one object to another
/// Sytanx to copy data from b to a
/// a = b;
/// </summary>
/// <param name="MaterialCopy"></param>
/// <returns></returns>
const Material& Material::operator=(const Material& MaterialCopy)
{
	if (this == &MaterialCopy) return(*this);

	ID = MaterialCopy.ID;
	name = MaterialCopy.name;
	materialColour = MaterialCopy.materialColour;
	density = MaterialCopy.density;

	return(*this);
}

//--------------------------------Getters----------------------------------
//-------------------------------------------------------------------------


int Material::get_ID()
{
	return ID;
}

std::string Material::get_Name()
{
	return name;
}

colour Material::get_Colour()
{
	return materialColour;
}

float Material::get_Density()
{
	return density;
}

//--------------------------------Setters----------------------------------
//-------------------------------------------------------------------------

/// <summary>
/// test other set id as int
/// </summary>
/// <param name="IDIn"></param>
void Material::set_ID(int IDIn)
{
	ID = IDIn;
}

void Material::set_Name(std::string nameIn)
{
	name = nameIn;
}

void Material::set_Colour(colour colourIn)
{
	materialColour = colourIn;
}

void Material::set_Density(float densityIn)
{
	density = densityIn;
}
