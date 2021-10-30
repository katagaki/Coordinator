// Coordinate object functions library

#include <string>
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"
#include "strfunc.h"

Point2D* getPoint2D(std::string data) {
    
    if (startsWith(data, "point2d")) {
        
        // Split string by comma > get right side > trim spaces > gets back coodinates
        // "[x, y]"
        std::string strRightSideData = trimString(getRightSide(data, ","));
        
        // Split data by comma > get left side > trim spaces > remove the first [ > trim again > gets back x
        // "x"
        std::string strX = trimString(removeFirstChar(trimString(getLeftSide(strRightSideData, ","))));
        int x = std::stoi(strX);
        
        // Split data by comma > get right side > trim spaces > remove the last ] > trim again > gets back y
        // "y"
        std::string strY = trimString(removeLastChar(trimString(getRightSide(strRightSideData, ","))));
        int y = std::stoi(strY);
        
        Point2D* pt = new Point2D(x, y);
                
        return pt;
        
    } else {
        throw std::string("The object specified is not a Point2D object: " + data);
    }
    
}

Point3D* getPoint3D(std::string data) {
    
    if (startsWith(data, "point3d")) {
        
        // Split string by first comma > get right side > trim spaces > gets back coordinates
        // "[x, y]"
        std::string strRightSideData = trimString(getRightSide(data, ","));
        
        // Split data by first comma > get left side > trim spaces > remove the first [ > trim again > gets back x
        // "x"
        std::string strX = trimString(removeFirstChar(trimString(getLeftSide(strRightSideData, ","))));
        int x = std::stoi(strX);
        
        // Split data by first comma > get right side > trim spaces > remove the last ] > trim again > gets back y and z
        // "y, z"
        std::string strYAndZ = trimString(removeLastChar(trimString(getRightSide(strRightSideData, ","))));
        
        // Split y and z by first comma > get left side > trim spaces > gets back y
        // "y"
        std::string strY = trimString(getLeftSide(strYAndZ, ","));
        int y = std::stoi(strY);
        
        // Split y and z by first comma > get right side > trim spaces > gets back z
        // "z"
        std::string strZ = trimString(getRightSide(strYAndZ, ","));
        int z = std::stoi(strZ);
        
        Point3D* pt = new Point3D(x, y, z);
                
        return pt;
        
    } else {
        throw std::string("The object specified is not a Point3D object: " + data);
    }
    
}

Line2D* getLine2D(std::string data) {
    
    // Remove the Line2D header, then create 2 Point2Ds in code and read in the Point2D using the getPoint2D function
    
    if (startsWith(data, "line2d")) {
        
        // Split string by first comma > get right side > trim spaces to get back the 2 points
        // "[x1, y1], [x2, y2]"
        std::string strRightSideData = trimString(getRightSide(data, ","));
        
        // Split data by first ] > get left side > trim spaces to get back the first point
        // "[x1, y1"
        std::string strPt1 = trimString(getLeftSide(strRightSideData, "]"));
        Point2D* pt1 = getPoint2D("point2d," + strPt1 + "]");
        
        // Split data by first ] > get right side > trim spaces > remove the first , > trim spaces
        // "[x2, y2]"
        std::string strPt2 = trimString(removeFirstChar(trimString(getRightSide(strRightSideData, "]"))));
        Point2D* pt2 = getPoint2D("point2d," + strPt2);
        
        Line2D* ln = new Line2D(*pt1, *pt2);
        
        return ln;
        
    } else {
        throw std::string("The object specified is not a Line2D object: " + data);
    }
    
}

Line3D* getLine3D(std::string data) {
    
    // Remove the Line3D header, then create 2 Point3Ds in code and read in the Point3D using the getPoint3D function
    
    if (startsWith(data, "line3d")) {
        
        // Split string by first comma > get right side > trim spaces to get back the 2 points
        // "[x1, y1, z1], [x2, y2, z2]"
        std::string strRightSideData = trimString(getRightSide(data, ","));
        
        // Split data by first ] > get left side > trim spaces to get back the first point
        // "[x1, y1, z1"
        std::string strPt1 = trimString(getLeftSide(strRightSideData, "]"));
        Point3D* pt1 = getPoint3D("point3d," + strPt1 + "]");
        
        // Split data by first ] > get right side > trim spaces > remove the first , > trim spaces
        // "[x2, y2, z2]"
        std::string strPt2 = trimString(removeFirstChar(trimString(getRightSide(strRightSideData, "]"))));
        Point3D* pt2 = getPoint3D("point3d," + strPt2);
        
        Line3D* ln = new Line3D(*pt1, *pt2);
        
        return ln;
        
    } else {
        throw std::string("The object specified is not a Line3D object: " + data);
    }
    
}
