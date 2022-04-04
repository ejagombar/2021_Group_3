#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

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
#include <vtkSTLReader.h>
#include <vtkShrinkFilter.h>
#include <vtkPlane.h>
#include <vtkClipDataSet.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSet.h>

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QColorDialog>

class RenderObject {

public:


    RenderObject(vtkAlgorithm,vtkActor,QString);
    ~RenderObject();

    //Source
    vtkAlgorithm Source;
    vtkActor Actor;

    //Filter variables so the filters that are selected for the object can be stored so the user can switch
    int Clip_Filter = 0;
    int Shrink_Filter = 0;
    int Filter3 = 0;
    int Filter4 = 0;

    //Colour of object to be rendered
    double r,g,b;

    QString Name;



    void reRenderObject( vtkRenderer *v ) {
        /* call filter function */

        /*mapper*/

        /*actor*/

        //add to renderer
    };
#endif // RENDER_OBJECT_H

//RenderObject::RenderObject(vtkAlgorithm source,vtkActor Actor,QString name)
{
    Name=name;
    Source=source;
    Actor=actor;
};

//RenderObject::~RenderObject(){};


