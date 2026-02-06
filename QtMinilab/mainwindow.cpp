#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_3->hide();
    numClicks = 0;

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::myButtonClick);

}

void MainWindow::myButtonClick(){
    numClicks += 1;

    ui->label->setText(QString::fromStdString("Number of Clicks: " + std::to_string(numClicks)));

    if (numClicks >= 10) {
        ui->label->hide();
        ui->label_2->hide();
        ui->label_3->show();
    }
}





MainWindow::~MainWindow()
{
    delete ui;
}
