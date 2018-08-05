#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QLabel>

class ImageWidget : public QWidget
{
public:
    virtual void paint(QImage *image);
};

#endif // IMAGEWIDGET_H
