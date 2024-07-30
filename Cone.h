#pragma once
#include "Vector.h"
class Cone
{
    Vector<3> center;
    Vector<3> axis;
    double radius;
    double height;

public:
    Cone() : center(), axis(), radius(1.0), height(1.0) {}
    Cone(const Vector<3>& c, const Vector<3>& a, double r, double h) : center(c), axis(a), radius(r), height(h) {}

    Vector<3> getCenter() const { return center; }
    Vector<3> getAxis() const { return axis; }
    double getRadius() const { return radius; }
    double getHeight() const { return height; }
};

