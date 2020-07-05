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
    RectangleDrawer,
    TriangleDrawer,
    LineDrawer,
    HandManipulator
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void handleSelectedFigure();
    void setIconsInitialized();
    void setButtonIcon(QPushButton* button, QString resource);
    void resizeEvent(QResizeEvent* resizeEvent) override;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_colourButton_pressed();

    void on_strippedBox_stateChanged(int arg1);

    void on_lineButton_pressed();

private:
    std::vector<Figure*> selectedFigures;

    QGraphicsItemGroup* figuresGroup;
    QGraphicsItemGroup* linesGroup;

    std::map<QAbstractButton*, Instruments> instrumentButtons;
    Instruments instrument = Instruments::CircleDrawer;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    bool dottedLine = false;
    QColor baseColour = Qt::white;
};
#endif // MAINWINDOW_H
