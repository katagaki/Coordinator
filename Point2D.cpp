#include <math.h>
#include "Point2D.h"

#include <iostream>

// MARK: Protected functions

void Point2D::setDistFrOrigin() {
    distFrOrigin = distanceFrom(Point2D(0, 0));
}

// MARK: Public functions

Point2D::Point2D() {
    x = 0;
    y = 0;
}

Point2D::Point2D(int x, int y) {
    this -> x = x;
    this -> y = y;
}

int Point2D::getX() {
    return x;
}

int Point2D::getY() {
    return y;
}

double Point2D::getScalarValue() {
    this -> setDistFrOrigin();
    return distFrOrigin;
}

double Point2D::distanceFrom(Point2D pt) {
    return *this - pt;
}

void Point2D::setX(int x) {
    this -> x = x;
}

void Point2D::setY(int y) {
    this -> y = y;
}

// Returns length between 2 points
double operator-(Point2D l, Point2D r) {
    return sqrt(((l.x - r.x) * (l.x - r.x)) +
                ((l.y - r.y) * (l.y - r.y)));
}

// Checks if 2 points are the same
bool operator==(Point2D l, Point2D r) {
    return (l.x == r.x) && (l.y == r.y);
}
