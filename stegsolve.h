#ifndef STEGSOLVE_H
#define STEGSOLVE_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QKeySequence>
#include <QDebug>
#include <QFileDialog>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class Stegsolve : public QMainWindow
{
    Q_OBJECT
private:
    QImage *image;
    void init_menubar();
    void init_statusbar();

private slots:
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
