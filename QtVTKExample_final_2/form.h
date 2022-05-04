#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QMainWindow>
#include "vtkSTLReader.h"
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkLight.h>
#include <vtkProperty.h>
#include <ModelRender.h>
#include <filter.h>
#include "mainwindow.h"
#include "ui_form.h"

namespace Ui {
class Form;
}

/*!
 * \brief The Form class
 */
class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    ModelRender* ModelS = new ModelRender();
    void render();

    void SetBackground(double arg1, double arg2, double arg3);

    Ui::Form *ui;
    vtkSmartPointer<vtkRenderer> getRenderer();

    ModelRender *getModel();

    std::vector<ModelRender *> *getModelList();

    /*!
     * \brief getFileNames
     */
    std::vector<QString> *getFileNames();

    /*!
     * \brief RenderWindow
     */
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> getRenderWindow();

private:
    void OpenGLWindow();

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow =  vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

    ModelRender* Model = new ModelRender();
    std::vector<ModelRender*> ModelList;  ///<vector for ModelRender class
    std::vector<QString> FileNames;  ///<vector for FileName
};

#endif // FORM_H
