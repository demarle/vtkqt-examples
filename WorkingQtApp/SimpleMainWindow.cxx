#include "SimpleMainWindow.h"

#include "ui_mainwindow.h"

#include <iostream>

SimpleMainWindow::SimpleMainWindow()
{
  Ui::MainWindow* uimw = new Ui::MainWindow();
  uimw->setupUi( this );

  QTreeWidgetItem* circle = new QTreeWidgetItem();
  circle->setText(0, "circle");

  QTreeWidgetItem* bigCircle = new QTreeWidgetItem(circle);
  bigCircle->setText(0, "big");

  QTreeWidgetItem* smallCircle = new QTreeWidgetItem(circle);
  smallCircle->setText(0, "small");

  QTreeWidgetItem* square = new QTreeWidgetItem();
  square->setText(0, "square");

  uimw->treeWidget->addTopLevelItem(circle);
  uimw->treeWidget->addTopLevelItem(square);

  this->scene = new QGraphicsScene();

  uimw->graphicsView->setScene(this->scene);

  QObject::connect( uimw->treeWidget, 
                    SIGNAL(itemClicked(QTreeWidgetItem*,int)), 
                    this, 
                    SLOT(onChangeShape(QTreeWidgetItem*,int)));
}

SimpleMainWindow::~SimpleMainWindow()
{

}

void SimpleMainWindow::onChangeShape(QTreeWidgetItem* item,int column)
{
  this->scene->clear();

  if( !item->text(0).compare("circle") )
    {
    this->scene->addEllipse( QRect( 0,0,100,100));
    }
  else if( !item->text(0).compare("square") )
    {
    this->scene->addRect( QRect( 0,0,100,100));
    }
  else if( !item->text(0).compare("big") )
    {
    if( item->parent() && !item->parent()->text(0).compare("circle") )
      {
      this->scene->addEllipse( QRect( 0,0,500,500));
      }
    else if( item->parent() && !item->parent()->text(0).compare("square") )
      {
      this->scene->addRect( QRect( 0,0,500,500));
      }
    }
  else if( !item->text(0).compare("small") )
    {
    if( item->parent() && !item->parent()->text(0).compare("circle") )
      {
      this->scene->addEllipse( QRect( 0,0,50,50));
      }
    else if( item->parent() && !item->parent()->text(0).compare("square") )
      {
      this->scene->addRect( QRect( 0,0,50,50));
      }
    }

  QTreeWidgetItem* parent = item;
  QString lastShape;
  while( parent )
    {
    lastShape = parent->text(0);
    std::cerr << lastShape.toStdString() << std::endl;
    parent = parent->parent( );
    }

  emit shapeChanged( lastShape );
}
