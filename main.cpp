// main.cpp-------------------------------------------------------------------
#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLWidget.h>
#include <QSplashScreen>

#include "mainwindow.h"

int main( int argc, char** argv )
{
  //Disables the warning screen
  vtkObject::GlobalWarningDisplayOff();

  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat( QVTKOpenGLWidget::defaultFormat() );

  QApplication a( argc, argv );

  //Creates the splash screen while the program loads
  QPixmap pixmap(":/Icons/Start0.5.2.png");
  QSplashScreen splash(pixmap);
  splash.show();

  //Displays the main program and then ends the splash screen
  MainWindow window;
  window.show();
  splash.finish(&window);

  return a.exec();
}
// /main.cpp------------------------------------------------------------------
