#pragma once
#include "Vector.h"
#include <cmath>
class Plane3D
{
    Vector<3> normal;
    double d;

public:
    Plane3D() : normal(), d(0) {}
    Plane3D(const Vector<3>& n, double d) : normal(n), d(d) {}
    Plane3D(const Vector<3>& p1, const Vector<3>& p2, const Vector<3>& p3)
    {
        normal = cross(p2 - p1, p3 - p1);
        d = -normal.dot(p1);
    }

    Vector<3> getNormal() const { return normal; }
    double getD() const { return d; }
    double distance(const Vector<3>& p) const { return abs(getSignedDistanceFromPoint(p)); }
    Vector<3> project(const Vector<3>& p) const { return p - normal * distance(p); }
    double getSignedDistanceFromPoint(const Vector<3>& p) const { return normal.dot(p) + d; }

};

