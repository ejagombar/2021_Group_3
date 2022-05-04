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

/*!
 * \brief The ModelRender class
 */
class ModelRender :public QObject
{
   Q_OBJECT

public:

    ModelRender();
    ModelRender(const ModelRender & ModelCopy);
    //void SetModel(const ModelRender ModelCopy);
    //void SetModel(const ModelRender * ModelCopy);

    /*!
     * \brief getActor
     */
    vtkSmartPointer<vtkActor> getActor();
    /*!
     * \brief getProperty
     */
    vtkSmartPointer<vtkProperty> getProp();
    /*!
     * \brief getSTLReader
     */
    vtkSmartPointer<vtkSTLReader> getSTLReader();
    /*!
     * \brief getDataSetMapper
     */
    vtkSmartPointer<vtkDataSetMapper> getMapper();
    /*!
     * \brief getPolyData
     */
    vtkSmartPointer<vtkPolyData> getPolyData();
    /*!
     * \brief getDataSetSurfaceFilter
     */
    vtkSmartPointer<vtkDataSetSurfaceFilter> getSurfaceFilter();

    /*!
     * \brief getFileName
     */
    QString  getFileName();

    /*!
     * \brief setFileName
     */
    void setFileName(QString Name);

    /*!
     * \brief Start Reade STL
     */
    void STLfileReader(QString fileName);

    /*!
     * \brief Start Rendering to renderer
     */
    void RenderingStarts(vtkSmartPointer<vtkRenderer> renderer);

    //void RenderingStartsInside();

    vtkSmartPointer<vtkPolyData> polydata;  ///<storage vtkPolyData
    vtkSmartPointer<vtkDataSetSurfaceFilter> surfacefilter;  ///<vtkDataSetSurfaceFilter
    vtkSmartPointer<vtkProperty> prop ;  ///<storage vtkProperty
    vtkSmartPointer<vtkSTLReader> reader;  ///<vtkSTLReader
    vtkSmartPointer<vtkDataSetMapper> mapper;  ///<storage vtkDataSetMapper
    vtkSmartPointer<vtkActor> actor;  ///<storage vtkActor
    vtkSmartPointer<vtkAxesActor> axesActor;  ///<storage vtkAxesActor

    /*!
     * \brief Change the position of the model's X-axis direction
     */
    void changeX(float x,vtkSmartPointer<vtkRenderer> renderer);

    /*!
     * \brief Change the position of the model's Y-axis direction
     */
    void changeY(float y,vtkSmartPointer<vtkRenderer> renderer);

    /*!
     * \brief Change the position of the model's Z-axis direction
     */
    void changeZ(float z,vtkSmartPointer<vtkRenderer> renderer);

    /*!
     * \brief Change the rotation of the model's X-axis direction
     */
    void changeRX(float x,vtkSmartPointer<vtkRenderer> renderer);

    /*!
     * \brief Change the rotation of the model's Y-axis direction
     */
    void changeRY(float y,vtkSmartPointer<vtkRenderer> renderer);

    /*!
     * \brief Change the rotation of the model's Z-axis direction
     */
    void changeRZ(float z,vtkSmartPointer<vtkRenderer> renderer);

    float getX();
    float getY();
    float getZ();
    float getRX();
    float getRY();
    float getRZ();

    /*!
     * \brief buildSphere
     */
    void buildSphere(vtkSmartPointer<vtkRenderer> renderer);

    /*!
     * \brief buildArrow
     */
    void buildArrow(vtkSmartPointer<vtkRenderer> renderer);

    /*!
     * \brief buildCone
     */
    void buildCone(vtkSmartPointer<vtkRenderer> renderer);

    /*!
     * \brief showaxes
     */
    void showaxes(vtkSmartPointer<vtkRenderer> renderer);
    void setActorColor();

private:

    QString file = "unknow";
    vtkSmartPointer<vtkSphereSource> sphere;
    vtkSmartPointer<vtkConeSource> cone;
    vtkSmartPointer<vtkArrowSource> arrow;

    float AR=1; ///<RGB color variable R
    float AG=1; ///<RGB color variable G
    float AB=1; ///<RGB color variable B

    float X=0; ///<Position variable X
    float Y=0; ///<Position variable Y
    float Z=0; ///<Position variable Z

    float RX=0; ///<Angle variable X
    float RY=0; ///<Angle variable Y
    float RZ=0; ///<Angle variable Z

    int which=0; ///<Used to determine the opened model
};





