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

void mediator::STLfileReader(QString fileName){

    QByteArray ba = fileName.toLocal8Bit();
    const char *c_str2 = ba.data();

    reader->SetFileName(c_str2);
    reader->Update();
    file=fileName;

}

void mediator::setPipeline(){
    polydata=reader->GetOutput();
    mapper->SetInputConnection(reader->GetOutputPort());
    actor->SetMapper(mapper);
    //actor->SetColor(0, 0, 0);
    //actor->SetProperty(prop);
    renderer->SetBackground(1,1,1);
    //mylight->SetColor(0,0,0);
    //renderer->RemoveAllViewProps();
    //renderer->AddLight(mylight);

    renderer->AddActor(actor);
    renderer->GetRenderWindow()->Render();
}


/*void mediator::setFileName(QString Name){
    this->file= Name;
}*/

QString mediator::getFileName(){
    return this->file;
}
vtkSmartPointer<vtkRenderer> mediator::getRenderer(){
    return this->renderer;
}

vtkSmartPointer<vtkActor> mediator::getActor(){
    return this->actor;

}
vtkSmartPointer<vtkProperty> mediator::getProp(){
    return this->prop;

}
vtkSmartPointer<vtkSTLReader> mediator::getSTLReader(){
   return this->reader;
}
vtkSmartPointer<vtkDataSetMapper> mediator::getMapper(){
   return this->mapper;
}
vtkSmartPointer<vtkLight> mediator::getLight(){
    return this->mylight;
}
vtkSmartPointer<vtkGenericOpenGLRenderWindow> mediator::getRenderWindow(){
    return this->renderWindow;
}

vtkSmartPointer<vtkPolyData> mediator::getPolyData(){
    return this->polydata;
}

vtkSmartPointer<vtkDataSetSurfaceFilter> mediator::getSurfaceFilter(){

    return this->surfacefilter;
}







































