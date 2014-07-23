#include <iostream>
#include <vector>

int gcd(int a, int b) {
  while (b != 0) {
    int r = b;
    b = a % b;
    a = r;
  }
  return a;
}

void Solve() {
  std::vector<int> denominators;
  std::vector<int> numerators;
  for (int numerator = 12; numerator < 99; ++numerator) {
    if ((numerator % 10 == numerator / 10) || (numerator % 10 == 0)) continue;

    for (int denominator = numerator + 1; denominator < 99; ++denominator) {
      if ((denominator % 10 == denominator / 10) || (denominator % 10 == 0)) continue;
      if ((numerator % 10 != denominator % 10) && (numerator % 10 != denominator / 10)
          && (numerator / 10 != denominator % 10) && (numerator / 10 != denominator % 10)) continue;

      int numerator_new, denominator_new;
      if (numerator % 10 == denominator % 10) { numerator_new = numerator / 10; denominator_new = denominator / 10; }
      if (numerator % 10 == denominator / 10) { numerator_new = numerator / 10; denominator_new = denominator % 10; }
      if (numerator / 10 == denominator % 10) { numerator_new = numerator % 10; denominator_new = denominator / 10; }
      if (numerator / 10 == denominator / 10) { numerator_new = numerator % 10; denominator_new = denominator % 10; }

      int gcd_big = gcd(denominator, numerator);
      int gcd_small = gcd(denominator_new, numerator_new);
      if ((denominator / gcd_big == denominator_new / gcd_small)
          && (numerator / gcd_big == numerator_new / gcd_small)) {
        numerators.push_back(numerator_new / gcd_small);
        denominators.push_back(denominator_new / gcd_small);
      }
    }
  }

  int numerator_multiplied = 1, denominator_multiplied = 1;
  for (int numerator : numerators) numerator_multiplied *= numerator;
  for (int denominator : denominators) denominator_multiplied *= denominator; 
  std::cout << denominator_multiplied / gcd(denominator_multiplied, numerator_multiplied) << std::endl;
}

int main() {
  Solve();
  return 0;
}
