#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include "capture_thread.h"
#include "opencv2/opencv.hpp"
#include <QMutex>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QtConcurrent/QtConcurrent>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QLabel>
#include <QListView>
#include <QCheckBox>
#include <QPushButton>
#include <QMutex>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString imagePath;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_Connect_clicked();

    void on_pushButton_Send_clicked();

    void on_pushButton_ScreenShot_clicked();

private slots:

    void openCamera();
    void updateFrame(cv::Mat*);
    void takePhoto();
    void appendSavedPhoto(QString name);
    //void updateMasks(int status);

private:
    void populateSavedList();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *imageScene;
    cv::Mat currentFrame;
    QMutex *data_lock;
    CaptureThread *capturer;

    QListView *saved_list;
    QStandardItemModel *list_model;
};
#endif // MAINWINDOW_H
