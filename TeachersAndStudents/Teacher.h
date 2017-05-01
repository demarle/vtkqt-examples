#ifndef __Teacher_h
#define __Teacher_h

#include <QObject>

class Teacher : public QObject
{
Q_OBJECT

public:
  Teacher(int);
  ~Teacher();

signals:
  void tell();

protected slots:
  void startCourse();
};

#endif //__Teacher_h

