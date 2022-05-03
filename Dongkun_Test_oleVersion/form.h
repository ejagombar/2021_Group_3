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

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    ModelRender* ModelS = new ModelRender();

private:
    Ui::Form *ui;
    void OpenGLWindow();
};

#endif // FORM_H
