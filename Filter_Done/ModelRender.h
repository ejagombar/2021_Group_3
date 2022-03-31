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
    vtkSmartPointer<vtkActor> actor ;

private:

    QString file;

};





