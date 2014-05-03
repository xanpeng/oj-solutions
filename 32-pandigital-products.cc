#include <iostream>
#include <iterator>
#include <unordered_set>
#include <numeric>
 
bool IsPandigital(int a, int b=0, int c=0) {
  int digit_count[10] = { 0 };
  while (a > 0) {
    ++digit_count[a%10];
    a /= 10;
  }
  while (b > 0) {
    ++digit_count[b%10];
    b /= 10;
  }
  int orig_c = c;
  while (c > 0) {
    ++digit_count[c%10];
    c /= 10;
  }

  if (digit_count[0] > 0) return false;
  for (int count : digit_count)
    if (count >= 2) return false;

  if (orig_c == 0) return true;
  for (int i = 1; i <= 9; ++i)
    if (digit_count[i] != 1) return false;
  return true;
}

void Solve() {
  std::unordered_set<int> products;
  for (int multiplicand = 2; multiplicand <= 98; ++multiplicand) {
    if (IsPandigital(multiplicand) == false) continue;

    for (int multiplier = multiplicand + 1; multiplier <= 9876; ++multiplier) {
      if (IsPandigital(multiplicand, multiplier) == false) continue;

      int product = multiplicand * multiplier;
      if (IsPandigital(multiplicand, multiplier, product) == false) continue;

      std::unordered_set<int>::const_iterator got = products.find(product);
      if (got != products.end()) continue;

      products.insert(product);
    }
  }

  std::copy(products.begin(), products.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::accumulate(products.begin(), products.end(), 0) << std::endl;
}

int main() {
  Solve();
  // std::cout << IsPandigital(332748) << std::endl;
  return 0;
}
