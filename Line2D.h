#include "Point2D.h"

#ifndef LINE2D
#define LINE2D

class Line2D {
    
private:
    
    Point2D pt1, pt2;
    
protected:
    
    double length;
    
    void setLength();
    
public:
    
    // Constructors
    Line2D();
    Line2D(Point2D pt1, Point2D pt2);
    
    // Accessors
    Point2D getPt1();
    Point2D getPt2();
    double getScalarValue();
    
    // Modifiers
    void setPt1(Point2D pt1);
    void setPt2(Point2D pt2);
    
    // Operator overloads
    friend bool operator==(Line2D l, Line2D r);
    
};

#endif
