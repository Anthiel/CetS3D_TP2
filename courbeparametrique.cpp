#include "courbeparametrique.h"
#include <math.h>
CourbeParametrique::CourbeParametrique(Point pA, Point pB, Point pC, Point pD, float r, float g, float b)
{

    this->A = pA;
    this->B = pB;
    this->C = pC;
    this->D = pD;

    this->r=r;
    this->g=g;
    this->b=b;

    A.setColor(r*0.8, g*0.8, b*0.8);
    B.setColor(r*0.8, g*0.8, b*0.8);
    C.setColor(r*0.8, g*0.8, b*0.8);
    D.setColor(r*0.8, g*0.8, b*0.8);

    S1 = new Segment(A, B);
    S2 = new Segment(B, C);
    S3 = new Segment(C, D);
    nbsegment += 3;

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
    point.push_back(A.getX()*pow(1-t, 3)+3 * B.getX()*t*pow(1-t,2)+ 3*C.getX()*pow(t,2)*(1-t)+D.getX()*pow(t,3));
    point.push_back(A.getY()*pow(1-t, 3)+3 * B.getY()*t*pow(1-t,2)+ 3*C.getY()*pow(t,2)*(1-t)+D.getY()*pow(t,3));
    point.push_back(A.getZ()*pow(1-t, 3)+3 * B.getZ()*t*pow(1-t,2)+ 3*C.getZ()*pow(t,2)*(1-t)+D.getZ()*pow(t,3));
    return point;
}

void CourbeParametrique::makeObject(QVector<GLfloat> *vertData){
    S1->makeObject(vertData);
    S2->makeObject(vertData);
    S3->makeObject(vertData);
    createListPoint();
    for(int i = 0; i < precision; i++){
        listSegment[i].makeObject(vertData);
    }
}

void CourbeParametrique::createListPoint(){
    for(int i= 0; i <= precision; i++){
        pointTmp = bezier(i);
        qDebug() << "Angle en " << i << " : " << GetAngle(i);
        Point *tmp = new Point(pointTmp[0],pointTmp[1],pointTmp[2], r, g, b);
        listPoint.push_back(*tmp);
    }
    for(int i = 0; i < precision; i++){
        Segment *tmp = new Segment(listPoint[i], listPoint[i+1]);
        listSegment.push_back(*tmp);
    }
    nbsegment += precision;
}

void CourbeParametrique::setStart(int start){
    this->start = start;
}

int CourbeParametrique::getSize(){
    return size;
}

int CourbeParametrique::getSizeCourbeParam(){
    return sizeCourbeParam;
}

int CourbeParametrique::getStart(){
    return start;
}

