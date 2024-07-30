#include "LSMSphereRecognition.h"
#include <stdexcept>

LSMSphereRecognition::LSMSphereRecognition()
{
}

Sphere LSMSphereRecognition::recognizeSphere(const std::vector<Vector<3>>& points)
{
    size_t n = points.size();
    if (n < 4) {
        throw std::invalid_argument("At least 4 points are required to fit a sphere.");
    }

    // Set up the system of linear equations
    double A[4][4] = { 0 };
    double B[4] = { 0 };

    for (const auto& point : points) {
        double x = point[0];
        double y = point[1];
        double z = point[2];
        double x2 = x * x;
        double y2 = y * y;
        double z2 = z * z;

        A[0][0] += x2 + y2 + z2;
        A[0][1] += x;
        A[0][2] += y;
        A[0][3] += z;
        A[1][0] += x;
        A[1][1] += 1;
        A[2][0] += y;
        A[2][2] += 1;
        A[3][0] += z;
        A[3][3] += 1;

        B[0] += x2 + y2 + z2;
        B[1] += x;
        B[2] += y;
        B[3] += z;
    }

    // Solve the system using Gaussian elimination
    for (int i = 0; i < 4; ++i) {
        // Pivot
        int maxRow = i;
        for (int k = i + 1; k < 4; ++k) {
            if (fabs(A[k][i]) > fabs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        for (int k = i; k < 4; ++k) {
            std::swap(A[maxRow][k], A[i][k]);
        }
        std::swap(B[maxRow], B[i]);

        // Eliminate
        for (int k = i + 1; k < 4; ++k) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < 4; ++j) {
                A[k][j] -= factor * A[i][j];
            }
            B[k] -= factor * B[i];
        }
    }

    // Back substitution
    double X[4] = { 0 };
    for (int i = 3; i >= 0; --i) {
        X[i] = B[i] / A[i][i];
        for (int k = i - 1; k >= 0; --k) {
            B[k] -= A[k][i] * X[i];
        }
    }

    // Extract sphere parameters
    double a = X[1] / 2;
    double b = X[2] / 2;
    double c = X[3] / 2;
    double r = sqrt(X[0] + a * a + b * b + c * c);

    return { {a, b, c}, r };
}
