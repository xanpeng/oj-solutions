#include <iostream>

void Solve(int width) {
  int diagonals_sum = 1, step = 0, i = 1;
  while (i < width * width) {  // < O(n)
    step += 2;
    for (int cycle = 4; cycle > 0; --cycle) {
      i += step;  // i should be less than width*width
      diagonals_sum += i;
    }
  }
  std::cout << diagonals_sum << std::endl;
}

int main() {
  Solve(1001);
  return 0;
}
