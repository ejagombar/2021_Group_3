#include <iostream>
#include "../include/Model.h"

int main()
{
    Model myModel;

    myModel.LoadModelFile("ExampleModel1.mod");

    //Data for ExampleModel1 file.

    uint16_t val = 12;
    if (myModel.GetNumOfVertices() != val) { return 1; }
    val = 2;
    if (myModel.GetNumOfCells() != val) { return 1; }
    val = 2;
    if (myModel.GetNumOfMaterials() != val) { return 1; }

    if (myModel.GetCellTypeCount(0) != 1) { return 1; }
    if (myModel.GetCellTypeCount(1) != 1) { return 1; }
    if (myModel.GetCellTypeCount(2) != 0) { return 1; }

    cout << "passed";

    return 0;
}