#ifndef APROPOS_H
#define APROPOS_H

#include <QDialog>
#include "ui_apropos.h"

namespace Ui {
class Apropos;
}

class Apropos : public QDialog
{
    Q_OBJECT

public:
    explicit Apropos(QWidget *parent = 0);
    ~Apropos();

private:
    Ui::Apropos *ui;
};

#endif // APROPOS_H
