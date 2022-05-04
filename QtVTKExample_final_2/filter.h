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

/*!
 * \brief The filter class
 */
class filter : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief filter
     */
    explicit filter();

    /*!
     * \brief shrink Filter
     */
    void shrinkFilter(ModelRender* ShrinkModel,vtkSmartPointer<vtkRenderer> renderer);
    /*!
     * \brief clip Filter
     */
    void clipFilter(ModelRender* ClipModel,vtkSmartPointer<vtkRenderer> renderer);
    /*!
     * \brief outLine Filter
     */
    void outLine(ModelRender* OutlineModel,vtkSmartPointer<vtkRenderer> renderer,float x,float y,float z);
    /*!
     * \brief smooth Filter independently
     */
    void smooth(ModelRender*SmoothModel,vtkSmartPointer<vtkRenderer> renderer);
    /*!
     * \brief calculate the area
     */
    double calcA(ModelRender*calcModel);
    /*!
     * \brief calculate the volume
     */
    double calcV(ModelRender*calcModel);
    /*!
     * \brief smooth Filter
     */
    void smoothadd(ModelRender*SmoothModel,vtkSmartPointer<vtkRenderer> renderer);
    /*!
     * \brief reflect Filter
     */
    void reflect(ModelRender* ReflectModel,vtkSmartPointer<vtkRenderer> renderer);
    /*!
     * \brief Remove all Filters
     */
    void RemoveFilter(ModelRender* removeModel,vtkSmartPointer<vtkRenderer> renderer);

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
        vtkSmartPointer<vtkDataSetMapper> clipdataset; //Store the data and functions required by each filter

        double area;
        double vol;

};

#endif // FILTER_H
