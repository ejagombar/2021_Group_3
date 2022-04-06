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
#include<QObject>
#include<QDebug>
#include<QString>
#include<QFileDialog>
#include<vtkTriangleFilter.h>
#include<vtkShrinkFilter.h>
#include<vtkClipDataSet.h>
#include<vtkClipDataSet.h>

#include<ModelRender.h>
#include<vtkMassProperties.h>

//#include<vtkTransform.h>

class filter : public QObject
{
    Q_OBJECT
public:
    explicit filter();

    void shrinkFilter(ModelRender* ShrinkModel,vtkSmartPointer<vtkRenderer> renderer);
    void clipFilter(ModelRender* ClipModel,vtkSmartPointer<vtkRenderer> renderer);
    void outLine(ModelRender* OutlineModel,vtkSmartPointer<vtkRenderer> renderer,float x,float y,float z);
    void smooth(ModelRender*SmoothModel,vtkSmartPointer<vtkRenderer> renderer);
    double calcA(ModelRender*calcModel);
    double calcV(ModelRender*calcModel);
    void smoothadd(ModelRender*SmoothModel,vtkSmartPointer<vtkRenderer> renderer);
    void reflect(ModelRender* ReflectModel,vtkSmartPointer<vtkRenderer> renderer);
    void RemoveFilter(ModelRender* removeModel,vtkSmartPointer<vtkRenderer> renderer);

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

        vtkSmartPointer<vtkTriangleFilter> trianglefilter;
        vtkSmartPointer<vtkMassProperties> calcFA;
        vtkSmartPointer<vtkMassProperties> calcFV;

        vtkSmartPointer<vtkShrinkFilter> shrinkfilter;
        vtkSmartPointer<vtkPolyData> shrinkpolydata;
        vtkSmartPointer<vtkDataSetMapper> shrinkdataset;

        vtkSmartPointer<vtkClipDataSet> clipfilter;
        vtkSmartPointer<vtkDataSetMapper> clipdataset;

        double area;
        double vol;

};

#endif // FILTER_H
