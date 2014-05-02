#include <iostream>

void Solve() {
  int target = 200;
  int coins[] = { 1, 2, 5, 10, 20, 50, 100, 200 };
  int ways[target+1] = { 0 };
  ways[0] = 1;

  for (int i = 0; i < sizeof(coins) / sizeof(int); ++i) {
    for (int j = coins[i]; j <= target; ++j) {
      ways[j] += ways[j - coins[i]];
    }
  }

  std::cout << ways[target] << std::endl;
}

int main() {
  Solve();
  return 0;
}
