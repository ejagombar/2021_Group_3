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
                case 'v':
                    ReadVectorFromFile(line);
                    break;
                case 'm':
                    ReadMaterialFromFile(line);
                    break;
                case 'c':
                    ReadCellFromFile(line);
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


//-------------------ReadCellFromFile----------------------
void Model::ReadCellFromFile(string& line)
{
    uint8_t searchState = 0;
    int8_t tempState = 4;
    string cellId, cellMaterial, cellType, verticeId;
    Vector* vectorPtr; //CHANGE THIS to correction vector class name
    uint8_t numOfElements;

    for (int i = 0; i < line.length(); i++)
    {
        char currentChar = line[i];

        if (currentChar == ' ')
        {
            searchState += 1;
        }
        else
        {
            switch (searchState)
            {
            case 0: //Reading first character defining it as a cell - does not need to be stored 
                break;
            case 1: //Reading second data entry in cell - cell ID
                cellId.push_back(currentChar);
                break;
            case 2: //Reading third data entry - cell type
                cellType.push_back(currentChar);
                switch (currentChar) {
                case 't': numOfElements = 4; break;
                case 'h': numOfElements = 8; break;
                case 'p': numOfElements = 5; break;
                default:
                    cout << "\nERROR - Cell type not found";
                }
                vectorPtr = (Vector*)malloc(numOfElements * sizeof(Vector)); //CHANGE THIS to correct vector class names
                break;
            case 3:
                cellMaterial.push_back(currentChar);
                break;
            default: // adds the rest of the data points to the array

                if (searchState != tempState)
                {   
                    cout << "Vert: " << verticeId << endl;
                    verticeId.clear();
                    tempState = searchState;
                }
                verticeId.push_back(currentChar);  
            }
        }
    }
    cout << "Vert: " << verticeId << endl;

    cout << "\nID:" << cellId << " Material:" << cellMaterial << " Type:" << cellType << endl;

}


//-------------------ReadVectorFromFile--------------------
void Model::ReadVectorFromFile(string& line)
{
    uint8_t searchState = 0;
    string vertexId, vertexX, vertexY, vertexZ;

    for (int i = 0; i < line.length(); i++)
    {
        char currentChar = line[i];

        if (currentChar == ' ')
        {
            searchState += 1;
        }
        else
        {
            switch (searchState)
            {
            case 0: //Reading first character defining it as a vertex - does not need to be stored 
                break;
            case 1: //Reading second data entry in vertex - vertex ID
                vertexId.push_back(currentChar);
                break;
            case 2: //Reading third data entry - x position
                vertexX.push_back(currentChar);
                break;
            case 3:  //Reading fourth data entry - y position
                vertexY.push_back(currentChar);
                break;
            case 4: //Reading fourth data entry - z position
                vertexZ.push_back(currentChar);
                break;
            default:
                cout << "\nERROR - State not found";
            }
        }
    }
    cout << "\nID:" << vertexId << " X:" << vertexX << " Y:" << vertexY << " Z:" << vertexZ << endl;
}


//-----------------ReadMaterialFromFile--------------------
void Model::ReadMaterialFromFile(string& line)
{
    uint8_t searchState = 0;
    string materialId , materialDensity, materialColour, materialName;
 
    for (int i = 0; i < line.length(); i++)
    {
        char currentChar = line[i];

        if (currentChar == ' ')
        {
            searchState += 1;
        }
        else
        {
            switch (searchState)
            {
            case 0: //Reading first character defining it as a material - does not need to be stored 
                break;
            case 1: //Reading second data entry in material - material index
                materialId.push_back(currentChar);
                break;
            case 2: //Reading third data entry - density
                materialDensity.push_back(currentChar);
                break;
            case 3:  //Reading fourth data entry - colour
                materialColour.push_back(currentChar); 
                break;
            case 4: //Reading fourth data entry - name
                materialName.push_back(currentChar);
                break;
            default:
                cout << "\nERROR - State not found";
            }
        }
    }
    cout << "\nID: " << materialId << "\nDensity: " << materialDensity << "\nColour: " << materialColour << "\nName: " << materialName << endl;
}


//--------------------CalculateCentre----------------------
void Model::CalculateCentre() {


}


