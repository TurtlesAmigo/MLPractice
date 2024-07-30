#pragma once

#include "Vector.h"

class Sphere
{
    Vector<3> center;
    double radius;
public:
    Sphere() : center(), radius(1.0) {}
    Sphere(const Vector<3>& c, double r) : center(c), radius(r) {}

    Vector<3> getCenter() const { return center; }
    double getRadius() const { return radius; }
};

