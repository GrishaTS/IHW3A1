#include <iostream>
#include <vector>
#include <random>
#include <cmath>

class Circle {
public:
  long double x, y, r;
  Circle() : x(0), y(0), r(0) {}
  Circle(const long double x, const long double y, const long double r) : x(x), y(y), r(r) {}

  [[nodiscard]] bool is_point_inside_circle(const long double p_x, const long double p_y) const {
    return (p_x - this->x) * (p_x - this->x) + (p_y - this->y) * (p_y - this->y) <= this->r * this->r;
  }
};

int main() {
  std::vector<Circle> circles (3);

  for (int i = 0; i < 3; i++) {
    std::cin >> circles[i].x >> circles[i].y >> circles[i].r;
  }
  long double x_max = std::max(std::max(circles[0].x + circles[0].r, circles[1].x + circles[1].r), circles[2].x + circles[2].r);
  long double x_min = std::min(std::min(circles[0].x - circles[0].r, circles[1].x - circles[1].r), circles[2].x - circles[2].r);
  long double y_max = std::max(std::max(circles[0].y + circles[0].r, circles[1].y + circles[1].r), circles[2].y + circles[2].r);
  long double y_min = std::min(std::min(circles[0].y - circles[0].r, circles[1].y - circles[1].r), circles[2].y - circles[2].r);
  std::random_device random_dev;
  std::mt19937 generator(random_dev());
  std::uniform_real_distribution<long double> random_x(x_min, x_max);
  std::uniform_real_distribution<long double> random_y(y_min, y_max);
  int m = 0;
  int n = 1000000;
  for (size_t iteration = 0; iteration < n; ++iteration) {
    const long double x = random_x(generator);
    const long double y = random_y(generator);
    bool flag = true;
    for (auto circle: circles) {
      flag = flag && circle.is_point_inside_circle(x, y);
    }
    if (flag) m++;
  }
  std::cout << (m * (x_max - x_min) * (y_max - y_min)) / n;
}