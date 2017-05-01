#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleSwitch.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkCommand.h>

#include <vtkSmartPointer.h>


#define Instantiate( obj, class ) vtkSmartPointer<class> obj = vtkSmartPointer<class>::New( );

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
    double value = 
      static_cast<double> (
        static_cast<vtkSliderRepresentation *> (
          sliderWidget->GetRepresentation()
        )->GetValue()
      );
    this->glyph->SetScaleFactor(value);
    }

  vtkGlyph3D *glyph;
};

int main( int argc, char** argv )
{
  Instantiate( sphereSource, vtkSphereSource );
  Instantiate( glyph, vtkGlyph3D );
  Instantiate( glyphMapper, vtkPolyDataMapper );
  Instantiate( glyphActor, vtkActor );
  Instantiate( sphereMapper, vtkPolyDataMapper );
  Instantiate( sphereActor, vtkActor );
  Instantiate( renderer, vtkRenderer );
  Instantiate( renderWindow, vtkRenderWindow );
  Instantiate( interactor, vtkRenderWindowInteractor );
  Instantiate( sliderWidget, vtkSliderWidget );
  Instantiate( sliderRepresentation, vtkSliderRepresentation2D );
  Instantiate( callback, vtkSliderCallback );

  sphereSource->SetRadius( 5 );
  sphereSource->SetPhiResolution( 36 );
  sphereSource->SetThetaResolution( 36 );

  glyph->SetInputConnection( sphereSource->GetOutputPort( ) );
  glyph->OrientOn( );
  glyph->SetVectorModeToUseNormal( );

  glyphMapper->SetInputConnection( glyph->GetOutputPort( ));

  glyphActor->SetMapper( glyphMapper );

  sphereMapper->SetInputConnection( sphereSource->GetOutputPort( ));

  sphereActor->SetMapper( sphereMapper );

  renderer->AddViewProp( sphereActor );
  renderer->AddViewProp( glyphActor );

  renderWindow->AddRenderer( renderer );

  renderWindow->SetInteractor( interactor );
  
  sliderRepresentation->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRepresentation->GetPoint1Coordinate()->SetValue(.1 ,.1);
  sliderRepresentation->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
  sliderRepresentation->GetPoint2Coordinate()->SetValue(.3, .1);
  sliderRepresentation->SetValue( 1.0 );

  sliderWidget->SetInteractor( interactor );
  sliderWidget->SetRepresentation( sliderRepresentation );
  sliderWidget->EnabledOn( );

  callback->glyph = glyph;
  sliderWidget->AddObserver( vtkCommand::InteractionEvent, callback );

  vtkInteractorStyleSwitch* style;
  style = vtkInteractorStyleSwitch::SafeDownCast(interactor->GetInteractorStyle());
  style->SetCurrentStyleToTrackballCamera( );

  interactor->Initialize( );
  interactor->Start( );
}
