#ifndef SimpleViewUI_H
#define SimpleViewUI_H
 
#include "vtkSmartPointer.h"
#include <QMainWindow>
 
// Forward Qt class declarations
class Ui_SimpleView;

#include <vtkSmartPointer.h>

class vtkSphereSource;
class vtkSliderRepresentation3D;

class SimpleView : public QMainWindow
{
  Q_OBJECT
public:
 
  // Constructor/Destructor
  SimpleView(); 
  ~SimpleView() {};

  void SetResolution(int res);
 
public slots:
 
  virtual void slotExit();
  void OnValue(int value);
 
protected:
 
protected slots:
 
private:
 
  // Designer form
  Ui_SimpleView *ui;


  // Some vtk instances we hold
  vtkSphereSource *sphereSource;
  vtkSliderRepresentation3D *sliderRep;
};
 
#endif // SimpleViewUI_H

