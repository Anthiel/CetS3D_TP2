#ifndef COURBEPARAMETRIQUE_H
#define COURBEPARAMETRIQUE_H

#include "segment.h"
#include <math.h>

class CourbeParametrique
{
public:
    CourbeParametrique(Point pA, Point pB, Point pC, Point pD, float r, float g, float b);
    void makeObject(QVector<GLfloat> *vertData);
    void setStart(int start);
    int getStart();
    int getSize();
    int getSizeCourbeParam();

    std::vector<float> bezier(float i);
    void createListPoint();

private:
    Point A,B,C,D;
    float r,g,b;
    int precision = 15;
    int nbsegment = 0;

    std::vector<float> pointTmp;
    std::vector<Point> listPoint;
    std::vector<Segment> listSegment;


    int variableSize = (precision)*2;
    int sizeCourbeParam=6;
    int size = sizeCourbeParam+variableSize;
    int start;

    Segment *S1;
    Segment *S2;
    Segment *S3;
};

#endif // COURBEPARAMETRIQUE_H
