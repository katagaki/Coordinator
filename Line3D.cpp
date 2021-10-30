#include "Line3D.h"
#include "Point3D.h"

#include <iostream>

// MARK: Protected functions

void Line3D::setLength() {
    length = pt1.distanceFrom(pt2);
}

// MARK: Public functions

Line3D::Line3D() {
    this -> pt1 = *(new Point3D(0, 0, 0));
    this -> pt2 = *(new Point3D(0, 0, 0));
}

Line3D::Line3D(Point3D pt1, Point3D pt2) {
    this -> pt1 = *(&pt1);
    this -> pt2 = *(&pt2);
}

Point3D Line3D::getPt1() {
    return pt1;
}

Point3D Line3D::getPt2() {
    return pt2;
}

double Line3D::getScalarValue() {
    this -> setLength();
    return length;
}

void Line3D::setPt1(Point3D pt1) {
    delete &pt1;
    pt1 = *(new Point3D(pt1.getX(), pt1.getY(), pt1.getZ()));
}

void Line3D::setPt2(Point3D pt2) {
    delete &pt2;
    pt2 = *(new Point3D(pt2.getX(), pt2.getY(), pt2.getZ()));
}

// Check if 2 lines are the same
bool operator==(Line3D l, Line3D r) {
    return (l.getPt1() == r.getPt1()) && (l.getPt2() == r.getPt2());
}
