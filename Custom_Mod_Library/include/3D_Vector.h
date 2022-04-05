///
/// @class Vector3D
/// @brief Class used to store 3D Vector points for the Model class
/// 



#ifndef Vector_H
#define Vector_H

#include <iostream>
using namespace std;


/// 
/// @brief Used to coordinates of the vectors that make up the cells models
/// Stores data about the the vector: its x,y,z position
/// 
class Vector3D
{
public:

    ///
    /// Constructor with parameters for 3 dimensions
    /// @param(float) x coordinate
    /// @param(float) y coordinate
    /// @param(float) z coordinate
    /// 
    Vector3D(float a, float b, float c); //Set

    ///
    /// Constructor with parameters for 2 dimensions
    /// Other axis can be manipulated later
    /// @param(float) x coordinate
    /// @param(float) y coordinate
    /// 
    Vector3D(float a, float b);

    ///
    /// Constructor with parameters for 1 dimension
    /// Other axis can be manipulated later
    /// @param(float) x coordinate
    /// 
    Vector3D(float a);

    ///
    /// Constructor with no parameters
    /// 
    Vector3D();

    ///
    /// Destructor
    /// 
    ~Vector3D();

    ///
    /// Copy Constructor
    /// @param(Vector3D) input vector
    ///
    Vector3D(const Vector3D& a);

    ///
    /// Overloaded '+' operator
    /// @param(Vector3D)
    /// @return(Vector3D)
    /// 
    Vector3D operator+ (const Vector3D& a);          //Overload '+' operator

    ///
    /// Overloaded '-' operator
    /// @param(Vector3D)
    /// @return(Vector3D)
    /// 
    Vector3D operator- (const Vector3D& a);          //Overload '-' operator

    ///
    /// Overloaded '*' operator
    /// @param(Vector3D)
    /// @return(Vector3D)
    /// 
    Vector3D operator* (const Vector3D& a);          //Overload '*' operator

    ///
    /// Overloaded '*' operator to mulitply all values by a float
    /// @param(float)
    /// @return(Vector3D)
    /// 
    Vector3D operator* (float a);

    ///
    /// Overloaded '^' operator to add exponent
    /// @param(Vector3D)
    /// @return(Vector3D)
    /// 
    Vector3D operator^ (const Vector3D& a);

    ///
    /// Overloaded '=' operator
    /// @param(Vector3D)
    /// @return(Vector3D)
    /// 
    const Vector3D& operator= (const Vector3D& a);   //Overload '=' operator

    ///
    /// Overloaded '+=' operator
    /// @param(Vector3D)
    /// @return(Vector3D)
    /// 
    Vector3D operator+= (const Vector3D& a);         //Overload '+=' operator

    ///
    /// Overloaded '>>' operator to output vector values
    /// @param(Vector3D)
    /// 
    friend istream& operator>> (istream& in, Vector3D& a);   //Overload '>>' operator

    ///
    /// Overloaded '<<' operator to output vector values
    /// @param(Vector3D)
    /// 
    friend ostream& operator<< (ostream& out, Vector3D& a);   //Overload '<<' operator

    //Sets and Gets for x y and z

    ///
    /// Return x value of vector
    /// @return(float) x value
    /// 
    float Get_x();

    ///
    /// Return y value of vector
    /// @return(float) y value
    /// 
    float Get_y();

    ///
    /// Return z value of vector
    /// @return(float) z value
    /// 
    float Get_z();

    ///
    /// Set x value of vector
    /// @param(float) x value
    /// 
    void Set_x(float a);

    ///
    /// Set x value of vector
    /// @param(float) y value
    /// 
    void Set_y(float a);

    ///
    /// Set z value of vector
    /// @param(float) z value
    /// 
    void Set_z(float a);


private:
    float x;
    float y;
    float z;
};

Vector3D operator+(float f, Vector3D& a);  //Overload operators, recognizing different orders of addition operations




#endif // 3D_VECTOR_H

