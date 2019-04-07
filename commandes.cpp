#include "commandes.h"
#include "ui_commandes.h"


commandes::commandes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::commandes)
{
    ui->setupUi(this);
    this->setWindowTitle("Liste des commandes");
}

commandes::~commandes()
{
    delete ui;
}
