#include "courbeparametrique.h"
#include <math.h>
CourbeParametrique::CourbeParametrique(std::vector<Point> cPoint,int controlPoints_x,int controlPoints_y, float r, float g, float b)
{
    this->r=r;
    this->g=g;
    this->b=b;

    this->controlPoints = std::vector<Point>(cPoint);
    this->controlPoints_x=controlPoints_x;
    this->controlPoints_y=controlPoints_y;

    setControlPointColor();

    makeControlSegment();

}

std::vector<float> CourbeParametrique::SoustractionVec(std::vector<float> p1, std::vector<float> p2){
    std::vector<float> res;
    res.push_back(p1.at(0) - p2.at(0));
    res.push_back(p1.at(1) - p2.at(1));
    res.push_back(p1.at(2) - p2.at(2));

    return res;
}

std::vector<float> CourbeParametrique::ProduitVec(std::vector<float> p1, std::vector<float> p2){
    std::vector<float> res;
    res.push_back(p1.at(1) * p2.at(2) - p1.at(2) * p2.at(1));
    res.push_back(p1.at(2) * p2.at(0) - p1.at(0) * p2.at(2));
    res.push_back(p1.at(0) * p2.at(1) - p1.at(1) * p2.at(0));
    return res;
}

float CourbeParametrique::ProduitScalaire(std::vector<float> p1, std::vector<float> p2){
  return p1.at(0)*p2.at(0) + p1.at(1)*p2.at(1) + p1.at(2)*p2.at(2);
}

float CourbeParametrique::GetAngle(float i){
    std::vector<float> point1 = bezier(i);
    std::vector<float> point2 = bezier(i+1/precision);
    std::vector<float> tauxAccroi = tauxAccroiss(i);
    std::vector<float> pointT = SoustractionVec(point2, point1);

//    qDebug() << "\t i : " << i;
//    qDebug() << "\t point 1 : " << point1 << "\t point 2 : " << point2;
//    qDebug() << "\t point T : " << pointT;
//    qDebug() << "\t Taux Accroi : " << tauxAccroi;
//    qDebug() << "\t ProduitScalaire("<<tauxAccroi<<","<<pointT<<") : " << ProduitScalaire(tauxAccroi, pointT);

    return acos(fabs(ProduitScalaire(tauxAccroi, pointT)));
}

std::vector<float> CourbeParametrique::tauxAccroiss(float i){
    double h = 1/1000000.0;
    std::vector<float> pointDeriv;
    std::vector<float> point1;
    std::vector<float> point2;
    point1 = bezier(i+h);
    point2 = bezier(i);

    for(int j = 0; j<3;j++){
        //qDebug() << "\t point1 = " << point1.at(j);
        //qDebug() << "\t point2 = " << point2.at(j);
        //qDebug() << "\t h = " << h;

        pointDeriv.push_back((point1.at(j)-point2.at(j))/h);
    }
    //qDebug() << "Taux Accroissement du point" << i << " : " << pointDeriv;
    return pointDeriv;
}

std::vector<float> CourbeParametrique::bezier(float i){
    std::vector<float> point;
    float t = i/precision;
    point.push_back(controlPoints[0].getX()*pow(1-t, 3)+3 * controlPoints[1].getX()*t*pow(1-t,2)+ 3*controlPoints[2].getX()*pow(t,2)*(1-t)+controlPoints[3].getX()*pow(t,3));
    point.push_back(controlPoints[0].getY()*pow(1-t, 3)+3 * controlPoints[1].getY()*t*pow(1-t,2)+ 3*controlPoints[2].getY()*pow(t,2)*(1-t)+controlPoints[3].getY()*pow(t,3));
    point.push_back(controlPoints[0].getZ()*pow(1-t, 3)+3 * controlPoints[1].getZ()*t*pow(1-t,2)+ 3*controlPoints[2].getZ()*pow(t,2)*(1-t)+controlPoints[3].getZ()*pow(t,3));
    return point;
}




int CourbeParametrique::factoriel(int n)
{
  return (n == 1 || n == 0) ? 1 : factoriel(n - 1) * n;
}

float CourbeParametrique::Bernstein(float u, int i, int n)
// u : paramètre entre [0,1], i et n les polynomes demandés
{
    float firstPart = factoriel(n)/(factoriel(i) * factoriel(n-i));
    float secondPart = pow(u,i) *pow(1-u,n-i);
    return firstPart*secondPart;
}

Point* CourbeParametrique::SurfaceBezier(float u, float v, int n, int m){

    Point *p= new Point(0,0,0,r,g,b);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            *p += (Bernstein(u, i, n-1) * Bernstein(v, j, m-1)) * controlPoints[n*j+i];
        }
    }
    return p;
}

void CourbeParametrique::createListPoint(){
    listPoint.clear();
    for(int i= 0; i <= precision; i++){
        for(int j = 0; j <= precision; j++){
            //qDebug() << "début des surfaces i : " << i << " j : " << j;
            Point *tmp = SurfaceBezier(i/precision, j/precision, controlPoints_x, controlPoints_y);
            listPoint.push_back(*tmp);
        }
    }
}

void CourbeParametrique::setStart(int start){
    this->start = start;
}
int CourbeParametrique::getStart(){
    return start;
}

void CourbeParametrique::setPrecision(int pas){
    precision=pas;
    update();
}

int CourbeParametrique::getSize(){
    return (nbsegment+controlSegment.size())*2;
}

int CourbeParametrique::getSizeCourbeParam(){
    return controlSegment.size()*2;
}

Point CourbeParametrique::getPoint(int numPoint){
    return controlPoints[numPoint];
}
void CourbeParametrique::setPoint(int numPoint,Point p){
    controlPoints[numPoint]=p;
    update();
}

void CourbeParametrique::setControlPointColor(){

    for (unsigned i=0;i<controlPoints.size();++i) {
        controlPoints[i].setColor(1.0, 0.0, 0.0);
    }
}

void CourbeParametrique::swapGridSurface(bool showGrid){
    this->showGrid=showGrid;
    update();
}

void CourbeParametrique::makeControlSegment(){
    controlSegment.clear();
    for (int j=0;j<controlPoints_y;++j) {
        for(int i=0;i<controlPoints_x-1;++i){
            controlSegment.push_back(*new Segment(controlPoints[controlPoints_x*j+i],controlPoints[controlPoints_x*j+i+1]));
        }
    }
    for (int j=0;j<controlPoints_x;++j) {
        for(int i=0;i<controlPoints_y-1;++i){
            controlSegment.push_back(*new Segment(controlPoints[i*controlPoints_x+j],controlPoints[(i+1)*controlPoints_x+j]));
        }
    }
}

void CourbeParametrique::update(){
    setControlPointColor();
    makeControlSegment();
    needCalcul=true;
}



void CourbeParametrique::makeObject(QVector<GLfloat> *vertData){
    for(unsigned i = 0; i < controlSegment.size(); i++){
        controlSegment[i].makeObject(vertData);
    }
    if(needCalcul){
        needCalcul=false;
        createListPoint();

        if(showGrid){
            listSegment.clear();
            for(int i= 0; i <= precision; i++){
                for(int j = 0; j < precision; j++){
                    Segment *tmp = new Segment(listPoint[i*(precision+1)+j], listPoint[i*(precision+1)+j+1]);
                    listSegment.push_back(*tmp);
                }
            }
            for(int i= 0; i <= precision; i++){
                for(int j = 0; j < precision; j++){
                    Segment *tmp = new Segment(listPoint[i+j*(precision+1)], listPoint[i+(j+1)*(precision+1)]);
                    listSegment.push_back(*tmp);
                }
            }
            nbsegment = 2*precision*(precision+1);
        }
    }
    if(showGrid){
        for(int i = 0; i < nbsegment; i++){
            listSegment[i].makeObject(vertData);
        }
    }
    else{
        for(int i= 0; i < precision; i++){
            for(int j = 0; j < precision; j++){
                int A=(i+0)*(precision+1)+(j+0);
                int B=(i+0)*(precision+1)+(j+1);
                int C=(i+1)*(precision+1)+(j+0);
                int D=(i+1)*(precision+1)+(j+1);

                QVector3D vAB(listPoint[B].getX()-listPoint[A].getX(),listPoint[B].getY()-listPoint[A].getY(),listPoint[B].getZ()-listPoint[A].getZ());
                QVector3D vAC(listPoint[C].getX()-listPoint[A].getX(),listPoint[C].getY()-listPoint[A].getY(),listPoint[C].getZ()-listPoint[A].getZ());
                QVector3D vDB(listPoint[B].getX()-listPoint[D].getX(),listPoint[B].getY()-listPoint[D].getY(),listPoint[B].getZ()-listPoint[D].getZ());
                QVector3D vDC(listPoint[C].getX()-listPoint[D].getX(),listPoint[C].getY()-listPoint[D].getY(),listPoint[C].getZ()-listPoint[D].getZ());

                QVector3D nABC = -QVector3D::normal(vAC, vAB);
                QVector3D nBDC = -QVector3D::normal(vDB, vDC);
                QVector3D nBC = (nABC+nBDC)/2;

                listPoint[A].makeObject(vertData);
                vertData->append(nABC.x());vertData->append(nABC.y());vertData->append(nABC.z());
                listPoint[B].makeObject(vertData);
                vertData->append(nBC.x());vertData->append(nBC.y());vertData->append(nBC.z());
                listPoint[C].makeObject(vertData);
                vertData->append(nBC.x());vertData->append(nBC.y());vertData->append(nBC.z());

                listPoint[B].makeObject(vertData);
                vertData->append(nBC.x());vertData->append(nBC.y());vertData->append(nBC.z());
                listPoint[C].makeObject(vertData);
                vertData->append(nBC.x());vertData->append(nBC.y());vertData->append(nBC.z());
                listPoint[D].makeObject(vertData);
                vertData->append(nBDC.x());vertData->append(nBDC.y());vertData->append(nBDC.z());
            }
        }
        nbsegment=3*precision*precision;
    }
}
