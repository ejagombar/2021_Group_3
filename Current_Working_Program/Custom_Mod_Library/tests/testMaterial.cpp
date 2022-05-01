#include <iostream>
#include "../include/Material.h"

int main()
{
	Material mat1;

	mat1.set_ID(13);
	std::cout << "\n\nHI " << mat1.get_ID() <<" !";

	if (mat1.get_ID() != 13) {return 1; }

	return 0;
}

