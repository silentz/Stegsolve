#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class ImageWidget: public QWidget
{
private:
    QLabel *label;
public:
    ImageWidget(QWidget *parent = nullptr);
    void paint(const QImage &image, const double scale);
};

#endif // IMAGEWIDGET_H
