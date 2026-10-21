#include "Line.hpp"
#include "Vector.hpp"
class Solver {
public:
  /*
    Point s - starting
    Point b - biased
    Point nb - non-biased point
  */
  const double TOLERANCE = 1e-9;
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
    // std::cout << s << std::endl;
    // point if you go straight to non-biased
    Vector v(nb.x - s.x, nb.y - s.y);
    // std::cout << "INITIAL V: " << v << std::endl;
    v.resize(t);
    // std::cout << v << std::endl;
    Point straight_point(v.x + s.x, v.y + s.y);
    // std::cout << v << std::endl;

    if (fairness.left_of_line(straight_point)) {
      std::cout << "LEFT OF FAIRNESS" << std::endl;
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

  Point forward_function_sampling(Point s, Point b, Point nb, double t) {
    // sample all points within circle of Point s and radius t
    std::vector<Point> points = pointsInCircle(s, t);
    Point best_point = s;
    for (auto &x : points) {
      double d = std::max(x.dist(b), x.dist(nb));
      if (d + TOLERANCE < std::max(b.dist(best_point), nb.dist(best_point))) {
        best_point = x;
      }
    }
    return best_point;
  }

private:
  // written with AI - not checked
  template <class Visitor>
  void forEachPointInCircle(const Point &center, double t, double step,
                            Visitor &&visit) {
    if (!(t >= 0.0) || !(step > 0.0))
      return;

    const double R = t / step; // radius in grid units
    const double R2 = R * R;
    const double eps = 1e-9;
    const long long n = static_cast<long long>(std::floor(R + eps));

    for (long long i = -n; i <= n; ++i) {
      const double rem = R2 - double(i) * double(i) + eps;
      if (rem < 0.0)
        continue;
      const long long m = static_cast<long long>(std::floor(std::sqrt(rem)));
      for (long long j = -m; j <= m; ++j)
        visit(Point{center.x + i * step, center.y + j * step});
    }
  }
  // Collects into a vector (default step 0.001)
  std::vector<Point> pointsInCircle(const Point &center, double t,
                                    double step = 0.01) {
    std::vector<Point> out;
    forEachPointInCircle(center, t, step,
                         [&](const Point &p) { out.push_back(p); });
    return out;
  }
};
