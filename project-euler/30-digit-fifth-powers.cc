#include <iostream>

void SolveBruteForce() {
  // the key is find the upper bound
  // 9^5=59049, 5 digits, 99999 produces 59049*5=295245, which is 6 digits, 999999 6*59049=354294
  // Looks like we can try 354294 as upper bound
  
  int result = 0;
  for (int i = 2; i < 354294; ++i) {
    int sum = 0, number = i, last;
    while (number > 0) {
      last = number % 10;
      number /= 10;
      sum += (last * last * last * last * last);
    }

    if (sum == i) result += i;
  }

  std::cout << result << std::endl;
}

int main() {
  SolveBruteForce();
  return 0;
}
