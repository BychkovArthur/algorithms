#include <initializer_list>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstdarg>
#include <cassert>

using std::vector;
using std::max;
using std::cout;
using std::cerr;

class Line;

namespace math {
  const double eps = 1e-5;

  const double pi = 3.14159265359;

  double degreeToRad(double angle) {
    return angle * pi / 180;
  }

  bool isEqual(double d1, double d2) {
    if (std::abs(d1 - d2) < eps) {
      return true;
    }
    return false;
  }
}  // namespace math

enum class type {
  direction,
  normal
};

struct Point {
public:
  double x, y;

  Point() {};

  Point(double new_x, double new_y) : x(new_x), y(new_y) {}

  bool operator==(const Point& other) const {
    if (math::isEqual(x, other.x) && math::isEqual(y, other.y)) {
      return true;
    }
    return false;
  }

  void operator+=(const Point& other) {
    x += other.x;
    y += other.y;
  }

  void operator-=(const Point& other) {
    x -= other.x;
    y -= other.y;
  }

  void operator*=(double other) {
    x *= other;
    y *= other;
  }

  void operator/=(double other) {
    x /= other;
    y /= other;
  }

  Point operator+(const Point& other) const {
    Point copy(*this);
    copy += other;
    return copy;
  }

  Point operator-(const Point& other) const {
    Point copy(*this);
    copy -= other;
    return copy;
  }

  double len() const {
    return sqrtl(x * x + y * y);
  }

  double dist(const Point &other) const {
    return sqrtl((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
  }

  Point operator/(double other) const {
    Point copy(*this);
    copy /= other;
    return copy;
  }

  Point operator*(double other) const {
    Point copy(*this);
    copy *= other;
    return copy;
  }
  Point operator-() const {
    return Point(-x, -y);
  }

  Point normalized() const {
    double length = len();
    return Point(x / length, y / length);
  }

  Point rotate(double angle) const {
    double new_x = cos(angle) * x - y * sin(angle);
    double new_y = cos(angle) * y + x * sin(angle);
    return Point(new_x, new_y);
  }

  void rotate(const Point& center, double angle) {
    angle = math::degreeToRad(angle);
    Point point_center = operator-(center);
    *this += (point_center.rotate(angle) - point_center);
  }

  void scale(const Point& center, double coefficient) {
    Point point_center = operator-(center);
    *this += point_center * (coefficient - 1);
  }

  void reflect(const Point& center) {
    Point point_center = center - *this;
    *this += point_center * 2;
  }

  void reflect(const Line& axis);

  double getAngle(const Point& other) const;

  bool isLenEq(const Point& other) const {
    return math::isEqual(len(), other.len());
  }
};

namespace math {
  double dotProduct(const Point& point, const Point& other) {
    return point.x * other.x + point.y * other.y;
  }
  double crossProduct(const Point& point, const Point& other) {
    return other.y * point.x - point.y * other.x;
  }
}

double Point::getAngle(const Point& other) const {
  return atan2(math::crossProduct(*this, other), math::dotProduct(*this, other));
}

class Line {
private:
  double a, b, c;

public:

  Line() = default;

  Line(double new_a, double new_b, double new_c) : a(new_a), b(new_b), c(new_c) {}

  Line(double new_k, double new_b) : a(-new_k), b(1), c(-new_b) {}

  Line(const Point& p1, const Point& p2) : a(p1.y - p2.y), b(p2.x - p1.x),
    c(-(a * p1.x + b * p1.y)) {}

  Line(const Point& p1, double new_k) : a(-new_k), b(1), c(-(a * p1.x + b * p1.y)) {}

  Line(const Point& direction, const Point& p1, enum type type_of_vector) {
    if (type_of_vector == type::direction) {
      a = direction.y;
      b = -direction.x;
    } else {
      a = direction.x;
      b = direction.y;
    }
    c = -(a * p1.x + b * p1.y);
  }

  bool isOnLine(const Point& other) const {
    if (math::isEqual(other.x * a + other.y * b + c, 0)) {
      return true;
    }
    return false;
  }

  const double& getA() const { return a; }

  const double& getB() const { return b; }

  const double& getC() const { return c; }

  double& getC() { return c; }

  void setNormal(double new_a, double new_b) {
    a = new_a;
    b = new_b;
  }

  Point getNormal() const {
    return Point(a, b);
  }

  void normalilizeNormal() {
    double len = Point(a, b).len();
    a /= len;
    b /= len;
    c /= len;
  }

  bool operator==(const Line& other) const {
    double a2 = other.getA();
    double b2 = other.getB();
    double c2 = other.getC();

    if (!math::isEqual(math::crossProduct(getNormal(), other.getNormal()),
                       0)) {
      return false;
    }
    Point p1(0, 0);
    if (!math::isEqual(c, 0)) {
      if (!math::isEqual(a, 0)) {
        p1.x = -c / a;
      } else {
        p1.y = -c / b;
      }
    }
    if (math::isEqual(a2 * p1.x + b2 * p1.y + c2, 0)) {
      return true;
    }
    return false;
  }

  double dist(const Point& other) const {
    double normal_len = Point(a, b).len();
    return std::abs(a * other.x + b * other.y + c) / normal_len;
  }

  Point intersect(const Line& other) {
    double a2 = other.getA();
    double b2 = other.getB();
    double c2 = other.getC();
    double d1 = -c * b2 + c2 * b;
    double d2 = -a * c2 + c * a2;
    double com = a * b2 - b * a2;
    return Point(d1 / com, d2 / com);
  }
};

void Point::reflect(const Line& axis) {
  double dist = axis.dist(*this);
  Point scaled_normal = axis.getNormal().normalized() * dist;
  Point newp = *this + scaled_normal;
  if (axis.isOnLine(newp)) {
    *this += scaled_normal * 2;
  } else {
    *this -= scaled_normal * 2;
  }
}

class Shape {
public:
  virtual double perimeter() const = 0;

  virtual double area() const = 0;

  virtual bool operator==(const Shape& other) const = 0;

  virtual bool operator!=(const Shape& other) const = 0;

  virtual bool isCongruentTo(const Shape& other) const = 0;

  virtual bool isSimilarTo(const Shape& other) const = 0;

  virtual bool containsPoint(const Point& Point) const = 0;

  virtual ~Shape() = default;

  virtual void rotate(const Point& center, double angle) = 0;

  virtual void reflect(const Point& center) = 0;

  virtual void reflect(const Line& axis) = 0;

  virtual void scale(const Point& center, double coefficient) = 0;
};

class Polygon : public Shape {
protected:
  std::vector<Point> points;

public:
  Polygon(const vector<Point>& new_pts) : points(new_pts) {}

  double getAngle(size_t index) const {
    index %= points.size();

    size_t next = (index + 1) % points.size();
    size_t prev = (points.size() + index - 1) % points.size();
    Point side1 = points[prev] - points[index];
    Point side2 = points[next] - points[index];
    return side1.getAngle(side2);
  }

  Polygon(int cnt) {
    points.resize(cnt, Point(0, 0));
  }

  template <typename... Args>
  Polygon(const Args&... args) : points {args...} {}

  size_t verticesCount() const {
    return points.size();
  }

  const std::vector<Point>& getVertices() const {
    return points;
  }

  bool isConvex() const {
    bool isnegative = 0;
    if (math::crossProduct(-getSide(0), getSide(1)) < 0) {
      isnegative = true;
    }
    size_t sz = points.size();
    for (size_t i = 1; i < sz; i++) {
      Point side1 = points[i - 1] - points[i];
      Point side2 = points[(i + 1) % sz] - points[i];

      if (math::crossProduct(side1, side2) >= 0) {
        if (isnegative)
          return false;
      } else {
        if (!isnegative)
          return false;
      }
    }
    return true;
  }

  double perimeter() const override {
    double per = 0;
    for (size_t i = 1; i <= points.size(); i++) {
      per += (points[i - 1] - points[i % points.size()]).len();
    }
    return per ;
  }

  double area() const override {
    double area = 0;
    for (size_t i = 2; i < points.size(); i++) {
      Point side1 = points[i - 1] - points[0];
      Point side2 = points[i] - points[0];

      area += math::crossProduct(side1, side2) / 2.0;
    }
    area = std::abs(area);
    return area;
  }

  double getSideLen(size_t index) const {
    if (index == 0) {
      return (points[0] - points.back()).len();
    }
    return (points[index] - points[index - 1]).len();
  }

  Point getSide(size_t index) const {
    if (index == 0) {
      return points[0] - points.back();
    }
    return points[index] - points[index - 1];
  }

  bool operator==(const Shape& other) const override {
    const Polygon *poly = dynamic_cast<const Polygon *>(&other);
    if (poly == nullptr)
      return false;
    if (points.size() != poly->verticesCount()) {
      return false;
    }
    size_t common_sz = points.size();
    for (size_t start = 0; start < common_sz; start++) {
      bool is_ok = true;
      for (size_t i = 0; i < common_sz; i++) {
        if (points[(start + i) % common_sz] != poly->getVertices()[i]) {
          is_ok = false;
          break;
        }
      }
      if (is_ok)
        return true;
      is_ok = true;
      for (size_t i = 0; i < common_sz; i++) {
        if (points[(start + i) % common_sz] != poly->getVertices()[common_sz - 1 - i]) {
          is_ok = false;
          break;
        }
      }
      if (is_ok)
        return true;
    }
    return false;
  }

  bool operator!=(const Shape& other) const override {
    return !operator==(other);
  }

  bool isCongruentTo(const Shape& other) const override {
    const Polygon *poly = dynamic_cast<const Polygon *>(&other);
    if (poly == nullptr)
      return false;
    if (!isSimilarTo(*poly)) {
      return false;
    }
    return math::isEqual(perimeter(), poly->perimeter());
  }

  bool isSimilarTo(const Shape& other) const override {
    const Polygon *poly = dynamic_cast<const Polygon *>(&other);
    if (poly == nullptr)
      return false;
    if (points.size() != poly->verticesCount()) {
      return false;
    }
    size_t common_sz = points.size();

    for (size_t start = 0; start < common_sz; start++) {
      bool is_ok = true;
      for (size_t i = 0; i < common_sz; i++) {
        double angle1 = getAngle(i);
        double angle2 = poly->getAngle(start + i);

        if (!math::isEqual(angle1, angle2) && !math::isEqual(angle1 + angle2, math::pi) &&
             !math::isEqual(angle1 + angle2, -math::pi) && !math::isEqual(angle1 + angle2, 0)) {
          is_ok = false;
          break;
        }
      }
      if (is_ok)
        return true;
      is_ok = true;
      for (size_t i = 0; i < points.size(); i++) {
        double angle1 = getAngle(common_sz - i);
        double angle2 = poly->getAngle(start + i);

        if (!math::isEqual(angle1, angle2) && !math::isEqual(angle1 + angle2, math::pi) &&
             !math::isEqual(angle1 + angle2, -math::pi) && !math::isEqual(angle1 + angle2, 0)) {
          is_ok = false;
          break;
        }
      }
      if (is_ok)
        return true;
    }
    return false;
  }

  bool containsPoint(const Point& inpoint) const override {
    double angle = 0;
    for (size_t i = 0; i < points.size(); i++) {
      Point vec1 = points[i] - inpoint;
      Point vec2;
      if (i == 0) {
        vec2 = points.back() - inpoint;
      } else {
        vec2 = points[i - 1] - inpoint;
      }
      double locangle = vec1.getAngle(vec2);
      angle += locangle;
    }
    if (math::isEqual(std::abs(angle), 2 * math::pi))
      return true;
    return false;
  }

  void rotate(const Point& center, double angle) override {
    for (size_t i = 0; i < points.size(); i++) {
      points[i].rotate(center, angle);
    }
  }

  void reflect(const Point& center) override {
    for (size_t i = 0; i < points.size(); i++) {
      points[i].reflect(center);
    }
  }

  void reflect(const Line& axis) override {
    for (size_t i = 0; i < points.size(); i++) {
      points[i].reflect(axis);
    }
  }

  void scale(const Point& center, double coefficient) override {
    for (size_t i = 0; i < points.size(); i++) {
      points[i].scale(center, coefficient);
    }
  }
};

class Ellipse: public Shape {
private:
  Point f1, f2;
  double semi_major_axis;

public:

  Ellipse(const Point &new_f1, const Point &new_f2, double a2) :
    f1(new_f1), f2(new_f2), semi_major_axis(std::abs(a2) / 2) {}

  std::pair<Point, Point> focuses() const {
    return {f1, f2};
  }

  std::pair<Line, Line> directrices() const {
    Line focus_line(f1, f2);
    Point centr = center();
    double dist = semi_major_axis / eccentricity();
    Point normalised_focus_line = (f1 - f2).normalized();
    Point pd1 = centr + normalised_focus_line * dist;
    Point pd2 = centr - normalised_focus_line * dist;
    Line dir1(focus_line.getNormal(), pd1, type::direction);
    Line dir2(focus_line.getNormal(), pd2, type::direction);
    return {dir1, dir2};
  }

  double eccentricity() const {
    double c = (f1 - f2).len() / 2;
    return c / semi_major_axis;
  }

  double getSemiMajorAxis() const {
    return semi_major_axis;
  }

  Point center() const {
    Point cnt = (f1 + f2) / 2;
    return cnt;
  }

public:
  double perimeter() const override {
    double c = (f1 - f2).len() / 2;
    double b = sqrt(semi_major_axis * semi_major_axis - c * c);
    return math::pi * (3 * (semi_major_axis + b) - sqrtl((3 * semi_major_axis + b) * (semi_major_axis + 3 * b)));
  }

  double area() const override {
    double c = (f1 - f2).len() / 2;
    double b = sqrt(semi_major_axis * semi_major_axis - c * c);
    return math::pi * semi_major_axis * b;
  }

  bool operator==(const Shape& other) const override {
    const Ellipse *other_ell = dynamic_cast<const Ellipse *>(&other);
    if (other_ell == nullptr)
      return false;
    std::pair<Point, Point> focuses = other_ell->focuses();
    if (f1 == focuses.first && f2 == focuses.second &&
        math::isEqual(semi_major_axis, other_ell->getSemiMajorAxis())) {
      return true;
    }
    return false;
  }

  bool operator!=(const Shape& other) const override {
    return !operator==(other);
  }

  bool isCongruentTo(const Shape& other) const override {
    const Ellipse *other_ell = dynamic_cast<const Ellipse *>(&other);
    if (other_ell == nullptr)
      return false;
    std::pair<Point, Point> focuses = other_ell->focuses();

    if (math::isEqual((f1 - f2).len(), (focuses.first - focuses.second).len()),
        math::isEqual(semi_major_axis, other_ell->getSemiMajorAxis())) {
      return true;
    }
    return false;
  }

  bool isSimilarTo(const Shape& other) const override {
    const Ellipse *other_ell = dynamic_cast<const Ellipse *>(&other);
    if (other_ell == nullptr)
      return false;
    if (math::isEqual(eccentricity(), other_ell->eccentricity())) {
      return true;
    }
    return false;
  }

  bool containsPoint(const Point& inpoint) const override {
    double dist = (inpoint - f1).len() + (inpoint - f2).len();
    if (dist < 2 * semi_major_axis || math::isEqual(dist, 2 * semi_major_axis))
      return true;
    return false;
  }

  void rotate(const Point& center, double angle) override {
    f1.rotate(center, angle);
    f2.rotate(center, angle);
  }

  void reflect(const Point& center) override {
    f1.reflect(center);
    f2.reflect(center);
  }

  void reflect(const Line& axis) override {
    f1.reflect(axis);
    f2.reflect(axis);
  }

  void scale(const Point& center, double coefficient) override {
    semi_major_axis *= coefficient;
    f1.scale(center, coefficient);
    f2.scale(center, coefficient);
  }
};

class Circle : public Ellipse {
public:
  Circle(const Point &new_c, double newr) : Ellipse(new_c, new_c, 2 * newr) {}

  double perimeter() const override {
    return 2 * math::pi * getSemiMajorAxis();
  }

  double radius() const { return getSemiMajorAxis(); }
};

class Rectangle : public Polygon {
public:
  Rectangle(const Point& p1, const Point& p2, double ratio) : Polygon(4) {
    if (ratio < 1)
      ratio = 1 / ratio;
    points[0] = p1;
    points[2] = p2;
    double angle1 = atan(ratio);
    Point side1 = p2 - p1;
    Point side1_normal = side1.normalized();

    side1_normal = side1_normal.rotate(angle1);
    side1_normal *= (cos(angle1) * side1.len());
    points[1] = p1 + side1_normal;
    Point side2 = points[2] - points[1];
    points[3] = p1 + side2;
  }

  std::pair<Line, Line> diagonals() {
    return {Line(points[0], points[2]), Line(points[1], points[3])};
  }

  Point center() {
    return (points[0] + points[2]) / 2;
  }
};

class Square : public Rectangle {
public:
  Square(const Point& p1, const Point& p2) : Rectangle(p1, p2, 1) {}

  Circle circumscribedCircle() {
    return Circle((points[0] + points[2]) / 2, getSideLen(0) / 2);
  }

  Circle inscribedCircle() {
    Point diag = points[0] - points[2];
    return Circle((points[0] + points[2]) / 2, diag.len() / 2);
  }
};

class Triangle : public Polygon {
public:
  Triangle(const Point& p1, const Point& p2, const Point& p3) : Polygon(p1, p2, p3) {}

  Circle inscribedCircle() const {
    Point side1 = getSide(0);
    Point side2 = getSide(1);
    Point side3 = getSide(2);
    double rad = area() / (side1.len() + side2.len() + side3.len()) * 2;
    Line l1(points[0], points[1]);
    Line l2(points[1], points[2]);
    l1.normalilizeNormal();
    l2.normalilizeNormal();
    l1.getC() -= rad;
    l2.getC() -= rad;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        Point res = l1.intersect(l2);
        if (containsPoint(res)) {
          return Circle(res, rad);
        }
        l2.getC() += 2 * rad;
      }
      l1.getC() += 2 * rad;
      l2.getC() -= 4 * rad;
    }
    return Circle(Point(0, 0), 0);
  }

  Circle circumscribedCircle() const {
    Point side1 = getSide(0);
    Point side2 = getSide(1);
    Point side3 = getSide(2);
    double rad = side1.len() * side2.len() * side3.len() / (4 * area());
    Point p2 = points[0] + side2 / 2;
    Point p3 = points[1] + side3 / 2;
    Line l1(side2, p2, type::normal);
    Line l2(side3, p3, type::normal);
    return Circle(l1.intersect(l2), rad);
  }

  Point orthocenter() const {
    Point side2 = getSide(1);
    Point side3 = getSide(2);
    Point p1 = points[2];
    Point p2 = points[0];
    Line l1(side2, p1, type::normal);
    Line l2(side3, p2, type::normal);
    return l1.intersect(l2);
  }

  Point centroid() const {
    Point side2 = getSide(1);
    Point side3 = getSide(2);
    Point p11 = points[2];
    Point p21 = points[0];
    Point p12 = points[0] + side2 / 2;
    Point p22 = points[1] + side3 / 2;
    Line l1(p11, p12);
    Line l2(p21, p22);
    return l1.intersect(l2);
  }

  Line EulerLine() const {
    Point orthoc = orthocenter();
    Point centroid = circumscribedCircle().center();

    return Line(orthoc, centroid);
  }

  Circle ninePointsCircle() const {
    return Triangle((points[0] + points[1]) / 2, (points[1] + points[2]) / 2,
                    (points[2] + points[0]) / 2).circumscribedCircle();
  }
};

std::ostream& operator<<(std::ostream& out, const Point& p) {
  cout << p.x << " " << p.y;
  return out;
}
