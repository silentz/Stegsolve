#ifndef DATAEXTRACT_H
#define DATAEXTRACT_H

#include <QDialog>
#include <QCheckBox>
#include <QGroupBox>
#include <QPushButton>
#include <QTextEdit>
#include <QList>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QImage>
#include <QRadioButton>
#include <QButtonGroup>
#include <QFontDatabase>
#include <QFileDialog>
#include <QFile>

class DataExtract : public QDialog
{
    Q_OBJECT
private:
    QImage image;

    QTextEdit *text;
    QList<QCheckBox*> alpha;
    QList<QCheckBox*> red;
    QList<QCheckBox*> green;
    QList<QCheckBox*> blue;
    QCheckBox *include_hexdump;
    QButtonGroup *extract_by;
    QButtonGroup *bit_order;
    QButtonGroup *bit_plane_order;

    void init_interface();
    QGroupBox* get_bit_planes();
    QGroupBox* get_preview_settings();
    QGroupBox* get_order_settings();
    QByteArray get_bytes();
    QByteArray get_bytes_by_col();
    QByteArray get_bytes_by_row();
    QByteArray process_pixel(QRgb pixel);
    QByteArray process_channel(int value, QList<QCheckBox*> *list);
    QString get_text_from_bytes(QByteArray data);

private slots:
    void preview_slot();
    void save_text_slot();
    void save_bin_slot();
    void cancel_slot();

public:
    DataExtract(QImage image, QWidget *parent = nullptr);
    ~DataExtract();
};

#endif // DATAEXTRACT_H
