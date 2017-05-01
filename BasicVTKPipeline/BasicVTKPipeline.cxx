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

#include <iostream>

#define Instantiate( obj, class ) vtkSmartPointer<class> obj = vtkSmartPointer<class>::New( );

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
  
  renderWindow->Render();
  cout << "Press enter to continue" << endl;
  cin.ignore();
  
}
