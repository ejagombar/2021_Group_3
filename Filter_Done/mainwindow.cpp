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
   connect(ui->actionFileOpen, &QAction::triggered, this, &MainWindow::readSTL);
   connect(ui->CalcA,&QPushButton::clicked,this,&MainWindow::CalcA);
   connect(ui->CalcV,&QPushButton::clicked,this,&MainWindow::CalcV);
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

void MainWindow::filterFunctionConnect()
{
    connect(ui->smooth,&QPushButton::clicked,this,&MainWindow::LaunchSmoothFilter);
    connect(ui->smoothadd,&QPushButton::clicked,this,&MainWindow::LaunchSmoothFilteradd);
    connect(ui->Cam,&QPushButton::released,this,&::MainWindow::handlCam);
    connect(ui->outline,&QPushButton::clicked,this,&MainWindow::LaunchOutLineFilter);
    connect(ui->reflection,&QPushButton::clicked,this,&MainWindow::LaunchReflectFilter);
    connect(ui->Remove,&QPushButton::clicked,this,&MainWindow::RemoveFilter);
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

void MainWindow::RemoveFilter()
{
    vtkFilter->RemoveFilter(Model);
    ui->statusbar->showMessage(tr("Remove Filter"),2000);
}

void MainWindow::handlCam() {

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

void MainWindow::CalcA()
{
    double area = Model->Getarea();
    Model->AreaAndVol();
    QMessageBox msgBox;
    msgBox.setText(tr("The area is:%1").arg(area));
    msgBox.exec();
}

void MainWindow::CalcV()
{
    double vol = Model->Getvol();
    Model->AreaAndVol();
    QMessageBox msgBox;
    msgBox.setText(tr("The volume is:%1").arg(vol));
    msgBox.exec();
}








