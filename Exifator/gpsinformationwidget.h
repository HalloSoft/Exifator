#ifndef GPSINFORMATIONWIDGET_H
#define GPSINFORMATIONWIDGET_H

#include <QWidget>

class QExifImageHeader;
class QQuickWidget;

namespace Ui {
class GpsInformationWidget;
}

class GpsInformationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GpsInformationWidget(QWidget *parent = 0);
    ~GpsInformationWidget();

    void initialize(QExifImageHeader* imageHeader) const;

private:
    Ui::GpsInformationWidget *ui;

    void showLatitude(QExifImageHeader* imageHeader) const;
    void showLongitude(QExifImageHeader *imageHeader) const;
    void showAltitude(QExifImageHeader *imageHeader) const;
    void showDateStamp(QExifImageHeader *imageHeader) const;
    void showTimeStamp(QExifImageHeader *imageHeader) const;

    QQuickWidget *_qmlWidget;
};

#endif // GPSINFORMATIONWIDGET_H
