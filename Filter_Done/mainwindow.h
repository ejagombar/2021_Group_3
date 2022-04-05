#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vtkSTLReader.h"
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkLight.h>
#include <vtkProperty.h>
#include <ModelRender.h>
#include <filter.h>


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

    //ModelRender* Model = new ModelRender();

private slots:
    void on_tabWidget_tabCloseRequested(int index);
    void on_actionAdd_triggered();

private:

    Ui::MainWindow *ui;

    ModelRender* Model = new ModelRender();
    ModelRender* Models[100];
    filter * vtkFilter = new filter();

    void UiSetup();
    void InitOpenGLWindow();

    void filterFunctionConnect();
    void ListViewSetup();
    void PositionChange();
    void BuildPreLoad();

};
#endif // MAINWINDOW_H
