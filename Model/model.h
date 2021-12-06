//-----------------------------//
//        Edward Agombar       //
//           20240645          //
//-----------------------------//



//-------------------------------Model Class-------------------------------
//-------------------------------------------------------------------------



class Model {


    public:

        void loadModelFile();
        void saveModelFile();

        void CalculateCentre();

        void GetNumOfVertices();
        void GetNumOfCellType();
        Vector GetModelCentre();
        

    private:

        Cell* cells;
        Vector* vectors;
        int numOfVertices;
        Vector ModelCentre;


};

