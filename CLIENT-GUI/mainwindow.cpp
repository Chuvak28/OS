#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "c_qt.h"


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
//       disconnect(capturer, &CaptureThread::fpsChanged, this, &MainWindow::updateFPS);
//        //disconnect(capturer, &CaptureThread::videoSaved, this, &MainWindow::appendSavedVideo);
//       // connect(capturer, &CaptureThread::finished, capturer, &CaptureThread::deleteLater);
//    }
    // I am using my second camera whose Index is 2.  Usually, the
    // Index of the first camera is 0.
    int camID = 0;
    capturer = new CaptureThread(camID, data_lock);
    connect(capturer, &CaptureThread::frameCaptured, this, &MainWindow::updateFrame);
    //connect(capturer, &CaptureThread::fpsChanged, this, &MainWindow::updateFPS);
    //connect(capturer, &CaptureThread::videoSaved, this, &MainWindow::appendSavedVideo);
    capturer->start();
    ui->lineEdit_Display_PATH->setText(QString("Capturing Camera %1").arg(camID));
//    monitorCheckBox->setCheckState(Qt::Unchecked);
//    recordButton->setText("Record");
//    recordButton->setEnabled(true);
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

void MainWindow::calculateFPS()
{
    if(capturer != nullptr) {
        capturer->startCalcFPS();
    }
}



void MainWindow::updateFPS(float fps)
{
    ui->lineEdit_Display_PATH->setText(QString("FPS of current camera is %1").arg(fps));
}


//void MainWindow::recordingStartStop() {
//    QString text = recordButton->text();
//    if(text == "Record" && capturer != nullptr) {
//        capturer->setVideoSavingStatus(CaptureThread::STARTING);
//        recordButton->setText("Stop Recording");
//        monitorCheckBox->setCheckState(Qt::Unchecked);
//        monitorCheckBox->setEnabled(false);
//    } else if(text == "Stop Recording" && capturer != nullptr) {
//        capturer->setVideoSavingStatus(CaptureThread::STOPPING);
//        recordButton->setText("Record");
//        monitorCheckBox->setEnabled(true);
//    }
//}


//void MainWindow::populateSavedList()
//{
//    QDir dir(Utilities::getDataPath());
//    QStringList nameFilters;
//    nameFilters << "*.jpg";
//    QFileInfoList files = dir.entryInfoList(
//        nameFilters, QDir::NoDotAndDotDot | QDir::Files, QDir::Name);

//    foreach(QFileInfo cover, files) {
//        QString name = cover.baseName();
//        QStandardItem *item = new QStandardItem();
//        list_model->appendRow(item);
//        QModelIndex index = list_model->indexFromItem(item);
//        list_model->setData(index, QPixmap(cover.absoluteFilePath()).scaledToHeight(145), Qt::DecorationRole);
//        list_model->setData(index, name, Qt::DisplayRole);
//    }
//}

//void MainWindow::appendSavedVideo(QString name)
//{
//    QString cover = Utilities::getSavedVideoPath(name, "jpg");
//    QStandardItem *item = new QStandardItem();
//    list_model->appendRow(item);
//    QModelIndex index = list_model->indexFromItem(item);
//    list_model->setData(index, QPixmap(cover).scaledToHeight(145), Qt::DecorationRole);
//    list_model->setData(index, name, Qt::DisplayRole);
//    saved_list->scrollTo(index);
//}

