//
// Idea: simulate division process.
//
#include <iostream>
#include <unordered_map>

void solve() {
  std::unordered_map<int, int> remainder_history_hash;
  int max_len = 0, d = 7; 

  for (int i = 1000; i > 1; --i) {
    int remainder = 1, remainders_size = 0;
    remainder_history_hash.clear();

    while (1) {
      remainder = (remainder * 10) % i;
      if (remainder == 0) break;

      std::unordered_map<int, int>::const_iterator search = remainder_history_hash.find(remainder);
      if (search == remainder_history_hash.end()) {
        remainder_history_hash.insert({remainder, remainders_size});
        remainders_size++;
        continue;
      }

      int curr_size = remainders_size - search->second;
      if (curr_size > max_len) {
        max_len = curr_size;
        d = i;
      }
      break;
    }
  }

  std::cout << "cycle length: " << max_len << ", d: " << d << std::endl;
}

int main() {
  solve();
  return 0;
}
