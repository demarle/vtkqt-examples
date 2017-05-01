#include <QApplication>
#include <ui_mainwindow.h>
#include <QMainWindow>

int main( int argc, char** argv )
{
  QApplication app(argc, argv);

  QMainWindow mainWindow;

  Ui::MainWindow* uimw = new Ui::MainWindow();
  uimw->setupUi( &mainWindow );

  mainWindow.show();

  return( app.exec() );
}
