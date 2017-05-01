#include "SimpleMainWindow.h"

#include "ui_mainwindow.h"

#include <QFileDialog>

#include <vtkPNGReader.h>
#include <vtkPNGWriter.h>
#include <vtkSmartPointer.h>
#include <vtkImageMagnitude.h>
#include <vtkImageGradientMagnitude.h>
#include <vtkImageShiftScale.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>

#define vsp(class,var) \
 vtkSmartPointer<class> tmpvar = vtkSmartPointer<class>::New( );\
 var = tmpvar;

SimpleMainWindow::SimpleMainWindow()
{
  Ui::MainWindow* uimw = new Ui::MainWindow();
  uimw->setupUi( this );

  QObject::connect( uimw->openButton, SIGNAL(clicked()), this, SLOT(onOpen()));
  QObject::connect( uimw->filterButton, SIGNAL(clicked()), this, SLOT(onFilter()));
  QObject::connect( uimw->saveButton, SIGNAL(clicked()), this, SLOT(onSave()));

  this->magnitude = vtkImageMagnitude::New( );

  vsp(vtkImageGradientMagnitude, this->gradient );
  gradient->SetInputConnection( magnitude->GetOutputPort( ));

  scale = vtkImageShiftScale::New( );
  scale->SetOutputScalarTypeToUnsignedChar( );
  scale->SetInputConnection( gradient->GetOutputPort( ));
}

SimpleMainWindow::~SimpleMainWindow()
{
  magnitude->Delete( );
  scale->Delete( ); // comment out to avoid seg mem leak
  //gradient->Delete( ); //don't because it already a smart pointer
}

void SimpleMainWindow::onOpen()
{
  QFileDialog fileDialog( this, "Open PNG image", QDir::homePath()+"/Data/", "*.png");

  fileDialog.exec();

  vtkPNGReader* reader;
  vsp(vtkPNGReader,reader);
  reader->SetFileName( fileDialog.selectedFiles()[0].toStdString().c_str() );
  reader->Update( );

  magnitude->SetInputConnection( reader->GetOutputPort( ));
}

void SimpleMainWindow::onFilter()
{
  gradient->Update( );

  double range[2];
  vtkImageData::SafeDownCast(gradient->GetOutputDataObject(0))->GetScalarRange( range );

  scale->SetShift( -range[0] );
  scale->SetScale( 255./(range[1] - range[0] ) );
  scale->Update( );
}

void SimpleMainWindow::onSave()
{
  vtkPNGWriter* writer;
  vsp(vtkPNGWriter,writer);

  writer->SetFileName( QFileDialog::getSaveFileName().toStdString().c_str() );

  writer->SetInputConnection( scale->GetOutputPort( ));  
  writer->Write( );
}
