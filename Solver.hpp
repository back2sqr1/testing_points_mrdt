#include "Line.hpp"
#include "Vector.hpp"
class Solver {
public:
  /*
    Point s - starting
    Point b - biased
    Point nb - non-biased point
  */
  const double TOLERANCE = 1e-5;
  Point forward_function(Point s, Point b, Point nb, double t) {
    Line b_nb(b, nb);
    Point mid = b.midpoint(nb);

    if (s.dist(mid) <= t - TOLERANCE) {
      return mid;
    }

    Line fairness = b_nb.get_perpendicular(mid);
    // std::cout << fairness << std::endl;

    // make sure b is biased and nb is not biased
    if (s.dist(b) > s.dist(nb)) {
      std::swap(b, nb);
    }
    // std::cout << b << " " << nb << std::endl;
    // point if you go straight to non-biased
    Vector v(nb.x - s.x, nb.y - s.y);
    std::cout << v << std::endl;
    v.resize(t);
    std::cout << v << std::endl;
    Point straight_point(v.x + s.x, v.y + s.y);
    // std::cout << v << std::endl;

    if (fairness.left_of_line(straight_point)) {
      // find lowest on line of fairness
      std::vector<Point> points_intersect_w_circle =
          fairness.get_points_on_secant(t, s);
      if (points_intersect_w_circle[0].dist(mid) >
          points_intersect_w_circle[1].dist(mid)) {
        return points_intersect_w_circle[1];
      } else {
        return points_intersect_w_circle[0];
      }
    } else {
      return straight_point;
    }
  }
};
