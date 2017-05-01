#include <QApplication>
#include <QStatusBar>
#include "SimpleMainWindow.h"

int main( int argc, char** argv )
{
  QApplication app(argc, argv);

  SimpleMainWindow mainWindow;
  
  mainWindow.show();

  QObject::connect( &mainWindow, SIGNAL( shapeChanged(QString) ), mainWindow.statusBar(), SLOT( showMessage(QString)));

  return( app.exec() );
}