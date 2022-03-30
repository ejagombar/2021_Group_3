#include "mediator.h"
#include "mainwindow.h"

mediator::mediator()
{
    actor = vtkSmartPointer<vtkActor>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();
    mylight  = vtkSmartPointer<vtkLight>::New();
    prop= vtkSmartPointer<vtkProperty>::New() ;
    reader= vtkSmartPointer<vtkSTLReader>::New();
    mapper= vtkSmartPointer<vtkDataSetMapper>::New();
    renderWindow =  vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    polydata = vtkSmartPointer<vtkPolyData>::New();

    surfacefilter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
}

void ModelRender::STLfileReader(QString fileName){

    reader->SetFileName(fileName.toLatin1().data());
    reader->Update();
    file=fileName;

}

void ModelRender::setPipeline(){
    polydata=reader->GetOutput();
    mapper->SetInputConnection(reader->GetOutputPort());
    actor->SetMapper(mapper);
    prop->SetColor(1.0, 0, 0);
    actor->SetProperty(prop);
    renderer->SetBackground(Red_B,Green_B,Blue_B);
    mylight->SetColor(0,0,0);
    //renderer->RemoveAllViewProps();
    renderer->AddLight(mylight);
    renderer->AddActor(actor);
    renderer->GetRenderWindow()->Render();
}


void ModelRender::setFileName(QString Name){
    this->file= Name;
}

QString ModelRender::getFileName(){
    return this->file;
}
vtkSmartPointer<vtkRenderer> ModelRender::getRenderer(){
    return this->renderer;
}

vtkSmartPointer<vtkActor> ModelRender::getActor(){
    return this->actor;

}
vtkSmartPointer<vtkProperty> ModelRender::getProp(){
    return this->prop;

}
vtkSmartPointer<vtkSTLReader> ModelRender::getSTLReader(){
   return this->reader;
}
vtkSmartPointer<vtkDataSetMapper> ModelRender::getMapper(){
   return this->mapper;
}
vtkSmartPointer<vtkLight> ModelRender::getLight(){
    return this->mylight;
}
vtkSmartPointer<vtkGenericOpenGLRenderWindow> ModelRender::getRenderWindow(){
    return this->renderWindow;
}

vtkSmartPointer<vtkPolyData> ModelRender::getPolyData(){
    return this->polydata;
}

vtkSmartPointer<vtkDataSetSurfaceFilter> ModelRender::getSurfaceFilter(){

    return this->surfacefilter;
}







































