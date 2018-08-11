#include "helpwidget.h"

HelpWidget::HelpWidget(QWidget *parent): QDialog(parent)
{
    QTextEdit *text = new QTextEdit();
    text->setReadOnly(true);
    text->setHtml("<h1>Stegsolve v2.0 by sil3ntz</h1>"
                  "<p>Stegsolve is a stegano solver for challenges. It provides these main functions:</p>"
                  "<ul>"
                  "<li>A quick view of different bit planes and some simple transformations.</li>"
                  "<li>Data extraction from planes. This can be row order or column order, with bits treated as a bitstream and converted into bytes.</li>"
                  "<li>Stereogram solver - simply change the offset until the image becomes visible.</li>"
                  "<li>Frame browser for animated images. This should also work for viewing layers in multi-layered PNG files.</li>"
                  "<li>Image combiner to combine two images in a variety of ways and browse through the different combinations.</li>"
                  "</ul>"
                  "<p>Copy/Cut and paste is available from most text using CTRL-C to copy, CTRL-V to paste and CTRL-X for cut.</p>"
                  "<p>If an image fails to load, for example because it is corrupt, then file analysis will still open the file that"
                  "you just tried to view. It may, however, crash out before reporting the information that you want to know."
                  "This will work though on images where the PNG has corrupted CRC values for example."
                  "</p>");

    QPushButton *ok = new QPushButton("OK");
    this->connect(ok, SIGNAL(clicked(bool)), this, SLOT(close()));

    QHBoxLayout *button = new QHBoxLayout;
    button->addStretch(1);
    button->addWidget(ok);
    button->addStretch(1);

    QVBoxLayout *layer = new QVBoxLayout();
    layer->addWidget(text);
    layer->addLayout(button);

    this->setLayout(layer);
    this->setWindowTitle("Help");
    this->setWindowFlags(Qt::Window);
    this->setGeometry(this->x(), this->y(), 500, 300);
}
