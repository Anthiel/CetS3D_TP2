/* R. Raffin
 * M1 Informatique, Aix-Marseille Université
 * Fenêtre principale
 * Au cas où, l'UI contient une barre de menu, une barre de status, une barre d'outils (cf QMainWindow).
 * Une zone est laissée libre à droite du Widget OpenGL pour mettre de futurs contrôles ou informations.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    connect(ui->settingsAction, &QAction::triggered, this, &MainWindow::settingsAction);
    connect(ui->importAction, &QAction::triggered, this, &MainWindow::importAction);
    connect(ui->exportAction, &QAction::triggered, this, &MainWindow::exportAction);
}

void  MainWindow::settingsAction(){
    if(settings == nullptr){
        settings = new Settings(this, ui->openGLWidget);
        settings->show();
    }
    if(!settings->isVisible()) settings->show();
}

void MainWindow::exportAction(){
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter", "",tr("Mesh Files (*.obj)"));
    if(fileName.isEmpty()) return;
    fileName += ".obj";
//    QFile file(fileName);
//    if (file.open(QIODevice::ReadWrite)) {
//        QTextStream stream(&file);

//        std::vector<Point> controlPoints = ui->openGLWidget->getControlPoints();
//        int controlPoints_x = ui->openGLWidget->getControlPointsX();
//        int controlPoints_y = ui->openGLWidget->getControlPointsY();

//        for(int i = 0; i < controlPoints.size(); i++){
//            stream << "v "
//                   << controlPoints[i].getX() << " "
//                   << controlPoints[i].getY() << " "
//                   << controlPoints[i].getZ() << "\n";
//        }

//        for (int j = 0; j < controlPoints_y - 1; ++j) {
//            for(int i = 1; i <= controlPoints_x - 1; ++i){
//                stream << "f "
//                       << j * controlPoints_x + i << " "
//                       << j * controlPoints_x + i + 1 << " "
//                       << (j + 1) * controlPoints_x + i + 1 << " "
//                       << (j + 1) * controlPoints_x + i << "\n";
//            }
//        }
//    }
    OpenMesh::IO::write_mesh(mesh, fileName.toUtf8().constData());
}

void MainWindow::importAction(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Mesh"), "", tr("Mesh Files (*.obj)"));
    OpenMesh::IO::read_mesh(mesh, fileName.toUtf8().constData());
    // Afficher le nouveau mesh
}

MainWindow::~MainWindow()
{
	delete ui;
}
