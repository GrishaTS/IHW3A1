#include <iostream>
#include <fstream>
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


long double intersection_area(const int n, long double scale = 1.0) {
  std::vector<Circle> circles (3);
  circles[0].x = 1; circles[0].y = 1; circles[0].r = 1;
  circles[1].x = 1.5; circles[1].y = 2; circles[1].r = sqrt(5) / 2;
  circles[2].x = 2; circles[2].y = 1.5; circles[2].r = sqrt(5) / 2;
  long double x_max = std::max(std::max(circles[0].x + circles[0].r, circles[1].x + circles[1].r), circles[2].x + circles[2].r);
  long double x_min = std::min(std::min(circles[0].x - circles[0].r, circles[1].x - circles[1].r), circles[2].x - circles[2].r);
  long double y_max = std::max(std::max(circles[0].y + circles[0].r, circles[1].y + circles[1].r), circles[2].y + circles[2].r);
  long double y_min = std::min(std::min(circles[0].y - circles[0].r, circles[1].y - circles[1].r), circles[2].y - circles[2].r);
  std::random_device random_dev;
  std::mt19937 generator(random_dev());
  std::uniform_real_distribution<long double> random_x(x_min * scale, x_max * scale);
  std::uniform_real_distribution<long double> random_y(y_min * scale, y_max * scale);
  int m = 0;
  for (size_t iteration = 0; iteration < n; ++iteration) {
    const long double x = random_x(generator);
    const long double y = random_y(generator);
    bool flag = true;
    for (auto circle: circles)
      flag = flag && circle.is_point_inside_circle(x, y);
    if (flag)
      m++;
  }
  return (m * (x_max - x_min) * (y_max - y_min)) / n;
}

int main() {
  long double y_true = M_PI/4 + 5*asin(0.8)/4 - 1;
  std::ofstream csv("n_perfomance.csv");
  csv << "n;area;diff\n";
  for(size_t n = 100; n < 100000; n += 500){
    long double area = intersection_area(n);
    csv<<n<<';'<<area<<';'<<std::abs(area - y_true)<<'\n';
  }
  csv = std::ofstream("scale_perfomance.csv");
  csv << "scale;area;diff\n";
  for(long double scale = 1; scale < 10; scale+=0.1){
    long double area = intersection_area(1000000, scale);
    csv<<scale<<';'<<area<<';'<<std::abs(area - y_true)<<'\n';
  }
}