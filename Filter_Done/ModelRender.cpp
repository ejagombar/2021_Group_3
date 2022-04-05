#include "ModelRender.h"
#include "vtkAutoInit.h"
#include "mainwindow.h"

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

void ModelRender::RenderingStarts()
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
    renderer->SetBackground(BR,BG,BB);
    renderer->AddActor(actor);
    renderer->GetRenderWindow()->Render();
}

void ModelRender::setActorColor()
{
    QColor ColourDialog = QColorDialog::getColor();
    AR=ColourDialog.redF();
    AG=ColourDialog.greenF();
    AB=ColourDialog.blueF();
}

void ModelRender::setBackgroundColor()
{
    QColor ColourDialog = QColorDialog::getColor();
    BR=ColourDialog.redF();
    BG=ColourDialog.greenF();
    BB=ColourDialog.blueF();
}

void ModelRender::changeX(float x)
{
    X = x;
    if (which==0){RenderingStarts();}
    if (which==1){buildSphere();}
    if (which==2){buildCone();}
    if (which==3){buildArrow();}
}

void ModelRender::changeY(float y)
{
    Y = y;
    if (which==0){RenderingStarts();}
    if (which==1){buildSphere();}
    if (which==2){buildCone();}
    if (which==3){buildArrow();}
}

void ModelRender::changeZ(float z)
{
    Z = z;
    if (which==0){RenderingStarts();}
    if (which==1){buildSphere();}
    if (which==2){buildCone();}
    if (which==3){buildArrow();}
}

void ModelRender::changeRX(float x)
{
    RX = x;
    if (which==0){RenderingStarts();}
    if (which==1){buildSphere();}
    if (which==2){buildCone();}
    if (which==3){buildArrow();}
}

void ModelRender::changeRY(float y)
{
    RY = y;
    if (which==0){RenderingStarts();}
    if (which==1){buildSphere();}
    if (which==2){buildCone();}
    if (which==3){buildArrow();}
}

void ModelRender::changeRZ(float z)
{
    RZ = z;
    if (which==0){RenderingStarts();}
    if (which==1){buildSphere();}
    if (which==2){buildCone();}
    if (which==3){buildArrow();}
}

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

void ModelRender::buildSphere()
{
    which = 1;
    file = "Sphere";
    qDebug()<<"build a sphere";
    polydata=sphere->GetOutput();
    sphere->Update();
    mapper->SetInputConnection(sphere->GetOutputPort());
    actor->SetMapper(mapper);
    prop->SetColor(AR,AG,AB);
    actor->SetProperty(prop);
    //renderer->RemoveAllViewProps();
    actor->SetPosition(X,Y,Z);
    actor->RotateX(RX);
    actor->RotateY(RY);
    actor->RotateZ(RZ);
    renderer->AddActor(actor);
    renderer->SetBackground(BR,BG,BB);
    renderer->GetRenderWindow()->Render();
}


void ModelRender::buildCone()
{
    which = 2;
    file = "Cone";
    qDebug()<<"build a Cone";
    polydata=cone->GetOutput();
    cone->Update();
    mapper->SetInputConnection(cone->GetOutputPort());
    actor->SetMapper(mapper);
    prop->SetColor(AR,AG,AB);
    actor->SetProperty(prop);
    //renderer->RemoveAllViewProps();
    renderer->AddActor(actor);
    actor->SetPosition(X,Y,Z);
    actor->RotateX(RX);
    actor->RotateY(RY);
    actor->RotateZ(RZ);
    renderer->SetBackground(BR,BG,BB);
    renderer->GetRenderWindow()->Render();
}


void ModelRender::buildArrow()
{
    which = 3;
    file = "Arrow";
    qDebug()<<"build a Arrow";
    polydata=arrow->GetOutput();
    arrow->Update();
    mapper->SetInputConnection(arrow->GetOutputPort());
    actor->SetMapper(mapper);
    prop->SetColor(AR,AG,AB);
    actor->SetProperty(prop);
    //renderer->RemoveAllViewProps();
    renderer->AddActor(actor);
    actor->SetPosition(X,Y,Z);
    actor->RotateX(RX);
    actor->RotateY(RY);
    actor->RotateZ(RZ);
    renderer->SetBackground( BR,BG,BB );
    renderer->GetRenderWindow()->Render();
}


void ModelRender::showaxes()
{
    renderer->AddActor(axesActor);
    renderer->GetRenderWindow()->Render();
}

void ModelRender::OneRender(vtkRenderer *render)
{
    renderer = render;
}













