/* R. Raffin
 * M1 Informatique, Aix-Marseille Université
 * Fenêtre principale
 * Au cas où, l'UI contient une barre de menu, une barre de status, une barre d'outils (cf QMainWindow).
 * Une zone est laissée libre à droite du Widget OpenGL pour mettre de futurs contrôles ou informations.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    connect(ui->settingsAction, &QAction::triggered, this, &MainWindow::settingsAction);
}

void  MainWindow::settingsAction(){
    if(settings == nullptr){
        settings = new Settings(this, ui->openGLWidget);
        settings->show();
    }
    if(!settings->isVisible()) settings->show();
}

MainWindow::~MainWindow()
{
	delete ui;
}
