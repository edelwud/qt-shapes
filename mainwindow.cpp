#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <triangle.h>
#include <QButtonGroup>
#include <QColorDialog>
#include <line.h>
#include <QGraphicsItemGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    instrumentButtons = {
        { ui->circleButton, Instruments::CircleDrawer },
        { ui->triangleButton, Instruments::TriangleDrawer },
        { ui->squareButton, Instruments::RectangleDrawer },
        { ui->lineButton, Instruments::LineDrawer },
        { ui->handButton, Instruments::HandManipulator }
    };

    QButtonGroup* group = new QButtonGroup(this);
    for (auto [button, instrument] : instrumentButtons) {
        group->addButton(button);
    }

    connect(group, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonPressed), [this](QAbstractButton *button){
        instrument = instrumentButtons[button];
        if (instrument == Instruments::LineDrawer) {
            for (auto item : figuresGroup->childItems()) {
                Figure* element = dynamic_cast<Figure*>(item);
                element->setPressHandler([&](QGraphicsSceneMouseEvent*, bool chosen) -> bool {
                    handleSelectedFigure(element);
                    return !chosen;
                });
            }
        } else {
            for (auto item : figuresGroup->childItems()) {
                Figure* element = dynamic_cast<Figure*>(item);
                element->setPressHandler([&](QGraphicsSceneMouseEvent*, bool) -> bool {
                    return false;
                });
            }
        }
    });
    setIconsInitialized();

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    figuresGroup = new QGraphicsItemGroup();
    linesGroup = new QGraphicsItemGroup();

    figuresGroup->setHandlesChildEvents(false);
    linesGroup->setHandlesChildEvents(false);

    scene->addItem(figuresGroup);
    scene->addItem(linesGroup);

    QTimer::singleShot(50, this, [this](){
        QRect rcontent = ui->graphicsView->contentsRect();
        ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());
    });
    ui->graphicsView->setScene(scene);

    Figure* figure;
    int handlerIdentifier;
    ui->graphicsView->AddMousePressHandler([this, &figure, &handlerIdentifier](QMouseEvent* event) {
        figure = Figure::createFigure((ElementaryFigures)instrument, baseColour);
        QPoint startPosition = event->pos();
        figure->setPos(startPosition);

        figuresGroup->addToGroup(figure);
        handlerIdentifier = ui->graphicsView->AddMouseMoveHandler([=](QMouseEvent* event){
            figure->setSize(event->pos() - startPosition);
            scene->update();
        });
    });

    ui->graphicsView->AddMouseReleaseHandler([this, &figure, &handlerIdentifier](QMouseEvent*){
        figure->setChosen(false);
        ui->graphicsView->RemoveMouseMoveHandler(handlerIdentifier);
    });

}

void MainWindow::resizeEvent(QResizeEvent*) {
    QTimer::singleShot(50, this, [this](){
        QRect rcontent = ui->graphicsView->contentsRect();
        ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());
    });
}

void MainWindow::handleSelectedFigure(Figure *selected) {
    for (auto item : figuresGroup->childItems()) {
        Figure* element = dynamic_cast<Figure*>(item);
        if (!element->isChosen()) {
            selectedFigures.push_back(element);
        }
    }
    if (selectedFigures.size() == 2) {
        Line* line = new Line(selectedFigures[0], selectedFigures[1]);
        linesGroup->addToGroup(line);
    }
    selectedFigures.erase(selectedFigures.begin(), selectedFigures.end());
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

void MainWindow::on_colourButton_pressed()
{
    baseColour = QColorDialog::getColor();
}
