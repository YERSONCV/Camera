#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QIntValidator>
#include <QDebug>
#include <QThread>

using namespace std;
using namespace cv;

Mat dummy_1ch = Mat::zeros(Size(800, 600), CV_8UC1);
Mat dummy_3ch = Mat::zeros(Size(800, 600), CV_8UC3);
QImage dummy_img_1ch(dummy_1ch.data, dummy_1ch.cols, dummy_1ch.rows, QImage::Format_Grayscale8);
QImage dummy_img_3ch(dummy_3ch.data, dummy_3ch.cols, dummy_3ch.rows, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QIntValidator *portValidator = new QIntValidator(0, 255);
    ui->camPort->setValidator(portValidator);
    connect(ui->PBTrun, SIGNAL(clicked()), this, SLOT(runCamera()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runCamera(void){
    if(this->RUNNING==true){
        ui->SRC->setPixmap(QPixmap::fromImage(dummy_img_3ch).scaled(ui->SRC->width(), ui->SRC->height(), Qt::KeepAspectRatio));

        ui->PBTrun->setText("Run");
    }else if(this->RUNNING==false){
        int port = ui->camPort->text().toInt();

        VideoCapture cap(port);

        if(!cap.isOpened()){
            QMessageBox::critical(this, "ERROR", "Please check your camera and port number.", QMessageBox::Ok);
            return;
        }

        this->camPort = port;
        ui->PBTrun->setText("Stop");

        this->RUNNING = true;

        Mat frame;

        vector<Mat> video;

        while(RUNNING==true){
            cap >> frame;
            QImage src;
            src = QImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
            ui->SRC->setPixmap(QPixmap::fromImage(src).scaled(ui->SRC->width(), ui->SRC->height(), Qt::KeepAspectRatio));

            waitKey(1);
        }
        cap.release();
    }
}








