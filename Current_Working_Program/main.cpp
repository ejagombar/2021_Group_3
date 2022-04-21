// main.cpp-------------------------------------------------------------------
#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLWidget.h>

#include "mainwindow.h"

int main( int argc, char** argv )
{
  QApplication a( argc, argv );
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat( QVTKOpenGLWidget::defaultFormat() );



  MainWindow window;
  window.show();

  return a.exec();
}
// /main.cpp------------------------------------------------------------------
