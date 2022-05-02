///
/// @file
///
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//Header files for model visualisation
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkSTLReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>

//Header files for filtering
#include <vtkShrinkFilter.h>
#include <vtkClipDataSet.h>
#include <vtkPlane.h>
#include <vtkElevationFilter.h>
#include <vtkTransformFilter.h>
#include <vtkTransform.h>

//Header files for model editing/program operation
#include <vtkCamera.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <stdio.h>
#include <string.h>
#include <QCloseEvent>
#include <QDesktopServices>
#include <vtkProperty.h>

//-----------------------------------------------------------------------------------------------//
//--------------------------------MainWindow Class Definiton-------------------------------------//
//-----------------------------------------------------------------------------------------------//


namespace Ui {
///
/// @brief QMainWindow class used to render and edit models.
///
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    ///
    /// Auto-Generated constructor
    ///
    explicit MainWindow(QWidget *parent = 0);
    ///
    /// Auto-Generated destructor
    ///
    ~MainWindow();
signals:
    ///
    /// Signal to allow for the use of a status bar in the program. Displays the text passed as variable "message".
    ///
    /// @param(const QString &) message
    /// @param(int) timeout
    void statusUpdateMessage( const QString & message, int timeout ); //Used to update the status bar

public slots:

    //-----------------------------------------------------------------------------------------------//
    //-----------------Functions to handle the rendering of different model types--------------------//
    //-----------------------------------------------------------------------------------------------//

    ///
    /// Function that handles the rendering of the chosen model type, given through the Qstring input "Source_Type".
    ///
    /// @param(QString) Source_Type, e.g. "cube" or "STL".
    ///
    void NewSource(QString);
    ///
    /// Function to call the NewSource function to render an STL file.
    ///
    void handlactionFileOpen();
    ///
    /// Function to call the NewSource function to render a cube.
    ///
    void handleBtn_Cube();
    ///
    /// Function to call the NewSource function to render a sphere.
    ///
    void handleBtn_Sphere();


    //-----------------------------------------------------------------------------------------------//
    //------------Functions to handle changes to be made to currently rendered models----------------//
    //-----------------------------------------------------------------------------------------------//

    ///
    /// Function that changes the x,y and z co-ordinates of the currently selected model.
    ///
    void handleBtn_Change_Position();
    ///
    /// Function that changes the colour of the currently selected model to a colour selected from a colour picker by the user.
    ///
    void handleBtn_Model_Colour();
    ///
    /// Function that resets the currently selected model to the default version without any filters or colour changes applied.
    ///
    void handleBtn_Reset_Actor();
    ///
    /// Function that removes the currently selected model.
    ///
    void handleBtn_Remove_Actor();

    //-----------------------------------------------------------------------------------------------//
    //----------------------------------Filter pipeline functions------------------------------------//
    //-----------------------------------------------------------------------------------------------//

    ///
    /// Function that applies the filters selected by the user to the currently selected model.
    ///
    void handleBtn_Filter();
    ///
    /// Function that applies a shrink filter to the currently selected model with the shrink factor set by the user.
    ///
    /// @param(vtkSmartPointer<vtkAlgorithm>) Input source
    /// @return(vtkSmartPointer<vtkAlgorithm>) Output source
    ///
    vtkSmartPointer<vtkAlgorithm> Shrink_Filter(vtkSmartPointer<vtkAlgorithm>);
    ///
    /// Function that applies a clip filter to the currently selected model.
    ///
    /// @param(vtkSmartPointer<vtkAlgorithm>) Input source
    /// @return(vtkSmartPointer<vtkAlgorithm>) Output source
    ///
    vtkSmartPointer<vtkAlgorithm> Clip_Filter(vtkSmartPointer<vtkAlgorithm>);
    ///
    /// Function that applies an elevation filter (along the y-axis) to the currently selected model.
    ///
    /// @param(vtkSmartPointer<vtkAlgorithm>) Input source
    /// @return(vtkSmartPointer<vtkAlgorithm>) Output source
    ///
    vtkSmartPointer<vtkAlgorithm> Elevation_Filter(vtkSmartPointer<vtkAlgorithm>);
    ///
    /// Function that applies a transform filter to the currently selected modelm, with the stretch factors for x,y and z set by the user.
    ///
    /// @param(vtkSmartPointer<vtkAlgorithm>) Input source
    /// @return(vtkSmartPointer<vtkAlgorithm>) Output source
    ///
    vtkSmartPointer<vtkAlgorithm> Transform_Filter(vtkSmartPointer<vtkAlgorithm>);

    //-----------------------------------------------------------------------------------------------//
    //-----------------------------Functions to manage the program UI--------------------------------//
    //-----------------------------------------------------------------------------------------------//

    ///
    /// Function that changes the colour of the currently selected tab's background to a colour selected from a colour picker by the user.
    ///
    void handleBtn_Change_Background();
    ///
    /// Function that resets the camera of the currently selected tab to default settings.
    ///
    void handleBtn_Camera_Reset();
    ///
    /// Function that resets the program to it's inital state, clearing all relevant variables and rendered models.
    ///
    void handleBtn_Clear();
    ///
    /// Function that resets the program UI to the default state for when a model is rendered.
    ///
    void reset_function();
    ///
    /// Function that displayes the shrink factor UI when the shrink filter is selected so the user may enter a value. The function also
    /// hides the shrink factor UI when the shrink filter is de-selected .
    ///
    void Shrink_Box_Checked();
    ///
    /// Function that displayes the transform filter UI when the transform filter is selected so the user may enter appropriate values.
    /// The function also hides the transform filter UI when the transform filter is de-selected .
    ///
    void Transform_Box_Checked();
    ///
    /// Function to connect the help button in the UI to the doxygen documentation for the program via URL.
    ///
    void Help();
    ///
    /// Function called when user closes program to check they meant to do so
    ///
    void closeEvent(QCloseEvent* event);

    //-----------------------------------------------------------------------------------------------//
    //-----------------------------Functions used to run the program---------------------------------//
    //-----------------------------------------------------------------------------------------------//

    ///
    /// Function called whenever the user selects a different model in the drop down menue to update the UI.
    ///
    void New_Actor_Selected();
    ///
    /// Function to check if the drop down menue is blank, returns 0 if blank, 1 if not blank.
    ///
    /// @param(QString) Title
    /// @param(QString) Message
    /// @return(bool) status
    ///
    bool Combo_Check(QString,QString);
    ///
    /// Function called whenever the user selects a different tab from the tab menue to refresh the drop down menue with the models
    /// currently rendered in that tab, and to refresh the program UI.
    ///
    void Tab_Changed();
    ///
    /// Function to find the actor of the currently selected model in the drop down menue
    ///
    /// @return(vtkSmartPointer<vtkActor>) currently selected model's actor
    ///
    vtkSmartPointer<vtkActor> FindActor();
    ///
    /// Function to add all the actors in a renderer to the drop down menue
    ///
    void Add_Rendered_Actors_To_Combo();

private:
    //UI and renderer elements
    Ui::MainWindow *ui;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderer> renderer_Tab2;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow_Tab2;

    //Sources and associated variables
    vtkNew<vtkSTLReader> reader;
    QString fileName;
    QByteArray ba;
    vtkSmartPointer<vtkCubeSource> CubeSource;
    vtkSmartPointer<vtkSphereSource> sphereSource;
    vtkSmartPointer<vtkAlgorithm> ModelData;

    //Actors
    vtkSmartPointer<vtkActor> Current_actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> Source_actor = vtkSmartPointer<vtkActor>::New();

    //Mappers
    vtkSmartPointer<vtkDataSetMapper> Current_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkDataSetMapper> Source_mapper = vtkSmartPointer<vtkDataSetMapper>::New();

    //Rendered Actor Arrays
    std::vector<vtkSmartPointer<vtkActor>> Rendered_Cube_Actor_Array;
    std::vector<vtkSmartPointer<vtkActor>> Rendered_Sphere_Actor_Array;
    std::vector<vtkSmartPointer<vtkActor>> Rendered_STL_Actor_Array;

    //Rendered STL FileNames Array
    std::vector<QString> File_Name_Array;

    //Message box
    QMessageBox warning_box;

    //Colour pointer
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

    //Colour values for the object as to not lose the colours when applying filters
    float Object_RedF=1;
    float Object_BlueF=1;
    float Object_GreenF=1;

};

#endif // MAINWINDOW_H
