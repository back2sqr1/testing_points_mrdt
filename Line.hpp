#pragma once
#include "Point.hpp"
#include <cmath>
#include <iostream>
#include <vector>

class Line {
public:
  // General form coefficients: ax + by + c = 0
  double a, b, c;

  // 1. General Constructor
  Line(double a, double b, double c) {
    this->a = a;
    this->b = b;
    this->c = c;
  }

  // 2. Slope-Intercept Constructor (y = mx + b)
  // Rearranged to standard form: mx - y + b = 0
  Line(double m, double b_val) {
    this->a = m;
    this->b = -1.0;
    this->c = b_val;
  }

  // 3. Two-Points Constructor (Safe for vertical and horizontal pairs)
  Line(Point p1, Point p2) {
    if (std::abs(p2.x - p1.x) < 1e-9) {
      // Vertical Line: x = p1.x  ->  1*x + 0*y - p1.x = 0
      this->a = 1.0;
      this->b = 0.0;
      this->c = -p1.x;
    } else {
      // General Line or Horizontal Line
      double m = (p2.y - p1.y) / (p2.x - p1.x);
      double intercept = p1.y - m * p1.x;
      this->a = m;
      this->b = -1.0;
      this->c = intercept;
    }
  }

  // Helper flags to detect special orientations safely
  bool is_vertical() const { return std::abs(b) < 1e-9; }
  bool is_horizontal() const { return std::abs(a) < 1e-9; }

  double dist(Point p) {
    return std::abs(a * p.x + b * p.y + c) / std::sqrt(a * a + b * b);
  }

  // Check if a point is to the left of the line direction vector
  bool left_of_line(Point p) {
    double d = a * p.x + b * p.y + c;
    if (!is_vertical()) {
      return (b > 0) ? (d < 0) : (d > 0);
    } else {
      return (a > 0) ? (d < 0) : (d > 0);
    }
  }

  // Safe Secant Intersection for a Circle at Center 'p' with Radius 'r'
  // Works flawlessly for horizontal, vertical, or skewed lines!
  std::vector<Point> get_points_on_secant(double r, Point p) {
    // 1. Find closest point on line to the circle center (projection)
    double d_val = a * a + b * b;
    double closest_x = (b * (b * p.x - a * p.y) - a * c) / d_val;
    double closest_y = (a * (-b * p.x + a * p.y) - b * c) / d_val;
    Point closest(closest_x, closest_y);

    // 2. Check how far that point is from the center
    double distance_to_center = dist(p);
    if (distance_to_center > r)
      return {}; // No intersection

    // 3. Compute distance from closest point to the intersection points (chord
    // half-length)
    double half_chord =
        std::sqrt(r * r - distance_to_center * distance_to_center);
    if (half_chord < 1e-9)
      return {closest}; // Tangent line (1 point)

    // 4. Extrapolate along the line's direction vector safely
    double dir_x = -b / std::sqrt(d_val);
    double dir_y = a / std::sqrt(d_val);

    Point pt1(closest.x + dir_x * half_chord, closest.y + dir_y * half_chord);
    Point pt2(closest.x - dir_x * half_chord, closest.y - dir_y * half_chord);

    return {pt1, pt2};
  }
  // Returns a new Line perpendicular to this one, passing through Point p
  Line get_perpendicular(Point p) {
    // Original: ax + by + c = 0
    // Perpendicular direction: bx - ay + d = 0
    double perp_a = b;
    double perp_b = -a;

    // Solve for 'd' (or perp_c) using the given point:
    // perp_a * p.x + perp_b * p.y + perp_c = 0
    double perp_c = -(perp_a * p.x + perp_b * p.y);

    return Line(perp_a, perp_b, perp_c);
  }
};

// --- Smart, ODR-compliant operator<< ---
inline std::ostream &operator<<(std::ostream &os, const Line &l) {
  if (l.is_vertical()) {
    // Vertical Line Format: x = k
    os << "x = " << (-l.c / l.a);
  } else if (l.is_horizontal()) {
    // Horizontal Line Format: y = k
    os << "y = " << (-l.c / l.b);
  } else {
    // Standard Sloped Line Format: y = mx + b
    double m = -l.a / l.b;
    double b_val = -l.c / l.b;

    os << "y = " << m << "x";
    if (b_val >= 0) {
      os << " + " << b_val;
    } else {
      os << " - " << std::abs(b_val);
    }
  }
  return os;
}
