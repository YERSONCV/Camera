#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QImage>
#include <QPixmap>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool RUNNING            = false;
    int width;
    int height;
    int camPort = 0;

public slots:
    void runCamera(void);
};
#endif // MAINWINDOW_H
