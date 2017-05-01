#include "SimpleMainWindow.h"

#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMouseEvent>

#include <vtkPNGReader.h>
#include <vtkPNGWriter.h>
#include <vtkSmartPointer.h>
#include <vtkImageMagnitude.h>
#include <vtkImageGradientMagnitude.h>
#include <vtkImageShiftScale.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkCommand.h>
#include <vtkEventQtSlotConnect.h>

#define vsp vtkSmartPointer

class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New()
    {
    return new vtkMyCallback;
    }

  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
    std::cerr << "Wheel";
    }
};

SimpleMainWindow::SimpleMainWindow()
{
  Ui::MainWindow* uimw = new Ui::MainWindow();
  uimw->setupUi( this );

  QObject::connect( uimw->openButton, SIGNAL(clicked()), this, SLOT(onOpen()));
  QObject::connect( uimw->filterButton, SIGNAL(clicked()), this, SLOT(onFilter()));
  QObject::connect( uimw->saveButton, SIGNAL(clicked()), this, SLOT(onSave()));
  QObject::connect( uimw->openButton, SIGNAL(clicked(bool)), uimw->filterButton, SLOT(setDisabled(bool)));
  QObject::connect( uimw->filterButton, SIGNAL(clicked(bool)), uimw->saveButton, SLOT(setDisabled(bool)));

  uimw->filterButton->setEnabled( false );
  uimw->saveButton->setEnabled( false );

  this->magnitude = vtkImageMagnitude::New( );

  this->gradient = vtkImageGradientMagnitude::New( );
  this->gradient->SetInputConnection( magnitude->GetOutputPort( ));

  this->scale = vtkImageShiftScale::New( );
  this->scale->SetOutputScalarTypeToUnsignedChar( );
  this->scale->SetInputConnection( gradient->GetOutputPort( ));

  this->renderer = vtkRenderer::New( );
  this->actor = vtkImageActor::New( );
  this->mapper = vtkImageSliceMapper::New( );

  this->actor->SetMapper( mapper );

  this->qvtkWidget = uimw->qvtkWidget;
  this->qvtkWidget->GetRenderWindow( )->AddRenderer( renderer );

  vtkInteractorStyleImage* style = vtkInteractorStyleImage::New( );
  this->qvtkWidget->GetRenderWindow( )
                  ->GetInteractor( )
                  ->SetInteractorStyle( style );
  style->Delete( );
}

SimpleMainWindow::~SimpleMainWindow()
{
  this->magnitude->Delete( );
  this->scale->Delete( );
  this->gradient->Delete( );
  this->mapper->Delete( );
  this->actor->Delete( );
  this->renderer->Delete( );
}

void SimpleMainWindow::onOpen()
{
  QFileDialog fileDialog( this, "Open PNG image", QDir::homePath()+"/Data/", "*.png");

  if( !fileDialog.exec() || fileDialog.selectedFiles().empty() )
    {
    return;
    }

  vsp<vtkPNGReader> reader = vsp<vtkPNGReader>::New( );
  reader->SetFileName( fileDialog.selectedFiles()[0].toStdString().c_str() );
  reader->Update( );

  this->mapper->SetInputConnection( reader->GetOutputPort() );
  this->renderer->AddViewProp( this->actor );
  this->renderer->ResetCamera( );
  this->qvtkWidget->update( );

  this->magnitude->SetInputConnection( reader->GetOutputPort( ));
}

void SimpleMainWindow::onFilter()
{
  this->gradient->Update( );

  double range[2];
  vtkImageData::SafeDownCast(gradient->GetOutputDataObject(0))->GetScalarRange( range );

  this->scale->SetShift( -range[0] );
  this->scale->SetScale( 255./(range[1] - range[0] ) );
  this->scale->Update( );

  this->mapper->SetInputConnection( this->scale->GetOutputPort() );
  this->renderer->ResetCamera( );
  this->qvtkWidget->update( );
}

void SimpleMainWindow::onSave()
{
  QString saveName = QFileDialog::getSaveFileName();
  if( !saveName.compare("") )
    {
    return;
    }

  vsp<vtkPNGWriter> writer = vsp<vtkPNGWriter>::New( );

  writer->SetFileName( saveName.toStdString().c_str() );

  writer->SetInputConnection( scale->GetOutputPort( ));  
  writer->Write( );
}
