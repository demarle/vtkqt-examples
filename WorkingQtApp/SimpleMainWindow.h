#ifndef __SimpleMainWindow_h
#define __SimpleMainWindow_h

#include <QMainWindow>

class QGraphicsScene;
class QTreeWidgetItem;

class SimpleMainWindow : public QMainWindow
{
Q_OBJECT

public:
  SimpleMainWindow();
  ~SimpleMainWindow();

signals:
  void shapeChanged( QString );

protected slots:
  void onChangeShape(QTreeWidgetItem*,int);

private:
  QGraphicsScene* scene;
};

#endif //__SimpleMainWindow_h