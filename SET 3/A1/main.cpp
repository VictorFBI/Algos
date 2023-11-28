#include <iostream>
#include <fstream>
#include <random>

std::ofstream fout_abs(R"(C:\Users\frolo\CLionProjects\assemblyTestProgram\abs_coordinates.txt)");
std::ofstream fout_rel(R"(C:\Users\frolo\CLionProjects\assemblyTestProgram\rel_coordinates.txt)");

std::pair<double, double> get_random_point(std::uniform_real_distribution<double> &unif,
                                           std::default_random_engine &re) {
  return std::make_pair(unif(re), unif(re));
}

double approximate_pi(int n) {
  double m = 0;
  std::uniform_real_distribution<double> unif(-1, 1);
  std::default_random_engine re; // NOLINT
  for (auto i = 0; i < n; ++i) {
    auto point = get_random_point(unif, re);
    auto x = point.first;
    auto y = point.second;
    if (x * x + y * y <= 1) m += 1;
  }

  auto app_pi = (4 * m) / n;
  fout_abs << "(" << n << ", " << app_pi << ") ";
  fout_rel << "(" << n << ", " << (std::abs(app_pi - M_PI) * 100 / M_PI) << ") ";

  return app_pi;
}

int main() {

  for (auto i = 100; i <= 5000; i += 100) {
    std::cout << "N = " << i << ": " << approximate_pi(i) << '\n';
  }

  return 0;
}
