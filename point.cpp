#include "point.h"

Point::Point()
{
	coords = new float[3];
    color = new float[3];
}

Point::~Point()
{
	delete [] coords;
	coords = nullptr;
    delete [] color;
    color = nullptr;
}

Point::Point(float x, float y, float z, float r, float g, float b)
{
    coords = new float[3];
    color = new float[3];
    coords[0]=x;
    coords[1]=y;
    coords[2]=z;
    color[0]=r;
    color[1]=g;
    color[2]=b;
}

Point::Point(const Point& p)
{
	coords = new float[3];
    color = new float[3];
    for (unsigned i=0; i<3; ++i){
        coords[i] = p.coords[i];
        color[i] = p.color[i];
    }


}

float Point::getX() const
{
	return getN(0);
}

float Point::getY() const
{
	return getN(1);
}

float Point::getZ() const
{
	return getN(2);
}

float Point::getR() const
{
    return color[0];
}

float Point::getG() const
{
    return color[1];
}

float Point::getB() const
{
    return color[2];
}

void Point::getColor(float * t) const
{
    for (unsigned i=0; i<3; ++i)
        t[i] = color[i];
}

void Point::get(float * t) const
{
	for (unsigned i=0; i<3; ++i)
		t[i] = coords[i];
}

float Point::getN(unsigned r) const
{
	if (r>2)
		r=2;
	return coords[r] ;
}

void Point::setN(unsigned r, const float & v)
{
	if (r>2)
		r=2;
	coords[r] = v;
}

void Point::set(const float * t)
{
	for (unsigned i=0; i<3; ++i)
		coords[i] = t[i];
}

void Point::setColor(float r, float g, float b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void Point::setColor(const float * t)
{
    for (unsigned i=0; i<3; ++i)
        color[i] = t[i];
}

void Point::setX(const float& v)
{
	setN(0, v);
}
void Point::setY(const float& v)
{
	setN(1, v);
}
void Point::setZ(const float& v)
{
	setN(2, v);
}

void Point::makeObjectSingle(QVector<GLfloat> *vertData){
    vertData->append(getX());
    vertData->append(getY());
    vertData->append(getZ());

    vertData->append(getR()*10);
    vertData->append(getG()*10);
    vertData->append(getB()*10);

    vertData->append(0);
    vertData->append(0);
    vertData->append(0);

}

void Point::makeObject(QVector<GLfloat> *vertData){
    vertData->append(getX());
    vertData->append(getY());
    vertData->append(getZ());

    vertData->append(getR());
    vertData->append(getG());
    vertData->append(getB());

}

Point& Point::operator= (const Point &p)
{
    for (unsigned i=0; i<3; ++i){
        coords[i] = p.coords[i];
        color[i]  = p.color[i];
    }
    return *this;

}

Point& Point::operator+= (const Point &p)
{
    for (unsigned i=0; i<3; ++i){
        coords[i] += p.coords[i];
    }
    return *this;
}

Point operator* (const float &f, const Point &p1)
{
    Point p;
    for (unsigned i=0; i<3; ++i){
        p.coords[i] = f*  p1.coords[i];
    }
    return p;
}

Point operator+ (const Point &p1, const Point &p2)
{
    Point p;
    for (unsigned i=0; i<3; ++i){
        p.coords[i] = p1.coords[i] + p2.coords[i];
        p.color[i] = ( p1.color[i] + p2.coords[i] )/2;
    }
    return p;
}

std::ostream& operator<<(std::ostream& out, const Point& p)
{
    return out << "[ " << p.coords[0] << " " << p.coords[1] << " " << p.coords[2] << " ]"  << "[ " << p.color[0] << " " << p.color[1] << " " << p.color[2] << " ]"; // can access private member Y::data
}
