#include <iostream>
#include "../include/Model.h"

int main()
{
    Model myModel;

    myModel.LoadModelFile("ExampleModel1.mod");

    cout << myModel.GetNumOfVertices() << "\n" << myModel.GetNumOfCells() << "\n" << myModel.GetNumOfMaterials();

    cout << "\nNum of Tetrahedron: " << myModel.GetCellTypeCount(0)
        << " Num of Hexahedron: " << myModel.GetCellTypeCount(1)
        << " Num of Pyramid: " << myModel.GetCellTypeCount(2);

    return 0;
}