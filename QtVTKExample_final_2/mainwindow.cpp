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
#include <QGraphicsBlurEffect>
#include "vtkAutoInit.h"
#include "form.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
int row = 0;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    setWindowOpacity(1);
    QGraphicsBlurEffect* ef = new QGraphicsBlurEffect;
    ef->setBlurRadius(0);
    ef->setBlurHints(QGraphicsBlurEffect::AnimationHint);
    this->setGraphicsEffect(ef);

    this->UiSetup();
    this->InitOpenGLWindow();
    this->filterFunctionConnect();
    this->BuildPreLoad();
    this->PositionChange();

    //this->setStyleSheet(":/Icons/B.jpg");

    //renderer->SetBackground(BR,BG,BB);
    //renderWindow->Render();

    //SetBackground(BR,BG,BB);
    //render();

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
    this->setWindowTitle("Group 3 D Viewer");
}

void MainWindow::InitOpenGLWindow()
{
    on_actionAdd_triggered();
    auto currentWidget = (Form*)ui->tabWidget->currentWidget();
    if(currentWidget) {
        currentWidget->ui->qvtkWidgetS->setRenderWindow(currentWidget->getRenderWindow());
        currentWidget->ui->qvtkWidgetS->renderWindow()->AddRenderer(currentWidget->getRenderer());
    }
        SetBackground(BR,BG,BB);
    render();
}

void MainWindow::BuildPreLoad()
{
    connect(ui->ball, &QAction::triggered, this, &MainWindow::BuildSphere);
    connect(ui->arrow, &QAction::triggered, this, &MainWindow::BuildArrow);
    connect(ui->cone, &QAction::triggered, this, &MainWindow::BuildCone);

    connect(ui->AColor, &QAction::triggered, this, &MainWindow::setActorColor);
    connect(ui->BColor, &QAction::triggered, this, &MainWindow::setBackgndColor);
}

void MainWindow::render()
{    
    qDebug() << __FUNCTION__;
    auto currentTab = getCurrentTab();
    if(currentTab) {
        currentTab->render();
    }
}

Form *MainWindow::getCurrentTab() const
{
    return (Form *)ui->tabWidget->currentWidget();
}

vtkSmartPointer<vtkRenderer> MainWindow::getCurentRender() const
{
    auto currentTab = getCurrentTab();
    if(currentTab) {
        return currentTab->getRenderer();
    }
    return nullptr;
}

ModelRender *MainWindow::getCurrentModel() const
{
    auto currentTab = getCurrentTab();
    if(currentTab) {
        return currentTab->getModel();
    }
    return nullptr;
}

std::vector<ModelRender *> *MainWindow::getCurrentModelList() const
{
    auto currentTab = getCurrentTab();
    if(currentTab) {
        return currentTab->getModelList();
    }
    return nullptr;
}

std::vector<QString> *MainWindow::getCurrentFileNames() const
{
    auto currentTab = getCurrentTab();
    if(currentTab) {
        return currentTab->getFileNames();
    }
    return nullptr;
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
    ModelRender* ModelNew = new ModelRender();
    ModelNew->buildCone(getCurentRender());
    SetBackground(BR,BG,BB);
    render();
    getCurrentModelList()->push_back(ModelNew);
    getCurrentFileNames()->push_back("Cone");
    upDateList();
//    LaunchClipFilter();
}

void MainWindow::BuildSphere(){
    ModelRender* ModelNew = new ModelRender();
    ModelNew->buildSphere(getCurentRender());
    render();
    getCurrentModelList()->push_back(ModelNew);
    getCurrentFileNames()->push_back("Sphere");
    upDateList();
}

void MainWindow::BuildArrow(){
    ModelRender* ModelNew = new ModelRender();
    ModelNew->buildArrow(getCurentRender());
    render();
    getCurrentModelList()->push_back(ModelNew);
    getCurrentFileNames()->push_back("Arrow");
    upDateList();
}

void MainWindow::setActorColor(){
    getCurrentModelList()->at(row)->setActorColor();
    render();
    //Model->RenderingStarts(renderer);
}

void MainWindow::SetBackground(double arg1, double arg2, double arg3)
{
    getCurentRender()->SetBackground(arg1,arg2,arg3);
}

void MainWindow::setBackgndColor(){
    QColor ColourDialog = QColorDialog::getColor();
    BR=ColourDialog.redF();
    BG=ColourDialog.greenF();
    BB=ColourDialog.blueF();
    SetBackground(BR,BG,BB);
    render();
}

void MainWindow::LaunchReflectFilter()
{
   vtkFilter->reflect(getCurrentModelList()->at(row),getCurentRender());
   render();
   ui->statusbar->showMessage(tr("Launch Reflect Filter"),2000);
}

void MainWindow::LaunchOutLineFilter()
{
   vtkFilter->outLine(getCurrentModelList()->at(row),getCurentRender(),x,y,z);
   render();
   ui->statusbar->showMessage(tr("Launch OutLine Filter"),2000);
}

void MainWindow::LaunchSmoothFilter()
{
    vtkFilter->smooth(getCurrentModelList()->at(row),getCurentRender());
    render();
    ui->statusbar->showMessage(tr("Launch Smooth Filter independent"),2000);
}

void MainWindow::LaunchSmoothFilteradd()
{
    vtkFilter->smoothadd(getCurrentModelList()->at(row),getCurentRender());
    render();
    ui->statusbar->showMessage(tr("Launch Smooth Filter add on"),2000);
}

void MainWindow::LaunchShrinkFilter()
{
    vtkFilter->shrinkFilter(getCurrentModelList()->at(row),getCurentRender());
    render();
    ui->statusbar->showMessage(tr("Launch Shrink Filter"),2000);
}

void MainWindow::LaunchClipFilter()
{
    vtkFilter->clipFilter(getCurrentModelList()->at(row),getCurentRender());
    render();
    ui->statusbar->showMessage(tr("Launch Cliip Filter"),2000);
}

void MainWindow::RemoveFilter()
{
    on_clear_clicked();
//    vtkFilter->RemoveFilter(getCurrentModelList()->at(row),getCurentRender());
    render();
    ui->statusbar->showMessage(tr("Remove Filter"),2000);
}

void MainWindow::handlCam()
{
    getCurentRender()->ResetCamera();
    getCurentRender()->GetActiveCamera()->Azimuth(30);
    getCurentRender()->GetActiveCamera()->Elevation(30);
    getCurentRender()->ResetCameraClippingRange();
    render();
}

void MainWindow::readSTL()
{
    ModelRender* ModelNew = new ModelRender();
    QString file = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl)"));
    ModelNew->STLfileReader(file);
    ModelNew->RenderingStarts(getCurentRender());
    getCurrentModelList()->push_back(ModelNew);
    getCurrentFileNames()->push_back(file);
    upDateList();
}

void MainWindow::axes()
{
    getCurrentModel()->showaxes(getCurentRender());
    render();
    ui->statusbar->showMessage(tr("Show Axes"),2000);
}

void MainWindow::CalcA()
{
    double area = vtkFilter->calcA(getCurrentModelList()->at(row));
    QMessageBox msgBox;
    msgBox.setText(tr("The area is:%1").arg(area));
    msgBox.exec();
}

void MainWindow::CalcV()
{
    double vol = vtkFilter->calcV(getCurrentModelList()->at(row));
    QMessageBox msgBox;
    msgBox.setText(tr("The volume is:%1").arg(vol));
    msgBox.exec();
}

void MainWindow::changeX()
{
    x = ui->changeX->value();
    getCurrentModelList()->at(row)->changeX(x,getCurentRender());
    render();
    ui->statusbar->showMessage(tr("Position Change X"),2000);
}

void MainWindow::changeY()
{
    y = ui->changeY->value();
    getCurrentModelList()->at(row)->changeY(y,getCurentRender());
    render();
    ui->statusbar->showMessage(tr("Position Change Y"),2000);
}

void MainWindow::changeZ()
{
    z = ui->changeZ->value();
    getCurrentModelList()->at(row)->changeZ(z,getCurentRender());
    render();
    ui->statusbar->showMessage(tr("Position Change Z"),2000);
}

void MainWindow::changeRX()
{
    float x;
    x = ui->RX->value()/60;
    getCurrentModelList()->at(row)->changeRX(x,getCurentRender());
    render();
    ui->statusbar->showMessage(tr("Angle Change X"),2000);
}

void MainWindow::changeRY()
{
    float y;
    y = ui->RY->value()/60;
    getCurrentModelList()->at(row)->changeRY(y,getCurentRender());
    render();
    ui->statusbar->showMessage(tr("Angle Change Y"),2000);
}

void MainWindow::changeRZ()
{
    float z;
    z = ui->RZ->value()/60;
    getCurrentModelList()->at(row)->changeRZ(z,getCurentRender());
    render();
    ui->statusbar->showMessage(tr("Angle Change Z"),2000);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionAdd_triggered()
{
    ui->tabWidget->addTab(new Form() , QString("Tab %0").arg(ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
}

void MainWindow::on_clear_clicked()
{
    ui->list->clear();
    vtkFilter->RemoveFilter(getCurrentModelList()->at(row),getCurentRender());
    render();
    getCurrentModelList()->clear();
    getCurrentFileNames()->clear();
//    ModelList.swap(ModelList);
}

void MainWindow::upDateList()
{
    ui->list->clear();
    auto currentFileNames = getCurrentFileNames();
    for(int i=0; i< currentFileNames->size(); i++)
    {
        ui->list->addItem(currentFileNames->at(i));
    }
}

void MainWindow::on_list_itemSelectionChanged()
{
    qDebug() << "Here";
    row = ui->list->currentRow();
    //getCurrentModelList()->at(row)->setActorColor();
    render();
    ui->changeX->setValue(getCurrentModelList()->at(row)->getX());
    ui->changeY->setValue(getCurrentModelList()->at(row)->getY());
    ui->changeZ->setValue(getCurrentModelList()->at(row)->getZ());

    ui->RX->setValue(getCurrentModelList()->at(row)->getRX());
    ui->RY->setValue(getCurrentModelList()->at(row)->getRY());
    ui->RZ->setValue(getCurrentModelList()->at(row)->getRZ());

    ui->statusbar->showMessage(tr("Selection Changed"),2000);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    upDateList();
}













