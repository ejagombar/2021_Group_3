// main.cpp-------------------------------------------------------------------
#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLWidget.h>
#include <QSplashScreen>

#include "mainwindow.h"

int main( int argc, char** argv )
{
  QApplication a( argc, argv );

  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat( QVTKOpenGLWidget::defaultFormat() );

  QPixmap pixmap(":/Icons/Start0.5.2.png");
  QSplashScreen splash(pixmap);
  splash.show();

  MainWindow window;
  window.show();
  splash.finish(&window);
  
  return a.exec();
}
// /main.cpp------------------------------------------------------------------
