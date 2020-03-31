#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

struct Point3D {
  double x, y, z;
};

std::istream &operator>>(std::istream &is, Point3D &p) {
  return is >> p.x >> p.y >> p.z;
}

std::ostream &operator<<(std::ostream &os, const Point3D &p) {
  return os << p.x << " " << p.y << " " << p.z;
}

inline double sqr(double a) { return a * a; }

double distance2(const Point3D &a, const Point3D &b) {
  return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z);
}

// on string_view process is more efficient but not compatible with istringstream
std::string trim(const std::string &str) {
  size_t first = str.find_first_not_of(" \n\t\r");
  if (std::string::npos == first) {
    return str;
  }
  size_t last = str.find_last_not_of(" \n\t\r");
  return str.substr(first, (last - first + 1));
}

Point3D compute_barycentre(std::vector<Point3D> const &points) {
  assert(!points.empty());
  auto that = std::accumulate(begin(points), end(points), Point3D{},
                              [](const Point3D &a, const Point3D &b) {
                                return Point3D{a.x + b.x, a.y + b.y, a.z + b.z};
                              });
  const size_t n = points.size();
  return Point3D{that.x / n, that.y / n, that.z / n};
}

Point3D find_closest(const std::vector<Point3D> &points, const Point3D &ref) {

  return *std::min_element(begin(points), end(points),
                           [&ref](const Point3D &a, const Point3D &b) {
                             return distance2(a, ref) < distance2(b, ref);
                           });
}

int main() {
  // std::ifstream f("file.txt");

  // demo without external file; use embedded data
  std::string data = R""(
 1  1  1
 1 -1  2
 1  2  3
 2  3  5
 1  2 -1
-1  0  2 
)"";
  data = trim(data);

  std::istringstream f(data);

  std::vector<Point3D> points;
  for (std::string line; std::getline(f, line);) {
    std::istringstream iss(line);
    Point3D p{};
    iss >> p;
    points.push_back(p);
    assert(!iss.fail() && iss.eof());
    std::cout << "> " << p << '\n';
  }

  const Point3D barycentre = compute_barycentre(points);
  std::cout << "Cloud barycentre: " << barycentre << '\n';
  const Point3D center = find_closest(points, barycentre);
  std::cout << "Closest point: " << center << '\n';
}