// http://blog.csdn.net/caopengcs/article/details/37657173
#include <string>
#include <vector>
#include <stack>
#include <cstdio>

using namespace std;

char s[1024], answer[30];

int main() {
  int z;
  for (scanf("%d", &z); z; --z) {
    scanf("%s", s);
    stack<int> st;
    vector<int> num(26, 0);

    for (int i = 0; s[i]; ++i)
      ++num[s[i] - 'a'];

    vector<bool> have(26, false);
    for (int i = 0; s[i]; ++i) {
      int c = s[i] - 'a';
      --num[c];

      if (have[c])
        continue;

      for (;
          (!st.empty()) && num[st.top()] && (st.top() > c);
          have[st.top()] = false, st.pop());
      st.push(c);
      have[c] = true;
    }
    
    answer[st.size()] = 0;
    for (int i = st.size(); !st.empty(); answer[--i] = st.top() + 'a', st.pop())
      ;
    puts(answer);
  }

  return 0;
}
