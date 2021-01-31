#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../src/hardware/Resources.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Pacman Clone");
    setWindowIcon(QIcon(QPixmap(res::resource(PACMAN_RIGHT).c_str())));

    gameWidget = new GameWidget(this);
    setCentralWidget(gameWidget);

    setFixedSize(640, 480);
}

MainWindow::~MainWindow()
{
    delete ui;
}

