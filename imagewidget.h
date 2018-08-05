#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>

class ImageWidget: public QWidget
{
private:
    QLabel *label;
public:
    ImageWidget(QWidget *parent = 0);
    void paint(QImage *image, int channel, float scale);
};

#endif // IMAGEWIDGET_H
