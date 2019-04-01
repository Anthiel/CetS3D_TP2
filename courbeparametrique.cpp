#include "courbeparametrique.h"
#include <math.h>

CourbeParametrique::CourbeParametrique(Point *cPoint, float r, float g, float b)
{

    this->r=r;
    this->g=g;
    this->b=b;

    this->controlPoint=cPoint;
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

    qDebug() << "\t i : " << i;
    qDebug() << "\t point 1 : " << point1 << "\t point 2 : " << point2;
    qDebug() << "\t point T : " << pointT;
    qDebug() << "\t Taux Accroi : " << tauxAccroi;
    qDebug() << "\t ProduitScalaire("<<tauxAccroi<<","<<pointT<<") : " << ProduitScalaire(tauxAccroi, pointT);

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
    point.push_back(controlPoint[0].getX()*pow(1-t, 3)+3 * controlPoint[1].getX()*t*pow(1-t,2)+ 3*controlPoint[2].getX()*pow(t,2)*(1-t)+controlPoint[3].getX()*pow(t,3));
    point.push_back(controlPoint[0].getY()*pow(1-t, 3)+3 * controlPoint[1].getY()*t*pow(1-t,2)+ 3*controlPoint[2].getY()*pow(t,2)*(1-t)+controlPoint[3].getY()*pow(t,3));
    point.push_back(controlPoint[0].getZ()*pow(1-t, 3)+3 * controlPoint[1].getZ()*t*pow(1-t,2)+ 3*controlPoint[2].getZ()*pow(t,2)*(1-t)+controlPoint[3].getZ()*pow(t,3));
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
            *p += (Bernstein(u, i, n-1) * Bernstein(v, j, m-1)) * controlPoint[n*i+j];
        }
    }
    return p;
}


void CourbeParametrique::createListPoint(){
    for(int i= 0; i <= precision; i++){
        for(int j = 0; j <= precision; j++){
            qDebug() << "début des surfaces i : " << i << " j : " << j;
            Point *tmp = SurfaceBezier(i/precision, j/precision, 4, 4);
            listPoint.push_back(*tmp);
        }
    }
    for(int i= 0; i <= precision; i++){
        for(int j = 0; j < precision; j++){
            Segment *tmp = new Segment(listPoint[i*(precision+1)+j], listPoint[i*(precision+1)+j+1]);
            listSegment.push_back(*tmp);
        }
    }
    for(int i= 0; i <= precision; i++){
        for(int j = 0; j < precision; j++){
            Segment *tmp = new Segment(listPoint[i+j*(precision+1)], listPoint[i+(j+1)*(precision+1)]);
            qDebug() <<"b" << i+j*(precision+1) << i+(j+1)*(precision+1) ;
            listSegment.push_back(*tmp);
        }
    }
    nbsegment = 2*precision*(precision+1);
}

void CourbeParametrique::resetListPoint(){
    listSegment.clear();
    listPoint.clear();
}

void CourbeParametrique::setStart(int start){
    this->start = start;
}
int CourbeParametrique::getStart(){
    return start;
}

int CourbeParametrique::getSize(){
    return (nbsegment+sizeCourbeParam)*2;
}

int CourbeParametrique::getSizeCourbeParam(){
    return sizeCourbeParam*2;
}

Point CourbeParametrique::getPoint(int numPoint){
    return controlPoint[numPoint];
}


void CourbeParametrique::setControlPointColor(){

    for (int i=0;i<16;++i) {
        controlPoint[i].setColor(1.0, 0.0, 0.0);
    }
}

void CourbeParametrique::makeControlSegment(){
    sizeCourbeParam=24;
    for (int j=0;j<4;++j) {
        for(int i=0;i<3;++i){
            controlSegment[3*j+i] = *new Segment(controlPoint[4*j+i],controlPoint[4*j+i+1]);
        }
    }

    for (int j=0;j<4;++j) {
        for(int i=0;i<3;++i){
            controlSegment[12+3*j+i] = *new Segment(controlPoint[i*4+j],controlPoint[(i+1)*4+j]);
        }
    }
}

void CourbeParametrique::update(){
    setControlPointColor();
    makeControlSegment();
    needCalcul=true;
}

void CourbeParametrique::makeObject(QVector<GLfloat> *vertData){
    for(int i = 0; i < sizeCourbeParam; i++){
        controlSegment[i].makeObject(vertData);
    }
    if(needCalcul){
        resetListPoint();
        createListPoint();
        needCalcul=false;
    }
    for(int i = 0; i < nbsegment; i++){
        listSegment[i].makeObject(vertData);
        qDebug() << i;
    }
}