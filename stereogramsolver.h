#ifndef STEREOGRAMSOLVER_H
#define STEREOGRAMSOLVER_H

#include <QDialog>
#include <QImage>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QFileDialog>

#include "imagewidget.h"

class StereogramSolver : public QDialog
{
    Q_OBJECT
private:
    int offset;
    QImage image;
    ImageWidget *screen;
    void init_interface();
    void paint_with_offset();
    QImage get_with_offset();
    QColor get_new_color(QColor a, QColor b);

private slots:
    void left_slot();
    void right_slot();
    void save_slot();

public:
    StereogramSolver(QImage image, QWidget *parent = nullptr);
    ~StereogramSolver();
};

#endif // STEREOGRAMSOLVER_H
