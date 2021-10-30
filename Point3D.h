#include "Point2D.h"

#ifndef POINT3D
#define POINT3D

class Point3D: public Point2D {
    
protected:
    
    int z;
    
    void setDistFrOrigin();
    
public:
    
    // Constructors
    Point3D();
    Point3D(int x, int y, int z);
    
    // Accessors
    int getZ();
    double getScalarValue();
    double distanceFrom(Point3D pt);
    
    // Modifiers
    void setZ(int z);
    
    // Operator overloads
    friend double operator-(Point3D l, Point3D r);
    friend bool operator==(Point3D l, Point3D r);
    
};

#endif
