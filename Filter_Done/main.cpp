// main.cpp-------------------------------------------------------------------
#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLWidget.h>
#include <QSplashScreen>
#include <QFile>
#include "mainwindow.h"

int main( int argc, char** argv )
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat( QVTKOpenGLWidget::defaultFormat() );

  QApplication a( argc, argv );

  QScreen *screen = QGuiApplication::screens().at(1);
  QPixmap pixmap("B.jpg");
  QSplashScreen splash(screen, pixmap);
  splash.show();

  // set the app style sheet
  QFile styleSheetFile(":/Adaptic.qss");
  styleSheetFile.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(styleSheetFile.readAll());
  a.setStyleSheet(styleSheet);

  MainWindow window;
  window.show();
  splash.finish(&window);
  return a.exec();

}
// /main.cpp------------------------------------------------------------------
