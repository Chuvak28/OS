#include <QTime>
#include <QtConcurrent/QtConcurrent>
#include <QDebug>
#include "capture_thread.h"

CaptureThread::CaptureThread(int camera, QMutex *lock):
    running(false), cameraID(camera), videoPath(""), data_lock(lock)
{
    fps_calculating = false;
    fps = 0.0;

    frame_width = frame_height = 0;
    video_saving_status = STOPPED;
    saved_video_name = "";
    video_writer = nullptr;

    motion_detecting_status = false;
}

CaptureThread::CaptureThread(QString videoPath, QMutex *lock):
    running(false), cameraID(-1), videoPath(videoPath), data_lock(lock)
{
    fps_calculating = false;
    fps = 0.0;

    frame_width = frame_height = 0;
    video_saving_status = STOPPED;
    saved_video_name = "";
    video_writer = nullptr;

    motion_detecting_status = false;
}

CaptureThread::~CaptureThread() {
}

void CaptureThread::run() {
    running = true;
    cv::VideoCapture cap(cameraID);
    cv::Mat tmp_frame;

//    frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
//    frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

//    segmentor = cv::createBackgroundSubtractorMOG2(500, 16, true);

   while(running) {
      // data_lock->lock();
        cap >> tmp_frame;
        if (tmp_frame.empty()) {
        //    data_lock->unlock();
            break;
        }
//        if(motion_detecting_status) {
//            motionDetect(tmp_frame);
//        }
//        if(video_saving_status == STARTING) {
//            startSavingVideo(tmp_frame);
//        }
//        if(video_saving_status == STARTED) {
//            video_writer->write(tmp_frame);
//        }
//        if(video_saving_status == STOPPING) {
//            stopSavingVideo();
//        }

        cvtColor(tmp_frame, tmp_frame, cv::COLOR_BGR2RGB);
        //data_lock->lock();
        frame = tmp_frame;
        data_lock->unlock();
        emit frameCaptured(&frame);
//        if(fps_calculating) {
//            calculateFPS(cap);
//        }
    }
    cap.release();
    running = false;
}

void CaptureThread::calculateFPS(cv::VideoCapture &cap)
{
    const int count_to_read = 100;
    cv::Mat tmp_frame;
    QTime timer;
    timer.start();
    for(int i = 0; i < count_to_read; i++) {
            cap >> tmp_frame;
    }
    int elapsed_ms = timer.elapsed();
    fps = count_to_read / (elapsed_ms / 1000.0);
    fps_calculating = false;
    emit fpsChanged(fps);
}


