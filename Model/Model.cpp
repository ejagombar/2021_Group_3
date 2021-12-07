// Model.cpp : Defines the entry point for the application.
//

#include "Model.h"
#include <string>


using namespace std;

//-------------------------------Model Class-------------------------------
//-------------------------------------------------------------------------



//Passing in a file of type ifstream
bool Model::loadModelFile(const string fileName)
{
	ifstream fileIn;

	fileIn.open(fileName);
	if (fileIn.is_open())
    {
        GetObjectCountsAndType(fileIn);

        fileIn.close();

     
	}
    else
    {
        cout << "ERROR - Failed to open file";
        return 0;
    }
    

    return 1;
}

void Model::saveModelFile()
{

}

bool Model::GetObjectCountsAndType(ifstream& fileIn)
{
    string line{};
    char firstLetter, cellType;
    uint16_t vCount = 0, mCount = 0, cCount = 0;
    uint16_t typeCount[3];
    typeCount[0] = typeCount[1] = typeCount[2] = 0;
 
    while (getline(fileIn, line))
    {
        if (fileIn.is_open() && (!line.empty()))
        {
            firstLetter = line.front();

            if (firstLetter == 'v') { vCount += 1; }
            else if (firstLetter == 'm') { mCount += 1; }
            else if (firstLetter == 'c')
            {
                cCount += 1;
                cellType = line.at(4);

                switch (cellType) {
                case 't':
                    typeCount[0] += 1;
                    break;
                case 'h':
                    typeCount[1] += 1;
                    break;
                case 'p':
                    typeCount[2] += 1;
                    break;
                default:
                    return 0; //error
                }

            }
        }
    }

    memmove(cellTypeCount, typeCount, sizeof(cellTypeCount));
    numOfVertices = vCount;
    numOfCells = cCount;
    numOfMaterials = mCount;

    return 1; //finished with no errors
}

void Model::CalculateCentre() {


}

uint16_t Model::GetNumOfVertices()
{
    return numOfVertices;
}

uint16_t Model::GetNumOfCells()
{
    return numOfCells;
}

uint16_t Model::GetNumOfMaterials()
{
    return numOfMaterials;
}

void Model::GetCellTypeCount(uint16_t CountArrOut[])
{
    memmove(CountArrOut, cellTypeCount, sizeof(CountArrOut));
}




int main()
{
	cout << "Hello CMake." << endl;
	fstream test;

    Model myModel;

    myModel.loadModelFile("exampleModel1.mod");

    cout << myModel.GetNumOfVertices() << "\n" << myModel.GetNumOfCells() << "\n" << myModel.GetNumOfMaterials();
    uint16_t cellTypeCount[3];
    myModel.GetCellTypeCount(cellTypeCount);
    //cout << "\nNum of Tetrahedron: " << cellTypeCount[0] << " Num of Hexahedron: " << cellTypeCount[1] << " Num of Pyramid: " << cellTypeCount[2];

	return 0;


}
