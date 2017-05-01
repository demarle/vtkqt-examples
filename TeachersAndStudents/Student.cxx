#include "Student.h"

#include <QString>

#include <iostream>

Student::Student(const QString& studentName)
{
  this->name = studentName;
}

Student::~Student()
{

}

void Student::listen()
{
  std::cout << this->name.toStdString() <<": I am listening" << std::endl;
}
