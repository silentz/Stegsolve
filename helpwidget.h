#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class HelpWidget : public QDialog
{
    Q_OBJECT
public:
    HelpWidget(QWidget *parent = nullptr);
};

#endif // HELPWIDGET_H
