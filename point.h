/* R. Raffin
 * M1 Informatique, Aix-Marseille Université
 * définition d'une classe Point
 * l'utilisation du tableau de float pour les coordonnées est là pour ne pas trop avoir peur de C++
 * mais c'(est une mauvaise façon d'écrire, préférez les objets de std::, comme std::vector par exemple
 * Cet objet est d'ailleurs directement utilsable comme un float[]
 * Si on veut généraliser le Point, il peut être d'une quelconque dimension (i.e. un nombre quelconque de coordonnées)
 */

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <QDebug>
#include <QOpenGLWidget>

class Point
{
private:
	float * coords;
    float * color;

public:
	Point();
	~Point();
    Point(float x, float y, float z, float r=1.0, float g=1.0, float b=1.0);
	Point(const Point&);

    Point& operator= (const Point &p);
    Point& operator+= (const Point &p);
    friend Point operator* (const float &f, const Point &p1);
    friend Point operator+ (const Point &p1, const Point &p2);


	float getN(unsigned) const;
	float getX() const;
	float getY() const;
    float getZ() const;
    float getR() const;
    float getG() const;
    float getB() const;
	void get(float *) const;
    void getColor(float * ) const;

	void setN(unsigned, const float&);
	void setX(const float&);
	void setY(const float&);
	void setZ(const float&);
    void set(const float *);
    void setColor(const float * t);
    void setColor(float r, float g, float b);
    void makeObject(QVector<GLfloat> *vertData);
    void makeObjectSingle(QVector<GLfloat> *vertData);

	friend std::ostream& operator<<(std::ostream&, const Point&);

};

#endif // POINT_H
