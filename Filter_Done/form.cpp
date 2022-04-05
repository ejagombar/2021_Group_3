#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->OpenGLWindow();
}

void Form::OpenGLWindow()
{
    ui->qvtkWidgetS->SetRenderWindow(ModelS->getRenderWindow());
    ui->qvtkWidgetS->GetRenderWindow()->AddRenderer(ModelS->getRenderer());
}

Form::~Form()
{
    delete ui;
}
