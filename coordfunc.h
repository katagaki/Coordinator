#include <fstream>
#include <iostream>

#ifndef COORDFUNC
#define COORDFUNC

// Gets a Point2D class with a line of data
Point2D* getPoint2D(std::string data);

// Gets a Point3D class with a line of data
Point3D* getPoint3D(std::string data);

// Gets a Line2D class with a line of data
Line2D* getLine2D(std::string data);

// Gets a Line3D class with a line of data
Line3D* getLine3D(std::string data);

#endif
