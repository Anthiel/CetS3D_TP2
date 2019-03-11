#ifndef COURBEPARAMETRIQUE_H
#define COURBEPARAMETRIQUE_H

#include "segment.h"

class CourbeParametrique
{
public:
    CourbeParametrique(Point pA, Point pB, Point pC, Point pD, float r, float g, float b);
    void makeObject(QVector<GLfloat> *vertData);
    void setStart(int start);
    int getSize();
private:

    int variableSize = 0;
    int size = 6+variableSize;
    int start;

    Segment *S1;
    Segment *S2;
    Segment *S3;
};

#endif // COURBEPARAMETRIQUE_H
