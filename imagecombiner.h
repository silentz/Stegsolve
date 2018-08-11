#ifndef IMAGECOMBINER_H
#define IMAGECOMBINER_H

#include <QDialog>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>

#include "imagewidget.h"

class ImageCombiner : public QDialog
{
    Q_OBJECT
private:
    int operation;
    ImageWidget *screen;
    QImage first;
    QImage second;

    void init_interface();
    void load_second_image();
    void update_screen();
    QImage get_image();
    QString get_title();

    QRgb get_first_pixel(int w, int h);
    QRgb get_second_pixel(int w, int h);

    QImage image_xor();
    QImage image_and();
    QImage image_or();
    QImage image_add();
    QImage image_add_separate();
    QImage image_sub();
    QImage image_sub_separate();
    QImage image_mul();
    QImage image_mul_separate();
    QImage image_lightest();
    QImage image_darkest();
    QImage image_horizontal_interlace();
    QImage image_vertiacal_interlace();

private slots:
    void right_slot();
    void left_slot();
    void save_slot();

public:
    ImageCombiner(QImage first, QWidget *parent = nullptr);
};

#endif // IMAGECOMBINER_H
