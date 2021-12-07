// Model.cpp : Defines the entry point for the application.
//

#include "Model.h"



using namespace std;

//------------------------------Constructors-------------------------------
//-------------------------------------------------------------------------

Model::Model()                                        //Constructor
{
 
}


Model::~Model() {}                                    //Destructor


Model::Model(const Model& ModelCopy)                  //Copy Constructor
    :numOfVertices(ModelCopy.numOfVertices),
    numOfCells(ModelCopy.numOfCells),
    numOfMaterials(ModelCopy.numOfMaterials)
{
    memmove(cellTypeCount, ModelCopy.cellTypeCount, sizeof(cellTypeCount));
}


const Model& Model::operator=(const Model& ModelCopy) //Assignment
{ 
    if (this == &ModelCopy) return(*this);

    numOfVertices = ModelCopy.numOfVertices;
    numOfCells = ModelCopy.numOfCells;
    numOfMaterials = ModelCopy.numOfMaterials;
    memmove(cellTypeCount, ModelCopy.cellTypeCount, sizeof(cellTypeCount));

    return(*this);
}




//--------------------------------Getters----------------------------------
//-------------------------------------------------------------------------

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

uint16_t Model::GetCellTypeCount(uint16_t cellType) //returns number of cells in file of type 'cellType'
{                                                  // 0 - Tetrahedron, 1 - Hexahedron, 2 - Pyramid
    if ((cellType < sizeof(cellTypeCount)) && (cellType >= 0))
    {
        return cellTypeCount[cellType]; //returns value as long as cellType is in range 
    }
    else
    {
        cout << "\nERROR - cellType out of range";
    }
}

Vector Model::GetModelCentre()
{
    return ModelCentre;
}


//---------------------------Public Functions------------------------------
//-------------------------------------------------------------------------



//---------------------LoadModelFile-----------------------
//Takes the name of the file as a string in input.
//fileName needs to include relative path to the model.exe file
//returns 0 if an error occurs or else returns 1
bool Model::LoadModelFile(const string fileName)
{
    ifstream fileIn;

    fileIn.open(fileName);
    if (fileIn.is_open())
    {
        if (!GetObjectCountsAndType(fileIn)) return 0;

        //the vertice and cell vector arrays can be set to length now we know the numbers of each
        verticeArray.resize(numOfVertices); 
        cellArray.resize(numOfCells);

        fileIn.clear(); //clear eof and fail flags from the file stream 
        fileIn.seekg(0); //return to start of file

        string line{};
        char firstLetter;

        while (getline(fileIn, line)) //sets current line to the line string and repeats until no lines left
        {
            if (fileIn.is_open() && (!line.empty())) //make sure file is still open and line is not empty
            {
                firstLetter = line.front();
                switch (firstLetter) {
                case 't':
                    //
                    break;
                case 'h':
                    //
                    break;
                case 'p':
                    //
                    break;
                }
            
            }
        }

        fileIn.close();


    }
    else
    {
        cout << "ERROR - Failed to open file";
        return 0;
    }

    return 1;
}


//---------------------SaveModelFile-----------------------
void Model::SaveModelFile()
{

}


//--------------------------Private Functions------------------------------
//-------------------------------------------------------------------------


//----------------GetObjectCountsAndType-------------------
//Must be called while the file is open
//The file is passed into the fucntion via reference
bool Model::GetObjectCountsAndType(ifstream& fileIn)
{
    string line{};
    char firstLetter, cellType;
    uint16_t vCount = 0, mCount = 0, cCount = 0;
    uint16_t typeCount[3];
    typeCount[0] = typeCount[1] = typeCount[2] = 0;

    while (getline(fileIn, line)) //sets current line to the line string and repeats until no lines left
    {
        if (fileIn.is_open() && (!line.empty())) //make sure file is still open and line is not empty
        {
            firstLetter = line.front();

            if (firstLetter == 'v') { vCount += 1; }
            else if (firstLetter == 'm') { mCount += 1; }
            else if (firstLetter == 'c')
            {
                cCount += 1;
                cellType = line.at(4); //character 5 denotes the cell type

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
                    cout << "\nERROR - Cell type not found";
                    return 0; //error as cell type not found
                }

            }
        }
    }

    //Count variables for the object are all set at the end of the function

    memmove(cellTypeCount, typeCount, sizeof(cellTypeCount));
    numOfVertices = vCount;
    numOfCells = cCount;
    numOfMaterials = mCount;

    return 1; //finished with no errors
}



//--------------------CalculateCentre----------------------
void Model::CalculateCentre() {


}


int main()
{
	cout << "Hello CMake." << endl;

    Model myModel;

    myModel.LoadModelFile("exampleModel1.mod");

    cout << myModel.GetNumOfVertices() << "\n" << myModel.GetNumOfCells() << "\n" << myModel.GetNumOfMaterials();
    uint16_t cellTypeCount[3];
    cout << "\nNum of Tetrahedron: " << myModel.GetCellTypeCount(0)
        << " Num of Hexahedron: " << myModel.GetCellTypeCount(1)
        << " Num of Pyramid: " << myModel.GetCellTypeCount(2);

	return 0;


}
