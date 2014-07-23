#include <iostream>
#include <string>

std::string DecimalToBinary(int number) {
  if (number == 0) return "0";
  if (number == 1) return "1";

  if (number % 2 == 0)
    return DecimalToBinary(number / 2) + "0";
  else
    return DecimalToBinary(number / 2) + "1";
}

bool IsPalindrome(std::string text) {
  int forward = 0, backward = text.length() - 1;
  for (; forward < backward; ++forward, --backward) {
    if (text.at(forward) != text.at(backward)) break;
  }
  if (forward < backward) return false;
  return true;
}

void Solve() {
  int palindrome_sum = 0;
  for (int i = 1; i < 1000000; ++i) {
    if (IsPalindrome(std::to_string(i)) == false) continue;
    if (IsPalindrome(DecimalToBinary(i)) == false) continue;
    palindrome_sum += i;
  }
  std::cout << palindrome_sum << std::endl;
}

int main() {
  Solve();
  return 0;
}
