#ifndef FILTER_H
#define FILTER_H

#include<vtkSmartPointer.h>
#include<vtkActor.h>
#include<vtkDelaunay2D.h>
#include<vtkVertexGlyphFilter.h>
#include<vtkPolyDataMapper.h>
#include<vtkOutlineFilter.h>
#include<vtkSmoothPolyDataFilter.h>
#include<vtkDataSetSurfaceFilter.h>
#include<vtkClipDataSet.h>
#include<vtkCutter.h>
#include<vtkShrinkFilter.h>
#include<vtkReflectionFilter.h>

#include<vtkColorSeries.h>
#include<vtkCurvatures.h>
#include<vtkLookupTable.h>
#include<vtkColorTransferFunction.h>
#include<vtkScalarBarActor.h>
#include<vtkColorSeries.h>
#include<vtkPointData.h>

#include<vtkDataSetMapper.h>
#include<vtkPlane.h>
#include<vtkPolyDataNormals.h>

#include <QObject>
#include<QDebug>
#include<QString>
#include<QFileDialog>

#include "mediator.h"

class Filter : public QObject
{
    Q_OBJECT
public:

    explicit Filter();
    void outLineFilter(mediator* OutlineModel);
    void shrinkFilter(mediator* ShrinkModel);
    void smoothFilter(mediator* SmoothModel);
    void clipFilter(mediator* ClipModel);
    void reflectFilter(mediator* ReflectModel);
    void curvatureFilter(mediator* curvatureModel);
    void resetFilter(mediator* resetModel);

    signals:
private:
    /*********Outline filter******************/
    vtkSmartPointer<vtkActor> outlineactor;
    vtkSmartPointer<vtkPolyDataMapper> outlinemapper;
    vtkSmartPointer<vtkOutlineFilter> outlinefilter;
    vtkSmartPointer<vtkPolyData> outlinepolydata;

    /*********Shrink filter******************/

    vtkSmartPointer<vtkShrinkFilter> shrinkfilter;
    vtkSmartPointer<vtkPolyData> shrinkpolydata;
    vtkSmartPointer<vtkDataSetMapper> shrinkdataset;

    /*********smooth filter******************/
    vtkSmartPointer<vtkSmoothPolyDataFilter> smoothfilter;
    vtkSmartPointer<vtkPolyData> smoothpolydata;

    vtkSmartPointer<vtkPolyDataMapper> inputmapper;
    vtkSmartPointer<vtkPolyDataMapper> smoothmapper;

    vtkSmartPointer<vtkDelaunay2D> smoothdelaunay;
    vtkSmartPointer<vtkPolyDataNormals> smoothnormals;
    vtkSmartPointer<vtkActor> smoothactor;
    /*********clip filter*********************/
    vtkSmartPointer<vtkClipDataSet> clipfilter;
    vtkSmartPointer<vtkDataSetMapper> clipdataset;
    /***************reflection filter*************************/
    vtkSmartPointer<vtkReflectionFilter> reflectfilter;
    vtkSmartPointer<vtkPolyData> reflectpolydata;
    vtkSmartPointer<vtkDataSetMapper> reflectdataset;
    /***************curvature filter**************************/
     vtkSmartPointer<vtkCurvatures> curvaturefilter;
     vtkSmartPointer<vtkScalarBarActor> scalarbar;
     vtkSmartPointer<vtkColorTransferFunction> lut;
     vtkSmartPointer<vtkColorSeries> colorseries;
     vtkSmartPointer<vtkPolyDataMapper> curvaturemapper;
     vtkSmartPointer<vtkPolyData> curvaturepoly;
     vtkSmartPointer<vtkActor> curvatureactor;

};

#endif // FILTER_H
























