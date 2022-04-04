#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkShrinkFilter.h>
#include <vtkPlane.h>
#include <vtkClipDataSet.h>
#include <vtkSTLReader.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void statusUpdateMessage( const QString & message, int timeout );

public slots:
    //Functions to change colour
    void handleBtn_Change_Background();
    void handleBtn_Model_Colour();

    //Functions to create objects
    void handlactionFileOpen();
    void handleBtn_Cube();
    void handleBtn_Sphere();
    void NewSource(QString);

    //Functions to manage the program
    void handleBtn_Camera_Reset();
    void handleCheckBox_Shrink_Change();
    void doubleSpinBox_value_changed();
    void handleBtn_Clear();
    void handleBtn_Change_Position();

    void reset_function();
    void handleBtn_Test();
    void handleBtn_Test2();

    vtkSmartPointer<vtkActor> FindActor();
    void Add_Rendered_Actors_To_Combo();
    void New_Actor_Selected();

    //Filter pipeline function
    void Filter();

    //void Object_Rendered();

private:
    //UI and rendered elements
    Ui::MainWindow *ui;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;

    //Sources
    vtkNew<vtkSTLReader> reader;
    vtkSmartPointer<vtkCubeSource> CubeSource;
    vtkSmartPointer<vtkSphereSource> sphereSource;
    QString fileName;
    QByteArray ba;

    //Actors
    vtkSmartPointer<vtkActor> STL_actor;
    vtkSmartPointer<vtkActor> Cube_actor;
    vtkSmartPointer<vtkActor> sphere_actor;
    vtkSmartPointer<vtkActor> Current_actor;
    vtkSmartPointer<vtkActor> Source_actor = vtkSmartPointer<vtkActor>::New();

    //Mappers
    vtkSmartPointer<vtkDataSetMapper> STL_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkDataSetMapper> Cube_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkDataSetMapper> sphere_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkDataSetMapper> Current_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkDataSetMapper> Source_mapper = vtkSmartPointer<vtkDataSetMapper>::New();

    //Filters
    vtkSmartPointer<vtkShrinkFilter>  STL_shrinkFilter;
    vtkSmartPointer<vtkShrinkFilter>  Cube_shrinkFilter;
    vtkSmartPointer<vtkShrinkFilter>  Sphere_shrinkFilter;

    vtkSmartPointer<vtkClipDataSet> Current_clipFilter;

    std::vector<vtkSmartPointer<vtkActor>> Rendered_Cube_Actor_Array;
    std::vector<vtkSmartPointer<vtkActor>> Rendered_Sphere_Actor_Array;
    std::vector<vtkSmartPointer<vtkActor>> Rendered_STL_Actor_Array;

    std::vector<QString> File_Name_Array;

    //Colour pointer
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

    //Colour values for the object and background as to not lose the colours when re-doing filters
    float Object_RedF=1;
    float Object_BlueF=1;
    float Object_GreenF=1;

    float Background_RedF=0;
    float Background_BlueF=0;
    float Background_Green=0;

    int Tracker=0;

};

#endif // MAINWINDOW_H
