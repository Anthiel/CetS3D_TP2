#ifndef COURBEPARAMETRIQUE_H
#define COURBEPARAMETRIQUE_H

#include "segment.h"
#include <QVector3D>
#include <math.h>

class CourbeParametrique
{
public:
    CourbeParametrique(std::vector<Point> controlPoint,int controlPoints_x,int controlPoints_y, float r, float g, float b);
    void makeObject(QVector<GLfloat> *vertData);
    void makeControlSegment();
    void setControlPointColor();
    void update();
    void setStart(int start);
    void setPrecision(int pas);
    void swapGridSurface();
    int getStart();
    int getSize();
    int getSizeCourbeParam();
    Point getPoint(int numPoint);
    void setPoint(int numPoint,Point p);

    std::vector<float> SoustractionVec(std::vector<float> p1, std::vector<float> p2);
    std::vector<float> ProduitVec(std::vector<float> p1, std::vector<float> p2);
    float ProduitScalaire(std::vector<float> p1, std::vector<float> p2);

    float GetAngle(float i);
    std::vector<float> tauxAccroiss(float i);
    std::vector<float> bezier(float i);
    void createListPoint();

    int factoriel(int n);
    float Bernstein(float u, int i, int n);
    Point* SurfaceBezier(float u, float v, int n, int m);




private:
    std::vector<Point> controlPoints;
    int controlPoints_x,controlPoints_y;
    std::vector<Segment> controlSegment;
    float r,g,b;
    float precision = 10;

    std::vector<Point> listPoint;
    std::vector<Segment> listSegment;

    bool needCalcul=true,showGrid=true;
    int nbsegment = 0;
    int sizeCourbeParam;
    int start;
};

#endif // COURBEPARAMETRIQUE_H
