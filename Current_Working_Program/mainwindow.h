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
#include <QMessageBox>


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

    //Functions to render models
    void handlactionFileOpen();
    void handleBtn_Cube();
    void handleBtn_Sphere();
    void NewSource(QString);

    //Functions to edit models
    void handleBtn_Change_Position();
    void handleBtn_Model_Colour();
    void handleBtn_Reset_Actor();
    void handleBtn_Remove_Actor();

    //Filter pipeline functions
    void handleBtn_Filter();
    vtkSmartPointer<vtkAlgorithm> Shrink_Filter(vtkSmartPointer<vtkAlgorithm>);
    vtkSmartPointer<vtkAlgorithm> Clip_Filter(vtkSmartPointer<vtkAlgorithm>);
    vtkSmartPointer<vtkAlgorithm> Elevation_Filter(vtkSmartPointer<vtkAlgorithm>);
    vtkSmartPointer<vtkAlgorithm> Transform_Filter(vtkSmartPointer<vtkAlgorithm>);

    //Functions to manage the program UI
    void handleBtn_Change_Background();
    void handleBtn_Camera_Reset();
    void handleBtn_Clear();
    void reset_function();
    void Shrink_Box_Checked();
    void Transform_Box_Checked();
    void Help();
    void closeEvent(QCloseEvent* event);

    //Functions used to run program
    void New_Actor_Selected();
    bool Combo_Check(QString,QString);
    void Tab_Changed();
    vtkSmartPointer<vtkActor> FindActor();
    void Add_Rendered_Actors_To_Combo();

    void handleBtn_Test();
    void handleBtn_Test2();

private:
    //UI and rendered elements
    Ui::MainWindow *ui;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderer> renderer_Tab2;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow_Tab2;

    //Sources and associated variables
    vtkNew<vtkSTLReader> reader;
    vtkSmartPointer<vtkCubeSource> CubeSource;
    vtkSmartPointer<vtkSphereSource> sphereSource;
    QString fileName;
    QByteArray ba;
    vtkSmartPointer<vtkAlgorithm> ModelData;

    //Actors
    vtkSmartPointer<vtkActor> Current_actor;
    vtkSmartPointer<vtkActor> Source_actor = vtkSmartPointer<vtkActor>::New();

    //Mappers
    vtkSmartPointer<vtkDataSetMapper> Current_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkDataSetMapper> Source_mapper = vtkSmartPointer<vtkDataSetMapper>::New();

    //Actor Arrays
    std::vector<vtkSmartPointer<vtkActor>> Rendered_Cube_Actor_Array;
    std::vector<vtkSmartPointer<vtkActor>> Rendered_Sphere_Actor_Array;
    std::vector<vtkSmartPointer<vtkActor>> Rendered_STL_Actor_Array;

    //STL FileName Array
    std::vector<QString> File_Name_Array;

    //Message box
    QMessageBox warning_box;

    //Colour pointer
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

    //Colour values for the object as to not lose the colours when re-doing filters
    float Object_RedF=1;
    float Object_BlueF=1;
    float Object_GreenF=1;

};

#endif // MAINWINDOW_H
