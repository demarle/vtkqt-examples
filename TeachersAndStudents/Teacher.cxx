#include "Teacher.h"

#include <QTimer>
#include <iostream>
Teacher::Teacher(int sympathy)
{
  QTimer::singleShot(sympathy, this, SLOT(startCourse()));
}

Teacher::~Teacher()
{

}

void Teacher::startCourse()
{
  std::cout << "Teacher: I am teaching now" << std::endl;
  emit tell();
  //QTimer::singleShot(1000, this, SLOT(startCourse()));
}
