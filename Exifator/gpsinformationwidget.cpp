#include "gpsinformationwidget.h"
#include "ui_gpsinformationwidget.h"

#include "qexifimageheader.h"
#include "gpsinformationwidget.h"

#include <QDebug>
#include <QQuickWidget>

GpsInformationWidget::GpsInformationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GpsInformationWidget),
    _qmlWidget(0)
{
    ui->setupUi(this);

    _qmlWidget = new QQuickWidget(this);
    _qmlWidget->setSource(QUrl("qrc:///file/MapView.qml"));
    _qmlWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

}

GpsInformationWidget::~GpsInformationWidget()
{
    delete ui;
}

void GpsInformationWidget::initialize(QExifImageHeader *imageHeader) const
{
    QGridLayout *mainLayout = dynamic_cast<QGridLayout *>( ui->groupBox->layout());
    if(mainLayout && _qmlWidget)
        mainLayout->addWidget(_qmlWidget, 5, 0, 1, 2);

#ifdef QT_DEBUG
    if(_qmlWidget) qDebug() << "QtQuick-Item-Staus" << _qmlWidget->status();
    else           qDebug() << "There is no QtQuick-Item";

#endif

    showLatitude(imageHeader);
    showLongitude(imageHeader);
    showAltitude(imageHeader);
    showDateStamp(imageHeader);
    showTimeStamp(imageHeader);
}

void GpsInformationWidget::showLatitude(QExifImageHeader *imageHeader) const
{
    if(!imageHeader)
        return;

    QExifValue latitudeValue = imageHeader->value(QExifImageHeader::GpsLatitude);
    QVector<QExifURational> latitudeVector = latitudeValue.toRationalVector();
    quint32 degree  = 0;
    quint32 minutes = 0;
    double  seconds = 0;

    if(latitudeVector.size() > 2)
    {
        degree = latitudeVector.at(0).first;
        minutes = latitudeVector.at(1).first;
        seconds = latitudeVector.at(2).first;
        seconds = seconds / latitudeVector.at(2).second;
    }

    QExifValue latitudeRefValue = imageHeader->value(QExifImageHeader::GpsLatitudeRef);
    QString latitudeRefString = latitudeRefValue.toString();

    QString displayString = QString("%1°%2'%3\"%4")
            .arg(degree).arg(minutes).arg(seconds).arg(latitudeRefString);

    ui->labelLattitude->setText(displayString);
}

void GpsInformationWidget::showLongitude(QExifImageHeader *imageHeader) const
{
    if(!imageHeader)
        return;

    QExifValue longitudeValue = imageHeader->value(QExifImageHeader::GpsLongitude);
    QVector<QExifURational> lingitudeVector = longitudeValue.toRationalVector();

    quint32 degree  = 0;
    quint32 minutes = 0;
    double  seconds = 0;
    bool isValid = false;
    if(lingitudeVector.size() > 2)
    {
        degree = lingitudeVector.at(0).first;
        minutes = lingitudeVector.at(1).first;
        seconds = lingitudeVector.at(2).first;
        seconds = seconds / lingitudeVector.at(2).second;
        isValid = true;
    }


    QExifValue lattitudeRefValue = imageHeader->value(QExifImageHeader::GpsLongitudeRef);
    QString lattitudeRefString = lattitudeRefValue.toString();



    QString displayString = QString("%1°%2'%3\"%4")
            .arg(degree).arg(minutes).arg(seconds).arg(lattitudeRefString);

    if(isValid)
        ui->labelLongitude->setText(displayString);
}

void GpsInformationWidget::showAltitude(QExifImageHeader *imageHeader) const
{
    if(!imageHeader)
        return;

    QExifValue altitudeValue = imageHeader->value(QExifImageHeader::GpsAltitude);
    QVector<QExifURational> altitudeVector = altitudeValue.toRationalVector();

    double altitude = 0;
    bool isValid = false;

    if(altitudeVector.size() > 0)
    {
        altitude = (double)altitudeVector.at(0).first / altitudeVector.at(0).second;
        isValid = true;
    }

    if(isValid)
        ui->labelAltitude->setText(QString::number(altitude));
}

void GpsInformationWidget::showDateStamp(QExifImageHeader *imageHeader) const
{
    if(!imageHeader)
        return;

    QExifValue dateValue = imageHeader->value(QExifImageHeader::GpsDateStamp);

    if(!dateValue.isNull())
        ui->labelDateStamp->setText(dateValue.toString());
}

void GpsInformationWidget::showTimeStamp(QExifImageHeader *imageHeader) const
{
    if(!imageHeader)
        return;

    QExifValue timeValue = imageHeader->value(QExifImageHeader::GpsTimeStamp);
    QVector<QExifURational> timeVector = timeValue.toRationalVector();

    quint32 hours   = 0;
    quint32 minutes = 0;
    double  seconds = 0;
    bool isValid = false;

    if(timeVector.size() > 2)
    {
        hours = timeVector.at(0).first;
        minutes = timeVector.at(1).first;
        seconds = (double)timeVector.at(2).first / timeVector.at(2).second;
        isValid = true;
    }

    if(isValid)
    {
        QString timeFormat = QString("%1:%2:%3").arg(hours).arg(minutes).arg(seconds);
        ui->labelTimeStamp->setText(timeFormat);
    }
}
