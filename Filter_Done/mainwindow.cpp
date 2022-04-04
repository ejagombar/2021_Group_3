#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
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
#include "vtkSTLReader.h"
#include <vtkSTLWriter.h>
#include "vtkPolyDataMapper.h"

#include "vtkClipPolyData.h"
#include <vtkLight.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QColorDialog>
#include <QDebug>
#include <QMessageBox>
#include <QPalette>
#include <typeinfo>
#include <QRadioButton>
#include <QLineEdit>
#include <QLine>
#include <ModelRender.h>
#include <QMessageBox>

#include "vtkAutoInit.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->UiSetup();
    this->InitOpenGLWindow();
    this->filterFunctionConnect();
    this->BuildPreLoad();
    this->PositionChange();
    connect(ui->actionFileOpen, &QAction::triggered, this, &MainWindow::readSTL);
    connect(ui->CalcA,&QPushButton::clicked,this,&MainWindow::CalcA);
    connect(ui->CalcV,&QPushButton::clicked,this,&MainWindow::CalcV);
    connect(ui->axes,&QPushButton::clicked,this,&MainWindow::axes);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UiSetup()
{
    ui->setupUi(this);
    this->setWindowTitle("Group3_Filter_Test");
}

void MainWindow::InitOpenGLWindow()
{
    ui->qvtkWidget->SetRenderWindow(Model->getRenderWindow());
    ui->qvtkWidget->GetRenderWindow()->AddRenderer(Model->getRenderer());
}

void MainWindow::BuildPreLoad()
{
    connect(ui->ball, &QAction::triggered, this, &MainWindow::BuildSphere);
    connect(ui->arrow, &QAction::triggered, this, &MainWindow::BuildArrow);
    connect(ui->cone, &QAction::triggered, this, &MainWindow::BuildCone);

    connect(ui->AColor, &QAction::triggered, this, &MainWindow::setActorColor);
    connect(ui->BColor, &QAction::triggered, this, &MainWindow::setBackgndColor);
}

void MainWindow::filterFunctionConnect()
{
    connect(ui->smooth,&QPushButton::clicked,this,&MainWindow::LaunchSmoothFilter);
    connect(ui->smoothadd,&QPushButton::clicked,this,&MainWindow::LaunchSmoothFilteradd);
    connect(ui->Cam,&QPushButton::released,this,&::MainWindow::handlCam);
    connect(ui->outline,&QPushButton::clicked,this,&MainWindow::LaunchOutLineFilter);
    connect(ui->clip,&QPushButton::clicked,this,&MainWindow::LaunchClipFilter);
    connect(ui->shrink,&QPushButton::clicked,this,&MainWindow::LaunchShrinkFilter);
    connect(ui->reflection,&QPushButton::clicked,this,&MainWindow::LaunchReflectFilter);
    connect(ui->Remove,&QPushButton::clicked,this,&MainWindow::RemoveFilter);
}

void MainWindow::PositionChange()
{
    //ui->changeX->setTracking(true);
    //ui->changeY->setTracking(true);
    //ui->changeZ->setTracking(true);
    connect(ui->changeX,&QSlider::valueChanged,this,&MainWindow::changeX);
    connect(ui->changeY,&QSlider::valueChanged,this,&MainWindow::changeY);
    connect(ui->changeZ,&QSlider::valueChanged,this,&MainWindow::changeZ);

    connect(ui->RX,&QSlider::valueChanged,this,&MainWindow::changeRX);
    connect(ui->RY,&QSlider::valueChanged,this,&MainWindow::changeRY);
    connect(ui->RZ,&QSlider::valueChanged,this,&MainWindow::changeRZ);
}

void MainWindow::BuildCone(){
    Model->buildCone();
}

void MainWindow::BuildSphere(){
    Model->buildSphere();
}

void MainWindow::BuildArrow(){
    Model->buildArrow();
}

void MainWindow::setActorColor(){
    Model->setActorColor();
    Model->RenderingStarts();
}

void MainWindow::setBackgndColor(){
    Model->setBackgroundColor();
    Model->RenderingStarts();
}

void MainWindow::LaunchReflectFilter()
{
   vtkFilter->reflect(Model);
   ui->statusbar->showMessage(tr("Launch Reflect Filter"),2000);
}

void MainWindow::LaunchOutLineFilter()
{
   vtkFilter->outLine(Model);
   ui->statusbar->showMessage(tr("Launch OutLine Filter"),2000);
}

void MainWindow::LaunchSmoothFilter()
{
    vtkFilter->smooth(Model);
    ui->statusbar->showMessage(tr("Launch Smooth Filter independent"),2000);
}

void MainWindow::LaunchSmoothFilteradd()
{
    vtkFilter->smoothadd(Model);
    ui->statusbar->showMessage(tr("Launch Smooth Filter add on"),2000);
}

void MainWindow::LaunchShrinkFilter()
{
    vtkFilter->shrinkFilter(Model);
    ui->statusbar->showMessage(tr("Launch Shrink Filter"),2000);
}

void MainWindow::LaunchClipFilter()
{
    vtkFilter->clipFilter(Model);
    ui->statusbar->showMessage(tr("Launch Cliip Filter"),2000);
}

void MainWindow::RemoveFilter()
{
    vtkFilter->RemoveFilter(Model);
    ui->statusbar->showMessage(tr("Remove Filter"),2000);
}

void MainWindow::handlCam()
{
    Model->renderer->ResetCamera();
    Model->renderer->GetActiveCamera()->Azimuth(30);
    Model->renderer->GetActiveCamera()->Elevation(30);
    Model->renderer->ResetCameraClippingRange();
    Model->renderWindow->Render();
}

void MainWindow::readSTL()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl)"));
    Model->STLfileReader(file);
    Model->RenderingStarts();
}

void MainWindow::axes()
{
    Model->showaxes();
    ui->statusbar->showMessage(tr("Show Axes"),2000);
}

void MainWindow::CalcA()
{
    double area = vtkFilter->calcA(Model);
    QMessageBox msgBox;
    msgBox.setText(tr("The area is:%1").arg(area));
    msgBox.exec();
}

void MainWindow::CalcV()
{
    double vol = vtkFilter->calcV(Model);
    QMessageBox msgBox;
    msgBox.setText(tr("The volume is:%1").arg(vol));
    msgBox.exec();
}

void MainWindow::changeX()
{
    float x;
    x = ui->changeX->value();
    Model->changeX(x);
    ui->statusbar->showMessage(tr("Position Change X"),2000);
}

void MainWindow::changeY()
{
    float y;
    y = ui->changeY->value();
    Model->changeY(y);
    ui->statusbar->showMessage(tr("Position Change Y"),2000);
}

void MainWindow::changeZ()
{
    float z;
    z = ui->changeZ->value();
    Model->changeZ(z);
    ui->statusbar->showMessage(tr("Position Change Z"),2000);
}

void MainWindow::changeRX()
{
    float x;
    x = ui->RX->value()/60;
    Model->changeRX(x);
    ui->statusbar->showMessage(tr("Angle Change X"),2000);
}

void MainWindow::changeRY()
{
    float y;
    y = ui->RY->value()/60;
    Model->changeRY(y);
    ui->statusbar->showMessage(tr("Angle Change Y"),2000);
}

void MainWindow::changeRZ()
{
    float z;
    z = ui->RZ->value()/60;
    Model->changeRZ(z);
    ui->statusbar->showMessage(tr("Angle Change Z"),2000);
}


































