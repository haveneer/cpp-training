#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>
#include <ctime>

int main() {
  std::chrono::time_point tp = std::chrono::system_clock::now();
  std::time_t tt = std::chrono::system_clock::to_time_t(tp);
  std::cout << "Running at " << std::ctime(&tt) << "\n";

  std::vector<int> v(1000, 3);
  auto start = std::chrono::system_clock::now();
  auto sum = std::accumulate(v.begin(), v.end(), 0);
  auto end = std::chrono::system_clock::now();
  int elapsed_seconds =
      std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
  
  std::cout << "sum = " << sum << ", elapsed time = " << elapsed_seconds
            << std::endl;
  return 0;
}