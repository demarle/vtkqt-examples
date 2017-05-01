#ifndef __SimpleMainWindow_h
#define __SimpleMainWindow_h

#include <QMainWindow>


class vtkImageMagnitude;
class vtkImageGradientMagnitude;
class vtkImageShiftScale;

class SimpleMainWindow : public QMainWindow
{
Q_OBJECT

public:
  SimpleMainWindow();
  ~SimpleMainWindow();

protected slots:
  void onOpen();
  void onFilter();
  void onSave();

private:
  vtkImageMagnitude* magnitude;
  vtkImageGradientMagnitude* gradient;
  vtkImageShiftScale* scale;
};

#endif //__SimpleMainWindow_h