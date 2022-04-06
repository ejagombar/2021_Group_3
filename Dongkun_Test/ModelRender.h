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
#include<QString>

#include<vtkAxesActor.h>

class ModelRender :public QObject
{
   Q_OBJECT

public:

    ModelRender();
    ModelRender(const ModelRender & ModelCopy);

    vtkSmartPointer<vtkActor> getActor();
    vtkSmartPointer<vtkProperty> getProp();
    vtkSmartPointer<vtkSTLReader> getSTLReader();
    vtkSmartPointer<vtkDataSetMapper> getMapper();
    vtkSmartPointer<vtkPolyData> getPolyData();
    vtkSmartPointer<vtkDataSetSurfaceFilter> getSurfaceFilter();

    QString  getFileName();
    void setFileName(QString Name);
    void STLfileReader(QString fileName);
    void RenderingStarts(vtkSmartPointer<vtkRenderer> renderer);
    void RenderingStartsInside();

    vtkSmartPointer<vtkPolyData> polydata;
    vtkSmartPointer<vtkDataSetSurfaceFilter> surfacefilter;
    vtkSmartPointer<vtkProperty> prop ;
    vtkSmartPointer<vtkSTLReader> reader;
    vtkSmartPointer<vtkDataSetMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkAxesActor> axesActor;

    void changeX(float x,vtkSmartPointer<vtkRenderer> renderer);
    void changeY(float y,vtkSmartPointer<vtkRenderer> renderer);
    void changeZ(float z,vtkSmartPointer<vtkRenderer> renderer);
    void changeRX(float x,vtkSmartPointer<vtkRenderer> renderer);
    void changeRY(float y,vtkSmartPointer<vtkRenderer> renderer);
    void changeRZ(float z,vtkSmartPointer<vtkRenderer> renderer);

    void buildSphere(vtkSmartPointer<vtkRenderer> renderer);
    void buildArrow(vtkSmartPointer<vtkRenderer> renderer);
    void buildCone(vtkSmartPointer<vtkRenderer> renderer);
    void showaxes(vtkSmartPointer<vtkRenderer> renderer);
    void setActorColor();


private:

    QString file = "unknow";
    vtkSmartPointer<vtkSphereSource> sphere;
    vtkSmartPointer<vtkConeSource> cone;
    vtkSmartPointer<vtkArrowSource> arrow;
    float AR=1;
    float AG=1;
    float AB=1;

    float X=0;
    float Y=0;
    float Z=0;

    float RX=0;
    float RY=0;
    float RZ=0;

    int which=0;
};





