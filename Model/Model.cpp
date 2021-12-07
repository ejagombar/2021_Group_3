// Model.cpp : Defines the entry point for the application.
//

#include "Model.h"
#include <string>


using namespace std;

//-------------------------------Model Class-------------------------------
//-------------------------------------------------------------------------



//Passing in a file of type ifstream
void Model::loadModelFile(const string fileName) {
	ifstream fileIn;
	fileIn.open(fileName);
	if (fileIn.is_open()) {

        string line{};
        char firstLetter;
        uint16_t mCount = 0, vCount = 0, cCount = 0;

        while (getline(fileIn, line)) {
            if (fileIn.is_open()) {

                firstLetter = line.front();

                if (firstLetter == 'V') { vCount += 1; }
                else if (firstLetter == 'M') { mCount += 1; }
                else if (firstLetter == 'C') { cCount += 1; }
                else {
                    std::cout << "No letters on this line \n";
                }
            }
        }
	}
	fileIn.close();

}

void Model::saveModelFile() {



}

void Model::CalculateCentre() {




}




int main()
{
	cout << "Hello CMake." << endl;
	fstream test;

	return 0;
}
