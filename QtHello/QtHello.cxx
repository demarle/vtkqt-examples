#include <QApplication>
#include <QMainWindow>
#include <QLabel>

int main( int argc, char** argv )
{
  QApplication app(argc, argv);

  QMainWindow mainWindow;
  QLabel labl("Hello World", &mainWindow);
  mainWindow.show();

  return( app.exec() );
}
