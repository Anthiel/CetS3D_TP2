#include "apropos.h"
#include "ui_apropos.h"

Apropos::Apropos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Apropos)
{
    this->setWindowTitle("A propos");
    ui->setupUi(this);
}

Apropos::~Apropos()
{
    delete ui;
}
