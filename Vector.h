#pragma once

#include <initializer_list>

template <int N>
class Vector
{
    double data[N];
public:
    Vector() : data{ 0 } {}
    Vector(const Vector<N>& v) {

        for (int i = 0; i < N; i++) {
            data[i] = v.data[i];
        }
    }
    Vector<N>& operator=(const Vector<N>& v)
    {
        for (int i = 0; i < N; i++) {
            data[i] = v.data[i];
        }
        return *this;
    }

    Vector(std::initializer_list<double> list)
    {
        int i = 0;
        for (double d : list) {
            data[i++] = d;
        }
    }

    double& operator[](int i) { return data[i]; }

    double operator[](int i) const { return data[i]; }

    Vector<N> operator+(const Vector<N>& v) const
    {
        Vector<N> sum;
        for (int i = 0; i < N; i++)
            sum[i] = data[i] + v[i];
        return sum;
    }

    Vector<N> operator-(const Vector<N>& v) const
    {
        Vector<N> diff;
        for (int i = 0; i < N; i++)
            diff[i] = data[i] - v[i];
        return diff;
    }

    Vector<N> operator*(double a) const
    {
        Vector<N> prod;
        for (int i = 0; i < N; i++)
            prod[i] = a * data[i];
        return prod;
    }

    Vector<N> operator/(double a) const
    {
        Vector<N> quot;
        for (int i = 0; i < N; i++)
            quot[i] = data[i] / a;
        return quot;
    }

    Vector<N>& operator+=(const Vector<N>& v)
    {
        for (int i = 0; i < N; i++)
            data[i] += v[i];
        return *this;
    }

    Vector<N>& operator-=(const Vector<N>& v)
    {
        for (int i = 0; i < N; i++)
            data[i] -= v[i];
        return *this;
    }

    Vector<N>& operator*=(double a)
    {
        for (int i = 0; i < N; i++)
            data[i] *= a;
        return *this;
    }

    Vector<N>& operator/=(double a)
    {
        for (int i = 0; i < N; i++)
            data[i] /= a;
        return *this;
    }

    double dot(const Vector<N>& v) const
    {
        double d = 0;
        for (int i = 0; i < N; i++) {
            d += data[i] * v[i];
        }
        return d;
    }

    double getMagnitude() const
    {
        return sqrt(dot(*this));
    }

    Vector<N> normalize() const
    {
        return *this / getMagnitude();
    }

    double getMagnitudeSquared() const
    {
        return dot(*this);
    }
};

static Vector<3> cross(const Vector<3>& a, const Vector<3>& b)
{
    return Vector<3>{
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0]
    };
}