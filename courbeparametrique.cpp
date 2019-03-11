#include "courbeparametrique.h"

CourbeParametrique::CourbeParametrique(Point pA, Point pB, Point pC, Point pD, float r, float g, float b)
{

    this->A = pA;
    this->B = pB;
    this->C = pC;
    this->D = pD;

    A.setColor(r, g, b);
    B.setColor(r, g, b);
    C.setColor(r, g, b);
    D.setColor(r, g, b);

    S1 = new Segment(A, B);
    S2 = new Segment(B, C);
    S3 = new Segment(C, D);
    nbsegment += 3;

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
        Point *tmp = new Point(pointTmp[0],pointTmp[1],pointTmp[2], 0.0, 0.0, 1.0);
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

int CourbeParametrique::getStart(){
    return start;
}

