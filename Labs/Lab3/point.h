#include <iostream>
#ifndef __POINT_H
#define __POINT_H


// A simple 3D point class.  In this simple world, we'll follow the
// convention often used in Computer Graphics.  y is the vertical
// axes, "pointing" up.  The x and z axes define the ground plane.

class Point {
public:
  // CONSTRUCTOR
  Point(double x, double y, double z);
  // ACCESSORS
  double get_x() const;
  double get_y() const;
  double get_z() const;  
private:
  // REPRESENTATION
  double x_,y_,z_;
};



// A helper function to print a Point.
std::ostream& operator<< (std::ostream &ostr, const Point &p);


// A helper function to compute the slope between two Points.
double compute_slope(const Point &a, const Point &b);
#endif