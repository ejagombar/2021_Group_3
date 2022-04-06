#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vtkSTLReader.h"
#include <vtkDataSetMapper.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <QVector>
#include <vtkLight.h>
#include <vtkProperty.h>
#include <ModelRender.h>
#include <filter.h>
#include <vtkRenderer.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setBackgndColor();
    void setActorColor();


signals:
    void signal_loadStl(QString path);

public slots:

    void readSTL();

    void LaunchOutLineFilter();
    void LaunchSmoothFilter();
    void handlCam();
    void LaunchReflectFilter();
    void LaunchSmoothFilteradd();
    void LaunchClipFilter();
    void LaunchShrinkFilter();
    void RemoveFilter();
    void axes();
    void CalcA();
    void CalcV();

    void BuildSphere();
    void BuildCone();
    void BuildArrow();

    void changeX();
    void changeY();
    void changeZ();

    void changeRX();
    void changeRY();
    void changeRZ();

    void upDateList();

private slots:
    void on_tabWidget_tabCloseRequested(int index);
    void on_actionAdd_triggered();

    void on_clear_clicked();

private:

    Ui::MainWindow *ui;

    ModelRender* Model = new ModelRender();
    std::vector<ModelRender> ModelList;
    filter * vtkFilter = new filter();

    void UiSetup();
    void InitOpenGLWindow();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow =  vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    void filterFunctionConnect();
    void PositionChange();
    void BuildPreLoad();
    std::vector<QString> FileName;
    int file = 0;

};
#endif // MAINWINDOW_H
