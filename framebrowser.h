#ifndef FRAMEBROWSER_H
#define FRAMEBROWSER_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QImage>
#include <QFileDialog>
#include <QBuffer>
#include <QMovie>
#include <QLabel>

#include "imagewidget.h"

class FrameBrowser : public QDialog
{
    Q_OBJECT
private:
    int current_frame;
    QMovie *movie;
    QLabel *status;
    QByteArray *data;
    ImageWidget *screen;
    void init_interface();
    void set_current_frame();
    QImage get_current_frame();

private slots:
    void left_slot();
    void right_slot();
    void save_slot();

public:
    FrameBrowser(QByteArray data, QWidget *parent = nullptr);
};

#endif // FRAMEBROWSER_H
