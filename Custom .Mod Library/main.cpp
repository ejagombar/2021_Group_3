#include <iostream>
#include <Material.h>
#include <Model.h>

int main()
{
	Material mat1;
    /*Model myModel;

    myModel.LoadModelFile("exampleModel1.mod");

    cout << myModel.GetNumOfVertices() << "\n" << myModel.GetNumOfCells() << "\n" << myModel.GetNumOfMaterials();

    cout << "\nNum of Tetrahedron: " << myModel.GetCellTypeCount(0)
        << " Num of Hexahedron: " << myModel.GetCellTypeCount(1)
        << " Num of Pyramid: " << myModel.GetCellTypeCount(2);*/


	mat1.set_ID(13);
	std::cout << "\n\nHI " << mat1.get_ID() <<" !";
	return 0;
}

