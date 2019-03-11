#include "courbeparametrique.h"

CourbeParametrique::CourbeParametrique(Point pA, Point pB, Point pC, Point pD, float r, float g, float b)
{

    pA.setColor(r, g, b);
    pB.setColor(r, g, b);
    pC.setColor(r, g, b);
    pD.setColor(r, g, b);

    S1 = new Segment(pA, pB);
    S2 = new Segment(pB, pC);
    S3 = new Segment(pC, pD);
}

void CourbeParametrique::makeObjects(QVector<GLfloat> *vertData){
    S1->makeObject(vertData);
    S2->makeObject(vertData);
    S3->makeObject(vertData);
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

