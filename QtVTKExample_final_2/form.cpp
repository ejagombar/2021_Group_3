#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->OpenGLWindow();
    ui->qvtkWidgetS->setRenderWindow(renderWindow);
    ui->qvtkWidgetS->renderWindow()->AddRenderer(renderer);
}

void Form::OpenGLWindow()
{
    //ui->qvtkWidgetS->SetRenderWindow(ModelS->getRenderWindow());
    //ui->qvtkWidgetS->GetRenderWindow()->AddRenderer(ModelS->getRenderer());
}

std::vector<QString> *Form::getFileNames()
{
    return &FileNames;
}

std::vector<ModelRender *> *Form::getModelList()
{
    return &ModelList;
}

vtkSmartPointer<vtkGenericOpenGLRenderWindow> Form::getRenderWindow() //const
{
    return renderWindow;
}

ModelRender *Form::getModel() //const
{
    return Model;
}

vtkSmartPointer<vtkRenderer> Form::getRenderer() //const
{
    return renderer;
}

Form::~Form()
{
    delete ui;
}

void Form::render()
{
    qDebug() << __FUNCTION__;
    renderWindow->Render();
}

void Form::SetBackground(double arg1, double arg2, double arg3)
{
    renderer->SetBackground(arg1,arg2,arg3);
}
