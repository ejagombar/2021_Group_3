#include "ModelRender.h"
#include<vtkMassProperties.h>
#include "vtkAutoInit.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

ModelRender::ModelRender(){
    actor = vtkSmartPointer<vtkActor>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();
    prop= vtkSmartPointer<vtkProperty>::New() ;
    reader= vtkSmartPointer<vtkSTLReader>::New();
    mapper= vtkSmartPointer<vtkDataSetMapper>::New();
    renderWindow =  vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    polydata = vtkSmartPointer<vtkPolyData>::New();

    surfacefilter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
}

void ModelRender::STLfileReader(QString fileName)
{
    reader->SetFileName(fileName.toLatin1().data());
    reader->Update();
    file=fileName;
}

void ModelRender::RenderingStarts()
{
    polydata=reader->GetOutput();
    mapper->SetInputConnection(reader->GetOutputPort());
    actor->SetMapper(mapper);
    prop->SetColor(1, 1, 1);
    actor->SetProperty(prop);
    renderer->SetBackground(0,0,0);
    renderer->AddActor(actor);
    renderer->GetRenderWindow()->Render();
}

void ModelRender::AreaAndVol()
{
    trianglefilter->SetInputData(getPolyData());
    trianglefilter->Update();

    vtkSmartPointer<vtkMassProperties> calc = vtkSmartPointer< vtkMassProperties >::New();

    calc->SetInputData(trianglefilter->GetOutput());
    //calc->Update();

    area = calc->GetVolume();
    vol = calc->GetSurfaceArea();
}

double ModelRender::Getarea(){return area;}

double ModelRender::Getvol(){return vol;}

void ModelRender::setFileName(QString Name){this->file= Name;}

QString ModelRender::getFileName(){return this->file;}

vtkSmartPointer<vtkDataSetMapper> ModelRender::getMapper(){return this->mapper;}

vtkSmartPointer<vtkGenericOpenGLRenderWindow> ModelRender::getRenderWindow(){return this->renderWindow;}

vtkSmartPointer<vtkPolyData> ModelRender::getPolyData(){return this->polydata;}

vtkSmartPointer<vtkProperty> ModelRender::getProp(){return this->prop;}

vtkSmartPointer<vtkSTLReader> ModelRender::getSTLReader(){return this->reader;}

vtkSmartPointer<vtkDataSetSurfaceFilter> ModelRender::getSurfaceFilter(){return this->surfacefilter;}

vtkSmartPointer<vtkRenderer> ModelRender::getRenderer(){return this->renderer;}

vtkSmartPointer<vtkActor> ModelRender::getActor(){return this->actor;}

