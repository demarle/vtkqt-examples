#include <vtkCommand.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
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
    int value = static_cast<int>(static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue());
    this->SphereSource->SetPhiResolution(value/2);
    this->SphereSource->SetThetaResolution(value);
    }
  vtkSliderCallback():SphereSource(0) {}
  vtkSphereSource *SphereSource;
};

int main(int ac, char **av)
{
  vtkRenderWindow *rwin = vtkRenderWindow::New();
  vtkRenderWindowInteractor *renderWindowInteractor =
    vtkRenderWindowInteractor::New();
  rwin->SetInteractor(renderWindowInteractor);
  vtkRenderer *renderer = vtkRenderer::New();
  rwin->AddRenderer(renderer);

  // sphere
  vtkSphereSource *sphereSource = vtkSphereSource::New();
  sphereSource->Update();

  vtkSliderRepresentation3D *sliderRep
    = vtkSliderRepresentation3D::New();
  sliderRep->SetMinimumValue(3.0);
  sliderRep->SetMaximumValue(50.0);
  sliderRep->SetValue(sphereSource->GetThetaResolution());
  sliderRep->SetTitleText("Sphere Resolution");
  sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToWorld();
  sliderRep->GetPoint1Coordinate()->SetValue(-4,6,0);
  sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToWorld();
  sliderRep->GetPoint2Coordinate()->SetValue(4,6,0);
  sliderRep->SetSliderLength(0.075);
  sliderRep->SetSliderWidth(0.05);
  sliderRep->SetEndCapLength(0.05);

  vtkSliderWidget *sliderWidget = vtkSliderWidget::New();
  renderWindowInteractor =
    rwin->GetInteractor();
  cerr << "GOT " << renderWindowInteractor << endl;
  sliderWidget->SetInteractor(renderWindowInteractor);
  sliderWidget->SetRepresentation(sliderRep);
  sliderWidget->SetAnimationModeToAnimate();
  sliderWidget->EnabledOn();

  vtkSliderCallback *callback = vtkSliderCallback::New();
  callback->SphereSource = sphereSource;
  sliderWidget->AddObserver(vtkCommand::InteractionEvent,callback);


  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor =
      vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);

  // VTK Renderer
  renderer->AddActor(sphereActor);
  renderer->AddActor(sliderRep);

  rwin->Render();
  renderWindowInteractor->Start();
};
