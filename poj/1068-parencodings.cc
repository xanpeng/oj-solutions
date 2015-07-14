#include <cstdio>
#include <string>
#include <iterator>
#include <stack>
using namespace std;

void ConvertToWseqAndPrint(int p_count[], int n) {
    string parenthese;
    int prev_left_count = 0;
    for (int i = 0; i < n; ++i) {
        int left_count = p_count[i] - prev_left_count;
        while (left_count--)
            parenthese.push_back('(');
        parenthese.push_back(')');
        prev_left_count = p_count[i];
    }

    int prev_right_count = 0;
    stack<char> paren_stack;
    for (string::iterator it = parenthese.begin(); it != parenthese.end(); ++it) {
        // cann't generate w-sequence with O(n)?
    }
}

int main() {
    int case_count, n;
    const int kSize = 20;
    int p_count[kSize];
    
    scanf("%d", &case_count); 
    while (case_count--) {
        scanf("%d", &n);
        for (int i = 0 ; i < n; ++i)
            scanf("%d", &p_count[i]);


        ConvertToWseqAndPrint(p_count, n);
    }

    return 0;
}
