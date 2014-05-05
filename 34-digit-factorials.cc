#include <iostream>

int Factorial(int digit) {
  if (digit == 0) return 1;
  int result = digit;
  for (int i = 1; i < digit; ++i)
    result *= i;
  return result;
}

void Solve() {
  int result = 0;
  // upper bound is 7*9! = 2540160, since 8*9! only has 7 digits
  for (int i = 10; i < 2540160; ++i) {
    int digits = i, sum = 0;
    while (digits > 0) {
      sum += Factorial(digits % 10);
      digits /= 10;
    }
    if (sum == i) result += i;
  }

  std::cout << result << std::endl;
}

int main() {
  Solve();
  return 0;
}
