#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "c_qt.h"
#include "utilities.h"


#include "opencv2/videoio.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    data_lock = new QMutex();
    imageScene = new QGraphicsScene(this);
    ui->imageView->setScene(imageScene);
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

    openCamera();
}

void MainWindow::on_pushButton_Send_clicked()
{
    char *str2 = ui->lineEdit_Display_PATH->text().toLatin1().data();

    //fileSEND("localhost", 4547, "1.jpg", "received.jpeg");
    fileSEND("localhost", 4547, str2, "received.png");
}

void MainWindow::openCamera()
{
    //    if(capturer != nullptr) {
    //        // if a thread is already running, stop it
    //        capturer->setRunning(false);
    //        disconnect(capturer, &CaptureThread::frameCaptured, this, &MainWindow::updateFrame);


    //       // connect(capturer, &CaptureThread::finished, capturer, &CaptureThread::deleteLater);
    //    }

    int camID = 0;
    capturer = new CaptureThread(camID, data_lock);
    connect(capturer, &CaptureThread::frameCaptured, this, &MainWindow::updateFrame);
    connect(capturer, &CaptureThread::photoTaken, this, &MainWindow::appendSavedPhoto);

    capturer->start();
    ui->lineEdit_Display_PATH->setText(QString("Capturing Camera %1").arg(camID));

}

void MainWindow::updateFrame(cv::Mat *mat)
{
    data_lock->lock();
    currentFrame=*mat;
    data_lock->unlock();

    QImage frame(currentFrame.data,currentFrame.cols,currentFrame.rows,currentFrame.step,QImage::Format_RGB888);
    QPixmap image = QPixmap::fromImage(frame);
    imageScene->clear();
    ui->imageView->resetMatrix();
    imageScene->addPixmap(image);
    imageScene->update();
    ui->imageView->setSceneRect(image.rect());
}



void MainWindow::on_pushButton_ScreenShot_clicked()
{
    takePhoto();
}

void MainWindow::takePhoto()
{
    if(capturer != nullptr) {

        capturer->takePhoto();
    }
}


void MainWindow::populateSavedList()
{
    QDir dir(Utilities::getDataPath());
    QStringList nameFilters;
    nameFilters << "*.jpg";
    QFileInfoList files = dir.entryInfoList(
        nameFilters, QDir::NoDotAndDotDot | QDir::Files, QDir::Name);

    foreach(QFileInfo photo, files) {
        QString name = photo.baseName();
        QStandardItem *item = new QStandardItem();
        list_model->appendRow(item);
        QModelIndex index = list_model->indexFromItem(item);
        list_model->setData(index, QPixmap(photo.absoluteFilePath()).scaledToHeight(145), Qt::DecorationRole);
        list_model->setData(index, name, Qt::DisplayRole);
    }
}

void MainWindow::appendSavedPhoto(QString name)
{
    QString photo_path = Utilities::getPhotoPath(name, "jpg");
    QStandardItem *item = new QStandardItem();
    list_model->appendRow(item);
    QModelIndex index = list_model->indexFromItem(item);
    list_model->setData(index, QPixmap(photo_path).scaledToHeight(145), Qt::DecorationRole);
    list_model->setData(index, name, Qt::DisplayRole);
    saved_list->scrollTo(index);
}


//void MainWindow::updateMasks(int status)
//{
//    if(capturer == nullptr) {
//        return;
//    }

//    QCheckBox *box = qobject_cast<QCheckBox*>(sender());
//    for (int i = 0; i < CaptureThread::MASK_COUNT; i++){
//        if (mask_checkboxes[i] == box) {
//            capturer->updateMasksFlag(static_cast<CaptureThread::MASK_TYPE>(i), status != 0);
//        }
//    }
//}
