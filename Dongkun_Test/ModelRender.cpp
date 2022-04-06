#include "ModelRender.h"
#include "vtkAutoInit.h"
//#include "mainwindow.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

ModelRender::ModelRender(){
    actor = vtkSmartPointer<vtkActor>::New();
    prop= vtkSmartPointer<vtkProperty>::New() ;
    reader= vtkSmartPointer<vtkSTLReader>::New();
    mapper= vtkSmartPointer<vtkDataSetMapper>::New();
    polydata = vtkSmartPointer<vtkPolyData>::New();

    cone = vtkSmartPointer<vtkConeSource>::New();
    sphere = vtkSmartPointer<vtkSphereSource>::New();
    arrow = vtkSmartPointer<vtkArrowSource>::New();

    surfacefilter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
    axesActor = vtkSmartPointer<vtkAxesActor>::New();
}

void ModelRender::STLfileReader(QString fileName)
{
    which = 0;
    reader->SetFileName(fileName.toLatin1().data());
    reader->Update();
    file=fileName;
}

void ModelRender::RenderingStarts(vtkSmartPointer<vtkRenderer> renderer)
{
    polydata=reader->GetOutput();
    mapper->SetInputConnection(reader->GetOutputPort());
    actor->SetMapper(mapper);
    prop->SetColor(AR,AG,AB);
    actor->SetProperty(prop);
    actor->SetPosition(X,Y,Z);
    actor->RotateX(RX);
    actor->RotateY(RY);
    actor->RotateZ(RZ);
}

void ModelRender::setActorColor()
{
    QColor ColourDialog = QColorDialog::getColor();
    AR=ColourDialog.redF();
    AG=ColourDialog.greenF();
    AB=ColourDialog.blueF();
    actor->GetProperty()->SetColor(AR,AG,AB);
}

void ModelRender::changeX(float x,vtkSmartPointer<vtkRenderer> renderer)
{
    X = x;
    if (which==0){RenderingStarts(renderer);}
    if (which==1){buildSphere(renderer);}
    if (which==2){buildCone(renderer);}
    if (which==3){buildArrow(renderer);}
}

void ModelRender::changeY(float y,vtkSmartPointer<vtkRenderer> renderer)
{
    Y = y;
    if (which==0){RenderingStarts(renderer);}
    if (which==1){buildSphere(renderer);}
    if (which==2){buildCone(renderer);}
    if (which==3){buildArrow(renderer);}
}

void ModelRender::changeZ(float z,vtkSmartPointer<vtkRenderer> renderer)
{
    Z = z;
    if (which==0){RenderingStarts(renderer);}
    if (which==1){buildSphere(renderer);}
    if (which==2){buildCone(renderer);}
    if (which==3){buildArrow(renderer);}
}

void ModelRender::changeRX(float x,vtkSmartPointer<vtkRenderer> renderer)
{
    RX = x;
    if (which==0){RenderingStarts(renderer);}
    if (which==1){buildSphere(renderer);}
    if (which==2){buildCone(renderer);}
    if (which==3){buildArrow(renderer);}
}

void ModelRender::changeRY(float y,vtkSmartPointer<vtkRenderer> renderer)
{
    RY = y;
    if (which==0){RenderingStarts(renderer);}
    if (which==1){buildSphere(renderer);}
    if (which==2){buildCone(renderer);}
    if (which==3){buildArrow(renderer);}
}

void ModelRender::changeRZ(float z, vtkSmartPointer<vtkRenderer> renderer)
{
    RZ = z;
    if (which==0){RenderingStarts(renderer);}
    if (which==1){buildSphere(renderer);}
    if (which==2){buildCone(renderer);}
    if (which==3){buildArrow(renderer);}
}

void ModelRender::setFileName(QString Name){this->file= Name;}

QString ModelRender::getFileName(){return file;}

vtkSmartPointer<vtkDataSetMapper> ModelRender::getMapper(){return this->mapper;}

vtkSmartPointer<vtkPolyData> ModelRender::getPolyData(){return this->polydata;}

vtkSmartPointer<vtkProperty> ModelRender::getProp(){return this->prop;}

vtkSmartPointer<vtkSTLReader> ModelRender::getSTLReader(){return this->reader;}

vtkSmartPointer<vtkDataSetSurfaceFilter> ModelRender::getSurfaceFilter(){return this->surfacefilter;}

vtkSmartPointer<vtkActor> ModelRender::getActor(){return this->actor;}

void ModelRender::buildSphere(vtkSmartPointer<vtkRenderer> renderer)
{
    which = 1;
    file = "Sphere";
    qDebug()<<"build a sphere";
    polydata=sphere->GetOutput();
    sphere->Update();
    //mapper->SetInputConnection(sphere->GetOutputPort());
    mapper->SetInputData(polydata);
    actor->SetMapper(mapper);
    prop->SetColor(AR,AG,AB);
    actor->SetProperty(prop);
    actor->SetPosition(X,Y,Z);
    actor->RotateX(RX);
    actor->RotateY(RY);
    actor->RotateZ(RZ);
    renderer->AddActor(actor);
}

ModelRender::ModelRender(const ModelRender & ModelCopy)
{}

void ModelRender::buildCone(vtkSmartPointer<vtkRenderer> renderer)
{
    which = 2;
    file = "Cone";
    qDebug()<<"build a Cone";
    polydata=cone->GetOutput();
    cone->Update();
    mapper->SetInputData(polydata);
    actor->SetMapper(mapper);
    prop->SetColor(AR,AG,AB);
    actor->SetProperty(prop);
    actor->SetPosition(X,Y,Z);
    actor->RotateX(RX);
    actor->RotateY(RY);
    actor->RotateZ(RZ);
    renderer->AddActor(actor);
}


void ModelRender::buildArrow(vtkSmartPointer<vtkRenderer> renderer)
{
    which = 3;
    file = "Arrow";
    qDebug()<<"build a Arrow";
    polydata=arrow->GetOutput();
    arrow->Update();
    mapper->SetInputData(polydata);
    actor->SetMapper(mapper);
    prop->SetColor(AR,AG,AB);
    actor->SetProperty(prop);
    renderer->AddActor(actor);
    actor->SetPosition(X,Y,Z);
    actor->RotateX(RX);
    actor->RotateY(RY);
    actor->RotateZ(RZ);
    renderer->AddActor(actor);
}


void ModelRender::showaxes(vtkSmartPointer<vtkRenderer> renderer)
{
    renderer->AddActor(axesActor);
}













