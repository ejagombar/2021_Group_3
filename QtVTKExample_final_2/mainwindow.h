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

/*!
 * \brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /*!
     * \brief setBackgndColor
     */
    void setBackgndColor();
    /*!
     * \brief setActorColor
     */
    void setActorColor();
    /*!
     * \brief setBackgndColor for a specific value
     */
    void SetBackground(double arg1, double arg2, double arg3);

signals:
    void signal_loadStl(QString path);

public slots:

    /*!
     * \brief readSTL
     */
    void readSTL();
    /*!
     * \brief Apply OutLineFilter
     */
    void LaunchOutLineFilter();
    /*!
     * \brief Apply SmoothFilter independently
     */
    void LaunchSmoothFilter();
    /*!
     * \brief reset camera position
     */
    void handlCam();
    /*!
     * \brief Apply ReflectFilter
     */
    void LaunchReflectFilter();
    /*!
     * \brief Apply SmoothFilter
     */
    void LaunchSmoothFilteradd();
    /*!
     * \brief Apply ClipFilter
     */
    void LaunchClipFilter();
    /*!
     * \brief Apply ShrinkFilter
     */
    void LaunchShrinkFilter();
    /*!
     * \brief Remove all fiters
     */
    void RemoveFilter();
    /*!
     * \brief Show the aces
     */
    void axes();
    /*!
     * \brief Get the area of model
     */
    void CalcA();
    /*!
     * \brief Get the volume of model
     */
    void CalcV();

    /*!
     * \brief BuildSphere
     */
    void BuildSphere();
    /*!
     * \brief BuildCone
     */
    void BuildCone();
    /*!
     * \brief BuildArrow
     */
    void BuildArrow();

    /*!
     * \brief change X position
     */
    void changeX();
    /*!
     * \brief change Y position
     */
    void changeY();
    /*!
     * \brief change Z position
     */
    void changeZ();

    /*!
     * \brief rotate X
     */
    void changeRX();
    /*!
     * \brief rotate Y
     */
    void changeRY();
    /*!
     * \brief rotate Z
     */
    void changeRZ();

    /*!
     * \brief update the list
     */
    void upDateList();

private slots:
    void on_tabWidget_tabCloseRequested(int index);
    void on_actionAdd_triggered();
    void on_clear_clicked();
    void on_list_itemSelectionChanged();

    void on_tabWidget_currentChanged(int index);
private:

    Ui::MainWindow *ui;

    ModelRender* Model = new ModelRender();
    std::vector<ModelRender*> ModelList;
    filter * vtkFilter = new filter();

    void UiSetup();
    void InitOpenGLWindow();
    void filterFunctionConnect();
    void PositionChange();
    void BuildPreLoad(); //for connection function
    std::vector<QString> FileName;
    void render();
    Form* getCurrentTab() const;
    vtkSmartPointer<vtkRenderer> getCurentRender() const;
    ModelRender* getCurrentModel() const;
    std::vector<ModelRender*> *getCurrentModelList() const;
    std::vector<QString> *getCurrentFileNames() const;

    int file = 0;

    float x = 0; ///<Position variable X
    float y = 0; ///<Position variable Y
    float z = 0; ///<Position variable Z

    float BR = 0.6; ///<Angle variable X
    float BG = 0.6; ///<Angle variable Y
    float BB = 0.6; ///<Angle variable Z

};
#endif // MAINWINDOW_H
