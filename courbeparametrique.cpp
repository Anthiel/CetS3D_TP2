#include "courbeparametrique.h"

CourbeParametrique::CourbeParametrique(Point pA, Point pB, Point pC, Point pD, float r, float g, float b)
{
    this->pointA = pA;
    this->pointB = pB;
    this->pointC = pC;
    this->pointD = pD;

    this->pointA.setColor(r, g, b);
    this->pointB.setColor(r, g, b);
    this->pointC.setColor(r, g, b);
    this->pointD.setColor(r, g, b);
}
