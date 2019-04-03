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
/*
void MainWindow::exportAction(){
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter", "",tr("Mesh Files (*.obj)"));
    if(fileName.isEmpty()) return;
    fileName += ".obj";
    OpenMesh::IO::write_mesh(mesh, fileName.toUtf8().constData());
}

void MainWindow::importAction(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Mesh"), "", tr("Mesh Files (*.obj)"));
    OpenMesh::IO::read_mesh(mesh, fileName.toUtf8().constData());
    resetAllColorsAndThickness(&mesh);
    displayMesh(&mesh);
}

void MainWindow::resetAllColorsAndThickness(MyMesh* _mesh)
{
    for (MyMesh::VertexIter curVert = _mesh->vertices_begin(); curVert != _mesh->vertices_end(); curVert++)
    {
        _mesh->data(*curVert).thickness = 1;
        _mesh->set_color(*curVert, MyMesh::Color(0, 0, 0));
    }

    for (MyMesh::FaceIter curFace = _mesh->faces_begin(); curFace != _mesh->faces_end(); curFace++)
    {
        _mesh->set_color(*curFace, MyMesh::Color(150, 150, 150));
    }

    for (MyMesh::EdgeIter curEdge = _mesh->edges_begin(); curEdge != _mesh->edges_end(); curEdge++)
    {
        _mesh->data(*curEdge).thickness = 1;
        _mesh->set_color(*curEdge, MyMesh::Color(0, 0, 0));
    }
}

void MainWindow::displayMesh(MyMesh* _mesh){
    for (MyMesh::VertexIter curVert = _mesh->vertices_begin(); curVert != _mesh->vertices_end(); curVert++)
    {
        OpenMesh::Vec3f pt = _mesh->point(*curVert);
        pointsControl.push_back(new Point(pt[0], pt[1], pt[2]));
    }
}
*/
MainWindow::~MainWindow()
{
	delete ui;
}
