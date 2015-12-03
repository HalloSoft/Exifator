#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qexifimageheader.h"
#include "qmetadata.h"

#include <QDebug>
#include <QFileDialog>
#include <QtQuickWidgets/QQuickWidget>

MainWindow::MainWindow(const QString &filePath, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    exif(0), header(0)
{
    ui->setupUi(this);

    bool isConnected = false; Q_UNUSED(isConnected);
    isConnected = connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));   Q_ASSERT(isConnected);

    if(!filePath.isEmpty())
        openFile(filePath);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openFile(QString filePathName)
{
    if(filePathName.isEmpty())
        filePathName = QFileDialog::getOpenFileName(this);

    exif = new(std::nothrow) QMetaData(filePathName, this, ui->textEditresult);

    foreach(QString entry, exif->keyWordList())
        qDebug() << entry;

    setThumbNail();
}

void MainWindow::setThumbNail()
{
    if(!exif)
        return;

    QList<QExifImageHeader *> *headers = exif->exifImageHeaderList();

    QImage thumbNail;

    if(headers->size() > 0)
    {
        header = headers->at(0);
        QList<QExifImageHeader::GpsTag>gpsTags = header->gpsTags();
        //qDebug() << "Number of GPS-Tags" << gpsTags.count();

        ui->gpsWidget->initialize(header);

//        foreach(QExifImageHeader::GpsTag gpsTag, gpsTags)
//        {
//            QExifValue exifValue = header->value(gpsTag);
//            if(!exifValue.isNull())
//                qDebug() << "Gps-Tag:" << QMetaData::tagToText(gpsTag)
//                         << "\tValue:" << exifValue.toString() << "\tType:" << exifValue.type();
//            else
//                qDebug() << "Gps-Tag:" << QMetaData::tagToText(gpsTag) << "is null";

//            if(exifValue.type() == QExifValue::Rational)
//            {
//                QVector<QExifURational> vector = exifValue.toRationalVector();
//                foreach(QExifURational rat, vector)
//                {
//                    qDebug() << "-----------" <<rat.first << rat.second;
//                }
//            }
//        }

        // show Thumbnail
        thumbNail = headers->at(0)->thumbnail();
    }
    else
        qDebug() << "No Exif-Header found";

    ui->labelThumbnail->setPixmap(QPixmap::fromImage(thumbNail));
}
