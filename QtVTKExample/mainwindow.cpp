#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkDiskSource.h>
#include <vtkArrowSource.h>
#include <vtkConeSource.h>
#include <vtkSphereSource.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QMessageBox>
#include <QAbstractListModel>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <fstream>
#include <iostream>
#include <QFile>
#include <vtkRenderWindow.h>
#include <vtkStdString.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSTLReader.h>
#include <QColorDialog>
#include <vtkGeometryFilter.h>
#include <vtkShrinkFilter.h>
#include <vtkSplineFilter.h>
#include <vtkPlane.h>
#include <vtkClipDataSet.h>
#include <vtkSphereSource.h>
#include <vtkVoxelContoursToSurfaceFilter.h>
#include <vtkWindowedSincPolyDataFilter.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyData.h>
#include<vtkVertexGlyphFilter.h>
#include<vtkPolyDataMapper.h>
#include<vtkOutlineFilter.h>
#include<vtkSmoothPolyDataFilter.h>
#include<vtkDataSetSurfaceFilter.h>
#include<vtkClipDataSet.h>
#include<vtkCutter.h>
#include<vtkShrinkFilter.h>
#include<vtkReflectionFilter.h>

//QT lib
#include<qobject.h>
#include<qdebug.h>
#include<QString>
#include<QFileDialog>
#include<QColor>
#include<QColorDialog>

//vtk lib

#include<vtkSTLReader.h>
#include<vtkCamera.h>
#include<vtkPolyData.h>
#include<vtkRenderer.h>
#include<vtkPolyDataMapper.h>
#include<vtkNamedColors.h>

#include<vtkCubeSource.h>
#include<vtkSphereSource.h>
#include<vtkCylinderSource.h>
#include<vtkDiskSource.h>
#include<vtkLineSource.h>
#include<vtkPyramid.h>
#include<vtkTetra.h>
#include<vtkConeSource.h>


#include <vtkLight.h>
#include<vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSTLWriter.h>
#include <vtkNew.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkCellType.h>
#include<vtkCellArray.h>
#include<vtkDataSetSurfaceFilter.h>

#include<vtkDelaunay2D.h>
#include<vtkPolyDataNormals.h>

#include<vtkGenericOutlineFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkDataSetSurfaceFilter.h>

#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridReader.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

vtkNew<vtkActor> actor;
vtkNew<vtkSTLReader> reader;
vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
float Red_B=0,Green_B=0,Blue_B=0;
float Red=1,Green=1,Blue=1;
double S=1;
int shape=0;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi( this );

    ui->qvtkWidget->SetRenderWindow( renderWindow );			// note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt creator

    ui->saveButton->setIcon(QIcon(":/Icons/save.png"));
    ui->openButton->setIcon(QIcon(":/Icons/file.png"));

    ui->arrow->setIcon(QIcon(":/Icons/arrow.png"));
    ui->cone->setIcon(QIcon(":/Icons/slz.png"));
    ui->disk->setIcon(QIcon(":/Icons/disk.png"));
    ui->ColorChoose->setIcon(QIcon(":/Icons/dark.png"));
    ui->Color->setIcon(QIcon());

    connect( ui->BoxShrink, &QCheckBox::stateChanged, this, &::MainWindow::on_checkBox_stateChanged);
    connect( ui->BoxClip, &QCheckBox::stateChanged, this, &::MainWindow::on_checkBoxclip_stateChanged);

    connect( ui->Filter, &QPushButton::released, this, &::MainWindow::handlFilter );
    connect( ui->Filter_T, &QPushButton::released, this, &::MainWindow::handlFilter_T );
}

void MainWindow::on_checkBox_stateChanged()
{

   if( ui->BoxShrink->isChecked() )
     {
       S=0.7;

       if (shape == 1){
           vtkNew<vtkSphereSource> cubeSource;
           vtkNew<vtkShrinkFilter> shrink;
           shrink->SetInputConnection(cubeSource->GetOutputPort());
           shrink->SetShrinkFactor(S);

           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection(shrink->GetOutputPort());
           actor->SetMapper(mapper);
           actor->GetProperty()->SetColor( Red,Green,Blue );

           renderer->AddActor(actor);
       }
       if (shape == 2){
           vtkNew<vtkArrowSource> cubeSource;
           vtkNew<vtkShrinkFilter> shrink;
           shrink->SetInputConnection(cubeSource->GetOutputPort());
           shrink->SetShrinkFactor(S);

           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection(shrink->GetOutputPort());
           actor->SetMapper(mapper);
           actor->GetProperty()->SetColor( Red,Green,Blue );

           renderer->AddActor(actor);
       }
       if (shape == 3){
           vtkNew<vtkConeSource> cubeSource;
           vtkNew<vtkShrinkFilter> shrink;
           shrink->SetInputConnection(cubeSource->GetOutputPort());
           shrink->SetShrinkFactor(S);

           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection(shrink->GetOutputPort());
           actor->SetMapper(mapper);
           actor->GetProperty()->SetColor( Red,Green,Blue );

           renderer->AddActor(actor);
       }

       if (shape == 0){
           vtkNew<vtkShrinkFilter> shrink;
           shrink->SetInputConnection(reader->GetOutputPort());
           shrink->SetShrinkFactor(S);
           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection(shrink->GetOutputPort());
           actor->SetMapper(mapper);
       }


       renderer->SetBackground( Red_B,Green_B,Blue_B );

       renderWindow->Render();
     }
   else if(ui->BoxShrink->isChecked() == false)
    {
       S=1;

       if (shape == 1){
           vtkNew<vtkSphereSource> cubeSource;
           vtkNew<vtkShrinkFilter> shrink;
           shrink->SetInputConnection(cubeSource->GetOutputPort());
           shrink->SetShrinkFactor(S);
           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection(shrink->GetOutputPort());
           actor->SetMapper(mapper);
       }
       if (shape == 2){
           vtkNew<vtkArrowSource> cubeSource;
           vtkNew<vtkShrinkFilter> shrink;
           shrink->SetInputConnection(cubeSource->GetOutputPort());
           shrink->SetShrinkFactor(S);
           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection(shrink->GetOutputPort());
           actor->SetMapper(mapper);
       }
       if (shape == 3){
           vtkNew<vtkConeSource> cubeSource;
           vtkNew<vtkShrinkFilter> shrink;
           shrink->SetInputConnection(cubeSource->GetOutputPort());
           shrink->SetShrinkFactor(S);
           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection(shrink->GetOutputPort());
           actor->SetMapper(mapper);
       }

       if (shape == 0){
           vtkNew<vtkShrinkFilter> shrink;
           shrink->SetInputConnection(reader->GetOutputPort());
           shrink->SetShrinkFactor(S);
           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection(shrink->GetOutputPort());
           actor->SetMapper(mapper);
       }

       actor->GetProperty()->SetColor( Red,Green,Blue );

       renderer->AddActor(actor);
       renderer->SetBackground( Red_B,Green_B,Blue_B );

       renderWindow->Render();
     }
}

void MainWindow::handlFilter_T() {   

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl)"));

    //vtkNew<vtkPolyDataMapper> mapper;
    vtkNew<vtkDataSetMapper> mapper;
    vtkSmartPointer<vtkSmoothPolyDataFilter> smoothfilter;
    vtkSmartPointer<vtkPolyData> smoothpolydata;

    vtkSmartPointer<vtkPolyDataMapper> inputmapper;
    vtkSmartPointer<vtkPolyDataMapper> smoothmapper;

    vtkSmartPointer<vtkDelaunay2D> smoothdelaunay;
    vtkSmartPointer<vtkPolyDataNormals> smoothnormals;
    vtkSmartPointer<vtkActor> smoothactor;

    //QByteArray ba = fileName.toLocal8Bit();
    //const char *c_str2 = ba.data();
    //reader->SetFileName(c_str2);

    vtkNew<vtkSTLReader> reader;

    reader->SetFileName(fileName.toLatin1().data());

    reader->Update();

    vtkSmartPointer<vtkPolyData> polydata;
    polydata = vtkSmartPointer<vtkPolyData>::New();
    polydata = reader->GetOutput();

    smoothdelaunay->SetInputData(polydata);
    smoothdelaunay->Update();
    smoothfilter->SetInputConnection(smoothdelaunay->GetOutputPort());
    smoothfilter->SetNumberOfIterations(15);
    // the larger the factor the smoother the model
    smoothfilter->SetRelaxationFactor(0.1);
    //stop smoothing the edge
    smoothfilter->FeatureEdgeSmoothingOff();
    smoothfilter->BoundarySmoothingOn();
    smoothfilter->Update();

    // Update normals on smoothed PolyData
    vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
    normalGenerator->SetInputConnection(smoothfilter->GetOutputPort());
    normalGenerator->ComputePointNormalsOn();
    normalGenerator->ComputeCellNormalsOn();
    normalGenerator->Update();
    smoothmapper->SetInputConnection(normalGenerator->GetOutputPort());
    smoothactor->SetMapper(smoothmapper);
    //rendering
    //SmoothModel->getRenderer()->AddActor(smoothactor);
    //SmoothModel->getRenderWindow()->Render();
    renderer->AddActor(smoothactor);
    renderWindow->Render();

}

void MainWindow::on_checkBoxclip_stateChanged()
{

   if( ui->BoxClip->isChecked() )
     {
       if (shape == 1){
           vtkNew<vtkSphereSource> source;
           planeLeft->SetOrigin(0.0, 0.0, 0.0);
           planeLeft->SetNormal(-0.5, 0.0, 0.0);
           vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
           clipFilter->SetInputConnection( source->GetOutputPort() ) ;
           clipFilter->SetClipFunction( planeLeft.Get() );
           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection( clipFilter->GetOutputPort() );

           actor->SetMapper(mapper);
           actor->GetProperty()->SetColor( Red,Green,Blue );

           renderer->AddActor(actor);
       }
       if (shape == 2){
           vtkNew<vtkArrowSource> source;
           planeLeft->SetOrigin(0.0, 0.0, 0.0);
           planeLeft->SetNormal(0.0, -1.0, 0.0);
           vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
           clipFilter->SetInputConnection( source->GetOutputPort() ) ;
           clipFilter->SetClipFunction( planeLeft.Get() );
           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection( clipFilter->GetOutputPort() );

           actor->SetMapper(mapper);
           actor->GetProperty()->SetColor( Red,Green,Blue );

           renderer->AddActor(actor);
       }
       if (shape == 3){
           vtkNew<vtkConeSource> source;
           planeLeft->SetOrigin(0.0, 0.0, 0.0);
           planeLeft->SetNormal(-1.0, 0.0, 0.0);
           vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
           clipFilter->SetInputConnection( source->GetOutputPort() ) ;
           clipFilter->SetClipFunction( planeLeft.Get() );
           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection( clipFilter->GetOutputPort() );

           actor->SetMapper(mapper);
           actor->GetProperty()->SetColor( Red,Green,Blue );

           renderer->AddActor(actor);
       }

       if (shape == 0){

           planeLeft->SetOrigin(0.0, 0.0, 0.0);
           planeLeft->SetNormal(-1.0, 0.0, 0.0);
           vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
           clipFilter->SetInputConnection( reader->GetOutputPort() ) ;
           clipFilter->SetClipFunction( planeLeft.Get() );
           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection( clipFilter->GetOutputPort() );

           actor->SetMapper(mapper);
           actor->GetProperty()->SetColor( Red,Green,Blue );

           renderer->AddActor(actor);

       }

       renderer->SetBackground( Red_B,Green_B,Blue_B );

       renderWindow->Render();
     }
   else if(ui->BoxClip->isChecked() == false)
    {
       if (shape == 1){
           vtkNew<vtkSphereSource> source;
           planeLeft->SetOrigin(-9990.0, 0.0, 0.0);
           planeLeft->SetNormal(1.0, 0.0, 0.0);
           vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
           clipFilter->SetInputConnection( source->GetOutputPort() ) ;
           clipFilter->SetClipFunction( planeLeft.Get() );

           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection( clipFilter->GetOutputPort() );

           actor->SetMapper(mapper);
           actor->GetProperty()->SetColor( Red,Green,Blue );

           renderer->AddActor(actor);
       }
       if (shape == 2){
           vtkNew<vtkArrowSource> source;
           planeLeft->SetOrigin(-9990.0, 0.0, 0.0);
           planeLeft->SetNormal(1.0, 0.0, 0.0);
           vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
           clipFilter->SetInputConnection( source->GetOutputPort() ) ;
           clipFilter->SetClipFunction( planeLeft.Get() );
           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection( clipFilter->GetOutputPort() );

           actor->SetMapper(mapper);
           actor->GetProperty()->SetColor( Red,Green,Blue );

           renderer->AddActor(actor);
       }
       if (shape == 3){
           vtkNew<vtkConeSource> source;
           planeLeft->SetOrigin(-9999.0, 0.0, 0.0);
           planeLeft->SetNormal(1.0, 0.0, 0.0);
           vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
           clipFilter->SetInputConnection( source->GetOutputPort() ) ;
           clipFilter->SetClipFunction( planeLeft.Get() );
           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection( clipFilter->GetOutputPort() );

           actor->SetMapper(mapper);
           actor->GetProperty()->SetColor( Red,Green,Blue );

           renderer->AddActor(actor);
       }

       if (shape == 0){

           planeLeft->SetOrigin(-99990.0, 0.0, 0.0);
           planeLeft->SetNormal(1.0, 0.0, 0.0);
           vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
           clipFilter->SetInputConnection( reader->GetOutputPort() ) ;
           clipFilter->SetClipFunction( planeLeft.Get() );
           vtkNew<vtkDataSetMapper> mapper;
           mapper->SetInputConnection( clipFilter->GetOutputPort() );

           actor->SetMapper(mapper);
           actor->GetProperty()->SetColor( Red,Green,Blue );

           renderer->AddActor(actor);

       }

       actor->GetProperty()->SetColor( Red,Green,Blue );

       renderer->AddActor(actor);
       renderer->SetBackground( Red_B,Green_B,Blue_B );

       renderWindow->Render();
     }
}

void MainWindow::on_disk_triggered() {

    shape = 1;

    vtkSmartPointer<vtkSphereSource> cubeSource = vtkSmartPointer<vtkSphereSource>::New();

    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputConnection( cubeSource->GetOutputPort() );

    actor->SetMapper(mapper);
    actor->GetProperty()->EdgeVisibilityOn();

    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    actor->GetProperty()->SetColor( Red,Green,Blue );

    randerbegan(actor);

}

void MainWindow::on_arrow_triggered() {

    shape = 2;

    vtkSmartPointer<vtkArrowSource> cubeSource = vtkSmartPointer<vtkArrowSource>::New();

    // Create a mapper that will hold the cube's geometry in a format suitable for rendering
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();

    mapper->SetInputConnection( cubeSource->GetOutputPort() );

    actor->SetMapper(mapper);
    actor->GetProperty()->EdgeVisibilityOn();

    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    actor->GetProperty()->SetColor( Red,Green,Blue );

    randerbegan(actor);
}

void MainWindow::on_cone_triggered() {

    shape = 3;

    vtkSmartPointer<vtkConeSource> cubeSource = vtkSmartPointer<vtkConeSource>::New();

    // Create a mapper that will hold the cube's geometry in a format suitable for rendering
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputConnection( cubeSource->GetOutputPort() );

    actor->SetMapper(mapper);
    actor->GetProperty()->EdgeVisibilityOn();

    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    actor->GetProperty()->SetColor( Red,Green,Blue );
    randerbegan(actor);
}

void MainWindow::on_ColorChoose_triggered() {
    ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );			// ###### ask the QtVTKOpenGLWidget for its renderWindow ######

    renderer->AddActor(actor);
    QColor ColourDialog = QColorDialog::getColor();

    Red_B=ColourDialog.redF();
    Green_B=ColourDialog.greenF();
    Blue_B=ColourDialog.blueF();

    renderer->SetBackground( Red_B,Green_B,Blue_B );

    renderWindow->Render();
}

void MainWindow::on_Color_triggered() {
    ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );			// ###### ask the QtVTKOpenGLWidget for its renderWindow ######

    // Add the actor to the scene
    renderer->AddActor(actor);
    QColor ColourDialog = QColorDialog::getColor();

    Red=ColourDialog.redF();
    Green=ColourDialog.greenF();
    Blue=ColourDialog.blueF();

    actor->GetProperty()->SetColor( Red,Green,Blue );

    renderWindow->Render();
}

void MainWindow::on_openButton_triggered()
{
    shape = 0;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl)"));

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(reader->GetOutputPort());

    QByteArray ba = fileName.toLocal8Bit();

    const char *c_str2 = ba.data();
    reader->SetFileName(c_str2);
    reader->Update();

    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor( Red,Green,Blue );

    randerbegan(actor);
}

void MainWindow::on_saveButton_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr(""),"",tr("Text files (*.stl )"));

    QFile file(fileName);
    //currentFile = fileName;
    //setWindowTitle(fileName);
    file.open( QIODevice::ReadWrite );
    QTextStream out(&file);

    file.close();
}

void MainWindow::handlFilter() {

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();
    renderWindow->Render();
}

void MainWindow::randerbegan(vtkSmartPointer<vtkActor> actor){
    ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );
    renderer->AddActor(actor);
    renderer->SetBackground( Red_B,Green_B,Blue_B );

    renderWindow->Render();
}

MainWindow::~MainWindow()
{
    delete ui;
}






