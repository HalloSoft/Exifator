#include "gpsinformationwidget.h"
#include "ui_gpsinformationwidget.h"

#include "qexifimageheader.h"
#include "gpsinformationwidget.h"

GpsInformationWidget::GpsInformationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GpsInformationWidget)
{
    ui->setupUi(this);
}

GpsInformationWidget::~GpsInformationWidget()
{
    delete ui;
}

void GpsInformationWidget::initialize(QExifImageHeader *imageHeader)
{
    showLatitude(imageHeader);
    showLongitude(imageHeader);
    showAltitude(imageHeader);
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

    if(lingitudeVector.size() > 2)
    {
        degree = lingitudeVector.at(0).first;
        minutes = lingitudeVector.at(1).first;
        seconds = lingitudeVector.at(2).first;
        seconds = seconds / lingitudeVector.at(2).second;
    }


    QExifValue lattitudeRefValue = imageHeader->value(QExifImageHeader::GpsLongitudeRef);
    QString lattitudeRefString = lattitudeRefValue.toString();



    QString displayString = QString("%1°%2'%3\"%4")
            .arg(degree).arg(minutes).arg(seconds).arg(lattitudeRefString);

    ui->labelLongitude->setText(displayString);
}

void GpsInformationWidget::showAltitude(QExifImageHeader *imageHeader) const
{

}
