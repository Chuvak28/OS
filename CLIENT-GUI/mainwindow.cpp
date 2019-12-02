#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "c_qt.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    imagePath = QFileDialog::getOpenFileName(this,tr("Open File"),
                                                     "",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
    ui->lineEdit_Display_PATH->setText(imagePath);
}

void MainWindow::on_pushButton_Connect_clicked()
{


}

void MainWindow::on_pushButton_Send_clicked()
{

    fileSEND("localhost", 4547, "1.jpg", "received.jpeg");
}
