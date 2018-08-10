#include "dataextract.h"

DataExtract::DataExtract(QImage image, QWidget *parent): QDialog(parent)
{
    this->image = image;
    this->init_interface();
    this->setWindowTitle("Data Extract");
    this->setWindowFlags(Qt::Window);
}


QByteArray DataExtract::process_channel(int value, QList<QCheckBox*> *list) {
    QByteArray data;
    bool lsb = this->bit_order->button(this->bit_order->checkedId())->text()[0] == 'L';
    int start = lsb ? 0 : 7;
    int finish = lsb ? 8 : -1;
    int delta = lsb ? 1 : -1;
    while (start != finish) {
        if (list->at(start)->isChecked()) {
            int tmp = (value >> start) & 1;
            if (tmp == 1) {
                data += '1';
            } else {
                data += '0';
            }
        }
        start += delta;
    }
    return data;
}

QByteArray DataExtract::process_pixel(QRgb pixel) {
    QByteArray data;
    QString bitord = this->bit_plane_order->button(this->bit_plane_order->checkedId())->text();
    data += this->process_channel(pixel >> 24 % 256, &this->alpha);
    for (int i = 0; i < bitord.length(); ++i) {
        if (bitord[i] == 'R') {
            data += this->process_channel(pixel >> 16 % 256, &this->red);
        } else if (bitord[i] == 'G') {
            data += this->process_channel(pixel >> 8 % 256, &this->green);
        } else if (bitord[i] == 'B') {
            data += this->process_channel(pixel % 256, &this->blue);
        }
    }
    return data;
}

QByteArray DataExtract::get_bytes_by_col() {
    QByteArray data;
    for (int a = 0; a < this->image.width(); ++a) {
        for (int b = 0; b < this->image.height(); ++b) {
            data += this->process_pixel(this->image.pixel(a, b));
        }
    }
    return data;
}

QByteArray DataExtract::get_bytes_by_row() {
    QByteArray data;
    for (int a = 0; a < this->image.height(); ++a) {
        for (int b = 0; b < this->image.width(); ++b) {
            data += this->process_pixel(this->image.pixel(b, a));
        }
    }
    return data;
}

QByteArray DataExtract::get_bytes() {
    int checked = this->extract_by->checkedId();
    QByteArray data;
    if (checked == -1) {
        data = QByteArray();
    } else if (this->extract_by->button(checked)->text() == "Row") {
        data = this->get_bytes_by_row();
    } else {
        data = this->get_bytes_by_col();
    }
    while (data.length() % 8) {
        data += '0';
    }
    QByteArray result;
    char value = 0;
    for (int i = 0; i < data.length(); ++i) {
        int tmp = (data[i] == '1') ? 1 : 0;
        value = (value << 1) + tmp;
        if (i > 0 && i % 8 == 7) {
            result.append(value);
            value = 0;
        }
    }
    return result;
}

QString DataExtract::get_text_from_bytes(QByteArray data) {
    QString result = "";
    for (int i = 0; i < data.length(); i += 16) {
        if (this->include_hexdump->isChecked()) {
            result += data.mid(i, 16).toHex();
            result += ' ';
        }
        QString letters = data.mid(i, 16);
        for (int i = 0; i < letters.length(); ++i) {
            if (not (letters[i] >= ' ' && letters[i] <= '~')) {
                letters[i] = '.';
            }
        }
        result += letters;
        if (this->include_hexdump->isChecked()) {
            result += '\n';
        }
    }
    return result;
}

void DataExtract::preview_slot() {
    QByteArray data = this->get_bytes();
    QString result = this->get_text_from_bytes(data);
    this->text->setText(result);
}

void DataExtract::save_bin_slot() {
    QByteArray data = this->get_bytes();
    QString filename = QFileDialog::getSaveFileName(this, "Save", "exracted.bin");
    if (filename.length() > 0) {
        QFile f(filename);
        f.open(QIODevice::WriteOnly);
        f.write(data);
        f.close();
    }
}

void DataExtract::save_text_slot() {
    QByteArray data = this->get_bytes();
    QString result = this->get_text_from_bytes(data);
    QString filename = QFileDialog::getSaveFileName(this, "Save", "exracted.txt");
    if (filename.length() > 0) {
        QFile f(filename);
        f.open(QIODevice::WriteOnly);
        f.write(result.toLocal8Bit());
        f.close();
    }
}

void DataExtract::cancel_slot() {
    this->close();
}

void DataExtract::init_interface() {
    text = new QTextEdit("");
    text->setReadOnly(true);
    text->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));

    QPushButton *preview = new QPushButton("Preview");
    this->connect(preview, SIGNAL(clicked(bool)), this, SLOT(preview_slot()));
    QPushButton *save_text = new QPushButton("Save text");
    this->connect(save_text, SIGNAL(clicked(bool)), this, SLOT(save_text_slot()));
    QPushButton *save_bin = new QPushButton("Save bin");
    this->connect(save_bin, SIGNAL(clicked(bool)), this, SLOT(save_bin_slot()));
    QPushButton *cancel = new QPushButton("Cancel");
    this->connect(cancel, SIGNAL(clicked(bool)), this, SLOT(cancel_slot()));

    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addStretch(1);
    buttons->addWidget(preview);
    buttons->addWidget(save_text);
    buttons->addWidget(save_bin);
    buttons->addWidget(cancel);
    buttons->addStretch(1);

    QHBoxLayout *title = new QHBoxLayout();
    title->addStretch(1);
    title->addWidget(new QLabel("Extract preview"));
    title->addStretch(1);

    QVBoxLayout *column = new QVBoxLayout();
    column->addWidget(this->get_bit_planes());
    column->addWidget(this->get_preview_settings());

    QHBoxLayout *settings = new QHBoxLayout();
    settings->addLayout(column);
    settings->addWidget(this->get_order_settings());

    QVBoxLayout *layer = new QVBoxLayout();
    layer->addLayout(title);
    layer->addWidget(text);
    layer->addLayout(settings);
    layer->addLayout(buttons);

    this->setLayout(layer);
}

QGroupBox* DataExtract::get_order_settings() {
    // extract by
    QRadioButton *row = new QRadioButton("Row");
    QRadioButton *column = new QRadioButton("Column");
    extract_by = new QButtonGroup();
    extract_by->addButton(row);
    extract_by->addButton(column);
    QHBoxLayout *first = new QHBoxLayout();
    row->setChecked(true);
    first->addWidget(row);
    first->addWidget(column);
    QGroupBox *a = new QGroupBox("Extract by");
    a->setLayout(first);

    // bit order
    QRadioButton *msb = new QRadioButton("MSB First");
    QRadioButton *lsb = new QRadioButton("LSB First");
    bit_order = new QButtonGroup();
    bit_order->addButton(msb);
    bit_order->addButton(lsb);
    msb->setChecked(true);
    QHBoxLayout *second = new QHBoxLayout();
    second->addWidget(msb);
    second->addWidget(lsb);
    QGroupBox *b = new QGroupBox("Bit Order");
    b->setLayout(second);

    // bit plane order
    QRadioButton *rgb = new QRadioButton("RGB");
    QRadioButton *rbg = new QRadioButton("RBG");
    QRadioButton *gbr = new QRadioButton("GBR");
    QRadioButton *grb = new QRadioButton("GRB");
    QRadioButton *brg = new QRadioButton("BRG");
    QRadioButton *bgr = new QRadioButton("BGR");
    bit_plane_order = new QButtonGroup();
    bit_plane_order->addButton(rgb);
    bit_plane_order->addButton(rbg);
    bit_plane_order->addButton(gbr);
    bit_plane_order->addButton(grb);
    bit_plane_order->addButton(brg);
    bit_plane_order->addButton(bgr);
    rgb->setChecked(true);
    QVBoxLayout *t1 = new QVBoxLayout();
    t1->addWidget(rgb);
    t1->addWidget(rbg);
    t1->addWidget(gbr);
    QVBoxLayout *t2 = new QVBoxLayout();
    t2->addWidget(grb);
    t2->addWidget(brg);
    t2->addWidget(bgr);
    QHBoxLayout *three = new QHBoxLayout();
    three->addLayout(t1);
    three->addLayout(t2);
    QGroupBox *c = new QGroupBox("Bit plane order");
    c->setLayout(three);

    QVBoxLayout *last =  new QVBoxLayout();
    last->addWidget(a);
    last->addWidget(b);
    last->addWidget(c);

    QGroupBox *result = new QGroupBox("Order settings");
    result->setLayout(last);
    return result;
}

QGroupBox* DataExtract::get_preview_settings() {
    QHBoxLayout *layer = new QHBoxLayout();
    include_hexdump = new QCheckBox("Include hexdump in preview");
    layer->addWidget(this->include_hexdump);

    QGroupBox *result = new QGroupBox("Preview settings");
    result->setLayout(layer);
    return result;
}

QGroupBox* DataExtract::get_bit_planes() {
    for (int i = 0; i < 8; ++i) {
        this->alpha.append(new QCheckBox(QString::number(i), this));
        this->red.append(new QCheckBox(QString::number(i), this));
        this->green.append(new QCheckBox(QString::number(i), this));
        this->blue.append(new QCheckBox(QString::number(i), this));
    }

    QHBoxLayout *alpha_layer = new QHBoxLayout;
    QHBoxLayout *red_layer = new QHBoxLayout;
    QHBoxLayout *green_layer = new QHBoxLayout;
    QHBoxLayout *blue_layer = new QHBoxLayout;

    alpha_layer->addWidget(new QLabel("Alpha"));
    red_layer->addWidget(new QLabel("Red"));
    green_layer->addWidget(new QLabel("Green"));
    blue_layer->addWidget(new QLabel("Blue"));

    for (int i = 7; i >= 0; --i) {
        alpha_layer->addWidget(this->alpha[i]);
        red_layer->addWidget(this->red[i]);
        green_layer->addWidget(this->green[i]);
        blue_layer->addWidget(this->blue[i]);
    }

    QVBoxLayout *layer = new QVBoxLayout();
    layer->addLayout(alpha_layer);
    layer->addLayout(red_layer);
    layer->addLayout(green_layer);
    layer->addLayout(blue_layer);

    QGroupBox *result = new QGroupBox("Bit planes");
    result->setLayout(layer);
    return result;
}

DataExtract::~DataExtract() {

}
