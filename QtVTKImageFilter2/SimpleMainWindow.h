#ifndef __SimpleMainWindow_h
#define __SimpleMainWindow_h

#include <QMainWindow>


class vtkImageMagnitude;
class vtkImageGradientMagnitude;
class vtkImageShiftScale;
class vtkImageSliceMapper;
class QVTKWidget;
class vtkImageActor;
class vtkRenderer;

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
  vtkImageSliceMapper* mapper;

  QVTKWidget* qvtkWidget;
  vtkRenderer* renderer;
  vtkImageActor* actor;
};

#endif //__SimpleMainWindow_h