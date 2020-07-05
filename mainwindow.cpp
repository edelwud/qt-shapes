#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <triangle.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    setIconsInitialized();

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    QTimer::singleShot(50, this, [this](){
        QRect rcontent = ui->graphicsView->contentsRect();
        ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());
    });
    ui->graphicsView->setScene(scene);

    int handlerIdentifier;
    ui->graphicsView->AddMousePressHandler([this, &handlerIdentifier](QMouseEvent* event){
        Figure* figure = Figure::createFigure(instrument);
        QPoint startPosition = event->pos();
        figure->setPos(startPosition);
        scene->addItem(figure);
        handlerIdentifier = ui->graphicsView->AddMouseMoveHandler([=](QMouseEvent* event){
            figure->setSize(event->pos() - startPosition);
            scene->update();
        });
    });

    ui->graphicsView->AddMouseReleaseHandler([this, &handlerIdentifier](QMouseEvent*){
        ui->graphicsView->RemoveMouseMoveHandler(handlerIdentifier);
    });

}

void MainWindow::resizeEvent(QResizeEvent*) {
    QTimer::singleShot(50, this, [this](){
        QRect rcontent = ui->graphicsView->contentsRect();
        ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());
    });
}

void MainWindow::setButtonIcon(QPushButton* button, QString resource) {
    QPixmap pixmap(resource);
    QIcon buttonIcon(pixmap);
    button->setIcon(buttonIcon);
    button->setIconSize(QSize(24, 24));
}

void MainWindow::setIconsInitialized() {
    setButtonIcon(ui->circleButton, ":/icons/circle");
    setButtonIcon(ui->squareButton, ":/icons/square");
    setButtonIcon(ui->triangleButton, ":/icons/triangle");
    setButtonIcon(ui->lineButton, ":/icons/line");
    setButtonIcon(ui->handButton, ":/icons/hand");
    setButtonIcon(ui->colourButton, ":/icons/colour");
    setButtonIcon(ui->saveButton, ":/icons/save");
}

MainWindow::~MainWindow()
{
    delete ui;
}

