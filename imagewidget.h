#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "imageboard.h"

class ImageWidget: public QWidget
{
private:
    QLabel *name;
    ImageBoard *board;
public:
    ImageWidget(QWidget *parent = nullptr);
    void paint(QString name, const QImage &image, const double scale);
};

#endif // IMAGEWIDGET_H
