// Material.cpp : Defines the entry point for the application.
//

#include "../include/Material.h"
#include <iostream>




//------------------------------Constructors-------------------------------
//-------------------------------------------------------------------------

Material::Material()
{
	ID = 0;
	name = "";
	materialColour.r = 0;
	materialColour.g = 0;
	materialColour.b = 0;
	density = 0;
}

Material::Material(int IDIn, std::string nameIn, colour colourIn, float densityIn)
{
	ID = IDIn;
	name = nameIn;
	materialColour = colourIn;
	density = densityIn;
}


Material::Material(const Material& MaterialCopy)
	:ID(MaterialCopy.ID),
	name(MaterialCopy.name),
	materialColour(MaterialCopy.materialColour),
	density(MaterialCopy.density)
{

}

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

void Material::set_ID(int IDIn)
{
	ID = IDIn;
}

void Material::set_Name(std::string nameIn)
{
	name = nameIn;
}

void Material::set_Coluour(colour colourIn)
{
	materialColour = colourIn;
}

void Material::set_Density(float densityIn)
{
	density = densityIn;
}
