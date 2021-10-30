#include "Point3D.h"
#include "Line2D.h"

#ifndef LINE3D
#define LINE3D

class Line3D: public Line2D {
    
private:
    
    Point3D pt1, pt2;
    
protected:
    
    void setLength();
    
public:
    
    // Constructors
    Line3D();
    Line3D(Point3D pt1, Point3D pt2);
    
    // Accessors
    Point3D getPt1();
    Point3D getPt2();
    double getScalarValue();
    
    // Modifiers
    void setPt1(Point3D pt1);
    void setPt2(Point3D pt2);
    
    // Operator overloads
    friend bool operator==(Line3D l, Line3D r);
    
};

#endif
