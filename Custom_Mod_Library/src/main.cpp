#include <iostream>
#include "../include/Material.h"
#include "../include/Model.h"
#include "../include/Cell.h"

int main()
{
	Material mat1;

	mat1.set_ID(13);
	std::cout << "\n\nHI " << mat1.get_ID() <<" !";
	return 0;
}
