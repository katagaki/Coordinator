#ifndef POINT2D
#define POINT2D

class Point2D {
    
protected:
    
    int x;
    int y;
    double distFrOrigin;
    
    void setDistFrOrigin();
    
public:
    
    // Constructors
    Point2D();
    Point2D(int x, int y);
    
    // Accessors
    int getX();
    int getY();
    double getScalarValue();
    double distanceFrom(Point2D pt);
    
    // Modifiers
    void setX(int x);
    void setY(int y);
    
    // Operator overloads
    friend double operator-(Point2D l, Point2D r);
    friend bool operator==(Point2D l, Point2D r);
    
};

#endif
