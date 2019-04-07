#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QRegularExpression>
#include <QStringList>

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

    int i = 0;
    for (MyMesh::VertexIter curVert = mesh.vertices_begin(); curVert != mesh.vertices_end(); curVert++)
    {
        VertexHandle current = *curVert;
        Point p = ui->openGLWidget->getControlPoints()[i];
        MyMesh::Point newPoint = { p.getX(), p.getY(), p.getZ() };
        qDebug() << newPoint.data();
        mesh.set_point ( current , newPoint );
        ++i;
    }

    OpenMesh::IO::write_mesh(mesh, fileName.toUtf8().constData());
    QFile file(fileName);
    if (file.open(QIODevice::Append)) {
        QTextStream stream(&file);
        stream << "\n# x, y\n"
               << "x " << ui->openGLWidget->getControlPointsX() << "\n"
               << "y " << ui->openGLWidget->getControlPointsY();
    }
}

void MainWindow::importAction(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Mesh"), "", tr("Mesh Files (*.obj)"));
    OpenMesh::IO::read_mesh(mesh, fileName.toUtf8().constData());
    QFile file(fileName);
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            while(!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0) {
                    if(lineParts.at(0).compare("x", Qt::CaseInsensitive) == 0) {
                       ui->openGLWidget->setControlPointsX(lineParts.at(1).toInt());
                    } else if(lineParts.at(0).compare("y", Qt::CaseInsensitive) == 0) {
                       ui->openGLWidget->setControlPointsY(lineParts.at(1).toInt());
                    }
                }
            }
        }
    }
    ui->openGLWidget->setIsImport(true);
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

    ui->openGLWidget->clearControlPoints();
    ui->openGLWidget->setIsImport(true);

    for (MyMesh::VertexIter curVert = _mesh->vertices_begin(); curVert != _mesh->vertices_end(); curVert++)
    {
        OpenMesh::Vec3f pt = _mesh->point(*curVert);
        ui->openGLWidget->addControlPoint(*new Point(pt[0], pt[1], pt[2]));
    }
    ui->openGLWidget->makeGLObjects();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionCommandes_triggered()
{
    commandes commande;
    if(commande.exec()){

    }
}

void MainWindow::on_action_propos_triggered()
{
    Apropos aprop;
    if(aprop.exec()){

    }
}
