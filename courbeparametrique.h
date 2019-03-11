#ifndef COURBEPARAMETRIQUE_H
#define COURBEPARAMETRIQUE_H

#include "point.h"

class CourbeParametrique
{
public:
    CourbeParametrique(Point pA, Point pB, Point pC, Point pD, float r, float g, float b);

private:
    Point pointA;
    Point pointB;
    Point pointC;
    Point pointD;
};

#endif // COURBEPARAMETRIQUE_H
