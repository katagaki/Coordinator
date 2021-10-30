#include <math.h>
#include "Point3D.h"

// MARK: Protected functions

void Point3D::setDistFrOrigin() {
    distFrOrigin = distanceFrom(Point3D(0, 0, 0));
}

// MARK: Public functions

Point3D::Point3D() {
    x = 0;
    y = 0;
    z = 0;
}

Point3D::Point3D(int x, int y, int z): Point2D(x, y) {
    this -> z = z;
}

int Point3D::getZ() {
    return z;
}

double Point3D::getScalarValue() {
    this -> setDistFrOrigin();
    return distFrOrigin;
}

double Point3D::distanceFrom(Point3D pt) {
    return *this - pt;
}

void Point3D::setZ(int z) {
    this -> z = z;
}

// Returns length between 2 points
double operator-(Point3D l, Point3D r) {
    return sqrt(((l.x - r.x) * (l.x - r.x)) +
                ((l.y - r.y) * (l.y - r.y)) +
                ((l.z - r.z) * (l.z - r.z)));
}

// Checks if 2 points are the same
bool operator==(Point3D l, Point3D r) {
    return (l.x == r.x) && (l.y == r.y) && (l.z == r.z);
}
