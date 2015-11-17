#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QMetaData;
class QExifImageHeader;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void openFile();
private:
    void setThumbNail();
    Ui::MainWindow *ui;

    QMetaData *exif;
    QExifImageHeader *header;
};

#endif // MAINWINDOW_H
