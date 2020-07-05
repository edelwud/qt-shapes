#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>

#include <circle.h>
#include <elementary.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum Instruments {
    CircleDrawer = 0,
    TriangleDrawer,
    RectangleDrawer,
    LineDrawer,
    HandManipulator,
    ColourPicker
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void setIconsInitialized();
    void setButtonIcon(QPushButton* button, QString resource);
    void resizeEvent(QResizeEvent* resizeEvent) override;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_circleButton_pressed();

private:
    std::map<QAbstractButton*, Instruments> instrumentButtons;
    Instruments instrument;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
