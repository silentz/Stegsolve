#include "stegsolve.h"

Stegsolve::Stegsolve(QImage *image, QWidget *parent)
    : QMainWindow(parent)
{
    this->scale = 100;
    this->mode = 0;
    this->filters = QList<ImageFilter*>();
    this->image = image;
    this->image_widget = new ImageWidget(this);

    this->init_menubar();
    this->init_statusbar();
    this->init_filters();

    QScrollArea *scrollarea = new QScrollArea();
    scrollarea->setWidget(image_widget);
    this->setCentralWidget(scrollarea);

    this->setWindowTitle("Stegsolve v2.0");
    this->setGeometry(100, 100, 500, 400);
}


void Stegsolve::paint_image() {
    ImageFilter *img_filter = this->filters[this->mode];
    QImage result = img_filter->filter(this->image);
    double image_scale = static_cast<double>(this->scale) / 100.0;
    this->image_widget->paint("kek", result, image_scale);
}


void Stegsolve::right_arrow_clicked() {
    this->mode = (this->mode + 1) % this->filters.length();
    this->paint_image();
}


void Stegsolve::left_arrow_clicked() {
    this->mode = this->mode - 1;
    if (this->mode < 0) {
        this->mode = this->filters.length() - 1;
    }
    this->paint_image();
}


void Stegsolve::open_slot() {
    QString filename = QFileDialog::getOpenFileName(this, "Open", ".",
                           "Images (*.png *.xpm *.jpg *.bmp *.gif *.jpeg *.pbm *.pgm *.ppm *.xbm)");
    if (filename.length() > 0) {
        if (this->image != nullptr) {
            delete this->image;
            this->image = nullptr;
        }
        this->image = new QImage(filename);
        this->paint_image();
    }
}


void Stegsolve::save_as_slot() {
    qDebug() << "save_as_slot";
}


void Stegsolve::exit_slot() {
    qDebug() << "exit_slot";
}


void Stegsolve::file_format_slot() {
    qDebug() << "file_format_slot";
}


void Stegsolve::data_extract_slot() {
    qDebug() << "data_extract_slot";
}


void Stegsolve::stereogram_solver_slot() {
    qDebug() << "stereogram_solver_slot";
}


void Stegsolve::frame_browser_slot() {
    qDebug() << "frame_browser_slot";
}


void Stegsolve::image_combiner_slot() {
    qDebug() << "image_combiner_slot";
}


void Stegsolve::about_slot() {
    qDebug() << "about_slot";
}


void Stegsolve::init_menubar() {
    QMenuBar *menubar = new QMenuBar();
    QMenu *file = menubar->addMenu("File");
    QMenu *analyse = menubar->addMenu("Analyse");
    QMenu *help = menubar->addMenu("Help");

    QAction *open = new QAction("Open", this);
    open->setShortcut(QKeySequence::Open);          // Ctrl+O
    this->connect(open, SIGNAL(triggered(bool)), this, SLOT(open_slot()));

    QAction *save_as = new QAction("Save As", this);
    save_as->setShortcut(QKeySequence::SaveAs);     // Ctrl+Shift+S
    this->connect(save_as, SIGNAL(triggered(bool)), this, SLOT(save_as_slot()));

    QAction *exit = new QAction("Exit", this);
    exit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));          // Ctrl+E
    this->connect(exit, SIGNAL(triggered(bool)), this, SLOT(exit_slot()));

    QAction *file_format = new QAction("File Format", this);
    file_format->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));   // Ctrl+F
    this->connect(file_format, SIGNAL(triggered(bool)), this, SLOT(file_format_slot()));

    QAction *data_extract = new QAction("Data Extract", this);
    data_extract->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));  // Ctrl+D
    this->connect(data_extract, SIGNAL(triggered(bool)), this, SLOT(data_extract_slot()));

    QAction *stereogram_solver = new QAction("Stereogram Solver", this);
    stereogram_solver->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));     // Ctrl+S
    this->connect(stereogram_solver, SIGNAL(triggered(bool)), this, SLOT(stereogram_solver_slot()));

    QAction *frame_browser = new QAction("Frame Browser", this);
    frame_browser->setShortcut(QKeySequence(Qt::CTRL +Qt::Key_B));          // Ctrl+B
    this->connect(frame_browser, SIGNAL(triggered(bool)), this, SLOT(frame_browser_slot()));

    QAction *image_combiner = new QAction("Image Combiner", this);
    image_combiner->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));        // Ctrl+I
    this->connect(image_combiner, SIGNAL(triggered(bool)), this, SLOT(image_combiner_slot()));

    QAction *about = new QAction("About", this);
    about->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));                 // Ctrl+A
    this->connect(about, SIGNAL(triggered(bool)), this, SLOT(about_slot()));

    file->addAction(open);
    file->addAction(save_as);
    file->addAction(exit);

    analyse->addAction(file_format);
    analyse->addAction(data_extract);
    analyse->addAction(stereogram_solver);
    analyse->addAction(frame_browser);
    analyse->addAction(image_combiner);

    help->addAction(about);

    this->setMenuBar(menubar);
}


void Stegsolve::init_statusbar() {
    QPushButton *left = new QPushButton("<");
    QPushButton *right = new QPushButton(">");
    left->setMaximumWidth(30);
    right->setMaximumWidth(30);
    this->connect(left, SIGNAL(clicked(bool)), this, SLOT(left_arrow_clicked()));
    this->connect(right, SIGNAL(clicked(bool)), this, SLOT(right_arrow_clicked()));

    QStatusBar *statusbar = new QStatusBar();
    QLayout *hb = statusbar->layout();
    for (int i = 0; i < hb->count(); ++i) {
        hb->removeItem(hb->takeAt(i));
    }
    hb->setAlignment(Qt::AlignCenter);
    hb->addWidget(left);
    hb->addWidget(right);

    statusbar->setContentsMargins(0, 4, 0, 4);
    this->setStatusBar(statusbar);
}


void Stegsolve::init_filters() {
    // normal image
    this->filters.push_back(new MaskImageFilter(Mask(0xffffffff, 0x00000000)));
    // xor image filter
    this->filters.push_back(new XorImageFilter());
    // alpha channel filters
    this->filters.push_back(new ChannelImageFilter(Mask(0x80000000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x40000000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x20000000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x10000000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x08000000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x04000000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x02000000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x01000000, 0x00000000)));
    // red channel filters
    this->filters.push_back(new ChannelImageFilter(Mask(0x00800000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00400000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00200000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00100000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00080000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00040000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00020000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00010000, 0x00000000)));
    // green channel filters
    this->filters.push_back(new ChannelImageFilter(Mask(0x00008000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00004000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00002000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00001000, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00000800, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00000400, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00000200, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00000100, 0x00000000)));
    // blue channel filters
    this->filters.push_back(new ChannelImageFilter(Mask(0x00000080, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00000040, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00000020, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00000010, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00000008, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00000004, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00000002, 0x00000000)));
    this->filters.push_back(new ChannelImageFilter(Mask(0x00000001, 0x00000000)));
    // full alpha
    this->filters.push_back(new ChannelImageFilter(Mask(0xff000000, 0x00000000)));
    // full red
    this->filters.push_back(new MaskImageFilter(Mask(0x00ff0000, 0xff000000)));
    // full green
    this->filters.push_back(new MaskImageFilter(Mask(0x0000ff00, 0xff000000)));
    // full blue
    this->filters.push_back(new MaskImageFilter(Mask(0x000000ff, 0xff000000)));
    // random color maps
    this->filters.push_back(new RandomColorMapImageFilter());
    this->filters.push_back(new RandomColorMapImageFilter());
    this->filters.push_back(new RandomColorMapImageFilter());
    // gray bits
    this->filters.push_back(new GrayBitsImageFilter());
}


Stegsolve::~Stegsolve()
{
    if (this->image != nullptr) {
        delete this->image;
    }
}
