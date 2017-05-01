#ifndef __Student_h
#define __Student_h

#include <QObject>

class QString;

class Student : public QObject
{
Q_OBJECT

public:
  Student(const QString&);
  ~Student();

protected slots:
  void listen();
private:
  QString name;
};

#endif //__Student_h

