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

class Form;

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

    void SetBackground(double arg1, double arg2, double arg3);

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
    void on_Test_clicked();
    void on_list_itemSelectionChanged();

    void on_tabWidget_currentChanged(int index);

private:

    Ui::MainWindow *ui;

    filter * vtkFilter = new filter();

    void UiSetup();
    void InitOpenGLWindow();

    void filterFunctionConnect();
    void PositionChange();
    void BuildPreLoad();

    void render();
    Form* getCurrentTab() const;
    vtkSmartPointer<vtkRenderer> getCurentRender() const;
    ModelRender* getCurrentModel() const;
    std::vector<ModelRender*> *getCurrentModelList() const;
    std::vector<QString> *getCurrentFileNames() const;

    int file = 0;

    float x = 0;
    float y = 0;
    float z = 0;

    float BR = 0.6;
    float BG = 0.6;
    float BB = 0.6;

};
#endif // MAINWINDOW_H
