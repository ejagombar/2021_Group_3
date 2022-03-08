#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkDiskSource.h>
#include <vtkArrowSource.h>
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
#include <QMessageBox>
#include <QAbstractListModel>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <fstream>
#include <iostream>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void randerbegan(vtkSmartPointer<vtkActor> actor);

private:
    Ui::MainWindow *ui;
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    //vtkSmartPointer<vtkPlane> planeLeft;

public slots:

    void on_saveButton_triggered();
    void on_openButton_triggered();
    void on_arrow_triggered();
    void on_disk_triggered();
    void on_cone_triggered();
    void on_ColorChoose_triggered();
    void on_Color_triggered();
    void on_checkBox_stateChanged();
    void on_checkBoxclip_stateChanged();

    void handlFilter();

//signals:
    //void statusUpdateMessage( const QString & message, int timeout );
};

#endif // MAINWINDOW_H
