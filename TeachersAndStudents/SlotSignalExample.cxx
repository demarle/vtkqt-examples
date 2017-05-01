#include <QApplication>
#include "Teacher.h"
#include "Student.h"
#include <QString>
#include <iostream>
int main( int argc, char** argv )
{
  QApplication app(argc, argv);

  Teacher teacher(3000);

  Student student1(QString("Andrew"));
  Student student2(QString("Barbara"));
  Student student3(QString("Conrad"));

  QObject::connect( &teacher, SIGNAL( tell() ), &student1, SLOT( listen()));
  QObject::connect( &teacher, SIGNAL( tell() ), &student2, SLOT( listen()));
  //QObject::connect( &teacher, SIGNAL( tell() ), &student3, SLOT( listen()));

  std::cout << "Teacher: Waiting 3s for late students..." << std::endl;
  return( app.exec() );
}
