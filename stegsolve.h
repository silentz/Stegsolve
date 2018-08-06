#ifndef STEGSOLVE_H
#define STEGSOLVE_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QKeySequence>
#include <QFileDialog>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QList>
//#include <vector>

#include <QDebug>

#include "mask.h"
#include "imagewidget.h"
#include "imagefilter.h"
#include "xorimagefilter.h"
#include "maskimagefilter.h"
#include "channelimagefilter.h"
#include "randomcolormapimagefilter.h"
#include "graybitsimagefilter.h"

class Stegsolve : public QMainWindow
{
    Q_OBJECT
private:
    int scale;
    int mode;
    QList<ImageFilter*> filters;
    QImage *image;
    ImageWidget *image_widget;

    void init_menubar();
    void init_statusbar();
    void init_filters();
    void paint_image();

private slots:
    void left_arrow_clicked();
    void right_arrow_clicked();
    void open_slot();
    void save_as_slot();
    void exit_slot();
    void file_format_slot();
    void data_extract_slot();
    void stereogram_solver_slot();
    void frame_browser_slot();
    void image_combiner_slot();
    void about_slot();

public:
    Stegsolve(QImage *image = nullptr, QWidget *parent = nullptr);
    ~Stegsolve();
};

#endif // STEGSOLVE_H
