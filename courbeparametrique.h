#ifndef COURBEPARAMETRIQUE_H
#define COURBEPARAMETRIQUE_H

#include "segment.h"
#include <math.h>

class CourbeParametrique
{
public:
    CourbeParametrique(Point *controlPoint, float r, float g, float b);
    void makeObject(QVector<GLfloat> *vertData);
    void makeControlSegment();
    void setControlPointColor();
    void update();
    void setStart(int start);
    int getStart();
    int getSize();
    int getSizeCourbeParam();
    Point getPoint(int numPoint);

    std::vector<float> SoustractionVec(std::vector<float> p1, std::vector<float> p2);
    std::vector<float> ProduitVec(std::vector<float> p1, std::vector<float> p2);
    float ProduitScalaire(std::vector<float> p1, std::vector<float> p2);

    float GetAngle(float i);
    std::vector<float> tauxAccroiss(float i);
    std::vector<float> bezier(float i);
    void createListPoint();

private:
    Point *controlPoint;
    Segment controlSegment[24];
    float r,g,b;
    float precision = 15;

    std::vector<float> pointTmp;
    std::vector<Point> listPoint;
    std::vector<Segment> listSegment;


    int nbsegment = 0;
    int sizeCourbeParam;
    int start;
};

#endif // COURBEPARAMETRIQUE_H
