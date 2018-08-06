#ifndef IMAGEBOARD_H
#define IMAGEBOARD_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class ImageBoard : public QWidget
{
private:
    QImage to_paint;
    QPainter *painter;
protected:
    void paintEvent(QPaintEvent *event);
public:
    ImageBoard(QWidget *parent = nullptr);
    void set_image(QImage image);
};

#endif // IMAGEBOARD_H
