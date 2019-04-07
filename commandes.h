#ifndef COMMANDES_H
#define COMMANDES_H

#include <QDialog>
#include "ui_commandes.h"


namespace Ui {
    class commandes;
}

class commandes : public QDialog
{
        Q_OBJECT

public:
    explicit commandes(QWidget *parent = nullptr);
    ~commandes();


private:
    Ui::commandes *ui;
};

#endif // COMMANDES_H
