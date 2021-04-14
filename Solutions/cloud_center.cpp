#include <algorithm>
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <sstream>
#include <vector>

struct Point3D {
  double x, y, z;
};

std::istream &operator>>(std::istream &is, Point3D &p) {
  return is >> p.x >> p.y >> p.z;
}

std::ostream &operator<<(std::ostream &os, const Point3D &p) {
  return os << "{" << p.x << ", " << p.y << ", " << p.z << "}";
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
  std::vector<Point3D> points;

  const bool do_random = false;

  if (do_random) {
    // Add random points
    std::random_device random_device;
    std::default_random_engine eng{random_device()};
    std::uniform_real_distribution<> dist{-5, 5};
    points.resize(10000);
    std::generate(points.begin(), points.end(), [&dist, &eng] {
      return Point3D{dist(eng), dist(eng), dist(eng)};
    });
  } else {
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
    
    std::cout << "Cloud:"
              << "\n";
    for (std::string line; std::getline(f, line);) {
      std::istringstream iss(line);
      Point3D p{};
      iss >> p;
      points.push_back(p);
      assert(!iss.fail() && iss.eof());
      std::cout << "> " << p << '\n';
    }
  }

  const Point3D barycentre = compute_barycentre(points);
  std::cout << "Cloud barycentre: " << barycentre << '\n';
  const Point3D center = find_closest(points, barycentre);
  std::cout << "Closest point: " << center << '\n';

  //// using std::set
  {
    auto start = std::chrono::steady_clock::now();

    class Point3DComparator {
    public:
      explicit Point3DComparator(Point3D center) : m_center(center) {}
      bool operator()(const Point3D &a, const Point3D &b) const {
        const auto da = distance2(a, m_center);
        const auto db = distance2(b, m_center);
        if (da != db)
          return da < db;
        else              // TODO what if da < db only ?
          return &a > &b; // arbitrary discriminator. Do you have a better idea ?
      }

    private:
      const Point3D m_center;
    };

    Point3DComparator comparator(center);
    std::set<Point3D, Point3DComparator> ordered_point_set(comparator);
    std::copy(std::begin(points), std::end(points),
              std::inserter(ordered_point_set, ordered_point_set.end()));

    auto end = std::chrono::steady_clock::now();
    int elapsed_us =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Point list using std::set (" << elapsed_us << "_us):\n";
    if (ordered_point_set.size() < 20) {
      std::copy(ordered_point_set.begin(), ordered_point_set.end(),
                std::ostream_iterator<Point3D>(std::cout, "\n"));
    }
  }

  //// using std::multimap // TODO what if only std::map ??
  {
    auto start = std::chrono::steady_clock::now();
    std::multimap<double, Point3D> ordered_point_map;
    std::transform(
        points.begin(), points.end(),
        std::inserter(ordered_point_map, ordered_point_map.end()),
        [center](const Point3D &p) -> decltype(ordered_point_map)::value_type {
          return {distance2(p, center), p};
        });
    auto end = std::chrono::steady_clock::now();
    int elapsed_us =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Point list using std::map (" << elapsed_us << "_us):\n";
    if (ordered_point_map.size() < 20) {
      for (auto &&[k, v] : ordered_point_map) { // structured binding of C++17
        std::cout << k << " -> " << v << "\n";
      }
    }
  }

  //// using vector data structure (will change points object)
  {
    auto start = std::chrono::steady_clock::now();
    std::sort(points.begin(), points.end(),
              [center](const Point3D &a, const Point3D &b) {
                return distance2(a, center) < distance2(b, center);
              });
    auto end = std::chrono::steady_clock::now();
    int elapsed_us =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Point list using std::vector (" << elapsed_us << "_us):\n";
    if (points.size() < 20) {
      std::copy(points.begin(), points.end(),
                std::ostream_iterator<Point3D>(std::cout, "\n"));
    }
  }
}