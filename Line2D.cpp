#include "Line2D.h"
#include "Point2D.h"

// MARK: Protected functions

void Line2D::setLength() {
    length = pt1.distanceFrom(pt2);
}

// MARK: Public functions

Line2D::Line2D() {
    this -> pt1 = *(new Point2D(0, 0));
    this -> pt2 = *(new Point2D(0, 0));
}

Line2D::Line2D(Point2D pt1, Point2D pt2) {
    this -> pt1 = *(&pt1);
    this -> pt2 = *(&pt2);
}

Point2D Line2D::getPt1() {
    return pt1;
}

Point2D Line2D::getPt2() {
    return pt2;
}

double Line2D::getScalarValue() {
    this -> setLength();
    return length;
}

void Line2D::setPt1(Point2D pt1) {
    delete &pt1;
    pt1 = *(new Point2D(pt1.getX(), pt1.getY()));
}

void Line2D::setPt2(Point2D pt2) {
    delete &pt2;
    pt2 = *(new Point2D(pt2.getX(), pt2.getY()));
}

// Check if 2 lines are the same
bool operator==(Line2D l, Line2D r) {
    return (l.getPt1() == r.getPt1()) && (l.getPt2() == r.getPt2());
}
