#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <triangle.h>
#include <QButtonGroup>
#include <QColorDialog>
#include <line.h>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent>
#include <QFileDialog>

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

    int handManipulatorPressId = -1;
    int handManipulatorMoveId = -1;
    connect(group, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonPressed), [this, handManipulatorPressId, handManipulatorMoveId](QAbstractButton *button) mutable {
        instrument = instrumentButtons[button];
        switch (instrument) {
        case Instruments::LineDrawer: {
            if (handManipulatorPressId != -1) {
                ui->graphicsView->RemoveMousePressHandler(handManipulatorPressId);
                handManipulatorPressId = -1;
            }

            if (handManipulatorMoveId != -1) {
                ui->graphicsView->RemoveMouseReleaseHandler(handManipulatorMoveId);
                handManipulatorMoveId = -1;
            }

            for (auto item : figuresGroup->childItems()) {
                Figure* element = dynamic_cast<Figure*>(item);
                element->setPressHandler([&](QGraphicsSceneMouseEvent*, bool) -> bool {
                    handleSelectedFigure();
                    return true;
                });
            }
        }
        break;
        case Instruments::HandManipulator: {
            for (auto item : figuresGroup->childItems()) {
                Figure* element = dynamic_cast<Figure*>(item);
                element->setPressHandler([&](QGraphicsSceneMouseEvent*, bool) -> bool {
                    return false;
                });
            }

            handManipulatorPressId = ui->graphicsView->AddMousePressHandler([this](QMouseEvent* position) mutable {
                int x = position->pos().x();
                int y = position->pos().y();
                scene->update();

                int handManipulatorMoveId = ui->graphicsView->AddMouseMoveHandler([this, x, y](QMouseEvent* event) mutable {
                    for (auto item : figuresGroup->childItems()) {
                        Figure* element = dynamic_cast<Figure*>(item);
                        if (element->isChosen()) {
                            element->setPos(element->pos() + (event->pos() - QPoint(x, y))/100);
                        }
                    }
                    x = event->pos().x();
                    y = event->pos().y();
                    scene->update();
                });

                ui->graphicsView->AddMouseReleaseHandler([this, handManipulatorMoveId](QMouseEvent*){
                    ui->graphicsView->RemoveMouseMoveHandler(handManipulatorMoveId);
                });
            });
        }
        break;
        default: {
            qDebug() << handManipulatorPressId;
            if (handManipulatorPressId != -1) {
                ui->graphicsView->RemoveMousePressHandler(handManipulatorPressId);
                handManipulatorPressId = -1;
            }

            if (handManipulatorMoveId != -1) {
                ui->graphicsView->RemoveMouseReleaseHandler(handManipulatorMoveId);
                handManipulatorMoveId = -1;
            }
            for (auto item : figuresGroup->childItems()) {
                Figure* element = dynamic_cast<Figure*>(item);
                element->setPressHandler([&](QGraphicsSceneMouseEvent*, bool) -> bool {
                    return false;
                });
            }
        }
        }
    });
    setIconsInitialized();

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    figuresGroup = new QGraphicsItemGroup();
    linesGroup = new QGraphicsItemGroup();
    manager = new GraphicsItemManager(figuresGroup, linesGroup);

    figuresGroup->setHandlesChildEvents(false);
    linesGroup->setHandlesChildEvents(false);

    scene->addItem(figuresGroup);
    scene->addItem(linesGroup);

    QTimer::singleShot(50, this, [this](){
        QRect rcontent = ui->graphicsView->contentsRect();
        ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());
    });
    ui->graphicsView->setScene(scene);

    int handlerIdentifier;
    ui->graphicsView->AddMousePressHandler([this, &handlerIdentifier](QMouseEvent* event) {
        try {
            Figure* figure = Figure::createFigure((ElementaryFigures)instrument, baseColour);
            QPoint startPosition = event->pos();
            figure->setPos(startPosition);
            scene->update();

            figuresGroup->addToGroup(figure);
            handlerIdentifier = ui->graphicsView->AddMouseMoveHandler([=](QMouseEvent* event){
                figure->setSize(event->pos() - startPosition);
                scene->update();
            });
        } catch(...) {}
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

void MainWindow::handleSelectedFigure() {
    for (auto item : figuresGroup->childItems()) {
        Figure* element = dynamic_cast<Figure*>(item);
        if (element->isChosen()) {
            selectedFigures.push_back(element);
        }
    }
    if (selectedFigures.size() == 2) {
        Line* line = new Line(selectedFigures[0], selectedFigures[1]);
        line->setDotted(dottedLine);
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
    setButtonIcon(ui->loadButton, ":/icons/load");
    setButtonIcon(ui->saveButton, ":/icons/save");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_colourButton_pressed()
{
    QColor colour = QColorDialog::getColor(Qt::white, this);
    for (auto item : figuresGroup->childItems()) {
        Figure* element = dynamic_cast<Figure*>(item);
        if (element->isChosen()) {
            element->setColour(colour);
        }
    }
    for (auto item : linesGroup->childItems()) {
        Line* element = dynamic_cast<Line*>(item);
        if (element->isChosen()) {
            element->setColour(colour);
        }
    }
}

void MainWindow::on_strippedBox_stateChanged(int status)
{
    dottedLine = status ? true : false;
}

void MainWindow::on_lineButton_pressed()
{
    handleSelectedFigure();
}

void MainWindow::on_saveButton_pressed()
{
    QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
    manager->Pack("file");
}

void MainWindow::on_loadButton_pressed()
{
    manager->Unpack("file");
}
