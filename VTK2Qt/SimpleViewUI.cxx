#include "ui_SimpleViewUI.h"
#include "SimpleViewUI.h"
 
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkSliderRepresentation3D.h>
#include <vtkSliderWidget.h>

#include "vtkSmartPointer.h"

class vtkSliderCallback : public vtkCommand
{
public:
  static vtkSliderCallback *New()
    {
    return new vtkSliderCallback;
    }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkSliderWidget *sliderWidget =
        reinterpret_cast<vtkSliderWidget*>(caller);
      int value = static_cast<int> (
       static_cast<vtkSliderRepresentation *> (
         sliderWidget->GetRepresentation())->GetValue());
      simpleView->SetResolution(value);
    }
  vtkSliderCallback():simpleView(0) {}
  SimpleView *simpleView;
};
 
void SimpleView::SetResolution(int value)
{
  this->ui->spinBox->setValue(value);
}

// Constructor
SimpleView::SimpleView() 
{
  this->ui = new Ui_SimpleView;
  this->ui->setupUi(this);

  // VTK Renderer
  vtkSmartPointer<vtkRenderer> renderer = 
      vtkSmartPointer<vtkRenderer>::New();

  // VTK/Qt wedded
  this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

  vtkRenderWindowInteractor *renderWindowInteractor =
    this->ui->qvtkWidget->GetRenderWindow()->GetInteractor();
 
  // sphere
  sphereSource = vtkSphereSource::New();
  sphereSource->Update();

  sliderRep = vtkSliderRepresentation3D::New();
  sliderRep->SetMinimumValue(3.0);
  sliderRep->SetMaximumValue(50.0);
  sliderRep->SetValue(sphereSource->GetThetaResolution());
  sliderRep->SetTitleText("Sphere Resolution");
  sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToWorld();
  sliderRep->GetPoint1Coordinate()->SetValue(-2,2,0);
  sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToWorld();
  sliderRep->GetPoint2Coordinate()->SetValue(2,2,0);
  sliderRep->SetSliderLength(0.075);
  sliderRep->SetSliderWidth(0.05);
  sliderRep->SetEndCapLength(0.05);

  vtkSliderWidget * sliderWidget = vtkSliderWidget::New();
  sliderWidget->SetInteractor(renderWindowInteractor);
  sliderWidget->SetRepresentation(sliderRep);
  sliderWidget->SetAnimationModeToAnimate();
  sliderWidget->EnabledOn();

  vtkSliderCallback *callback = vtkSliderCallback::New();
  callback->simpleView = this;
  sliderWidget->AddObserver(vtkCommand::InteractionEvent,callback);

  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor = 
      vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
 
  renderer->AddActor(sphereActor);
  renderer->AddActor(sliderRep);

  // Set up action signals and slots
  connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
  connect(this->ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(OnValue(int)));
};
 
void SimpleView::slotExit() 
{
  qApp->exit();
}

void SimpleView::OnValue(int value)
{
  sliderRep->SetValue(value);
  sphereSource->SetPhiResolution(value);
  sphereSource->SetThetaResolution(value);
  this->ui->qvtkWidget->GetRenderWindow()->Render();
}
