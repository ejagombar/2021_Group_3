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

#include<ModelRender.h>



class filter : public QObject
{
    Q_OBJECT
public:
    explicit filter();
    void outLine(ModelRender* OutlineModel);
    void curvature(ModelRender* curvatureModel);
    void smooth(ModelRender*SmoothModel);
    void smoothadd(ModelRender*SmoothModel);
    void reflect(ModelRender* ReflectModel);
    void RemoveFilter(ModelRender* removeModel);

signals:

private:

        vtkSmartPointer<vtkActor> outlineactor;
        vtkSmartPointer<vtkPolyDataMapper> outlinemapper;
        vtkSmartPointer<vtkOutlineFilter> outlinefilter;
        vtkSmartPointer<vtkPolyData> outlinepolydata;

        vtkSmartPointer<vtkSmoothPolyDataFilter> smoothfilter;
        vtkSmartPointer<vtkPolyData> smoothpolydata;

        vtkSmartPointer<vtkPolyDataMapper> inputmapper;
        vtkSmartPointer<vtkPolyDataMapper> smoothmapper;

        vtkSmartPointer<vtkDelaunay2D> smoothdelaunay;
        vtkSmartPointer<vtkPolyDataNormals> smoothnormals;
        vtkSmartPointer<vtkActor> smoothactor;

        vtkSmartPointer<vtkReflectionFilter> reflectfilter;
        vtkSmartPointer<vtkPolyData> reflectpolydata;
        vtkSmartPointer<vtkDataSetMapper> reflectdataset;

        vtkSmartPointer<vtkActor> removeactor;
        vtkSmartPointer<vtkPolyDataMapper> removemapper;
        vtkSmartPointer<vtkPolyData> removepolydata;

};

#endif // FILTER_H
