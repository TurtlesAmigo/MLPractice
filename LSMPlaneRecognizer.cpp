#include "LSMPlaneRecognizer.h"

#include <stdexcept>
#include "Utils.h"
#include <array>


using Matrix3x3 = std::array<std::array<double, 3>, 3>;

static Matrix3x3 Add(const Matrix3x3& a, const Matrix3x3& b) {
    Matrix3x3 result = {};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    return result;
}

static Matrix3x3 outerProduct(const Vector<3>& a, const Vector<3>& b) {
    Matrix3x3 result = {};
    result[0][0] = a[0] * b[0];
    result[0][1] = a[0] * b[1];
    result[0][2] = a[0] * b[2];
    result[1][0] = a[1] * b[0];
    result[1][1] = a[1] * b[1];
    result[1][2] = a[1] * b[2];
    result[2][0] = a[2] * b[0];
    result[2][1] = a[2] * b[1];
    result[2][2] = a[2] * b[2];
    return result;
}

LSMPlaneRecognizer::LSMPlaneRecognizer()
{
}

Plane3D LSMPlaneRecognizer::recognizePlane(const std::vector<Vector<3>>& points)
{
    int n = points.size();
    if (n < 3) {
        throw std::invalid_argument("At least 3 points are required to fit a plane.");
    }

    // Calculate the centroid of the points
    Vector<3> centroid = { 0, 0, 0 };
    for (const auto& point : points) {
        centroid += point;
    }
    centroid = centroid / n;

    Matrix3x3 covarianceMatrix = {};
    for (const auto& point : points) {
        Vector<3> centered = point - centroid;
        covarianceMatrix = Add(covarianceMatrix, outerProduct(centered, centered));
    }

    double a = covarianceMatrix[0][0];
    double b = covarianceMatrix[0][1];
    double c = covarianceMatrix[0][2];
    double d = covarianceMatrix[1][1];
    double e = covarianceMatrix[1][2];
    double f = covarianceMatrix[2][2];

    double p1 = b * b - a * d;
    double p2 = c * c - a * f;
    double p3 = e * e - d * f;

    double q = (a + d + f) / 3.0;
    double p = sqrt((a - q) * (a - q) + (d - q) * (d - q) + (f - q) * (f - q) + 2 * (b * b + c * c + e * e)) / 3.0;
    double r = (a * d * f + 2 * b * c * e - a * e * e - d * c * c - f * b * b) / 2.0;

    double phi = acos(r / (p * p * p)) / 3.0;
    double eig1 = q + 2 * p * cos(phi);
    double eig2 = q + 2 * p * cos(phi + 2 * M_PI / 3);
    double eig3 = q + 2 * p * cos(phi + 4 * M_PI / 3);

    Vector<3> normal;
    if (eig1 <= eig2 && eig1 <= eig3) {
        normal = { covarianceMatrix[0][0] - eig1, covarianceMatrix[0][1], covarianceMatrix[0][2] };
    }
    else if (eig2 <= eig1 && eig2 <= eig3) {
        normal = { covarianceMatrix[0][0] - eig2, covarianceMatrix[0][1], covarianceMatrix[0][2] };
    }
    else {
        normal = { covarianceMatrix[0][0] - eig3, covarianceMatrix[0][1], covarianceMatrix[0][2] };
    }

    // Normalize the normal vector
    double norm = sqrt(normal.dot(normal));
    normal = { normal[0] / norm, normal[1] / norm, normal[2] / norm };

    // Calculate the plane constant d
    double planeD = -normal.dot(centroid);

    return { normal, planeD };
}
