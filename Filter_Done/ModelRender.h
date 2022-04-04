#pragma once

#include<qobject.h>
#include<qdebug.h>
#include<QString>
#include<QFileDialog>
#include<QColor>
#include<QColorDialog>

#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkCellType.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSTLWriter.h>
#include <vtkNew.h>
#include <vtkCellArray.h>
#include <vtkDataSetSurfaceFilter.h>

#include<vtkSTLReader.h>
#include<vtkCamera.h>
#include<vtkPolyData.h>
#include<vtkRenderer.h>
#include<vtkPolyDataMapper.h>
#include<vtkNamedColors.h>

#include<vtkSphereSource.h>
#include<vtkArrowSource.h>
#include<vtkConeSource.h>

#include<vtkAxesActor.h>

class ModelRender :public QObject
{
   Q_OBJECT

public:

    ModelRender();

    vtkSmartPointer<vtkRenderer> getRenderer();
    vtkSmartPointer<vtkActor> getActor();
    vtkSmartPointer<vtkProperty> getProp();
    vtkSmartPointer<vtkSTLReader> getSTLReader();
    vtkSmartPointer<vtkDataSetMapper> getMapper();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> getRenderWindow();
    vtkSmartPointer<vtkPolyData> getPolyData();
    vtkSmartPointer<vtkDataSetSurfaceFilter> getSurfaceFilter();

    QString  getFileName();
    void setFileName(QString Name);
    void STLfileReader(QString fileName);
    void RenderingStarts();

    vtkSmartPointer<vtkRenderer> renderer ;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkPolyData> polydata;
    vtkSmartPointer<vtkDataSetSurfaceFilter> surfacefilter;
    vtkSmartPointer<vtkProperty> prop ;
    vtkSmartPointer<vtkSTLReader> reader;
    vtkSmartPointer<vtkDataSetMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkAxesActor> axesActor;

    void changeX(float x);
    void changeY(float y);
    void changeZ(float z);
    void changeRX(float x);
    void changeRY(float y);
    void changeRZ(float z);

    void buildSphere();
    void buildArrow();
    void buildCone();

    void showaxes();

    void setActorColor();
    void setBackgroundColor();


private:

    QString file;
    vtkSmartPointer<vtkSphereSource> sphere;
    vtkSmartPointer<vtkConeSource> cone;
    vtkSmartPointer<vtkArrowSource> arrow;
    float AR=1;
    float AG=1;
    float AB=1;

    float BR=0;
    float BG=0;
    float BB=0;

    float X=0;
    float Y=0;
    float Z=0;

    float RX=0;
    float RY=0;
    float RZ=0;

    int which=0;
};





